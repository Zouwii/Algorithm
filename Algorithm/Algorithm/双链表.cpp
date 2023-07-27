#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "algorithm.h"

typedef struct dulnode {
	struct dulnode* prior;
	ElemType data;
	struct dulnode* next;
}dulnode,*dulinklist;

dulinklist InitList(); //初始化
int Listlength(dulinklist l); //长度
int GetElem(dulinklist l, ElemType e); //获取元素位置
int GetElemByIndex(dulinklist l, int index, ElemType* e); //获取指定元素
Status ListInsert(dulinklist l, int i, ElemType e); //添加元素
Status ListDelete(dulinklist l, int i); //删除元素
void ListClear(dulinklist* l); //清空表
void print(dulinklist l); //输出表

dulinklist InitList() {
	int data,size;
	dulinklist l, last,p;
	l = (dulinklist)malloc(sizeof(dulnode));
	l->prior = NULL;
	l->next = NULL;
	last = l;
	printf("请输入节点值，（-1表示输入完成）：\n");
	size = 0;
	printf("当前链表的大小：%d\n",size);
	while (true)
	{
		if (scanf("%d", &data) != 1)break;
		if (data == -1) break;
		p = (dulinklist)malloc(sizeof(dulnode));
		if (p == NULL) {
			printf("内存不足，终止操作！\n");
		}
		p->data = data;        //[]   []    []
		last->next = p;        //     p-----p
		p->prior = last;
		p->next = NULL;
		last = p;
	}
	last->next = NULL;
	return l;
}

int Listlength(dulinklist l)
{
	int length = 0;
	if (l == NULL)return 0;
	if (l->next == NULL) return 0;
	while (l->next) {
		l = l->next;
		length++;
	}
	return length;
}

int GetElem(dulinklist l, ElemType e) {
	int found = 0;
	int index = 1;
	if (l == NULL)return ERROR;
	if (l->next == NULL) return ERROR;
	l = l->next;
	do {
		if (l->data == e)
		{
			printf("找到一个节点，位置在：%d\n", index);
			found = 1;
		}
		
		l = l->next;
		index++;
	} while (l);
	if (found == 0)
	{
		printf("指定值的节点，一个也没找到！\n");
		return ERROR;
	}
	return OK;
}

int GetElemByIndex(dulinklist l, int index, ElemType* e)
{
	int i=0;
	if (l == NULL || l->next == NULL||index<1) { return ERROR; }
	while (l->next && i < index) {
		l = l->next;
		i++;
	}
	if (i == index) {
		*e = l->data;
	}
	return ERROR;

}

Status ListInsert(dulinklist l, int i, ElemType e)
{
	dulinklist inserted;
	int index = 0;
	int length = Listlength(l);
	if ((l == NULL) || (i > length+1) || (i <= 0)) {
		return ERROR;
	}
	while((l->next != NULL )&&(index<i-1)) {
		l = l->next;
		index++;
	}
	inserted = (dulinklist)malloc(sizeof(dulnode));
	inserted->data = e;
	inserted->next = l->next;
	inserted->prior = l;
	if (l->next)
	{
		l->next->prior = inserted;
	}
	l->next = inserted;
	return OK;
	
}

Status ListDelete(dulinklist l, int i) {
	int length = Listlength(l);
	int index = 0;

	if (i <= 0 || (i > length) || (l == NULL) || (l->next == NULL))
	{
		return ERROR;
	}
	while (l->next && index < i)
	{
		l = l->next;
		index++;
	}
	l->prior->next = l->next;
	if (l->next) {
		l->next->prior = l->prior;
	}
	free(l);
	return OK;
}

void ListClear(dulinklist* l)
{
	dulinklist p = *l;
	while (p->next) {
		p = p->next;
		free(p->prior);
	}
	free(p);
	*l = NULL;
}

void print(dulinklist l)
{
	int index = 0;
	while (l->next) {
		l = l->next;
		if (index > 0) printf("->");
		printf("%d", l->data);
		index++;
	}
	printf("\n");
}

int algorithm003()
{
	ElemType e;
	int index;
	dulinklist l;
	printf("请输入节点数据，输入-1为终止\n");
	l = InitList();
	printf("双链表的长度：%d\n", Listlength(l));
	print(l);
	printf("请输入想要知道的第几个位置：");
	scanf("%d", &index);
	GetElemByIndex(l, index, &e);
	printf("该位置上的数为：%d\n", e);
	printf("请输入想知道链表是否存在该元素的值：");
	scanf("%d", &e);
	GetElem(l, e);

	printf("请输入你想在第几个位置插入元素:");
	scanf("%d", &index);
	printf("请输入你想插入元素的值:");
	scanf("%d", &e);
	ListInsert(l, index, e);
	print(l);

	printf("输入你想删除的节点位置：");
	scanf("%d", &index);
	ListDelete(l, index);
	print(l);
	ListClear(&l);
	printf("双链表的长度：%d\n", Listlength(l));
	print(l);

	return 0;
}