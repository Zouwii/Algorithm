// Algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"
#include "algorithm.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20

typedef int Status;
typedef int ElemType;  //别名
typedef struct {
    ElemType data[MAXSIZE];     //数据
    int length;     //长度
}SqList;

Status InitList(SqList* L)
{
    if (L == NULL) return ERROR;
    L->length = 0;
    return OK;
}


Status ClearList(SqList* L)
{
    if (L == NULL) return ERROR;
    L->length = 0;
    return OK;
}

Status isListEmpty(SqList* L)
{
    if (L == NULL) return TRUE;
    if (L->length==0) return TRUE;
    return FALSE;
}

int ListLength(SqList* L)
{
    return L->length;
}

Status ListInsert(SqList* L, int index, const ElemType e)
{
    if ((index >= 1) && (L->length<MAXSIZE))
    {
        if (index <= L->length) {
            for (int k = L->length - 1; k >= index - 1; k--)
            {
                L->data[k + 1] = L->data[k];
            }
        }
        L->data[index - 1] = e;
        L->length++;
        return OK;
    }
}

Status ListDelete(SqList* L, int index, ElemType* e)
{
    if (L->length == 0) return ERROR;
    if (index<1 || index>L->length) return ERROR;
    *e = L->data[index - 1];
    if (index < L->length)
    {
        for (int k = index ; k < L->length ; k++)
        {
            L->data[k-1] = L->data[k];
        }
        L->length--;
        return OK;
    }
    
}

Status visit(ElemType c)
{
    printf("%d->",c);
    return OK;
}

Status GetElem(SqList* L, int index, ElemType* e)
{
    if ((L->length==0)||(index<1) || (index>L->length)) return ERROR;
    *e = L->data[index - 1];
    return OK;
}



Status ListTraverse(SqList* L)
{
    for (int i = 0; i < L->length; i++)
    {
        visit(L->data[i]);
    }
    printf("\r\n");
    return OK;
}


int algorithm001()
{
    SqList L;
    ElemType e;
    Status ret;
    int j, k;
    ret = InitList(&L);
    printf("初始化后：L.length=%d\n", L.length);
    for (j = 1; j <= 5; j++)
        ret = ListInsert(&L, 1, j);
    ListTraverse(&L);
    ret = isListEmpty(&L);
    printf("L是否为空:%d\n", ret);
    ClearList(&L);
    ret = isListEmpty(&L);
    printf("L是否为空:%d\n", ret);
    for (j = 1; j <= 10; j++)
        ret = ListInsert(&L, 1, j);
    ListTraverse(&L);
    ListInsert(&L, 1, 0);
    ListTraverse(&L);
    GetElem(&L, 5, &e);
    printf("第五元素是：%d\n", e);
    k = ListLength(&L);
    for (j = k + 1; j >= k; j--)
    {
        ret = ListDelete(&L, j, &e);
        if (ret == ERROR)
        {
            printf("删除第%d个元素失败\n", j);
        }
        else {
            printf("删除第%d个元素成功: %d\n", j,e);
        }
    }
    ListTraverse(&L);
    ListDelete(&L, 5, &e);
    printf("删除第%d个元素成功: %d\n", 5, e);
    return 0;
}

//##############################################################################





int main()
{
    return algorithm003();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
