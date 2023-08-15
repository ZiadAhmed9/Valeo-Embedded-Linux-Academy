#include<stdio.h>
#include<stdint.h>

int64_t add(int32_t num1,int32_t num2)
{
return num1+num2;
}
int32_t sub(int32_t num1,int32_t num2)
{
return num2-num1;
}
int64_t mul(int32_t num1,int32_t num2)
{
return num1*num2;
}
int32_t sqrt1(int64_t num2)
{

int32_t i;
for(i=0;i<=num2/2;i++)
{

if(i*i==num2)
{
  return i;
}

}

return 1;
}
