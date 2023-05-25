#include <stdio.h>

typedef struct SqStack
{
    SElemType stack[100];
    int top;
} SqStack;

typedef char SElemType;

//初始化栈
void InitStack(SqStack *S)
{
    S->top = 0;
}

//判断栈是否为空
int StackEmpty(SqStack S)
{
    return S.top == 0;
}

// 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
int GetTop(SqStack *S, SElemType *e)
{
    if (S->top > 0)
    {
        *e = S->stack[S->top - 1]; // (1)
        return 1;
    }
    else
        return -1;
}

// 插入元素e为新的栈顶元素
void Push(SqStack *S, SElemType e)
{
    if (S->top > 100) // 栈满，
    {
        printf("栈满，出错！");
    }
    else
    {
        S->stack[S->top] = e;
        S->top++; // (2 )
    }
}

//出栈
int Pop(SqStack *S, SElemType *e)
{
    if (S->top)
    {
        *e = S->stack[--S->top];
        return *e;
    }
    else
    {
        printf("栈已空\n");
        return 0;
    }
}