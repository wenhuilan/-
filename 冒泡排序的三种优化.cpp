#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//��һ���Ż���ʽ������flag�ж�������ж����Ѿ��ź�
void bubble1(int num[], int size)
{
    int i, k, temp, flag;
    flag = size - 1;
 
    while(flag > 0)
    {
        k = flag;//��ʼ��Ϊsize-1���Ժ�ÿһ��ȡ��flag
        flag = 0;//ÿһ��flag����Ϊ0
 
        for(i = 0; i < k; i++)
        {
            if(num[i] > num[i+1])
            {
                temp = num[i];
                num[i] = num[i+1];
                num[i+1] = temp;
                flag = i;//i���յ�ֵΪ���������±�
            }
        }
    }
}



//˫��ð��-�ڶ����Ż���ʽΪͬʱ�����ϸ����³�
void bubble2(int num[], int size)
{
    int i, j, k, temp, flag;
 
    for(i = 0; i < size / 2; i++)//��Ϊ˫��ͬʱ���У�����ֻ��Ҫsize/2�δ�ѭ��
    {
        flag = 0;
        for(j = 0; j < size - i - 1; j++)//��ǰ������
        {
            if(num[j] > num[j+1])
            {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                flag = 1;
            }
        }
        for(k = size - 1 - i; k > 0; k--)//�Ӻ���ǰ��
        {
            if(num[k] < num[k-1])
            {
                temp = num[k];
                num[k] = num[k-1];
                num[k-1] = temp;
                flag = 1;
            }
        }
 
        if(!flag)
        {
            break;
        }
    }
}


//������-����flag��˫��ð��
void bubble3(int num[], int size)
{
    int i, j, k, up, down, temp, flag;
    up = size - 1;
    down = 0;
    for(i = size - 1; i > 0; i--)//��ǰ������
    {
        for(j = down; j < up; j++)
        {
            if(num[j] > num[j+1])
            {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                flag = j;//ȡ����ǰ������±꣬���±�֮��������Ѿ��ź���
            }
        }
 
            if(flag == -1)
            {
                break;
            }
            up = flag;//ȡ��flag��ֵ
            flag = -1;//����flag
 
            for(k = up; k > down; k--)
            {
                if(num[k] < num[k-1])
                {
                    temp = num[k];
                    num[k] = num[k-1];
                    num[k-1] = temp;
                    flag = k;//ȡ���Ӻ���ǰ���±꣬���±�֮ǰ�������Ѿ��ź���
                }
            }
 
            if(flag == -1)
            {
                break;
            }
            down = flag;//ȡ��flag��ֵ
            flag = -1;//����flag
    }
}


int main()
{
     int MAX=10;
	 int a[20];
	    //�������
		    srand(time(NULL));
		    for(int i=0; i<20; i++)
		    {
		        a[i]=rand()%MAX;
		    }
	    printf("\n");
	    bubble3(a,20);
	    printf("����������Ż����������������\n");
	    for(int i=0;i<20;i++)
	    printf("%d ",a[i]);
	     return 0;
	    
}
