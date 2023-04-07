#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 1000000
#define MAX1 10000
#define MAX2 50000
#define MAX3 200000
#define MAX4 100

//ѧ�Ὺ�ٶ�̬�ڴ�ռ�-���Դ���һ���ܴ�����飬Ҳ���Լ��������ڴ��������
//��̬�ڴ������ŵ㻹�У�
//1.���㴢����Ͷ���
//2.�ڳ������й����и��������ڴ�ռ䡣


//�����ݽ��д���ļ���
void writeData(char* filename,int* result,int n){
    remove(filename);
    // ����һ����Ϊdata.txt���ļ�
    FILE* pFile = fopen(filename, "w");//������ļ���ʹpFileָ����ļ�
    if (pFile == NULL)
    {
        // �ļ�����ʧ��
        puts("Fail to open file!");
        exit(0);  //��ֹ����
    }

    for(int i=0; i<n; i++){
        //������a������д�뵽�ļ�
        fprintf(pFile, "%d\n",result[i]);
    }
    // �ر��ļ�
    fclose(pFile);
}

//���ɲ������ݣ������浽�ļ�data.text�С����Ҷ�ȡ�ļ��е�����
void creatNumFile(int* arr,int* b,int n){
    //���ɵ����ݷ���a�����ļ���ȡ�����ݷ���b
    int* a=(int*)malloc(sizeof(int)*n);
    char d[50];
   sprintf(d,"data%d.txt",n);  
   printf("��ӡ%s\n",d);
    remove(d);//ɾ���ɵ��ļ�
    // ����һ����Ϊdata.txt���ļ�,
 // data%d.txt  �������ݴ�ŵ��ļ�����
    FILE* pFile = fopen(d, "w");
    if (pFile == NULL)
    {
        // �ļ�����ʧ��
        puts("Fail to open file!");
        exit(0);
    }

    for(int i=0; i<n; i++){
       a[i]=arr[i];
        //������a������д�뵽�ļ�
        fprintf(pFile, "%d\n",a[i]);
    }
    // �ر��ļ�
    fclose(pFile);

    // ����һ����Ϊdata.txt���ļ�
    pFile = fopen(d, "r");
    if (pFile == NULL)
    {
        // �ļ�����ʧ��
        puts("Fail to open file!");
        exit(0);
    }
    int count = 0;
    while (1)
    {
        // ��������Ѿ�����n��Ԫ�أ��򲻼�����ȡ
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
    // �ر��ļ�
    fclose(pFile);
}


//��������
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


//�鲢�����Ӻ�����
void _MergeSort(int *a, int left, int right, int *tmp) {
    if (left >= right)//�鲢������������ֻ��һ�����ݻ������в�����ʱ������Ҫ�ٷֽ�
    {
        return;
    }
    int mid = left + (right - left) / 2;//�м��±�
    _MergeSort(a, left, mid, tmp);//�������н��й鲢
    _MergeSort(a, mid + 1, right, tmp);//�������н��й鲢
    int begin1 = left, end1 = mid;
    int begin2 = mid + 1, end2 = right;
    //��������������й鲢���鲢�������tmp��
    int i = left;
    while (begin1 <= end1 && begin2 <= end2) {
        //����С���������ȷ���tmp
        if (a[begin1] < a[begin2])
            tmp[i++] = a[begin1++];
        else
            tmp[i++] = a[begin2++];
    }
    //������������һ�����䣬����һ������ʣ�������ֱ�ӷŵ�tmp�ĺ���
    while (begin1 <= end1)
        tmp[i++] = a[begin1++];
    while (begin2 <= end2)
        tmp[i++] = a[begin2++];
    //�鲢��󣬿�����ԭ����
    int j = 0;
    for (j = left; j <= right; j++)
        a[j] = tmp[j];
}

//�鲢�������庯����
void MergeSort(int *a, int n) {
    int *tmp = (int *) malloc(sizeof(int) * n);//����һ����ԭ�����С��ͬ�Ŀռ�
    if (tmp == NULL) {
        printf("malloc fail\n");
        exit(-1);
    }
    _MergeSort(a, 0, n - 1, tmp);//�鲢����
    free(tmp);//�ͷſռ�
}

//���ţ��ݹ�棩
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

    QuickSort(a,first,j-1);//������
    QuickSort(a,j+1,last);//���Ұ��
}




//��������
void CountSort(int *a, int n) {
    int min = a[0];//��¼�����е���Сֵ
    int max = a[0];//��¼�����е����ֵ
    for (int i = 0; i < n; i++) {//�������Сֵ
        if (a[i] < min)
            min = a[i];
        if (a[i] > max)
            max = a[i];
    }
    int num = max - min + 1;//min��max֮�����Ȼ������������min��max����
    int *count = (int *) malloc(num*sizeof(int));//���ٿɴ���num�����͵��ڴ�ռ�
    for(int i=0;i<n;i++)
    {
		count[i]=0;//���ڴ�ռ���0
	}
    if (count == NULL) {
        printf("malloc fail\n");
        exit(-1);//�쳣�˳�
    }
    //ͳ����ͬԪ�س��ִ���
    for (int i = 0; i < n; i++) {
        count[a[i] - min]++;
    }
    int i = 0;
    //����ͳ�ƽ�������л��յ�ԭ����������
    for (int j = 0; j < num; j++) {
        while (count[j]--) {
            a[i++] = j + min;
        }
    }
    free(count);//�ͷſռ�
}


//�ҵ����������е����ֵ
int getMax(int array[],int n) {
    int i, max = array[0];
    for (i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}


void countingSort(int array[], int place,int n) {
    int *output = (int *) malloc(sizeof(int) * n);//����һ����ԭ�����С��ͬ�Ŀռ�
    int i;
    //��ʼ��һ������,��������Ԫ�صĳ��ִ���
    int count[10] = { 0 };
    //�����һ��Ԫ��ָ����λ�ϵ�ֵ���
    int max = (array[0] / place) % 10;
    //�ҵ�������λ��ֵ����Ԫ��
    for (i = 1; i < n; i++) {
        if (((array[i] / place) % 10) > max)
            max = array[i];
    }
    //ͳ�Ƹ���Ԫ�س��ֵĴ���
    for (i = 0; i < n; i++)
        count[(array[i] / place) % 10]++;
    //�ۼ� count �����еĳ��ִ���
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    //���� count �����е���Ϣ���ҵ�����Ԫ�����������λ�ã��洢�� output ������
    for (i = n - 1; i >= 0; i--) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }
    //�� output �����е�����ԭ�ⲻ���ؿ����� array ������
    for (i = 0; i < n; i++){
        array[i] = output[i];
    }
    free(output);//�ͷſռ�
}
//���������㷨
void radixSort(int array[],int n) {
    //�ҵ������е����ֵ
    int place, max = getMax(array,n);
    //�������ֵ���е�λ�����ӵ�λ���ε��ü��������㷨
    for (place = 1; max / place > 0; place *= 10)
        countingSort(array, place,n);
}






//ϴ�����ɲ��ظ�����
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


int* copyArray(int *source, int n) {//ÿ������ú����¿����������¸�����������
    int *dest;
    int i;
    // ����ռ�
    dest = (int *) malloc(n * sizeof(int));
    // ˳����
    for (i = 0; i<n; i++)
        dest[i] = source[i];
    return dest;
}

void testBigNum(int* arr,int n){
    int* testNum=(int*)malloc(sizeof(int)*n);
    creatNumFile(arr,testNum,n);
    clock_t start, stop;
    double duration;
    //���������ʱ
    int* insertTestNum=copyArray(testNum,n);
    start = clock();;
    InsertSort(insertTestNum, n);
    stop = clock();
    duration = (double)(stop - start);
    //��ӡ��ʱ
    printf("%d���������ʱ: %fms\n",n, duration);
   
    //�鲢�����ʱ
    int* mergeSortTestNum=copyArray(testNum,n);
    start = clock();
    MergeSort(mergeSortTestNum, n);
    stop = clock();
    duration = (double)(stop - start);
    //��ӡ��ʱ
    printf("%d�鲢�����ʱ: %fms\n",n, duration);
    //���������ʱ
    int* quickSortTestNum=copyArray(testNum,n);
    start = clock();
    QuickSort(quickSortTestNum,0, n-1);
    stop = clock();
    duration = (double)(stop - start);
    //��ӡ��ʱ
    printf("%d���������ʱ: %fms\n",n, duration);
    //���������ʱ
    int* countSortTestNum=copyArray(testNum,n);
    start = clock();
    CountSort(countSortTestNum, n);
    stop = clock();
    duration = (double)(stop - start);
    //��ӡ��ʱ
    printf("%d���������ʱ: %fms\n",n, duration);
    
    //�������������ʱ
	    int* radixSortTestNum=copyArray(testNum,n);
	    start = clock();
	    radixSort(radixSortTestNum, n);
	    stop = clock();
	    duration = (double)(stop - start);
	    //��ӡ��ʱ
	    printf("%d�������������ʱ: %fms\n\n",n, duration);
	    
	   
	   
}


void testSmallNum(int* arr,int n){
    int* testNum=(int*)malloc(sizeof(int)*n);
   creatNumFile(arr,testNum,n);
    clock_t start, stop;
    double duration;
    
    //���������ʱ
    start = clock();
    for(int test=1;test<=100000;test++){  //100�����ݵ�������100000��
        int* insertTestNum=copyArray(testNum,n);
        InsertSort(insertTestNum, n);
    }
    stop = clock();
    duration = (double)(stop - start);
    //��ӡ��ʱ
    printf("%d���������ʱ: %fms\n",n, duration);
    
    
    char d[50];
    snprintf(d,50,"dataSmallResult%d.txt",n);
    int* insertTestNum=copyArray(testNum,n);
    InsertSort(insertTestNum, n);
    writeData(d,insertTestNum,n);
    
    
    //�鲢�����ʱ
    start = clock();
    for(int test=1;test<=100000;test++){
        int* mergeSortTestNum=copyArray(testNum,n);
        MergeSort(mergeSortTestNum, n);
    }
    stop = clock();
    duration = (double)(stop - start);
    //��ӡ��ʱ
    printf("%d�鲢�����ʱ: %fms\n",n, duration);
    
    
    //���������ʱ
    start = clock();
    for(int test=1;test<=100000;test++){
        int* quickSortTestNum=copyArray(testNum,n);
        QuickSort(quickSortTestNum,0, n-1);
    }
    stop = clock();
    duration = (double)(stop - start);
    //��ӡ��ʱ
    printf("%d���������ʱ: %fms\n",n, duration);
    
    
    //���������ʱ
    start = clock();
    for(int test=1;test<=100000;test++){
        int* countSortTestNum=copyArray(testNum,n);//ÿ������
        CountSort(countSortTestNum, n);
    }
    stop = clock();
    duration = (double)(stop - start);
    //��ӡ��ʱ
    printf("%d���������ʱ: %fms\n",n, duration);
    
      //�������������ʱ
	    start = clock();
	    for(int test=1;test<=100*1000;test++){
	        int* radixSortTestNum=copyArray(testNum,n);
	        radixSort(radixSortTestNum, n);
	    }
	    stop = clock();
	    duration = (double)(stop - start);
	    //��ӡ��ʱ
	    printf("%d�������������ʱ: %fms\n",n, duration);
}



void colorSort() {
    /*
1.�����������ָ�룬p0��p2��p
2.��p0��ǰ���������ָ���һ����0��λ�ã�p2�Ӻ���ǰ������ָ���һ����2��λ��
3.Ȼ��p��p0��ʼ���������
   ����0�ͺ�p0������p0++;
   ����1ʲôҲ����;
   ����2�ͺ�p2������p2��ǰ��������һ����2��λ�ã�������Ҫ���¼��p��ֵ,Ϊ0�ͼ���p0������p0++;
   ֱ��p��p2������
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
            if (0 == arr[p]) {//������֮��p��ǰָ���Ԫ��Ϊ0���������pָ���Ԫ�غ�p0ָ���Ԫ�ؽ��н���
                int temp;
                temp = arr[p];
                arr[p] = arr[p0];
                arr[p0] = temp;
                p0++;//����֮�󣬽�p0��ǰ�ƶ�һλ
            }
            p2--;
            while (arr[p2] == 2)//���ƶ�֮��ָ���Ԫ�ػ���2���������ǰ�ƶ���ֱ��ָ���һ����2��Ԫ��
                p2--;
        }
        ++p;//��p��ǰ�ƶ�
    }
    //��ԭ�����ӡ����
    printf("��ɫ������:");
    for (int i = 0; i <13; ++i)
    { printf("%d  ", arr[i]); }
}



void findK(int k){
    int arr[7] = {5,2,8,4,3,7,6};
    QuickSort(arr,0,6);
    printf("�ҵ���%dС����%d\n",k,arr[k-1]);
}


int main() {
    int* arr=(int*)malloc(sizeof(int)*MAX_NUM);//���ٶ�̬�ڴ������ѵ�ַת��Ϊint*�ͣ�Ȼ�����arr��
    shuffle(arr,MAX_NUM);//ϴ�����ɲ��ظ�����
    //���Դ�����
    testBigNum(arr,MAX1);
    testBigNum(arr,MAX2);
    testBigNum(arr,MAX3);
    //����С����
    testSmallNum(arr,MAX4);
    
     printf("\n����{0, 1, 2, 1, 2, 0, 2, 0, 1, 2, 2, 2, 1, 2}��ɫ����\n");
	    colorSort();
	    printf("\n������������{5��2��8��4��3��7��6}�ҵ�����С����\n");
	    findK(3);
}
