#ifndef COMMON_H_
#define COMMON_H_

#define ENABLE_DBG(dbgVa, dbgType) (dbgVa = (dbgVa)|(dbgType))
#define DISABLE_DBG(dbgVa, dbgType) (dbgVa = (dbgVa)&(~dbgType))
#define DBG_PUSH_FILE_END (1<<1)
#define DBG_IS_SEPERATOR (1<<2)
#define DBG_RES (1<<3)
#define DBG_REC_GET (1<<4)
static inline void OutString(int dbgInfo, const char* pStr, ...)
{
    unsigned int dbgSwitch = 1;
//    ENABLE_DBG(dbgSwitch, DBG_PUSH_FILE_END);
//    ENABLE_DBG(dbgSwitch, DBG_IS_SEPERATOR);
//    ENABLE_DBG(dbgSwitch, DBG_RES);
    ENABLE_DBG(dbgSwitch, DBG_REC_GET);

    if(dbgInfo & dbgSwitch)
    {
        va_list arg;
        va_start(arg, pStr);
        vprintf(pStr, arg);
        va_end(arg); 
    }
}

#endif
