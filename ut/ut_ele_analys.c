#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ut.h"
#include "../func/ele_analys.h"
#include "../func/readin_file_ele.h"


extern inline int imatchText(REC_INFO* pRec, const char* pStr);
void imatchText_ut()
{
    REC_INFO rec = {0};
    rec.type = ELE_TEXT;
    rec.pContent = (char*)malloc(10);
    strcpy(rec.pContent,"AbC");
    Assert(imatchText(&rec, "abc") == 0);
    Assert(imatchText(&rec, "aBc") == 0);
    Assert(imatchText(&rec, "abd") != 0);
}

extern inline int matchSep(const REC_INFO* pRec, enum ELE_SEPERATOR_TYPE sepType);
void matchSep_ut()
{
    REC_INFO rec = {0};
    rec.type = ELE_SEPERATOR;
    rec.sep = SEP_COLON;
    Assert(matchSep(&rec, SEP_COLON) == 0);
    Assert(matchSep(&rec, SEP_SPACE) != 0);
}

extern int ignoreSpaces(const REC_INFO* pRec);
void ignoreSpaces_ut()
{
    REC_INFO rec1 = {0};
    REC_INFO rec2 = {0};
    REC_INFO rec3 = {0};
    REC_INFO rec4 = {0};

    rec1.type = ELE_SEPERATOR;
    rec1.sep = SEP_SPACE;
    rec1.pNext = &rec2;
    rec2.type = ELE_SEPERATOR;
    rec2.sep = SEP_SPACE;
    rec2.pNext = &rec3;
    rec3.type = ELE_SEPERATOR;
    rec3.sep = SEP_SPACE;
    rec3.pNext = &rec4;
    rec4.type = ELE_SEPERATOR;
    rec4.sep = SEP_COLON;
    rec4.pNext = NULL;

    Assert(ignoreSpaces(&rec1) == 3);

    rec2.sep = SEP_COMMA;
    Assert(ignoreSpaces(&rec1) == 1);

    rec1.sep = SEP_EQUAL;
    Assert(ignoreSpaces(&rec1) == 0);
    
}

extern int GetTimeStamp(REC_INFO* pRec, void* pVal);
void GetTimeStamp_ut()
{
    REC_INFO rec8 = {ELE_SEPERATOR,NULL,SEP_COMMA,NULL};
    REC_INFO rec7 = {ELE_TEXT,"22",0,&rec8};
    REC_INFO rec6 = {ELE_SEPERATOR,NULL,SEP_COLON,&rec7};
    REC_INFO rec5 = {ELE_TEXT,"21",0,&rec6};
    REC_INFO rec4 = {ELE_SEPERATOR,NULL,SEP_COLON,&rec5};
    REC_INFO rec3 = {ELE_TEXT,"20",0,&rec4};
    REC_INFO rec2 = {ELE_SEPERATOR,NULL,SEP_SPACE,&rec3};
    REC_INFO rec1 = {ELE_TEXT,"2013.3.31",0,&rec2};

    TIME_INFO time = {0};
    
    Assert(GetTimeStamp(&rec1, &time) == 7);
    rec1.pContent = "2013.4.31";
    Assert(GetTimeStamp(&rec1, &time) < 0);
}

extern int PushStr(char** ppDstStr, unsigned int* pDstMaxLen, const char* pStr);
void PushStr_ut()
{
    unsigned int dstMax = 32;
    char* pDst = malloc(dstMax);
    Assert(pDst != NULL);
    memset(pDst,0,dstMax);
    
    Assert(PushStr(&pDst, &dstMax, "http://www.google.com") == 0);
    Assert(strcmp(pDst,"http://www.google.com") == 0);
    Assert(dstMax == 32);

    Assert(PushStr(&pDst, &dstMax, "http://www.google.com") == 0);
    Assert(strcmp(pDst,"http://www.google.comhttp://www.google.com") == 0);
    Assert(dstMax == 64);

    memset(pDst,0,dstMax);
    Assert(PushStr(&pDst, &dstMax, "http://www.google.com/abcdefghijklmnopqrspuvwxyzabcdefghijklmnopqrspuvwxyzabcdefghijklmnopqrspuvwxyzabcdefghijklmnopqrspuv") == 0);
    Assert(strcmp(pDst,"http://www.google.com/abcdefghijklmnopqrspuvwxyzabcdefghijklmnopqrspuvwxyzabcdefghijklmnopqrspuvwxyzabcdefghijklmnopqrspuv") == 0);
    Assert(dstMax == 128);
}

extern int GetUrl(REC_INFO* pRec, void* pVal);
void GetUrl_ut()
{

    REC_INFO rec8 = {ELE_SEPERATOR,NULL,SEP_COMMA,NULL};
    REC_INFO rec7 = {ELE_TEXT,"ict&site",0,&rec8};
    REC_INFO rec5 = {ELE_TEXT,"str",0,&rec7};
    REC_INFO rec4 = {ELE_SEPERATOR,NULL,SEP_EQUAL,&rec5};
    REC_INFO rec3 = {ELE_TEXT,"1&safe",0,&rec4};
    REC_INFO rec2 = {ELE_SEPERATOR,NULL,SEP_EQUAL,&rec3};
    REC_INFO rec1 = {ELE_TEXT,"http://www.google.com.hk/#newwindow",0,&rec2};
    
    char* pStr = NULL;
    Assert(GetUrl(&rec1, &pStr) == 6);
    Assert(pStr != NULL);

    if(pStr)
    {
        Assert(strcmp(pStr,"http://www.google.com.hk/#newwindow=1&safe=strict&site") == 0);
        free(pStr);
    }

}

int main()
{
    imatchText_ut();
    matchSep_ut();
    ignoreSpaces_ut();
    GetTimeStamp_ut();
    PushStr_ut();
    GetUrl_ut();
}

