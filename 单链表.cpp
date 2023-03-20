#include<stdio.h> 
#include<stdlib.h>     //c��׼���ͷ�ļ� 
#include<malloc.h>     //�ڴ����ͷ�ļ� 
# define LEN sizeof(struct Student)
struct Student {
	long num;
	float score;
	struct Student *next;
};
int n;//������ 


void showMenu() 
{
  printf("----------������Ĺ���----------\n\n");
  printf("ϵͳ�ṩ���¹��ܣ�\n");
  printf("1:����\n");
  printf("2:ɾ��\n");
  printf("3:����\n");
  printf("4:����\n");
  printf("5:��ż����\n");
  printf("6:�ҵ��н��\n");
  printf("7:�ж������Ƿ�ɻ�\n");
  printf("8:��ת����\n");
  printf("0:�˳�ϵͳ\n\n");
}


//����������� creat
struct Student *creat(void) 
{
	struct Student*head;
	struct Student *p1,*p2;
	n=0;
	p1=p2=(struct Student *)malloc(LEN);//�����µ�Ԫ 
	printf("����ѧ��,����\n"); 
	scanf("%ld,%f",&p1->num,&p1->score);
	head=NULL;
	while(p1->num!=0)
	{
		n=n+1;
		if(n==1)head=p1;
		else p2->next=p1;
		p2=p1;//ʹ��һ�� ����Ԫ�ظ���ͷ��� 
		p1=(struct Student *)malloc(LEN);
		scanf("%ld,%f",&p1->num,&p1->score);//�ظ���������������� 
	}
	p2->next=NULL;
	return(head);//����������ʼ��ַ 
}


//�������print
void print(struct Student *head)
{
	struct Student*p;
	printf("\nNow,These %d records are:\n",n);
	p=head;
	if(head!=NULL)
	{
		do{
			printf("%ld %5.1f\n",p->num,p->score);
			p=p->next;
		}while(p!=NULL);
	}
	printf("\n");
}

//�����½�� 
void insert(struct Student *head) //iָ�������λ�� 
{
//	1���ж������Ƿ�Ϊ�գ���Ϊ�գ��ܾ����� 
if(!head) return ;
int i;
printf("�����λ�ã�"); 
scanf("%d",&i);
//  2�� �������� ���ҵ������λ��
struct Student *p = head;
for(int j=1;j<i-1&&p->next!=NULL;j++)      //��ֹ������Χ 
{
	p=p->next;
}
struct Student *p3;
p3=(struct Student *)malloc(LEN);   //�����µĽ�� 
printf("�²����ѧ�š�����:");
scanf("%ld,%f",&p3->num,&p3->score);
printf("\n");
//�����½�� 
p3->next=p->next;        
p->next=p3;
printf("�����½���ĵ�����");
}


//ɾ�����
void delet(struct Student *head) //iָ��ɾ����λ�� 
{
//	1���ж������Ƿ�Ϊ�գ���Ϊ�գ��ܾ����� 
if(!head) return ;
        int i;
    printf("ɾ����λ��: ");
      scanf("%d",&i);
      if(i<=0) return;
//  2�� �������� ���ҵ�ɾ����λ��
struct Student *p = head;
struct Student *q; 
for(int j=1;j<i-1&&p->next!=NULL;j++)      
{
	p=p->next;
}
//3��ɾ���ҵ��Ľ�� 
   if(!p) return;
    q=p->next;
   p->next=q->next;
      free(q);
printf("ɾ��ĳ����ĵ�����");
}


//�޸�
void revis(struct Student *head)
{
	struct Student *p=head;
	struct Student *q;
	printf("������Ҫ�޸ĵ�ѧ��ѧ��:");
	scanf("%ld",&q->num);
	while(p!=NULL)
	{
		if(p->num==q->num)
		{
			int nu;
			float scor;
			printf("�޸ĺ����ѧ�ź��·���Ϊ��");
			scanf("%ld,%5.1f",&nu,&scor) ;
			p->num=nu;
			p->score=scor;
			break;
		}
		else p=p->next;
	}
	if(p==NULL) printf("Ҫ�޸ĵĵ����ݲ����ڣ��������޸�");
	else {
		p=head;
		printf("�޸ĳɹ����޸ĺ������Ϊ��\n");
		print(p);
	}
		
		
}


//����
void checkstu(struct Student *head)
{
	//�жϲ��ҵ������Ƿ�Ϊ�� 
	if(!head) return;
	//�����������ҵ��Ƿ���ͬ�Ľ��
	struct Student *p=head; 
	int i,j=1;
	printf("��������Ҫ���ҵĽ��λ��:"); 
	scanf("%d",&i);
	while(p->next&&j<i){
		p=p->next;
		j++;
	}
	if(!p)
	printf("��%d��Ԫ�ز�����\n",i);
	else if(j==i)
	printf("���ҵ�ѧ�źͷ���Ϊ:%ld,%5.1f\n",p->num,p->score);
	printf("\n");
}


//��ż����
void swap(struct Student *head)
{
	struct Student *q1=head;
	struct Student *q2=head->next;
	//�ȵ������1��2��λ�� 
	head=q2;
	q1->next=q2->next;
	q2->next=q1;
	//q1��������Ϊż����ѭ����q�����q1��λ�� 
	struct Student *q;
	q=q1;
	for(int k=1;k<=(n/2)-1;k++)
	{
		q1=q->next;
		q2=q1->next;
		
		q->next=q2;
		q1->next=q2->next;
		q2->next=q1;
		
		q=q1;
	}
	q=head;
	printf("��ż�����������λ��Ϊ��\n");
	//�����ż����λ��֮������� 
	while(q!=NULL)
	{
		printf("%ld %5.1f\n",q->num,q->score);
		q=q->next;
	}	
}


//ʹ��˫ָ�룬һ����ָ�룬һ����ָ�룬�ҵ���������е��� 
void middlenode(struct Student *head) 
{
	struct Student *fast=head;
	struct Student *slow=head;
	fast=fast->next->next; 
	while(fast!=NULL&&fast->next!=NULL)
	{
		slow=slow->next;        //��ָ��һ����һ�� 
		fast=fast->next->next;   //��ָ��һ�������� 	
	}
	if(n%2==1)
	{
		printf("����н�������Ԫ��Ϊ:\n");
		printf("ѧ�š�������%ld,%5.1f\n",slow->next->num,slow->next->score);
	}
	else if(n%2==0)
	{
		printf("��������н�������Ԫ��Ϊ:\n");
		printf("ѧ�š�������%ld,%5.1f\n",slow->num,slow->score);
		printf("ѧ�š�������%ld,%5.1f\n",slow->next->num,slow->next->score);
	}
	
}


//�ж������Ƿ�ɻ�
 void hascircular(struct Student *head)
 {
 	int x;//xΪ1����ʾ�ɻ���xΪ0����ʾ���ɻ� 
 	if(head==NULL)
 	x=0;
 	if(head->next==NULL)
 	x=0;
 	struct Student *fast=head;
	struct Student *slow=head;
	 
	while(fast!=NULL)
	{
	slow=slow->next;      
	fast=fast->next->next;  
	if(fast==slow) x=1;
	else x=0;
	}
	if(x==1)
	printf("������ɻ���\n");
	else if(x==0)
	printf("�������ɻ�!\n");
	
 }



//��ת����
void reverselist(struct Student *head)
{
	struct Student *p=head;
	struct Student *q=NULL;
//	if(head==NULL||head->next==NULL) return *head; 
	while(p != NULL)
     {
          struct Student *pnext = p->next;
          p->next = q;
          q = p;
          p = pnext;
     }
   
     printf("��ת�����������Ϊ��\n");
     while(q!=NULL)
	{
		printf("%ld %5.1f\n",q->num,q->score);
		q=q->next;
	}	
     
}



int main() 
{  
struct Student *pt;
	pt=creat();
	printf("������n:%d\n",n);
  showMenu();     // ��ʾ�������˵� 
  char a[10];
  while(1)
  {
  printf("������0-8���س�����!\n");
  int temp=getchar();
  if(temp!='\n')
  {
  
   switch (temp)
	  {
      case '0':    // �˳����� 
        printf("ByeBye,�´��ټ�!\n");
        exit(0);
        
      case '1':    //���Ӳ��� 
	       insert(pt);
	       print(pt);     
            break;
            
      case '2':    //ɾ��   
          delet(pt);
	      print(pt);     
          break;
        
      case '3':     //���� 
        revis(pt);
        break;
        
      case '4':     //���� 
        checkstu(pt);
        break;
      case '5':   //��ż����
	      swap(pt);
	      break;
	  case '6':    //�ҵ���������е� 
           middlenode(pt);
           break;
      case '7':   //�ж������Ƿ�ɻ� 
         hascircular(pt);
           break;
      
      case '8':   //��ת����
      reverselist(pt);
           break;
        default:
		  printf("input error!\n");
	}
}
else {
   if (fgets(a, 1024, stdin) != NULL) 
	{  // ���ж�ȡ��0-8�ַ���ʾ����
	  switch (a[0])
	  {
      case '0':    // �˳����� 
        printf("ByeBye,�´��ټ�!\n");
        exit(0);
        
      case '1':    //���Ӳ��� 
	       insert(pt);
	       print(pt);     
            break;
            
      case '2':    //ɾ��   
          delet(pt);
	      print(pt);     
          break;
        
      case '3':     //���� 
        revis(pt);
        break;
        
      case '4':     //���� 
        checkstu(pt);
        break;
      case '5':   //��ż����
	      swap(pt);
	      break;
	  case '6':    //�ҵ���������е� 
           middlenode(pt);
           break;
      case '7':   //�ж������Ƿ�ɻ� 
          hascircular(pt);
           break;
      case '8':   //��ת����
      reverselist(pt);
           break;
        default:
		  printf("input error!\n");
		  	  
       }
    }
 }
}
 return 0;
}
	
	

