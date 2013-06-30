#include <stdio.h>

#define Assert(a) if(!(a)) {printf("Assert at file[%s], line[%d]\n", __FILE__, __LINE__);}
