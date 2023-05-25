#include <stdio.h>
#include <stdlib.h>
// 单向循环链表定义
typedef struct ListNode
{
    long long value;
    struct ListNode *next;
} ListNode, *LinkList;

// 定义两个List 分别存储 m 和 n 的值.
LinkList m_ListHead;
LinkList n_ListHead;

// 单向循环链表next 等于自身时，为空
int is_Empty(LinkList ListHead)
{
    return ListHead->next == ListHead;
}

// 入栈,使用头插法插入元素
void push(LinkList ListHead, long long num)
{
    LinkList List_tmp;
    List_tmp = (LinkList)malloc(sizeof(struct ListNode));
    List_tmp->value = num;
    List_tmp->next = ListHead->next;

    ListHead->next = List_tmp;
}

// 出栈, 从头部删除元素
void pop(LinkList ListHead)
{
    LinkList List_tmp;
    if (!is_Empty(ListHead))
    {
        List_tmp = ListHead->next;
        ListHead->next = List_tmp->next;
        free(List_tmp); // 释放元素
    }
}

void clear_List(LinkList ListHead)
{
    int count = 0;
    LinkList List_tmp = ListHead->next;

    while (List_tmp != ListHead)
    {
        ListHead->next = List_tmp->next;
        free(List_tmp);
        List_tmp = ListHead->next;
        count++;
    }
    printf("\n释放了%d个链表元素！！！\n", count);
}

// 阿克曼函数实现
long long ack(long long m, long long n)
{
    push(m_ListHead, m);          // 将 m 入栈
    push(n_ListHead, n);          // 将 n 入栈
    while (!is_Empty(m_ListHead)) // 判断 m 链表是否为空
    {
        // m != 0时，入栈
        while (m != 0)
        {
            if (n == 0)
            {
                printf("[%s][%4d] 当前m=%lld, n=%lld, 即将入栈m-1=%lld, n=1 \n", __func__, __LINE__, m, n, m - 1);

                m--;
                n = 1;
                push(m_ListHead, m); // 将 m 入栈
                push(n_ListHead, n); // 将 n 入栈
            }
            else
            {
                // 使用 -1 代表 ack(m - 1, ack(m, n - 1)); 的情况
                printf("[%s][%4d] 当前m=%lld, n=%lld, 即将入栈m-1=%lld, n=-1 \n", __func__, __LINE__, m, n, m - 1);
                n--;
                push(m_ListHead, m - 1); // 将 m 入栈
                push(n_ListHead, -1);    // 将 n 入栈
            }
        }
        // 当 m==0 时 出栈
        printf("[%s][%4d] 当前m=%lld, n=%lld, 计算 n=n+1 = %lld\n", __func__, __LINE__, m, n, n + 1);
        n++;
        while (!is_Empty(m_ListHead) && n_ListHead->next->value != -1)
        {

            printf("[%s][%4d] 当前m=%lld, n=%lld, 即将出栈 m =%lld, n=%lld \n",
                   __func__, __LINE__, m, n, m_ListHead->next->value, n_ListHead->next->value);

            pop(m_ListHead);
            pop(n_ListHead);
        }

        // 处理  ack(m - 1, ack(m, n - 1));的情况，此时，获取m-1 的值，弹出-1, 将当前n push 入栈
        if (!is_Empty(m_ListHead))
        {
            m = m_ListHead->next->value;
            pop(n_ListHead);
            push(n_ListHead, n);
            printf("[%s][%4d] 当前m=%lld, n=%lld \n", __func__, __LINE__, m, n);
        }
    }
    return n;
}

int main(void)
{
    long long m = 0;
    long long n = 0;

    // 分配 List 头结点
    m_ListHead = (LinkList)malloc(sizeof(struct ListNode));
    n_ListHead = (LinkList)malloc(sizeof(struct ListNode));
    m_ListHead->next = m_ListHead;
    n_ListHead->next = n_ListHead;

    while (m != -1)
    {
        scanf("%d %d", &m, &n);
        printf("\n\n计算结果===> m=%lld,n=%lld 时, ack=%lld \n\n", m, n, ack(m, n));
    }

    // 释放链表头节点内存
    free(m_ListHead);
    free(n_ListHead);

    return 0;
}