#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TURE 1
#define FALSE 0
 
typedef int Status;
typedef int ElemType;
 
//结点的结构
typedef struct QNode
{
	ElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

//队列的链式存储
typedef struct
{
	QueuePtr front;//队头
	QueuePtr rear;//队尾
}LinkQueue;
 
//初始化，构造 
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		return ERROR;
	Q->front->next = NULL;
	return OK;
}
 
//销毁
Status DesQueue(LinkQueue* Q)
{
	while (Q->front)//从队头开始销毁
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}
 
//判断队列是否为空
Status EmptyQueue(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TURE;
	else
		return FALSE;
}
 
//取队列长度
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
 
 //清空
 Status ClearQueue(LinkQueue *Q)

 {
 	Q->rear=(Q->front)->next;
 	while(Q->front->next){
 		Q->rear=Q->rear->next;//队尾指针后移 
 		free(Q->front->next);//释放队头指针和队尾指针中间的结点
		 
 		Q->front->next=Q->rear;//连接队列 
	 }
	 Q->rear=Q->front;
	 printf("清空成功！"); 
	 
 }
 
 //判满
void IsFullQueue(LinkQueue *Q) 
{
	if(Q->rear+1==Q->front)
	{
		printf("队列已满！\n"); 
	}
	else printf("队列未满!\n"); 
}
 
//获取队头元素
int GetHead(LinkQueue Q, ElemType* e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	*e = p->data;
	return *e;
}
 
//入队，队尾插入 
Status InQueue(LinkQueue* Q, ElemType e)
{
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));//分配空间
	if (!s)//分配失败
		return ERROR;
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;//原来队尾的下一个指向s
	Q->rear = s;//新的队尾为s
	return OK;
}
 
//出队 
Status DeQueue(LinkQueue* Q, ElemType* e)
{
	if (Q->front == Q->rear)//如果队列为空
		return ERROR;
	QueuePtr p;
	p = Q->front->next;//让p指向队头元素
	*e = p->data;//用e存储队头元素
	Q->front->next = p->next;//新的队头元素为原队头元素的下一个
	if (Q->rear == p)//如果队头=队尾
		Q->rear = Q->front;//让队尾指向头结点
	free(p);//释放p
	return OK;
}
 
//遍历输出 
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
 
	printf("请输入队列中的元素个数:\n");
	scanf("%d", &n);
	printf("请依次输入队列中的元素:\n");
	for (i = 0;i < n;i++)
	{
		scanf("%d", &a[i]);
	}
	for (j = 0;j < n;j++)
	{
		InQueue(&q, a[j]);
	}
 
	printf("当前队列是否为空\n");
	if (EmptyQueue(q) == 1)
		printf("空\n");
	else
		printf("不空\n");
 
	printf("当前队列长度为：");
	printf("%d\n", LengthQueue(q));
 
	printf("当前队列的队头元素为：");
	printf("%d\n", GetHead(q,&d));
 
	printf("现在队列中的元素:\n");
	PrintQueue(q);
    printf("队列是否已满:");
    IsFullQueue(&q);
	ElemType m;
	printf("请输入你要在队尾插入的数：\n");
	scanf("%d", &m);
	InQueue(&q,m);
	printf("遍历输出现在队列中的元素为:\n");
	PrintQueue(q);
 
	printf("出队：删除队头元素\n");
	m=DeQueue(&q,&m);
	printf("删除的元素为:%d\n", m);
	printf("现在队列中的元素为:\n");
	PrintQueue(q);
     printf("清空后队列中元素为：\n");
     ClearQueue(&q);
     PrintQueue(q);
	DesQueue(&q);
	printf("队列销毁\n");
 getchar();
	return 0;
}
