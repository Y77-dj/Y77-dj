#include <stdio.h>
#include "SqStack.h"


//判断是否回文
int IsPalindrome(SqStack *S, SElemType *c)
{
    while (*c != '\0')
    {
        Push(S, *c);
        c++;
    }
    c -= S->top;
    while (!StackEmpty(*S))
    {
        SElemType e;
        Pop(S, &e);
        if (*c == e)
            c++;
        else
            return 0;
    }
    return 1;
}

int main()
{
    SqStack S;
    InitStack(&S);
    char c[100];

    printf("请输入一个字符串：");
    scanf("%s",c);
    printf("是否为回文数：%d (1是 0不是)",IsPalindrome(&S,c));
    return 0;
}