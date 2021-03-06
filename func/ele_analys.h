#ifndef ELE_ANALYS_H_
#define ELE_ANALYS_H_

typedef struct TIME_INFO_STRU
{
    unsigned short year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short min;
    unsigned short sec;
}TIME_INFO;

enum REC_EVENT
{
    EVENT_LOGIN,
    EVENT_LOGOUT,
    EVNET_END
};

typedef struct RECORD_STATE_STRU
{
    unsigned int svrlId; 
    unsigned int userId;
    TIME_INFO time;
    enum REC_EVENT event;
}STATE_INFO;

enum FLOW_METHOD
{
    METHOD_GET,
    METHOD_POST,
    METHOD_END
};
/* 没有任何条件说明或者暗示流量信息与控制信息都会有serverId，userId，time，所以不将它们合并为一个结构体 */
typedef struct FLOW_INFO_STRU
{
    unsigned int svrlId;
    unsigned int userId;
    TIME_INFO time;
    char* pUrl;
    enum FLOW_METHOD  method;
    unsigned int flowCount;
}FLOW_INFO;

#endif
