#ifndef READIN_FILE_ELE_H_
#define READIN_FILE_ELE_H_

/* element type
 * 分为分隔符和字符串*/
enum ELE_TYPE
{
    ELE_SEPERATOR,
    ELE_TEXT,
    ELE_END
};

/* element seperator type
 * 分隔符的种类，代码中的全局变量需要同步修改*/
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

extern const char seperator[SEP_END];

/* ELEMENT INFO
 * 一个词素的基本信息 */
typedef struct REC_INFO_STRU
{
    enum ELE_TYPE type;
    char* pContent;
    enum ELE_SEPERATOR_TYPE sep;
    struct REC_INFO_STRU* pNext;
}REC_INFO;


/* 将读入输入文件句柄中的一行，并解析出词素输出 */
int ReadInLine(FILE* pFile, REC_INFO* pLineInfo);

/* 删除所有的element */
void DelAllEle(REC_INFO* pEle);


#endif
