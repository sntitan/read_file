#ifndef READ_IN_FILE_H_
#define READ_IN_FILE_H_
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
}REC_STATE;

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

enum ELE_TYPE
{
    ELE_SEPERATOR,
    ELE_TEXT,
    ELE_END
};

enum ELE_SEPERATOR_TYPE
{
    SEP_COMMA,/*,*/
    SEP_COLON,/*:*/
    SEP_EQUAL,/*=*/
    SEP_SPACE,/* */
    SEP_RETURN,/*\r*/
    SEP_NEXTLINE,/*\n*/
    SEP_END
};

typedef struct REC_INFO_STRU
{
    enum ELE_TYPE type;
    char* pContent;
    enum ELE_SEPERATOR_TYPE sep;
    struct REC_INFO_STRU* pNext;
}REC_INFO;


#define ENABLE_DBG(dbgVa, dbgType) (dbgVa = (dbgVa)|(dbgType))
#define DISABLE_DBG(dbgVa, dbgType) (dbgVa = (dbgVa)&(~dbgType))
#define DBG_PUSH_FILE_END (1<<1)
#define DBG_IS_SEPERATOR (1<<2)
#define DBG_RES (1<<3)
static inline void OutString(int dbgInfo, const char* pStr, ...)
{
    unsigned int dbgSwitch = 1;
//    ENABLE_DBG(dbgSwitch, DBG_PUSH_FILE_END);
//    ENABLE_DBG(dbgSwitch, DBG_IS_SEPERATOR);
//    ENABLE_DBG(dbgSwitch, DBG_RES);

    if(dbgInfo & dbgSwitch)
    {
        va_list arg;
        va_start(arg, pStr);
        vprintf(pStr, arg);
        va_end(arg); 
    }
}

#endif
