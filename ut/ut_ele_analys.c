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

int main()
{
    imatchText_ut();
}
