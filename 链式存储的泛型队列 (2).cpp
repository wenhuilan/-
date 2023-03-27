#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TURE 1
#define FALSE 0
 
typedef int Status;
typedef int ElemType;
 
//���Ľṹ
typedef struct QNode
{
	ElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

//���е���ʽ�洢
typedef struct
{
	QueuePtr front;//��ͷ
	QueuePtr rear;//��β
}LinkQueue;
 
//��ʼ�������� 
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		return ERROR;
	Q->front->next = NULL;
	return OK;
}
 
//����
Status DesQueue(LinkQueue* Q)
{
	while (Q->front)//�Ӷ�ͷ��ʼ����
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}
 
//�ж϶����Ƿ�Ϊ��
Status EmptyQueue(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TURE;
	else
		return FALSE;
}
 
//ȡ���г���
int LengthQueue(LinkQueue Q)
{
	int i = 0;
	QueuePtr p = Q.front;
	while (p != Q.rear)
	{
		i++;
		p = p->next;
	}
	return i;
}
 
 //���
 Status ClearQueue(LinkQueue *Q)

 {
 	Q->rear=(Q->front)->next;
 	while(Q->front->next){
 		Q->rear=Q->rear->next;//��βָ����� 
 		free(Q->front->next);//�ͷŶ�ͷָ��Ͷ�βָ���м�Ľ��
		 
 		Q->front->next=Q->rear;//���Ӷ��� 
	 }
	 Q->rear=Q->front;
	 printf("��ճɹ���"); 
	 
 }
 
 //����
void IsFullQueue(LinkQueue *Q) 
{
	if(Q->rear+1==Q->front)
	{
		printf("����������\n"); 
	}
	else printf("����δ��!\n"); 
}
 
//��ȡ��ͷԪ��
int GetHead(LinkQueue Q, ElemType* e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	*e = p->data;
	return *e;
}
 
//��ӣ���β���� 
Status InQueue(LinkQueue* Q, ElemType e)
{
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));//����ռ�
	if (!s)//����ʧ��
		return ERROR;
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;//ԭ����β����һ��ָ��s
	Q->rear = s;//�µĶ�βΪs
	return OK;
}
 
//���� 
Status DeQueue(LinkQueue* Q, ElemType* e)
{
	if (Q->front == Q->rear)//�������Ϊ��
		return ERROR;
	QueuePtr p;
	p = Q->front->next;//��pָ���ͷԪ��
	*e = p->data;//��e�洢��ͷԪ��
	Q->front->next = p->next;//�µĶ�ͷԪ��Ϊԭ��ͷԪ�ص���һ��
	if (Q->rear == p)//�����ͷ=��β
		Q->rear = Q->front;//�ö�βָ��ͷ���
	free(p);//�ͷ�p
	return OK;
}
 
//������� 
Status PrintQueue(LinkQueue Q)
{
	QueuePtr p;
	p = Q.front->next;
	while (p)
	{
		printf("%5d", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}
 
int main()
{
	int i, j, n,a[10];
	ElemType d;
	LinkQueue q;
	i = InitQueue(&q);
 
	printf("����������е�Ԫ�ظ���:\n");
	scanf("%d", &n);
	printf("��������������е�Ԫ��:\n");
	for (i = 0;i < n;i++)
	{
		scanf("%d", &a[i]);
	}
	for (j = 0;j < n;j++)
	{
		InQueue(&q, a[j]);
	}
 
	printf("��ǰ�����Ƿ�Ϊ��\n");
	if (EmptyQueue(q) == 1)
		printf("��\n");
	else
		printf("����\n");
 
	printf("��ǰ���г���Ϊ��");
	printf("%d\n", LengthQueue(q));
 
	printf("��ǰ���еĶ�ͷԪ��Ϊ��");
	printf("%d\n", GetHead(q,&d));
 
	printf("���ڶ����е�Ԫ��:\n");
	PrintQueue(q);
    printf("�����Ƿ�����:");
    IsFullQueue(&q);
	ElemType m;
	printf("��������Ҫ�ڶ�β���������\n");
	scanf("%d", &m);
	InQueue(&q,m);
	printf("����������ڶ����е�Ԫ��Ϊ:\n");
	PrintQueue(q);
 
	printf("���ӣ�ɾ����ͷԪ��\n");
	m=DeQueue(&q,&m);
	printf("ɾ����Ԫ��Ϊ:%d\n", m);
	printf("���ڶ����е�Ԫ��Ϊ:\n");
	PrintQueue(q);
     printf("��պ������Ԫ��Ϊ��\n");
     ClearQueue(&q);
     PrintQueue(q);
	DesQueue(&q);
	printf("��������\n");
 getchar();
	return 0;
}
