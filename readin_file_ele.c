#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "read_in_file.h"
#include "readin_file_ele.h"

#define MAX_LINE_CHAR_COUNT 128

char seperator[SEP_END] = {',', ':', '=', ' ', '\r', '\n'};
inline int IsSeperator(char ch, enum ELE_SEPERATOR_TYPE *pType)
{
    int i = 0;
    for(i = 0; i < sizeof(seperator)/sizeof(seperator[0]); ++i)
    {
        if(seperator[i] == ch)
        {
            OutString(DBG_IS_SEPERATOR, "FindSeperator[%c]\n",ch);
            *pType = i;
            return 1;
        }
    }
    return 0;
}

inline int IsLineEnd(char ch)
{
    return ((ch == '\n') || (ch == '\r'));
}

REC_INFO* NewRecEle()
{
    REC_INFO* pRec = NULL;
    pRec = (REC_INFO*)malloc(sizeof(REC_INFO));
    OutString(DBG_RES,"Malloc ELE\n");
    if(pRec == NULL)
    {
        return NULL;
    }
    memset(pRec,0,sizeof(REC_INFO));
    return pRec;
}

int SaveTextInfo(REC_INFO* pEle, char* pStr, size_t strLen)
{
    if(strLen > 0)
    {
        pEle->pContent = (char*)malloc(strLen + 1);
        if(pEle->pContent == NULL)
        {
            return -1;
        }
        memcpy(pEle->pContent, pStr, strLen);
        pEle->pContent[strLen] = '\0';
    }
    /* 内容为空也认为正确 */
    return 0;
}

int SaveSepInfo(REC_INFO* pEle, enum ELE_SEPERATOR_TYPE sepType)
{
    pEle->sep = sepType;
    return 0;
}

REC_INFO* PushEleEnd(REC_INFO* pEle, enum ELE_TYPE ele, void* pCon, size_t strLen)
{
    pEle->type = ele;
    switch(ele)
    {
        case ELE_SEPERATOR:
            SaveSepInfo(pEle, *(enum ELE_SEPERATOR_TYPE*)pCon);
            break;
        case ELE_TEXT:
            SaveTextInfo(pEle, (char*)pCon, strLen);
            break;
        default:
            return NULL;
    }

    if(pEle->pNext == NULL)
    {
        pEle->pNext = NewRecEle();
    }
    else
    {
        if(pEle->pNext->pContent)
        {
            free(pEle->pNext->pContent);
            pEle->pNext->pContent = NULL;
        }
    }
    pEle->pNext->type = ELE_END;

    return pEle->pNext; 
}

void DelAllEle(REC_INFO* pEle)
{
    REC_INFO* pEleDel;
    REC_INFO* pEleNext;
    pEleDel = pEle;
    while(pEleDel)
    {
        pEleNext = pEleDel->pNext;
        if(pEleDel->pContent)
        {
            free(pEleDel->pContent);
        }
        free(pEleDel);
        OutString(DBG_RES, "FREE ELE\n");
        pEleDel = pEleNext;
    }
    return;
}

int ReadInLine(FILE* pFile, REC_INFO* pLineInfo)
{
    char* pLine = NULL;
    int ret = 0;
    unsigned int readPos = 0;
    unsigned int eleLen = 0;
    size_t lineLen = 0;
    REC_INFO* pEleEnd = pLineInfo;
    enum ELE_SEPERATOR_TYPE sepType = SEP_END;

    pLine = (char*)malloc(MAX_LINE_CHAR_COUNT);
    OutString(DBG_RES, "Malloc Local pLine\n");
    if(pLine == NULL)
    {
        return -1;
    }
    memset(pLine, 0, MAX_LINE_CHAR_COUNT);

    ret = -2;
    while(fgets(pLine, MAX_LINE_CHAR_COUNT, pFile) != NULL)
    {
        lineLen = strlen(pLine);
        for(readPos = 0, eleLen = 0; readPos < lineLen; ++readPos)
        {
            if(IsSeperator(pLine[readPos],&sepType))
            {
                if(eleLen > 0)
                {
                    pEleEnd = PushEleEnd(pEleEnd, ELE_TEXT, pLine + readPos - eleLen, eleLen);
                    if(pEleEnd == NULL)
                    {
                        ret = -3;
                        goto FREE_AND_RETURN;
                    }
                    eleLen = 0;
                }

                pEleEnd = PushEleEnd(pEleEnd, ELE_SEPERATOR, &sepType, 0);
                if(pEleEnd == NULL)
                {
                    ret = -3;
                    goto FREE_AND_RETURN;
                }
            }
            else
            {
                ++eleLen;
            }
        } 
        if(eleLen != 0)
        {
            pEleEnd = PushEleEnd(pEleEnd, ELE_TEXT, pLine + readPos - eleLen, eleLen);
            if(pEleEnd == NULL)
            {
                ret = -3;
                goto FREE_AND_RETURN;
            }
            eleLen = 0;
        }
        if(lineLen == 0)
        {
            ret = -4;
            goto FREE_AND_RETURN;
        }
        if(IsLineEnd(pLine[lineLen - 1]))
        {
            ret = 0;
            goto FREE_AND_RETURN;
        }
    }
    
FREE_AND_RETURN:
    free(pLine);
    OutString(DBG_RES, "FREE Local pLine\n");
    return ret;
}

void OutputRecInfo(REC_INFO* pEle)
{
    while(pEle)
    {
        switch(pEle->type)
        {
            case ELE_TEXT:
                printf("ELE_TEXT[%s]\n", pEle->pContent);
                break;
            case ELE_SEPERATOR:
                printf("ELE_SEPERATOR[%c]\n", seperator[pEle->sep]);
                break;
            default:
                return;
        }
        pEle = pEle->pNext;
    }
    return;
}

int main(int argc, char* argv[])
{
    FILE* pfile = NULL;
    REC_INFO lineInfo = {0};
    int lineCount = 0;
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

    while(ReadInLine(pfile, &lineInfo) == 0)
    {
        printf("Line[%d]:\n",++lineCount);
        OutputRecInfo(&lineInfo);
    } 

    DelAllEle(lineInfo.pNext);

    fclose(pfile);
    printf("read over!\n");
    return 0;
    
}
