#include <stdio.h>
#include "../func/readin_file_ele.h"

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
