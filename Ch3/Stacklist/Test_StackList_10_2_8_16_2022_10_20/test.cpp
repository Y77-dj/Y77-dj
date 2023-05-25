#include <stdio.h>
#include "SqStack.h"


//进制转换函数
void Fun_10_2_8_16(int number,int cet)
{
	SqStack S;
	SElemType e;
	InitStack(&S);
	if(number==0) 
	{
		printf("转换后的%d进制数为:0",cet);
	}
	while(number)
	{
		Push(&S,number%cet);
		number=number/cet;
	}
	
	printf("转换后的%d进制数为：",cet); 
	while(!StackEmpty(S))
	{
		Pop(&S,&e);
		switch(e)          //十六进制时整型数转成字符输出 
		{
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15: e+=55;break;
			default :e+=48;
		}
		printf("%c",e);
	}
	printf("\n");
}

int main()
{
	int number,cet;
	printf("请输入要转换的十进制数：");
	scanf("%d",&number);
	// printf("请输入要转换的数制：");
	// scanf("%d",&cet);
	Fun_10_2_8_16(number,2);
	Fun_10_2_8_16(number,8);
	Fun_10_2_8_16(number,16);
	return 0;
}
