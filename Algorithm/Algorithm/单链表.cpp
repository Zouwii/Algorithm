#include "stdio.h"    
#include "string.h"
#include "ctype.h"      
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"
#include "algorithm.h"

typedef struct Node    
{
	ElemType data;
	struct Node* next;
}Node;

typedef struct Node* LinkList;               //----------------Node* 别名 LL      

//别名 Node a   ==    struct Node a
//typedef  别名  ----------struct Node别名Node



Status InitList(LinkList* l)
{
	*l = (LinkList)malloc(sizeof(Node));
	if (*l == NULL)return ERROR;
	(*l)->next = NULL;
	return OK;
}

Status ClearList(LinkList* l)
{
	LinkList p, q;
	p = (*l)->next;
	while(p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
	(*l)->next = NULL;
	return OK;
}

Status isListEmpty(LinkList l)
{
	if (l->next != NULL) return FALSE;
	return TRUE;
}

int ListLength(LinkList l)
{
	int i = 0;
	LinkList p = l->next;
	while (p) {
		i++;
		p = p->next;
	}
	return i;
}


Status GetElem(LinkList l, int i, ElemType* e)
{
	int j;
	LinkList p;
	p = l->next;
	j = 1;
	while (p && (j < i))
	{
		p = p->next;
		j++;
	}
	if (p == NULL || (j>i))return ERROR; //前一个指过来了
	*e = p->data;
	return OK;
}

int LocateElem(LinkList l, ElemType e)
{
	int i = 0;
	LinkList p = l->next;
	while (p) {
		i++;
		if (p->data == e)
			return i;
		p = p->next;
	}
	return 0;
}

Status ListInsert(LinkList* l, int i, ElemType e)
{
	int j;
	LinkList p, s;
	p = *l;
	j = 1;
	while (p && (j < i))  //链表只能顺着来访问
	{
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	s = (LinkList)malloc(sizeof(Node));
	if (s == NULL) return ERROR;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete(LinkList* l, int i, ElemType* e)
{
	int j;
	LinkList p, s;
	p = *l;
	j = 1;
	while (p && (j < i))  //链表只能顺着来访问
	{
		p = p->next;     //p是删掉前面那个
		++j;
	}
	if (!p || j > i) return ERROR;
	s = p->next;
	if (s == NULL) return ERROR;
	//printf("%d %d", s->data, p->data);
	p->next = s->next;
	*e = s->data;
	free(s);
	return OK;
}

Status ListTraverse(LinkList l) //遍历
{
	LinkList p = l->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

Status CreateListHead(LinkList* l, int n)
{
	LinkList p;
	int i;
	srand((unsigned)time(NULL)); //随机数
	*l = (LinkList)malloc(sizeof(Node));
	if (*l == NULL) return ERROR;
	(*l)->next = NULL;
	for (int i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		if (p == NULL)return ERROR;
		p->data = rand() % 100 + 1;
		p->next = (*l)->next;
		(*l)->next = p;
	}
	return OK;
}

Status CreateListTail(LinkList* l, int n)
{
	LinkList p, r;
	int i;
	srand((unsigned)time(0));
	*l = (LinkList)malloc(sizeof(Node));
	if (*l == NULL) return ERROR;
	(*l)->next = NULL;
	r = *l;
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		if (p == NULL) return ERROR;
		p->data = rand() % 100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

int algorithm002()
{
	LinkList l;
	ElemType e;
	Status ret;
	int j, k;
	ret = InitList(&l);
	printf("init length%d\r", ListLength(l));
	for (j = 1; j <= 5; j++)
	{
		ret = ListInsert(&l, 1, j);
	}
	printf("after insert 5 members:");
	ListTraverse(l);
	ret = isListEmpty(l);
	printf("is null or not : %d\n", ret);
	ret = ClearList(&l);
	printf("after clear length:%d\n", ListLength(l));
	ret = isListEmpty(l);
	printf("is null or not : %d\n", ret);
	for (j = 1; j <= 10; j++)
	{
		ret = ListInsert(&l, j, j);
	}
	printf("after insert 10 members:");
	ListTraverse(l);
	ret = isListEmpty(l);
	printf("after insert 10 length:%d\n", ListLength(l));
	GetElem(l, 5, &e);
	printf("NO5 member:%d\n", e);
	k = ListLength(l);
	for (j = k + 1; j >= k; j--)
	{
		ret = ListDelete(&l, j, &e);
		if (ret == ERROR)
			printf("delete %d member failed!\n", j);
		else
			printf("delete %d member success! %d\n", j,e);
	}
	printf("after delete:");
	ListTraverse(l);
	ret = ListDelete(&l, 5, &e);
	if (ret == ERROR)
		printf("delete %d member failed!\n", j);
	else
		printf("delete %d member success! %d\n", 5, e);
	printf("after delete:");
	ListTraverse(l);
	ClearList(&l);

	CreateListHead(&l, 20);
	printf("from head create:");
	ListTraverse(l);
	ClearList(&l);

	CreateListTail(&l, 20);
	printf("from tail create:");
	ListTraverse(l);
	ClearList(&l);
	free(l);
	return 0;
}