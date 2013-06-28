#include <stdio.h>

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


int file_into_stru(FILE* pfile)
{
    return 0;
}


int main(int argc, char* argv[])
{
    FILE* pfile = NULL;
    if(argc != 2)
    {
	printf("need a file name!\n");
        return -1;
    }
    if(argv[1] == NULL)
    {
        return -1;
    }
    printf("read in file %s\n",argv[1]);
    pfile = fopen(argv[1], "rb");

    file_into_stru(pfile);

    fclose(pfile);
    printf("read over!\n");
    return 0;
    
}
