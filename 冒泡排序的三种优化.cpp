#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//第一种优化方式，加入flag判断最大数有多少已经排好
void bubble1(int num[], int size)
{
    int i, k, temp, flag;
    flag = size - 1;
 
    while(flag > 0)
    {
        k = flag;//初始化为size-1，以后每一次取出flag
        flag = 0;//每一次flag重置为0
 
        for(i = 0; i < k; i++)
        {
            if(num[i] > num[i+1])
            {
                temp = num[i];
                num[i] = num[i+1];
                num[i+1] = temp;
                flag = i;//i最终的值为最后被排序的下标
            }
        }
    }
}



//双向冒泡-第二种优化方式为同时进行上浮和下沉
void bubble2(int num[], int size)
{
    int i, j, k, temp, flag;
 
    for(i = 0; i < size / 2; i++)//因为双向同时进行，所以只需要size/2次大循环
    {
        flag = 0;
        for(j = 0; j < size - i - 1; j++)//从前往后排
        {
            if(num[j] > num[j+1])
            {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                flag = 1;
            }
        }
        for(k = size - 1 - i; k > 0; k--)//从后往前排
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


//第三种-设立flag加双向冒泡
void bubble3(int num[], int size)
{
    int i, j, k, up, down, temp, flag;
    up = size - 1;
    down = 0;
    for(i = size - 1; i > 0; i--)//从前往后排
    {
        for(j = down; j < up; j++)
        {
            if(num[j] > num[j+1])
            {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                flag = j;//取出从前往后的下标，在下标之后的数都已经排好序
            }
        }
 
            if(flag == -1)
            {
                break;
            }
            up = flag;//取出flag的值
            flag = -1;//重置flag
 
            for(k = up; k > down; k--)
            {
                if(num[k] < num[k-1])
                {
                    temp = num[k];
                    num[k] = num[k-1];
                    num[k-1] = temp;
                    flag = k;//取出从后往前的下标，在下标之前的数都已经排好序
                }
            }
 
            if(flag == -1)
            {
                break;
            }
            down = flag;//取出flag的值
            flag = -1;//重置flag
    }
}


int main()
{
     int MAX=10;
	 int a[20];
	    //随机播种
		    srand(time(NULL));
		    for(int i=0; i<20; i++)
		    {
		        a[i]=rand()%MAX;
		    }
	    printf("\n");
	    bubble3(a,20);
	    printf("输出第三种优化方法的随机数排序\n");
	    for(int i=0;i<20;i++)
	    printf("%d ",a[i]);
	     return 0;
	    
}
