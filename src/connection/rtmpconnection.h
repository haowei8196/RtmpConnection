//
//  NetConnection.h
//  AVSession
//
//  Created by whw on 2016/11/1.
//  Copyright © 2016年 meixin. All rights reserved.
//
#ifndef RtmpConnection_h
#define RtmpConnection_h

#include "../avdefine.h"
#include "../base/thread.h"
#include "librtmp/rtmp.h"
#include <list>

typedef enum {
	Connection_Up,
	Connection_Down,
}ConnectionType;

typedef enum {
	Connection_Succuss,
	Connection_Fail, //
	Connection_Exception, //
	Stream_Fail,     //
}ConnectionStatus;

enum RTMP_STATUS
{
	RTMP_Inited,
	RTMP_Connected,
	RTMP_Closed
};

class ConnectionHandle:public Reporter
{
public:
	virtual void onConnectionStatus(uint64_t uid, ConnectionStatus res) = 0;
	virtual void onReceiveFrame(uint64_t uid,const MediaFrame& frame) = 0;
	virtual void onBandwidth(uint64_t uid,int stat) = 0;
};

class RtmpConnection :public Thread
{
public:
	RtmpConnection(ConnectionType type, ConnectionHandle* callback,uint64_t uid,std::string& uri);
	~RtmpConnection();

	void enableAudio(bool flag);
	bool enableAudio();

	void enableVideo(bool flag);
	bool enableVideo();

	void sendFrame(MediaFrame& frame);
protected:
	virtual void Run();
private:
	int connectRtmp();
	void closeRtmp();
	void setChunkSize(int size);
	int handle_output();
	int handle_input();
	void stat_bytes(int len);
	void processPackets();
	void doVideoFrameDelay(bool bBFramesOnly);
private:
	ConnectionHandle* _callback;

	bool    _running;
	RTMP_STATUS		_rtmp_status;
	bool    _iFrameRequired;
	RTMP*   _rtmp;
	int     _streamid;
	long    _starttime;
	std::string   _uri;
	std::list<RTMPPacket> _mediaData[NumOfMedia];
	CMutex  _mutex[NumOfMedia];
	int     _type;
	uint64_t     _uid;
	bool    _enableVideo;
	bool    _enableAudio;

	int     _sleepms;

	//drop packet
	uint32_t    _minFrameDropTs;
	uint32_t    _lastBFrameDropTs;

	//bandwidth stat
	float			total_byte_count_;
	long		    begin_stat_bw_time_;
	long            total_idle_time_;
	long            last_begin_idle_time_;
	float			last_stat_bw_;
	float			measure_stat_bw_;
};

#endif // !RtmpConnection_h

