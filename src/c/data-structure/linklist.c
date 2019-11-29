#include "linklist.h"
typedef int ElemType;
LinkListNode *createLinklistNode(ElemType val)
{
    LinkListNode *newNode = (LinkListNode *)malloc(sizeof(LinkListNode));
    newNode->next = NULL;
    newNode->val = val;
    return newNode;
}
/**
 * 打印链表
 */
void printLinkList(LinkListNode *head)
{
    while (head != NULL)
    {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

/**
 * 头部插入
 * 循环操作
 * 缺点是需要判断头结点为空
 */
LinkListNode *headInsert(LinkListNode *head, ElemType val)
{
    LinkListNode *newNode = createLinklistNode(val);
    newNode->next = head;
    return newNode;
}

/**
 * 朴素尾部插入
 * 循环操作
 * 缺点是需要判断头结点为空
 */
LinkListNode *tailInsert(LinkListNode *head, ElemType val)
{
    LinkListNode *newNode = createLinklistNode(val);
    LinkListNode *temp = head;
    if (head == NULL)
        return newNode;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    return head;
}

/**
 * 递归尾部插入
 */
LinkListNode *tailInsertRecursion(LinkListNode *head, ElemType val)
{
    if (head == NULL)
        return createLinklistNode(val);

    LinkListNode *temp = head;

    if (temp->next == NULL)
    {
        temp->next = createLinklistNode(val);
        return head;
    }
    tailInsertRecursion(temp->next, val);
}

/**
 * 创建定长随机链表
 */
LinkListNode *createRandomLinklist(int len)
{
    srand(rand());
    if (len <= 0)
    {
        return NULL;
    }
    LinkListNode *head = createLinklistNode(rand() % 100);
    int i = 1;
    while (i++ < len)
    {
        LinkListNode *temp = createLinklistNode(rand() % 100);
        temp->next = head;
        head = temp;
    }
    return head;
}

/**
 * 创建定长顺序链表
 */
LinkListNode *creatSortedLinklist(int len)
{
    ElemType val = rand() % 10;
    if (len <= 0)
    {
        return NULL;
    }
    LinkListNode *head = createLinklistNode(val += rand() % 10);
    int i = 1;
    while (i++ < len)
    {
        head = tailInsert(head, val += rand() % 10);
    }
    return head;
}

/**
 * 顺序插入链表
 * 构造一个虚拟头结点，值为最小值。
 * 这样就可以将头部插入情况转换为中间插入情况，且无需考虑空链表插入。
 */
LinkListNode *insertSortedLinklist(LinkListNode *head, ElemType val)
{
    LinkListNode *newNodeNode = createLinklistNode(val);
    LinkListNode *tempHead = createLinklistNode(-__INT_MAX__); // 虚拟头结点
    tempHead->next = head;                                     //指向原头结点
    LinkListNode *temp = tempHead;
    // 寻找插入点
    while (temp->next != NULL && temp->next->val < val)
    {
        temp = temp->next;
    }
    // 插入
    newNodeNode->next = temp->next;
    temp->next = newNodeNode;
    // 返回临时结点的下一个结点，因为头结点可能会变动
    return tempHead->next;
}

/**
 * 原地翻转数组 
 * 需要引入虚拟头结点
 */
LinkListNode *reverseLinklist(LinkListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    LinkListNode *t1 = head;
    LinkListNode *t2 = head->next;
    LinkListNode *t3 = t2->next;
    t2->next = t1;
    t1->next = NULL;
    while (t3 != NULL)
    {
        t1 = t2;
        t2 = t3;
        t3 = t3->next;
        t2->next = t1;
    }
    t2->next = t1;
    return t2;
}
/**
 * 合并两个有序链表
 */
LinkListNode *mergeSortedLinklist(LinkListNode *a, LinkListNode *b)
{
    if (a == NULL)
    {
        return b;
    }
    if (b == NULL)
    {
        return a;
    }
    LinkListNode *t = createLinklistNode(-__INT_MAX__);
    LinkListNode *th = t;

    while (a != NULL && b != NULL)
    {
        if (a->val < b->val)
        {
            t->next = a;
            a = a->next;
        }
        else
        {
            t->next = b;
            b = b->next;
        }
        t = t->next;
    }
    if (a != NULL)
    {
        t->next = a;
    }
    if (b != NULL)
    {
        t->next = b;
    }
    return th->next;
}

void testLinklist()
{
    LinkListNode *l = createRandomLinklist(3);
    printf("[创建随机链表]\t");
    printLinkList(l);

    l = headInsert(l, -1);
    printf("[链表头部插入]\t");
    printLinkList(l);

    l = tailInsert(l, -2);
    printf("[链表尾部插入]\t");
    printLinkList(l);

    printf("[创建顺序链表]\t");
    l = creatSortedLinklist(5);
    printLinkList(l);

    printf("[顺序插入链表]\t");
    l = insertSortedLinklist(l, 20);
    printLinkList(l);

    l = creatSortedLinklist(5);
    printf("[原始顺序链表]\t");
    printLinkList(l);
    l = reverseLinklist(l);
    printf("[翻转顺序链表]\t");
    printLinkList(l);

    printf("[创建有序链表]\t");
    LinkListNode *a = creatSortedLinklist(3);
    printLinkList(a);

    printf("[创建有序链表]\t");
    LinkListNode *b = creatSortedLinklist(3);
    printLinkList(b);
    printf("[合并两个链表]\t");
    l = mergeSortedLinklist(a, b);
    printLinkList(l);
}