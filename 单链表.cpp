#include<stdio.h> 
#include<stdlib.h>     //c标准库的头文件 
#include<malloc.h>     //内存分配头文件 
# define LEN sizeof(struct Student)
struct Student {
	long num;
	float score;
	struct Student *next;
};
int n;//结点个数 


void showMenu() 
{
  printf("----------单链表的功能----------\n\n");
  printf("系统提供以下功能：\n");
  printf("1:插入\n");
  printf("2:删除\n");
  printf("3:更改\n");
  printf("4:查找\n");
  printf("5:奇偶互换\n");
  printf("6:找到中结点\n");
  printf("7:判断链表是否成环\n");
  printf("8:反转链表\n");
  printf("0:退出系统\n\n");
}


//建立链表过程 creat
struct Student *creat(void) 
{
	struct Student*head;
	struct Student *p1,*p2;
	n=0;
	p1=p2=(struct Student *)malloc(LEN);//开辟新单元 
	printf("输入学号,分数\n"); 
	scanf("%ld,%f",&p1->num,&p1->score);
	head=NULL;
	while(p1->num!=0)
	{
		n=n+1;
		if(n==1)head=p1;
		else p2->next=p1;
		p2=p1;//使第一个 数据元素赋给头结点 
		p1=(struct Student *)malloc(LEN);
		scanf("%ld,%f",&p1->num,&p1->score);//重复建立多个结点的链表 
	}
	p2->next=NULL;
	return(head);//返回链表起始地址 
}


//输出链表print
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

//插入新结点 
void insert(struct Student *head) //i指定插入的位置 
{
//	1、判断链表是否为空，若为空，拒绝插入 
if(!head) return ;
int i;
printf("插入的位置："); 
scanf("%d",&i);
//  2、 遍历链表 ，找到插入的位置
struct Student *p = head;
for(int j=1;j<i-1&&p->next!=NULL;j++)      //防止超过范围 
{
	p=p->next;
}
struct Student *p3;
p3=(struct Student *)malloc(LEN);   //申请新的结点 
printf("新插入的学号、分数:");
scanf("%ld,%f",&p3->num,&p3->score);
printf("\n");
//插入新结点 
p3->next=p->next;        
p->next=p3;
printf("插入新结点后的单链表");
}


//删除结点
void delet(struct Student *head) //i指定删除的位置 
{
//	1、判断链表是否为空，若为空，拒绝插入 
if(!head) return ;
        int i;
    printf("删除的位置: ");
      scanf("%d",&i);
      if(i<=0) return;
//  2、 遍历链表 ，找到删除的位置
struct Student *p = head;
struct Student *q; 
for(int j=1;j<i-1&&p->next!=NULL;j++)      
{
	p=p->next;
}
//3、删除找到的结点 
   if(!p) return;
    q=p->next;
   p->next=q->next;
      free(q);
printf("删掉某结点后的单链表");
}


//修改
void revis(struct Student *head)
{
	struct Student *p=head;
	struct Student *q;
	printf("输入需要修改的学生学号:");
	scanf("%ld",&q->num);
	while(p!=NULL)
	{
		if(p->num==q->num)
		{
			int nu;
			float scor;
			printf("修改后的新学号和新分数为：");
			scanf("%ld,%5.1f",&nu,&scor) ;
			p->num=nu;
			p->score=scor;
			break;
		}
		else p=p->next;
	}
	if(p==NULL) printf("要修改的的数据不存在，请重新修改");
	else {
		p=head;
		printf("修改成功！修改后的数据为：\n");
		print(p);
	}
		
		
}


//查找
void checkstu(struct Student *head)
{
	//判断查找的链表是否为空 
	if(!head) return;
	//遍历单链表，找到是否相同的结点
	struct Student *p=head; 
	int i,j=1;
	printf("请输入需要查找的结点位置:"); 
	scanf("%d",&i);
	while(p->next&&j<i){
		p=p->next;
		j++;
	}
	if(!p)
	printf("第%d个元素不存在\n",i);
	else if(j==i)
	printf("查找的学号和分数为:%ld,%5.1f\n",p->num,p->score);
	printf("\n");
}


//奇偶互换
void swap(struct Student *head)
{
	struct Student *q1=head;
	struct Student *q2=head->next;
	//先调换结点1，2的位置 
	head=q2;
	q1->next=q2->next;
	q2->next=q1;
	//q1从奇数变为偶数后，循环用q来标记q1的位置 
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
	printf("奇偶调换后的数据位置为：\n");
	//输出奇偶交换位置之后的数据 
	while(q!=NULL)
	{
		printf("%ld %5.1f\n",q->num,q->score);
		q=q->next;
	}	
}


//使用双指针，一个快指针，一个慢指针，找到单链表的中点结点 
void middlenode(struct Student *head) 
{
	struct Student *fast=head;
	struct Student *slow=head;
	fast=fast->next->next; 
	while(fast!=NULL&&fast->next!=NULL)
	{
		slow=slow->next;        //慢指针一次走一步 
		fast=fast->next->next;   //快指针一次走两步 	
	}
	if(n%2==1)
	{
		printf("输出中结点的数据元素为:\n");
		printf("学号、分数：%ld,%5.1f\n",slow->next->num,slow->next->score);
	}
	else if(n%2==0)
	{
		printf("输出两个中结点的数据元素为:\n");
		printf("学号、分数：%ld,%5.1f\n",slow->num,slow->score);
		printf("学号、分数：%ld,%5.1f\n",slow->next->num,slow->next->score);
	}
	
}


//判断链表是否成环
 void hascircular(struct Student *head)
 {
 	int x;//x为1，表示成环，x为0，表示不成环 
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
	printf("此链表成环！\n");
	else if(x==0)
	printf("此链表不成环!\n");
	
 }



//反转链表
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
   
     printf("反转后的数据排序为：\n");
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
	printf("结点个数n:%d\n",n);
  showMenu();     // 显示功能主菜单 
  char a[10];
  while(1)
  {
  printf("请输入0-8，回车结束!\n");
  int temp=getchar();
  if(temp!='\n')
  {
  
   switch (temp)
	  {
      case '0':    // 退出程序 
        printf("ByeBye,下次再见!\n");
        exit(0);
        
      case '1':    //增加插入 
	       insert(pt);
	       print(pt);     
            break;
            
      case '2':    //删除   
          delet(pt);
	      print(pt);     
          break;
        
      case '3':     //更改 
        revis(pt);
        break;
        
      case '4':     //查找 
        checkstu(pt);
        break;
      case '5':   //奇偶互换
	      swap(pt);
	      break;
	  case '6':    //找到单链表的中点 
           middlenode(pt);
           break;
      case '7':   //判断链表是否成环 
         hascircular(pt);
           break;
      
      case '8':   //反转链表
      reverselist(pt);
           break;
        default:
		  printf("input error!\n");
	}
}
else {
   if (fgets(a, 1024, stdin) != NULL) 
	{  // 按行读取，0-8字符表示功能
	  switch (a[0])
	  {
      case '0':    // 退出程序 
        printf("ByeBye,下次再见!\n");
        exit(0);
        
      case '1':    //增加插入 
	       insert(pt);
	       print(pt);     
            break;
            
      case '2':    //删除   
          delet(pt);
	      print(pt);     
          break;
        
      case '3':     //更改 
        revis(pt);
        break;
        
      case '4':     //查找 
        checkstu(pt);
        break;
      case '5':   //奇偶互换
	      swap(pt);
	      break;
	  case '6':    //找到单链表的中点 
           middlenode(pt);
           break;
      case '7':   //判断链表是否成环 
          hascircular(pt);
           break;
      case '8':   //反转链表
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
	
	

