#include <stdio.h>
#include<stdint.h>
#include "mathlib.h"

int main(void)
{
//printf("Square root of 25 is ",sqrt1(25))
int x,y;
printf("\nenter two numbers\n");
scanf("%d%d",&x,&y);
printf("\n%d + %d = %ld",x,y,add(x,y));
printf("\n%d - %d = %ld",x,y,sub(x,y));
printf("\n%d x %d = %ld\n",x,y,mul(x,y));
return 0;
}


