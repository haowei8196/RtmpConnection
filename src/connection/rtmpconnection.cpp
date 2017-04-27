//
//  RtmpConnection.m
//  AVSession
//
//  Created by whw on 2016/11/1.
//  Copyright © 2016年 meixin. All rights reserved.
//

#include "rtmpconnection.h"
#include <assert.h>
#include "../base/utils.h"
#define CHUNKSIZE 4096
#define BASEBW 380.f*1024.f/8.f
#define BWDURING  3000

#define IFRAMESHOLDDROP 1000
#define BFRAMESHOLDDROP 600

RtmpConnection::RtmpConnection(ConnectionType type, ConnectionHandle * callback, uint64_t uid, std::string& uri)
{
	_callback = callback;
	_uid = uid;
	_type = type;
	_uri = uri;

	_enableAudio = false;
	_enableVideo = false;

	_minFrameDropTs = 0;
	_lastBFrameDropTs = 0;
	total_byte_count_ = 0.0f;
	begin_stat_bw_time_ = 0;
	total_idle_time_ = 0;
	last_begin_idle_time_ = 0;
	last_stat_bw_ = 0;
	measure_stat_bw_ = 0;

	_rtmp = RTMP_Alloc();
	_running = true;
	Start();
}

RtmpConnection::~RtmpConnection()
{
	_running = false;
	_rtmp_status = RTMP_Closed;
	Thread::SleepMs(100);

	if (_rtmp)
	{
		RTMP_Close(_rtmp);
		RTMP_Free(_rtmp);
		_rtmp = 0;
		_streamid = -1;
	}
	Stop();
	if (_type != Connection_Up)
		return;
	for (int i = NO_MEDIA; i < NumOfMedia; ++i)
	{
		CAutoLock lock(&_mutex[i]);
		for (std::list<RTMPPacket>::iterator it = _mediaData[i].begin(); it != _mediaData[i].end(); it++)
		{
			RTMPPacket pPacket = *it;
			RTMPPacket_Free(&pPacket);
		}
		_mediaData[i].clear();
	}
}

void RtmpConnection::enableAudio(bool flag)
{
	if (_enableAudio == flag)
		return;
	_enableAudio = flag;
	if (_rtmp && _running && _rtmp_status == RTMP_Connected)
	{
		RTMP_SendReceiveAudio(_rtmp, flag);
	}
}

bool RtmpConnection::enableAudio()
{
	return _enableAudio;
}

void RtmpConnection::enableVideo(bool flag)
{
	if (_enableAudio == flag)
		return;
	_enableVideo = flag;
	if (_rtmp && _running && _rtmp_status == RTMP_Connected)
	{
		RTMP_SendReceiveVideo(_rtmp, flag);
	}
}

bool RtmpConnection::enableVideo()
{
	return _enableVideo;
}

void RtmpConnection::sendFrame(MediaFrame & frame)
{
	if (_rtmp_status!= RTMP_Connected || !frame.data)
		return;

	if (_enableVideo && _iFrameRequired)
	{
		if (frame.data[0] != 0x17)
			return;
		_iFrameRequired = FALSE;
	}

	long interval = 0;
	if (!_starttime)
	{
		_starttime = frame.ts;
	}
	else
	{
		interval = frame.ts - _starttime;
	}

	if (!_running)
		return;

	if (frame.type != VIDEO_MEDIA && frame.type == AUDIO_MEDIA)
		return;

	CAutoLock lock(&_mutex[frame.type]);

	if (frame.type == VIDEO_MEDIA)
		processPackets();

	RTMPPacket pPacket;
	RTMPPacket_Alloc(&pPacket, frame.len);
	memcpy(pPacket.m_body, frame.data, frame.len);
	pPacket.m_packetType = frame.type == VIDEO_MEDIA?0x09:0x08;
	pPacket.m_nBodySize = frame.len;
	pPacket.m_nTimeStamp = (uint32_t)(interval);
	pPacket.m_nChannel = 4;
	pPacket.m_headerType = RTMP_PACKET_SIZE_LARGE;
	pPacket.m_nInfoField2 = _streamid;
	_mediaData[frame.type].push_back(pPacket);
}
void RtmpConnection::setChunkSize(int nVal)
{
	if (!_rtmp)
		return;

	RTMPPacket pack;
	RTMPPacket_Alloc(&pack, 4);

	pack.m_packetType = 0x01;
	pack.m_nChannel = 0x02;
	pack.m_headerType = RTMP_PACKET_SIZE_LARGE;
	pack.m_nTimeStamp = 0;
	pack.m_nInfoField2 = 0;
	pack.m_nBodySize = 4;

	pack.m_body[3] = nVal & 0xff; //大字节序
	pack.m_body[2] = nVal >> 8;
	pack.m_body[1] = nVal >> 16;
	pack.m_body[0] = nVal >> 24;

	_rtmp->m_outChunkSize = nVal;

	//we send packet 1024 bytes
	RTMP_SendPacket(_rtmp, &pack, 1);
	RTMPPacket_Free(&pack);
}
int RtmpConnection::connectRtmp()
{
	RTMP_Init(_rtmp);
		
	int ret = RTMP_SetupURL(_rtmp, (char*)_uri.c_str());
	if (!ret)
	{
		_callback->onConnectionStatus(_uid, Connection_Fail);
		return -1;
	}
	if (_type == Connection_Up)
		RTMP_EnableWrite(_rtmp);

	ret = RTMP_Connect(_rtmp, NULL);
	if (ret <= 0)
	{
		_callback->onConnectionStatus(_uid, Connection_Fail);
		return -1;
	}
	if (_type == Connection_Up)
	{	
		setChunkSize(CHUNKSIZE);
	}
	ret = RTMP_ConnectStream(_rtmp, 0);
	if (ret <= 0)
	{
		_callback->onConnectionStatus(_uid, Stream_Fail);
		return -1;
	}

	if (_enableAudio)
	{
		RTMP_SendReceiveAudio(_rtmp, _enableAudio);
	}

	if (_enableVideo)
	{
		RTMP_SendReceiveVideo(_rtmp, _enableVideo);
	}

	_rtmp_status = RTMP_Connected;
	_iFrameRequired = true;

	_starttime = 0;
	_sleepms = 1;
	_streamid = _rtmp->m_stream_id;

	_callback->onConnectionStatus(_uid, Connection_Succuss);

	return 0;
}
void RtmpConnection::closeRtmp()
{
	if (_rtmp)
	{
		RTMP_Free(_rtmp);
		_rtmp = 0;
		_streamid = -1;
	}
	_rtmp = RTMP_Alloc();
	_rtmp_status = RTMP_Inited;
}
void RtmpConnection::Run()
{
	while (_running)
	{
		{
			ProcessMessages(10);
		}

		if (_rtmp != 0)
		{
			switch (_rtmp_status)
			{
			case RTMP_Inited:
			{
				if (connectRtmp() != 0)
				{
					closeRtmp();
				}
				break;
			}
			case RTMP_Connected:
			{
				//send packet
				int ret = 0;
				if (_type == Connection_Up)
				{
					ret = handle_output();
				}
				else if (_type == Connection_Down)
				{
					ret = handle_input();
				}
				else
				{
					//AVLogError(@"err connection type");
				}
				if (ret != 0&&_running)
				{
					if (_callback)
						_callback->onConnectionStatus(_uid, Connection_Exception);
					closeRtmp();
				}
				break;
			}
			default:
				break;
			}
		}
	}
}
int RtmpConnection::handle_input()
{
	RTMPPacket packet = { 0 };
	int read = RTMP_GetNextMediaPacket(_rtmp, &packet);
	if (read <= 0 || read == 2)
	{
		//AVLogError(@"RTMP_GetNextMediaPacket %d" ,read);
		//read <= 0 : Error occur
		//read == 2 : Got Play.Complete or Play.Stop from server.
		return -1;
	}

	uint8_t *packetBody = (uint8_t *)packet.m_body;
	unsigned int nPacketLen = packet.m_nBodySize;

	if (_callback && _running)
	{
		if (packet.m_packetType == 0x09 && nPacketLen > 5)
		{
			_callback->onReceiveFrame(_uid, { packetBody ,(int)nPacketLen ,(long)packet.m_nTimeStamp ,VIDEO_MEDIA });
		}
		else if (packet.m_packetType == 0x08 && nPacketLen > 12) //带rtp头
		{
			_callback->onReceiveFrame(_uid, { packetBody ,(int)nPacketLen ,(long)packet.m_nTimeStamp ,AUDIO_MEDIA });
		}
	}
	stat_bytes(packet.m_nBodySize);
	RTMPPacket_Free(&packet);
	return 0;
}
int RtmpConnection::handle_output()
{
	for (int i = NO_MEDIA; i < NumOfMedia && _running; ++i)
	{
		RTMPPacket pPacket = { 0 };
		{
            CAutoLock lock(&_mutex[i]);
			if (_mediaData[i].size()>0)
			{
				pPacket = _mediaData[i].front();
				_mediaData[i].pop_front();
			}
		}
		if (pPacket.m_packetType == 0)
			continue;

		int64_t begin = session::TimeMillis();

		if (!RTMP_SendPacket(_rtmp, &pPacket, 0))
		{
			if (pPacket.m_body[0] != 0x27)
			{
				CAutoLock lock(&_mutex[NO_MEDIA]);
				_mediaData[NO_MEDIA].push_back(pPacket);
			}
			return -1;
		}

		stat_bytes(pPacket.m_nBodySize);
		RTMPPacket_Free(&pPacket);

		int64_t end = session::TimeMillis();
		int time = (int)(end - begin);
		if (time > 30)
		{
			//AVLogWarn(@"send packet so long....");
			if (_callback)
				_callback->onWarning(Warning_BindwidthSent_Bad);
		}
	}
	return 0;
}
void RtmpConnection::stat_bytes(int nlen)
{
	long now = (long)session::TimeMillis();

	if (0 == begin_stat_bw_time_ \
		|| now - begin_stat_bw_time_ > 5000 \
		|| now < begin_stat_bw_time_)
	{
		begin_stat_bw_time_ = now;
		total_byte_count_ = (float)nlen;
		last_begin_idle_time_ = 0;
		return;
	}
	total_byte_count_ += nlen;

	//三秒统计一次
	float fStatTimeSpan = (float)(now - begin_stat_bw_time_);
	if (fStatTimeSpan < BWDURING)
		return;

	if (0 != last_begin_idle_time_)
	{
		assert(last_begin_idle_time_ >= begin_stat_bw_time_ && begin_stat_bw_time_ <= now);
		total_idle_time_ += now - last_begin_idle_time_;
		last_begin_idle_time_ = 0;
	}
	float fRealSpan = fStatTimeSpan - static_cast<float>(total_idle_time_);
	float fLastBW = last_stat_bw_;
	if (0.0f != fRealSpan)
		last_stat_bw_ = total_byte_count_ / fRealSpan * 1000;//ms->s


	if (last_stat_bw_ <= 0.0f)
		last_stat_bw_ = measure_stat_bw_;
	if (BASEBW == measure_stat_bw_)
		measure_stat_bw_ = last_stat_bw_;
	else
		measure_stat_bw_ = (fLastBW + last_stat_bw_) / 2.0f;

	measure_stat_bw_ = last_stat_bw_;

	if (_callback)
	{
		_callback->onBandwidth(_uid, measure_stat_bw_ * 8 / 1024);
	}

	begin_stat_bw_time_ = now;
	total_byte_count_ = 0;
	total_idle_time_ = 0;
}
void RtmpConnection::processPackets()
{
	std::list<RTMPPacket>& packQueue = _mediaData[VIDEO_MEDIA];
	if (packQueue.size() && _minFrameDropTs < packQueue.front().m_nTimeStamp)
	{
		uint32_t queueDuration = packQueue.back().m_nTimeStamp > packQueue.front().m_nTimeStamp ? (packQueue.back().m_nTimeStamp - packQueue.front().m_nTimeStamp) : 0;

		long curTime = (long)session::TimeMillis();

		if (queueDuration >= IFRAMESHOLDDROP)
		{
			_minFrameDropTs = packQueue.back().m_nTimeStamp+_starttime;

			//AVLogWarn(@"dropped all, total duration is %u, %u in queue\r\n", queueDuration, (uint32_t)packQueue.size());

			doVideoFrameDelay(false);
		}
		else if (queueDuration >= BFRAMESHOLDDROP && curTime - _lastBFrameDropTs >= IFRAMESHOLDDROP)
		{
			//AVLogWarn(@"dropped b - frames, total duration is %u, %u in queue\r\n", queueDuration, (uint32_t)packQueue.size());

			doVideoFrameDelay(true);

			_lastBFrameDropTs = (uint32_t)curTime;
		}
	}
}
void RtmpConnection::doVideoFrameDelay(bool bBFramesOnly)
{
	std::list<RTMPPacket>& packQueue = _mediaData[VIDEO_MEDIA];
	for (std::list<RTMPPacket>::iterator it = packQueue.begin(); it != packQueue.end();)
	{
		RTMPPacket& packet = *it;
		if (bBFramesOnly && packet.m_body[0] == 0x27)
		{
			RTMPPacket_Free(&packet);
			it = packQueue.erase(it);
		}
		else if (!bBFramesOnly)
		{
			RTMPPacket_Free(&packet);
			it = packQueue.erase(it);
		}
		else
		{
			++it;
		}
	}
}
