#include <stdio.h>
#include "read_in_file.h"

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
