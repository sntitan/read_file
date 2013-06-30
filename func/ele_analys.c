#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "readin_file_ele.h"
#include "ele_analys.h"

enum RECORD_TYPE
{
    REC_STATE,
    REC_FLOW,
    REC_TYPE_END
};

typedef int (*REC_TYPE_JUDGE)(REC_INFO* pEle);

typedef struct REC_TYPE_CTRL_STRU
{
    REC_TYPE_JUDGE IsType;
}REC_TYPE_CTRL;

extern int IsRecState(REC_INFO* pRec);
extern int IsRecFlow(REC_INFO* pRec);

REC_TYPE_CTRL g_recType[REC_TYPE_END] = \
{
    {
        IsRecState,
    },
    {
        IsRecFlow,
    },
};

enum REC_INFO_TYPE
{
    REC_INFO_SERVERID,
    REC_INFO_USERID,
    REC_INFO_TIMESTAMP,
    REC_INFO_EVENT,
    REC_INFO_URL,
    REC_INFO_METHOD,
    REC_INFO_FLOW,
    REC_INFO_END
};

typedef int (*REC_INFO_GET)(REC_INFO* pRec, void* pStr);
typedef struct REC_INFO_CTRL_STRU
{
    char name[32];
    REC_INFO_GET GetValue;
}REC_INFO_CTRL;

extern int GetServerId(REC_INFO* pRec, void* pVal);
extern int GetUserId(REC_INFO* pRec, void* pVal);
extern int GetTimeStamp(REC_INFO* pRec, void* pVal);
extern int GetEvent(REC_INFO* pRec, void* pVal);
extern int GetUrl(REC_INFO* pRec, void* pVal);
extern int GetMethod(REC_INFO* pRec, void* pVal);
extern int GetFlow(REC_INFO* pRec, void* pVal);

REC_INFO_CTRL g_recInfoCtrl[REC_INFO_END] = \
{
    {
        "svrid",
        GetServerId,
    },
    {
        "user",
        GetUserId,
    },
    {
        "timestamp",
        GetTimeStamp,
    },
    {
        "event",
        GetEvent,
    },
    {
        "url",
        GetUrl,
    },
    {
        "method",
        GetMethod,
    },
    {
        "flow",
        GetFlow,
    },
};

inline int imatchText(REC_INFO* pRec, const char* pStr)
{
    size_t cmpLen = strlen(pStr);
    size_t cmpPos = 0;
    if(pRec->type != ELE_TEXT)
    {
        return -1;
    }
    if(pRec->pContent == NULL)
    {
        return -1;
    }
    if(strlen(pRec->pContent) < cmpLen)
    {
        return -1;
    }
    for(cmpPos = 0; cmpPos < cmpLen; ++cmpPos)
    {
        if(tolower(pRec->pContent[cmpPos]) != tolower(pStr[cmpPos]))
        {
            return -1;
        }
    }
    return 0;
}

inline int matchSep(const REC_INFO* pRec, enum ELE_SEPERATOR_TYPE sepType)
{
    if(pRec->type != ELE_SEPERATOR)
    {
        return -1;
    }
    return (pRec->sep == sepType) ? 0 : -1;
}

int ignoreSpaces(const REC_INFO* pRec)
{
    int iCnt = 0;
    while(matchSep(pRec, SEP_SPACE) == 0)
    {
        ++iCnt;
        pRec = pRec->pNext;
        if(pRec == NULL)
        {
            return 0;
        }
    }
    return iCnt;
}

REC_INFO* goaheadRec(REC_INFO* pRec, int steps)
{
    if(steps < 0)
    {
        return NULL;
    }
    while(steps != 0)
    {
        if(pRec == NULL)
        {
            return NULL;
        }
        pRec = pRec->pNext;
        --steps;
    }
    return pRec;
}

int IsRecState(REC_INFO* pRec)
{
    if(pRec->type != ELE_TEXT)
    {
        return 0;
    }
    if(pRec->pContent == NULL)
    {
        return 0;
    }
    return ((pRec->pContent[0] == 'S') || (pRec->pContent[0] == 's'));
}

int IsRecFlow(REC_INFO* pRec)
{
    if(pRec->type != ELE_TEXT)
    {
        return 0;
    }
    if(pRec->pContent == NULL)
    {
        return 0;
    }
    return ((pRec->pContent[0] == 'T') || (pRec->pContent[0] == 't'));
}

int IsNumber(const char* pStr)
{
    size_t strLen = strlen(pStr);
    size_t curPos = 0;
    for(curPos = 0; curPos < strLen; ++curPos)
    {
        if((pStr[curPos] > '9') || (pStr[curPos] < '0'))
        {
            return 0;
        }
    }
    return 1;
}

inline int GetNumberFromRec(const REC_INFO* pRec, void* pVal)
{
    unsigned int* pNum = pVal;
    unsigned int num = 0;

    if(!IsNumber(pRec->pContent))
    {
        return -1;
    }
    if(sscanf(pRec->pContent, "%u",&num) != 1)
    {
        return -1;
    }
    *pNum = num;
    return 0;
}

int GetServerId(REC_INFO* pRec, void* pVal)
{
    unsigned int* pServerId = pVal;
    unsigned int serverId = 0;

    if(GetNumberFromRec(pRec, &serverId) != 0)
    {
        return -1;
    }

    if((serverId < 1) || (serverId > 100))
    {
        return -2;
    }
    *pServerId = serverId;
    return 1;
}

int GetUserId(REC_INFO* pRec, void* pVal)
{
    unsigned int* pUserId = pVal;
    unsigned int userId = 0;

    if(GetNumberFromRec(pRec, &userId) != 0)
    {
        return -1;
    }
    if((userId < 1) || (userId > 10000))
    {
        return -2;
    }
    *pUserId = userId;
    return 1;
}

int GetFlow(REC_INFO* pRec, void* pVal)
{
    unsigned int* pFlow = pVal;
    unsigned int flowCount = 0;

    if(GetNumberFromRec(pRec, &flowCount) != 0)
    {
        return -1;
    }
    /* 暂时不做流量为0的判断(题目没有要求）
    if(flowCount == 0)
    {
        return -2;
    }
    */
    *pFlow = flowCount;
    return 1;
}

#define RETURN_IF_NULL(p,va) (if((p) == NULL) return va;)
/*  判断是否为闰年，1为闰年，0不是闰年 */
int IsYearRun(unsigned int year)
{
    if(year % 3200 == 0)
    {
        return ((year % 172800) == 0) ? 1 : 0;
    }

    if(year % 100 == 0)
    {
        return ((year % 400) == 0) ? 1 : 0;
    }

    /* 到这里，已经没有世纪年  */
    if(year % 4 == 0)
    {
        return 1;
    }

    return 0;
}

/* 判断时间是否合法 */
int IsValidTime(const TIME_INFO* pTime)
{
    unsigned short dayInMon[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if((pTime->year < 2008) || (pTime->year > 2020))
    {
        return 0;
    }

    /* 简单点好，闰年的判断方法上面有函数(未经测试)  */
    if((pTime->year == 2008) 
    || (pTime->year == 2012) 
    || (pTime->year == 2016) 
    || (pTime->year == 2020))
    {
        dayInMon[1] = 29;
    }

    if((pTime->month < 1) || (pTime->month > 12))
    {
        return 0;
    }

    if((pTime->day < 1) || (pTime->day > dayInMon[pTime->month - 1]))
    {
        return 0;
    }

    if(pTime->hour > 23)
    {
        return 0;
    }

    if(pTime->min > 59)
    {
        return 0;
    }

    if(pTime->sec > 59)
    {
        return 0;
    }
    
    return 1;
}

int GetTimeStamp(REC_INFO* pRec, void* pVal)
{
    REC_INFO* pCurRec = pRec;
    int recNum = 0;
    int temp = 0;
    unsigned int tempu = 0;
    TIME_INFO timeInfo = {0};
    if(sscanf(pCurRec->pContent, "%hu.%hu.%hu",&(timeInfo.year), &(timeInfo.month), &(timeInfo.day)) != 3)
    {
        return -1;
    }

    /* 删除空格 */
    ++recNum;
    pCurRec = goaheadRec(pCurRec, 1);
    temp = ignoreSpaces(pCurRec);
    if(temp <= 0)
    {
        return -1;
    }
    recNum += temp;
    pCurRec = goaheadRec(pCurRec, temp);

    /* 向前走4个，确保没有空指针 */
    if(goaheadRec(pCurRec,4) == NULL)
    {
        return -1;
    }

    /*  获取hour */
    if(GetNumberFromRec(pCurRec, &tempu) != 0)
    {
        return -1;
    }
    timeInfo.hour = (unsigned short)tempu;

    /* 获取minite */
    ++recNum;
    pCurRec = goaheadRec(pCurRec, 1);
    if(matchSep(pCurRec, SEP_COLON) != 0)
    {
        return -1;
    }
    ++recNum;
    pCurRec = goaheadRec(pCurRec, 1);
    if(GetNumberFromRec(pCurRec, &tempu) != 0)
    {
        return -1;
    }
    timeInfo.min = (unsigned short)tempu;

    /* 获取second */
    ++recNum;
    pCurRec = goaheadRec(pCurRec, 1);
    if(matchSep(pCurRec, SEP_COLON) != 0)
    {
        return -1;
    }
    ++recNum;
    pCurRec = goaheadRec(pCurRec, 1);
    if(GetNumberFromRec(pCurRec, &tempu) != 0)
    {
        return -1;
    }
    timeInfo.sec = tempu;

    if(!IsValidTime(&timeInfo))
    {
        return -2;
    }

    memcpy(pVal, &timeInfo, sizeof(timeInfo));
    ++recNum;

    return recNum;
}

int GetEvent(REC_INFO* pRec, void* pVal)
{
    enum REC_EVENT *pEvent = pVal;
    if(imatchText(pRec, "Login") == 0)
    {
        *pEvent = EVENT_LOGIN;
    }
    else if(imatchText(pRec, "Logout") == 0)
    {
        *pEvent = EVENT_LOGOUT;
    }
    else
    {
        return -1;
    }
    return 1;
}

int GetMethod(REC_INFO* pRec, void* pVal)
{
    enum FLOW_METHOD* pMethod = pVal;
    if(imatchText(pRec, "GET") == 0)
    {
        *pMethod = METHOD_GET;
    }
    else if(imatchText(pRec, "POST") == 0)
    {
        *pMethod = METHOD_POST;
    }
    else
    {
        return -1;
    }
    return 1;
}

int PushStr(char** ppDstStr, unsigned int* pDstMaxLen, const char* pStr)
{
    size_t curLen = strlen(*ppDstStr);
    size_t srcLen = strlen(pStr);
    size_t freeLen = 0;
    size_t mallocLen = 0;

    if(*pDstMaxLen > 0)
    {
        freeLen = *pDstMaxLen - curLen - 1;
    }

    while(srcLen > freeLen + mallocLen)
    {
        if(mallocLen == 0)
        {
            /* maxLen 也是0，说明字符串还未初始化，首先初始化为32长度 */
            mallocLen = *pDstMaxLen * 2;
            if(mallocLen == 0)
            {
                mallocLen = 32;
            }
            freeLen = 0;
        }
        else
        {
            mallocLen *= 2;
        }
    }

    /* 经过上面的操作之后，freeLen可能已经失效*/
    if(mallocLen != 0)
    {
        char* pTempStr = NULL;
        pTempStr = (char*)malloc(mallocLen);
        if(pTempStr == NULL)
        {
            return -1;
        }
        memset(pTempStr, 0, mallocLen);
        if(*ppDstStr != NULL)
        {
            strcpy(pTempStr,*ppDstStr);
            free(*ppDstStr);
        }
        *ppDstStr = pTempStr;
        *pDstMaxLen = mallocLen;
    }

    strcpy(*ppDstStr + curLen, pStr);
    
    return 0;
}

int PushChar(char** ppDstStr, unsigned int* pDstMaxLen, char ch)
{
    char cha[2] = {ch,'\0'};
    return PushStr(ppDstStr, pDstMaxLen, cha);
}

int GetUrl(REC_INFO* pRec, void* pVal)
{
    REC_INFO* pCurRec = pRec;
    unsigned int recCount = 0;
    char** ppUrl = pVal;
    char* pTemp = NULL;
    unsigned int urlMaxLen = 0;
    while(pCurRec)
    {
        if(pCurRec->type == ELE_SEPERATOR)
        {
            if(pCurRec->sep == SEP_COMMA)
            {
                *ppUrl = pTemp;
                return recCount;
            }
            else
            {
                if(PushChar(&pTemp,&urlMaxLen, seperator[pCurRec->sep]) != 0)
                {
                    break;
                }
                ++recCount;
            }
        }
        else if(pCurRec->type == ELE_TEXT)
        {
            if(PushStr(&pTemp, &urlMaxLen, pCurRec->pContent) != 0)
            {
                break;
            }
            ++recCount;
        }
        else
        {
            break;
        }

    }

    if(pTemp)
    {
        free(pTemp);
    }
    return -1;
}

