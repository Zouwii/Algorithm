#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "algorithm.h"

typedef struct dulnode {
	struct dulnode* prior;
	ElemType data;
	struct dulnode* next;
}dulnode,*dulinklist;

dulinklist InitList(); //��ʼ��
int Listlength(dulinklist l); //����
int GetElem(dulinklist l, ElemType e); //��ȡԪ��λ��
int GetElemByIndex(dulinklist l, int index, ElemType* e); //��ȡָ��Ԫ��
Status ListInsert(dulinklist l, int i, ElemType e); //���Ԫ��
Status ListDelete(dulinklist l, int i); //ɾ��Ԫ��
void ListClear(dulinklist* l); //��ձ�
void print(dulinklist l); //�����

dulinklist InitList() {
	int data,size;
	dulinklist l, last,p;
	l = (dulinklist)malloc(sizeof(dulnode));
	l->prior = NULL;
	l->next = NULL;
	last = l;
	printf("������ڵ�ֵ����-1��ʾ������ɣ���\n");
	size = 0;
	printf("��ǰ����Ĵ�С��%d\n",size);
	while (true)
	{
		if (scanf("%d", &data) != 1)break;
		if (data == -1) break;
		p = (dulinklist)malloc(sizeof(dulnode));
		if (p == NULL) {
			printf("�ڴ治�㣬��ֹ������\n");
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
			printf("�ҵ�һ���ڵ㣬λ���ڣ�%d\n", index);
			found = 1;
		}
		
		l = l->next;
		index++;
	} while (l);
	if (found == 0)
	{
		printf("ָ��ֵ�Ľڵ㣬һ��Ҳû�ҵ���\n");
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
	printf("������ڵ����ݣ�����-1Ϊ��ֹ\n");
	l = InitList();
	printf("˫����ĳ��ȣ�%d\n", Listlength(l));
	print(l);
	printf("��������Ҫ֪���ĵڼ���λ�ã�");
	scanf("%d", &index);
	GetElemByIndex(l, index, &e);
	printf("��λ���ϵ���Ϊ��%d\n", e);
	printf("��������֪�������Ƿ���ڸ�Ԫ�ص�ֵ��");
	scanf("%d", &e);
	GetElem(l, e);

	printf("�����������ڵڼ���λ�ò���Ԫ��:");
	scanf("%d", &index);
	printf("�������������Ԫ�ص�ֵ:");
	scanf("%d", &e);
	ListInsert(l, index, e);
	print(l);

	printf("��������ɾ���Ľڵ�λ�ã�");
	scanf("%d", &index);
	ListDelete(l, index);
	print(l);
	ListClear(&l);
	printf("˫����ĳ��ȣ�%d\n", Listlength(l));
	print(l);

	return 0;
}