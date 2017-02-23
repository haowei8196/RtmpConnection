
#ifndef AVDefine_h
#define AVDefine_h

#include "AVSessionDefines.h"
#include "stdint.h"
typedef enum{
    ftSysHead=0xF0,//文件头
    ftIFrame=0xF1,//I帧
    ftBFrame=0xF2,//B帧
    ftAudio=0xF3,//音频帧
    ftPos=0xF4,//位置帧
}FrameType;

typedef enum {
	NO_MEDIA = 0,
	AUDIO_MEDIA,
	VIDEO_MEDIA,
	NumOfMedia = 3
}MediaType;

typedef struct MediaFrame
{
	uint8_t* data;
	int len;
	long ts;
	MediaType type;
}MediaFrame;

#ifdef IOS
#define Version_iOS_8 ((NSFoundationVersionNumber >= NSFoundationVersionNumber_iOS_8_0) ? YES : NO)
#endif // IOS


#define StreamHeadFlag      0xFFEE9988;//


#define Cmd_Mob_Login       0x0F01;//登陆命令
#define Cmd_Mob_Setup       0x0F02;//设置视频参数，gps频率、视频大小、帧率等
#define Cmd_Mob_StartVideo  0x0F03;//开始采集音视频数据
#define CMd_Mob_StopVideo   0x0F04;//停止采集音视频数据
#define Cmd_Mob_KeepLive    0x0FF0;//心跳包
#define Cmd_Mob_AVData      0x0FFF;//该命令后面跟的是音视频数据

typedef struct _StreamHead{
    uint32_t          Flag;//标志  0xFFEE9988
    uint32_t          CmdType;//命令标志
    uint32_t          Len;//后面的数据块的长度
}*StreamHead;

typedef struct _LoginInfo{
    char            Username[32];//用户名
    char            Password[32];//密码
}*LoginInfo;

typedef struct _AVSreamInfo{
	uint32_t             Port;//
}*AVStreamInfo;


typedef struct _AVDateTime{
	uint32_t          year;//年
    uint8_t*            Month;//月
	uint8_t*            Day;//日
	uint8_t*            Hour;//时
	uint8_t*            Minute;//分
	uint8_t*            Second;//秒
    uint16_t          Millisecond;//毫秒
}*AVDateTime;

typedef struct _AVData{
	uint32_t          FrameFlag;//帧头标志
	uint32_t          FrameType;//帧类型
    AVDateTime      FrameSmiple;//帧时间
	uint32_t          FrameSize;//帧长度
}*AVData;


typedef struct _SysHead{
    bool         Video;//是否有视频
	bool         Audio;//是否有音频
    
    int             BitDepthHint;//量化位数
    int             SampleRatel;//取样频率
    int             ChannelsNum;//声道数
    
    int             width;//视频宽
    int             height;//视频高
    int             hLen;//PSP,SSP的长度（解码器需要）
}*SysHead;

typedef struct _PosInfo{
    double          ix;//经度
    double          iy;//纬度
}*PosInfo;

class Reporter
{
public:
	virtual void onError(int err) {};
	virtual void onWarning(int err) {};
};
#endif

