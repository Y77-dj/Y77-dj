#include <stdio.h>
#include <stdBool.h>
#include <stdlib.h>
#include <assert.h>
#define ERROR -1

typedef struct SqStack
{
    char stack[100];
    int top;
} SqStack;

typedef char SElemType;

void InitStack(SqStack* S)
{
    assert(S);
    (*S).top = 0;
}
//判断栈是否为空
int StackEmpty(SqStack S)
{
        return S.top == 0;

}

// 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
int GetTop(SqStack S, SElemType* e)
{
    if (S.top > 0)
    {
        *e = S.stack[S.top - 1]; // (1)
        return 1;
    }
    else
        return -1;
}

// 插入元素e为新的栈顶元素
void Push(SqStack* S, SElemType e)
{
    if (S->top > 100) // 栈满，
    {
        printf("栈满，出错！");
    }
    else
    {
        S->stack[S->top] = e;
        S->top = S->top + 1; // (2 )
    }
}
//出栈
int Pop(SqStack* S, SElemType* e)
{
    if (S->top)
    {
        *e = S->top--;
        return *e;
    }
    else
    {
        printf("栈已空\n");
        return 0;
    }
}
//判断字符是否为七种运算之一
bool In(SElemType c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '\n':
        return true;
        break;
    default:
        return false;
        break;
    }
}
// 根据教科书表3.1，判断t1，t2两符号的优先关系('#'用'\n'代替)
char Precede(SElemType t1, SElemType t2)
{
    char f;
    switch (t2)
    {
    case '+':
    case '-':
        if (t1 == '(' || t1 == '\n')
            f = '<'; // t1<t2
        else
            f = '>'; // t1>t2
        break;
    case '*':
    case '/':
        if (t1 == '*' || t1 == '/' || t1 == ')')
            f = '>'; // t1>t2
        else
            f = '<'; // t1<t2
        break;
    case '(':
        if (t1 == ')')
        {
            printf("括号不匹配\n");
            exit(ERROR);
        }
        else
            f = '<'; // t1<t2
        break;
    case '\n':
        if (t1 == ')')
        {
            printf(")不匹配\n");
            exit(ERROR);
        }
        else if (t1 == '\n')
        {
            f = '=';
        }
        else
            f = '<'; // t1<t2
        break;
    }
}

//算数运算
char Operate(a, x, b)
{
    switch (x) //开始运算
    {
    case '+':
        return (char)(a + b);
        break;
    case '-':
        return (char)(a - b);
        break;
    case '*':
        return (char)(a * b);
        break;
    case '/':
        return (char)(a / b);
        break;
    }
}
// 算术表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈
SElemType EvaluateExpression() // 算法3.4，有改动
{
    SqStack* OPTR, * OPND;
    SElemType a, b, c, x;
    InitStack(OPTR); // 初始化运算符栈OPTR和运算数栈OPND
    InitStack(OPND);
    Push(OPTR, '\n');              // 将换行符压入运算符栈OPTR的栈底(改)
    c = getchar();                 // 由键盘读入1个字符到c
    GetTop(*OPTR, &x);              // 将运算符栈OPTR的栈顶元素赋给x
    while (c != '\n' || x != '\n') // c和x不都是换行符
    {
        if (In(c))                 // c是7种运算符之一
            switch (Precede(x, c)) // 判断x和c的优先权
            {
            case '<':
                Push(OPTR, c); // 栈顶元素x的优先权低，入栈c
                c = getchar(); // 由键盘读入下一个字符到c
                break;
            case '=':
                Pop(OPTR, &x);  // x='('且c=')'情况，弹出'('给x(后又扔掉)
                c = getchar(); // 由键盘读入下一个字符到c(扔掉')')
                break;
            case '>':
                Pop(OPTR, &x);
                // 栈顶元素x的优先权高，弹出运算符栈OPTR的栈顶元素给x(改)
                Pop(OPND, &b);
                // 依次弹出运算数栈OPND的栈顶元素给b，a
                Pop(OPND, &a);
                Push(OPND, Operate(a, x, b));
                // 做运算a x b，并将运算结果入运算数栈
            }
        else if (c >= '0' && c <= '9') // c是操作数
        {
            Push(OPND, c - 48);
            // 将该操作数的值(不是ASCII码)压入运算数栈OPND
            c = getchar(); // 由键盘读入下一个字符到c
        }
        else // c是非法字符
        {
            printf("出现非法字符\n");
            exit(ERROR);
        }
        GetTop(*OPTR, &x); // 将运算符栈OPTR的栈顶元素赋给x
    }
    Pop(OPND, &x);          // 弹出运算数栈OPND的栈顶元素(运算结果)给x(改此处)
    if (!StackEmpty(*OPND)) // 运算数栈OPND不空(运算符栈OPTR仅剩'\n')
    {
        printf("表达式不正确\n");
        exit(ERROR);
    }
    return x;
}

int main()
{
    char cdata = EvaluateExpression();
    printf("表达式的值为：%c", cdata);
    return 0;
}
