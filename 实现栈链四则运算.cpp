#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct pnode
{
	//��ջ�ͳ�ջ����ջ������
    char data;//����
    struct pnode* next;//ָ��
}pnode;

typedef struct seqstack
{
    int size;//��¼ջ�Ĵ�С
    pnode* top;//ָ��ջ��Ԫ��
}phead;

//����ջ,��ʼ����ջ 
phead*  initstack()
{
    phead* p=(phead*)malloc(sizeof(phead));//Ϊͷ�ڵ����ռ�
    if(p!=NULL)
    {
        p->top=NULL;
        p->size=0;
    }
    return p;
}

//�ж�ջΪ��
int isempty(phead* p)
{
    if(p->top==NULL)
    {
        return 1;//ջΪ��
    }
    return 0;//ջ��Ϊ��
}

//��ȡջ��Ԫ�ص����ݽڵ�
pnode* seqstack_top(phead* p)
{
    if(p->size!=0)//ջ��Ϊ��
    {
        return p->top;//���ص���ջ�������ݽڵ������ջ����Ԫ��
    }
    return NULL;
}

//����ջ��Ԫ��
pnode* seqstack_pop(phead* p)
{
    if(isempty(p)==0)//ջ��Ϊ��
    {
        pnode* account=p->top;//��¼ջ�������ݽڵ�
        p->top=p->top->next;//ָ��ջ����һ��Ԫ��
        p->size--;//��¼ջ�Ĵ�С
        return account;//���ص��������ݽڵ�
    }
    return NULL;
}

//��ջ
void seqstack_push(phead* p,char x)
{
   pnode* temp;//������ջ�����ݽڵ�
   temp=(pnode*)malloc(sizeof(pnode));
   temp->data=x;//���������
   temp->next=p->top;//����ջ�������ݽڵ�
   p->top=temp;//�䵱ջ��
   p->size++;//��¼ջ��С�ı仯
   return;
}
 //��������׺���ʽת��׺���ʽ�ĺ���
 char buffer[256]={0};//����������ÿ�����ݶ���ʼ��Ϊ'\0'
 //bufferΪ�����
 void char_put(char ch)//�������ַ������������
 {
     static int index=0;//static���徲̬����,�ź����б�ʾindexֻ��ʼ��һ��,ֻ����index�ĸı�
     buffer[index++]=ch;
 }
 
 
 int priority(char ch)//�����Ƚ����ȼ�
 {
     int ret=0;
     switch(ch)
     {
        case '+'://case��͸,����һ��caseû��break���ʱ���������ִ��
        case '-':
            ret=1;
            break;
        case '*':
        case '/':
            ret=2;
            break;
        default:
            break;
     }
     return ret;
 }
 
 int is_number(char ch)//�ж�����
 {
     return(ch>='0'&&ch<='9');//���ַ���1�����򷵻�0
 }
 
 int is_operator(char ch)//������ж� 
 {
     return(ch=='+'||ch=='-'||ch=='*'||ch=='/');
 }
 
 int is_left(char ch)//�ж�������
 {
     return(ch=='(');
 }
 
 int is_right(char ch)//�ж�������
 {
     return(ch==')');
 }
 
 int transform(char str[])//ʹ��const��������,������������׺ת���ɺ�׺
 {
     phead* p=initstack();//����һ��ջ
     int i=0;
     while(str[i]!='\0')//���������ַ���
    {
        //�ж��ǲ�������
        if(is_number(str[i])==1)
        {
            if(is_number(str[i+1])==1)//����1Ҳ������,��ֱ�ӷ�
            {
                char_put(str[i]);//����ֱ�ӷ�������
            }
            else//���治������,���һ���ո���Ϊ�ָ���
            {
                char_put(str[i]);
                char_put(' ');
            }
        }
        else if(is_operator((str[i]))==1)
        {
            if(str[i+1]=='0'&&str[i]=='/')  //������ĸ����Ϊ0 
            {
                printf("illegal��");
                return 0;
            }
            if(isempty(p)==0)//ջ��Ϊ��
            {
                while((isempty(p)==0)&&(priority(str[i])<=(priority(seqstack_top(p)->data))))//ջ��Ϊ�ղ�������������ȼ�С�ڵ��� ջ��
                {
                    char_put(seqstack_pop(p)->data);//����������ջ���͵�����ֱ������������
                    char_put(' ');
                }
            }
            //�ٽ����������ջ
            seqstack_push(p,str[i]);
        }
        else if(is_left(str[i]))//������ֱ����ջ
        {
            seqstack_push(p,str[i]);
        }
        else if(is_right(str[i]))//�ж��ǲ���������
        {
            while(is_left(seqstack_top(p)->data)!=1)//ջ�����������ŵ����
            {
                char_put(seqstack_pop(p)->data);//�������洢�������
                if(isempty(p)==1)//ջΪ����δ�ҵ�������
                {
                    printf("û��ƥ�䵽������\n");
                    return -1;
                }
            }
            //��ʱƥ�䵽��������
            seqstack_pop(p);
            //����������,���ﲢ���ñ���,���������������
        }
        else
        {
            printf("�в���ʶ����ַ�\n");
            return -1;
        }
        i++;//���� 
    }

    //��������
    if(str[i]=='\0')//�ɹ��������ַ���ĩβ
    {
        while(isempty(p)==0)//����ȫ��ջ��Ԫ��
        {
            if(seqstack_top(p)->data=='(')//ջ��Ԫ��Ϊ������
            {
                printf("��û��ƥ�䵽��'(',ȱ��')'\n");
                return -1;
            }
            char_put(seqstack_pop(p)->data);//��ջ��Ԫ�ط������մ�
        }
    }
    else
    {
        printf("����û����ɣ�\n");
    }
    return 1;
 }

 //�����׺���ʽ�ĺ���
 //��ǰ������ 
 typedef struct node1
{
    int pdata;//����
    struct node1* next;//ָ��
}pnode1;

typedef struct seqstack1
{
    int size;//��¼ջ�Ĵ�С
    pnode1* top;//ָ��ջ��Ԫ��
}phead1;

phead1*  initstack1()//����ջ,��ʼ����ջ 
{
	//Ϊͷ�ڵ����ռ�
    phead1* p=(phead1*)malloc(sizeof(phead1));
    if(p!=NULL)
    {
        p->top=NULL;
        p->size=0;
    }
    return p;
}

//�ж�ջΪ��
int isempty1(phead1* p)
{
    if(p->top==NULL)
    {
        return 1;//ջΪ��
    }
    return 0;//ջ��Ϊ��
}

//��ȡջ��Ԫ��
int seqstack_top1(phead1* p)
{
    if(p->size!=0)//ջ��Ϊ��
    {
    	//���ص���ջ��������
        return p->top->pdata;
    }
    return 0;
}

int seqstack_pop1(phead1* p)//����ջ��Ԫ��
{
    if(isempty1(p)==0)//ջ��Ϊ��
    {
        int account=p->top->pdata;//��¼ջ�������ݽڵ�
        p->top=p->top->next;//ָ��ջ����һ��Ԫ��
        p->size--;//��¼ջ�Ĵ�С
        return account;//���ص��������ݽڵ�
    }
   return 0;
}

void seqstack_push1(phead1* p,int x)//��ջ
{
   pnode1* temp;//����ѹջ�����ݽڵ�
   temp=(pnode1*)malloc(sizeof(pnode1));
   temp->pdata=x;//���������
   temp->next=p->top;//����ջ�������ݽڵ�
   p->top=temp;//�䵱ջ��
   p->size++;//��¼ջ��С�ı仯
   return;
}

 int express(int left,int right,char op)
 //opΪ�����,����������
 {
     switch (op)
     {
        case '+':
            return left+right;
        case '-':
            return left-right;
        case '*':
            return left*right;
        case '/':
            if(right==0)
            {
                return 999;
            }
            return left/right;
        default:
            break;
     }
     return -1;
 }
 
 
 int getsize(phead1* stack)
 {
     return stack->size;
 }
 
 
 int calculate(char str[])//�����׺���ʽ
 {
     phead1* p2=initstack1();//����ջ
     int i=0;
     while(str[i]!='\0')//����������׺���ʽ
    {
        char a[6]={0};
        int index=0;
        if(is_number(str[i])==1)
        {
            while(is_number(str[i])==1)
            {
                a[index]=str[i];
                index++;
                i++;
            }
            
            //�ɹ���ȡ����
            seqstack_push1(p2,atoi(a));//����������ջ
        }
        else if(is_operator(str[i])==1)
        {
            int right=seqstack_pop1(p2);
            int left=seqstack_pop1(p2);
            int ret=express(left,right,str[i]);
            if(ret==999)//������Ϊ0��
            {
                printf("ILLEGAL");
                return 999;
            }
            seqstack_push1(p2,ret);//��������ջ
        }
        else if(str[i]==' ')
        {
 
        }
        else
        {
            printf("error\n");
            break;
        }
        i++;
    }
    if(str[i]=='\0'&&getsize(p2))
    {
        return seqstack_top1(p2);
    }
    return 0;
 }
 
int main()
{
    char str[1024]={0};//������ÿ��Ԫ�ظ�ֵΪ'\0'
    printf("����������������ʽ:\n");
    scanf("%s",str);
    int number=transform(str);
    if(number==-1)
    {
        printf("���ʽת������:\n");
    }
    else if(number==1)
    {
        printf("ת����ı��ʽ: %s\n",buffer);
    }
    else
    {
        return 0;
    }
 
    //�·������׺���ʽ
    int num=calculate(buffer);
    if(num==999)
    {
        return 0;
    }
    printf("%d\n",num);
}
 
