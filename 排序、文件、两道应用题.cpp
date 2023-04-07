#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 1000000
#define MAX1 10000
#define MAX2 50000
#define MAX3 200000
#define MAX4 100

//学会开辟动态内存空间-可以创建一个很大的数组，也可以极大地提高内存的利用率
//动态内存分配的优点还有：
//1.方便储存大型对象；
//2.在程序运行过程中给予额外的内存空间。


//将数据结果写入文件中
void writeData(char* filename,int* result,int n){
    remove(filename);
    // 创建一个名为data.txt的文件
    FILE* pFile = fopen(filename, "w");//打开输出文件并使pFile指向此文件
    if (pFile == NULL)
    {
        // 文件创建失败
        puts("Fail to open file!");
        exit(0);  //终止程序
    }

    for(int i=0; i<n; i++){
        //将数组a的内容写入到文件
        fprintf(pFile, "%d\n",result[i]);
    }
    // 关闭文件
    fclose(pFile);
}

//生成测试数据，并保存到文件data.text中。并且读取文件中的数据
void creatNumFile(int* arr,int* b,int n){
    //生成的数据放入a，从文件读取的数据放入b
    int* a=(int*)malloc(sizeof(int)*n);
    char d[50];
   sprintf(d,"data%d.txt",n);  
   printf("打印%s\n",d);
    remove(d);//删除旧的文件
    // 创建一个名为data.txt的文件,
 // data%d.txt  测试数据存放的文件名称
    FILE* pFile = fopen(d, "w");
    if (pFile == NULL)
    {
        // 文件创建失败
        puts("Fail to open file!");
        exit(0);
    }

    for(int i=0; i<n; i++){
       a[i]=arr[i];
        //将数组a的内容写入到文件
        fprintf(pFile, "%d\n",a[i]);
    }
    // 关闭文件
    fclose(pFile);

    // 创建一个名为data.txt的文件
    pFile = fopen(d, "r");
    if (pFile == NULL)
    {
        // 文件创建失败
        puts("Fail to open file!");
        exit(0);
    }
    int count = 0;
    while (1)
    {
        // 如果数组已经填满n个元素，则不继续读取
        if (count >= n)
        {
            printf("numbers is full");
            break;
        }
        int get = fscanf(pFile, "%d", &b[count]);
        if (get == EOF)
        {
            break;
        }
        count++;
    }
    putchar('\n');
    // 关闭文件
    fclose(pFile);
}


//插入排序
void InsertSort (int a[],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=i;j>0;j--)
        {
            if(a[j]<a[j-1])
            {
                int c;
                c=a[j];
                a[j]=a[j-1];
                a[j-1]=c;
            }
            else break;
        }
    }
}


//归并排序（子函数）
void _MergeSort(int *a, int left, int right, int *tmp) {
    if (left >= right)//归并结束条件：当只有一个数据或是序列不存在时，不需要再分解
    {
        return;
    }
    int mid = left + (right - left) / 2;//中间下标
    _MergeSort(a, left, mid, tmp);//对左序列进行归并
    _MergeSort(a, mid + 1, right, tmp);//对右序列进行归并
    int begin1 = left, end1 = mid;
    int begin2 = mid + 1, end2 = right;
    //将两段子区间进行归并，归并结果放在tmp中
    int i = left;
    while (begin1 <= end1 && begin2 <= end2) {
        //将较小的数据优先放入tmp
        if (a[begin1] < a[begin2])
            tmp[i++] = a[begin1++];
        else
            tmp[i++] = a[begin2++];
    }
    //当遍历完其中一个区间，将另一个区间剩余的数据直接放到tmp的后面
    while (begin1 <= end1)
        tmp[i++] = a[begin1++];
    while (begin2 <= end2)
        tmp[i++] = a[begin2++];
    //归并完后，拷贝回原数组
    int j = 0;
    for (j = left; j <= right; j++)
        a[j] = tmp[j];
}

//归并排序（主体函数）
void MergeSort(int *a, int n) {
    int *tmp = (int *) malloc(sizeof(int) * n);//申请一个与原数组大小相同的空间
    if (tmp == NULL) {
        printf("malloc fail\n");
        exit(-1);
    }
    _MergeSort(a, 0, n - 1, tmp);//归并排序
    free(tmp);//释放空间
}

//快排（递归版）
void QuickSort(int a[],int first,int last)
{

    if(first>=last) return ;
    int i=first,j=last;
    int base=a[first];
    while(i<j)
    {
        while(i<j&&a[j]>=base) j--;
        while(i<j&&a[i]<=base) i++;
        if(i<j){
            int c;
            c=a[i];
            a[i]=a[j];
            a[j]=c;
        }
    }
    int c;
    c=a[i];
    a[i]=a[first];
    a[first]=c;

    QuickSort(a,first,j-1);//排左半段
    QuickSort(a,j+1,last);//排右半段
}




//计数排序
void CountSort(int *a, int n) {
    int min = a[0];//记录数组中的最小值
    int max = a[0];//记录数组中的最大值
    for (int i = 0; i < n; i++) {//找最大最小值
        if (a[i] < min)
            min = a[i];
        if (a[i] > max)
            max = a[i];
    }
    int num = max - min + 1;//min和max之间的自然数个数（包括min和max本身）
    int *count = (int *) malloc(num*sizeof(int));//开辟可储存num个整型的内存空间
    for(int i=0;i<n;i++)
    {
		count[i]=0;//将内存空间置0
	}
    if (count == NULL) {
        printf("malloc fail\n");
        exit(-1);//异常退出
    }
    //统计相同元素出现次数
    for (int i = 0; i < n; i++) {
        count[a[i] - min]++;
    }
    int i = 0;
    //根据统计结果将序列回收到原来的序列中
    for (int j = 0; j < num; j++) {
        while (count[j]--) {
            a[i++] = j + min;
        }
    }
    free(count);//释放空间
}


//找到整个序列中的最大值
int getMax(int array[],int n) {
    int i, max = array[0];
    for (i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}


void countingSort(int array[], int place,int n) {
    int *output = (int *) malloc(sizeof(int) * n);//申请一个与原数组大小相同的空间
    int i;
    //初始化一个数组,继续各个元素的出现次数
    int count[10] = { 0 };
    //假设第一个元素指定数位上的值最大
    int max = (array[0] / place) % 10;
    //找到真正数位上值最大的元素
    for (i = 1; i < n; i++) {
        if (((array[i] / place) % 10) > max)
            max = array[i];
    }
    //统计各个元素出现的次数
    for (i = 0; i < n; i++)
        count[(array[i] / place) % 10]++;
    //累加 count 数组中的出现次数
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    //根据 count 数组中的信息，找到各个元素排序后所在位置，存储在 output 数组中
    for (i = n - 1; i >= 0; i--) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }
    //将 output 数组中的数据原封不动地拷贝到 array 数组中
    for (i = 0; i < n; i++){
        array[i] = output[i];
    }
    free(output);//释放空间
}
//基数排序算法
void radixSort(int array[],int n) {
    //找到序列中的最大值
    int place, max = getMax(array,n);
    //根据最大值具有的位数，从低位依次调用计数排序算法
    for (place = 1; max / place > 0; place *= 10)
        countingSort(array, place,n);
}






//洗牌生成不重复数字
void shuffle(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    srand((unsigned int) time(NULL));

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


int* copyArray(int *source, int n) {//每次排序好后重新拷贝，方便下个排序函数调用
    int *dest;
    int i;
    // 分配空间
    dest = (int *) malloc(n * sizeof(int));
    // 顺序复制
    for (i = 0; i<n; i++)
        dest[i] = source[i];
    return dest;
}

void testBigNum(int* arr,int n){
    int* testNum=(int*)malloc(sizeof(int)*n);
    creatNumFile(arr,testNum,n);
    clock_t start, stop;
    double duration;
    //插入排序耗时
    int* insertTestNum=copyArray(testNum,n);
    start = clock();;
    InsertSort(insertTestNum, n);
    stop = clock();
    duration = (double)(stop - start);
    //打印耗时
    printf("%d插入排序耗时: %fms\n",n, duration);
   
    //归并排序耗时
    int* mergeSortTestNum=copyArray(testNum,n);
    start = clock();
    MergeSort(mergeSortTestNum, n);
    stop = clock();
    duration = (double)(stop - start);
    //打印耗时
    printf("%d归并排序耗时: %fms\n",n, duration);
    //快速排序耗时
    int* quickSortTestNum=copyArray(testNum,n);
    start = clock();
    QuickSort(quickSortTestNum,0, n-1);
    stop = clock();
    duration = (double)(stop - start);
    //打印耗时
    printf("%d快速排序耗时: %fms\n",n, duration);
    //计数排序耗时
    int* countSortTestNum=copyArray(testNum,n);
    start = clock();
    CountSort(countSortTestNum, n);
    stop = clock();
    duration = (double)(stop - start);
    //打印耗时
    printf("%d计数排序耗时: %fms\n",n, duration);
    
    //基数计数排序耗时
	    int* radixSortTestNum=copyArray(testNum,n);
	    start = clock();
	    radixSort(radixSortTestNum, n);
	    stop = clock();
	    duration = (double)(stop - start);
	    //打印耗时
	    printf("%d基数计数排序耗时: %fms\n\n",n, duration);
	    
	   
	   
}


void testSmallNum(int* arr,int n){
    int* testNum=(int*)malloc(sizeof(int)*n);
   creatNumFile(arr,testNum,n);
    clock_t start, stop;
    double duration;
    
    //插入排序耗时
    start = clock();
    for(int test=1;test<=100000;test++){  //100个数据的数组排100000次
        int* insertTestNum=copyArray(testNum,n);
        InsertSort(insertTestNum, n);
    }
    stop = clock();
    duration = (double)(stop - start);
    //打印耗时
    printf("%d插入排序耗时: %fms\n",n, duration);
    
    
    char d[50];
    snprintf(d,50,"dataSmallResult%d.txt",n);
    int* insertTestNum=copyArray(testNum,n);
    InsertSort(insertTestNum, n);
    writeData(d,insertTestNum,n);
    
    
    //归并排序耗时
    start = clock();
    for(int test=1;test<=100000;test++){
        int* mergeSortTestNum=copyArray(testNum,n);
        MergeSort(mergeSortTestNum, n);
    }
    stop = clock();
    duration = (double)(stop - start);
    //打印耗时
    printf("%d归并排序耗时: %fms\n",n, duration);
    
    
    //快速排序耗时
    start = clock();
    for(int test=1;test<=100000;test++){
        int* quickSortTestNum=copyArray(testNum,n);
        QuickSort(quickSortTestNum,0, n-1);
    }
    stop = clock();
    duration = (double)(stop - start);
    //打印耗时
    printf("%d快速排序耗时: %fms\n",n, duration);
    
    
    //计数排序耗时
    start = clock();
    for(int test=1;test<=100000;test++){
        int* countSortTestNum=copyArray(testNum,n);//每次重新
        CountSort(countSortTestNum, n);
    }
    stop = clock();
    duration = (double)(stop - start);
    //打印耗时
    printf("%d计数排序耗时: %fms\n",n, duration);
    
      //基数计数排序耗时
	    start = clock();
	    for(int test=1;test<=100*1000;test++){
	        int* radixSortTestNum=copyArray(testNum,n);
	        radixSort(radixSortTestNum, n);
	    }
	    stop = clock();
	    duration = (double)(stop - start);
	    //打印耗时
	    printf("%d基数计数排序耗时: %fms\n",n, duration);
}



void colorSort() {
    /*
1.设置三个标记指针，p0，p2，p
2.令p0从前往后遍历，指向第一个非0的位置，p2从后往前遍历，指向第一个非2的位置
3.然后p从p0开始往后遍历：
   遇到0就和p0交换，p0++;
   遇到1什么也不做;
   遇到2就和p2交换，p2向前滑动到下一个非2的位置，交换后还要重新检查p的值,为0就继续p0交换，p0++;
   直到p与p2相遇。
     */
    int arr[14] = {0, 1, 2, 1, 2, 0, 2, 0, 1, 2, 2, 2, 1, 2};
    int p0 = 0, p2 = 13, p = 0;
    while (0 == arr[p0])
        p0++;
    while (2 == arr[p2])
        p2--;
    p = p0;
    while (p<= p2) {
        if (0 == arr[p]) {
            int temp;
            temp = arr[p];
            arr[p] = arr[p0];
            arr[p0] = temp;
            ++p0;
        } else if (2 == arr[p]) {
            int temp;
            temp = arr[p];
            arr[p] = arr[p2];
            arr[p2] = temp;
            if (0 == arr[p]) {//若交换之后，p当前指向的元素为0，则继续将p指向的元素和p0指向的元素进行交换
                int temp;
                temp = arr[p];
                arr[p] = arr[p0];
                arr[p0] = temp;
                p0++;//交换之后，将p0向前移动一位
            }
            p2--;
            while (arr[p2] == 2)//若移动之后指向的元素还是2，则继续向前移动，直到指向第一个非2的元素
                p2--;
        }
        ++p;//将p向前移动
    }
    //将原数组打印出来
    printf("颜色排序结果:");
    for (int i = 0; i <13; ++i)
    { printf("%d  ", arr[i]); }
}



void findK(int k){
    int arr[7] = {5,2,8,4,3,7,6};
    QuickSort(arr,0,6);
    printf("找到第%d小的数%d\n",k,arr[k-1]);
}


int main() {
    int* arr=(int*)malloc(sizeof(int)*MAX_NUM);//开辟动态内存区，把地址转化为int*型，然后放在arr中
    shuffle(arr,MAX_NUM);//洗牌生成不重复数字
    //测试大数据
    testBigNum(arr,MAX1);
    testBigNum(arr,MAX2);
    testBigNum(arr,MAX3);
    //测试小数据
    testSmallNum(arr,MAX4);
    
     printf("\n进行{0, 1, 2, 1, 2, 0, 2, 0, 1, 2, 2, 2, 1, 2}颜色排序\n");
	    colorSort();
	    printf("\n在无序序列中{5，2，8，4，3，7，6}找到第三小的数\n");
	    findK(3);
}
