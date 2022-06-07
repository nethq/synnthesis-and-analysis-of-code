#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArr(int *arr,int min,int max,int size)
{
    for (int i = 0; i < size; i++) {
        arr[i]=(rand()%(max-min+1))+min;
    }
}
void fillarr(int *arr,int size)
{
    for (int i = 0; i < size; i++) {
        arr[i]=(rand()%size);
    }
}


void printArr(int *arr,int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}


//cifrovata sortirovka izpolzva zadadeni min i max za da znae kakuv vtorichen masiv da suzdade za da zapisva vutre broq na encounternatite elementi
void cifrovaSortirovka(int *arr,int min,int max)
{
    int absSize=abs(max)+abs(min);
    int *barr = (int*)calloc((absSize+1),sizeof(int));
    for (int i = 0; i < absSize-max; i++) {
        barr[arr[i]+abs(min)]++;
    }
    for (int i = 0; i <= absSize; i++) {
        for (int j = 0; j <barr[i]; ++j) {
            printf("%d ",i+min);
        }
    }
    printf("\n");
}
//O(n^2)
void prqkaSelekciq(int *arr,int size)
{
    for(int i =0;i<size;i++)
    {
        int min=i   ;//index of the smallest element
        for (int j = i; j < size; j++){
            if(arr[min]>arr[j])
                min=j;
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}
//O(n^2)
void prqkoVmukvane(int *arr,int size) {
    int i, j, x;
    for (i = 1; i < size; i++)
    {
        x = arr[i];
        j = i -1;
        while (j >= 0 && x < arr[j])
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = x;
    }

}
//O(n^2)mehura proklet
void prqkaRazmqnaDesc(int *arr, int size)
{
    for(int i =0;i<size;i++)
    {
        for (int j = i+1; j < size; j++) {
            if(arr[j]>arr[j-1])
            {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }

}
//O(n^2)prqka razmqna ascending
void bubble_sortAsc(int A[], int n)
{
    for (int i = 0; i < n-1; i++)
        for (int j = n-1; j > i; j--)
            if (A[j] < A[j-1])
            {
                int x;//temp
                x = A[j];
                A[j] = A[j-1];
                A[j-1] = x;
            }
}
//O(n^2)
void bubble_sort_flag( int A[], int n)
{
    int flag;
    do
    {
        flag = 1;
        for(int i=0; i<n-1; i++)
            if (A[i]>A[i+1])
            {
                int x =A[i];
                A[i] = A[i+1];
                A[i+1] = x;
                flag = 0;
            }
    }
    while (!flag);
}
void Nedelcho_sort_desc(int *arr,int size){
    for(int i =0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(arr[i]>arr[j]){
                int temp = arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}
//vremeto za quicksort e O(n*log(n)) v nai dobriq sluchai i nai loshiq O(n^2)
void quicksort(int A[], int start, int stop)
{
    int i,j;
    int middleElem=A[(start+stop)/2];
    do
    {
        while (A[i]<middleElem) i++;//namirame sledvashtiq po maluk element ot middleElem (vurvi ot nachalo kum kraq (lqvo na dqsno))
        while (A[j]>middleElem) j--;//namirame sledvashtiq po golqm element ot middleElem (vurvi ot kraq kum nachalo (dqsno na lqvo))
        if(i<=j)//ako se razminat indeksite 'i' i 'j' znachi che sme namerili 2 elementa ,ediniq po malkiq e otdqsno , a po golemiq e otlqvo , a trqbva da e obratnoto
        {//sledovatelno gi razmenqme
            int x = A[i];
            A[i] = A[j];
            A[j] = x;
            i++; j--;
        }
    }while (i<=j);
    if (start < j)//preizvikvame funkciqta za opredelenata podchast koqto ne sme obhodili
        quicksort(A, start, j);
    if (i < stop)
        quicksort(A, i, stop);
}

void binSearch(int start , int end , int *arr, int searchValue)
{
    if(arr[start]<=searchValue && arr[end]>=searchValue)
    {
        int mid = arr[(start+end)/2];
        if(mid==searchValue)
            printf("%d\n",mid);
        else if(mid>searchValue)
            binSearch(start,(start+end)/2,arr,searchValue);
        else
            binSearch((start+end)/2,end,arr,searchValue);
    }
}

int main()
{
    srand(time(NULL));
    int size=10;
    int min=-10;
    int max=10;
    int arr[20];

    printf("Cifrova sortirovka\n");
    int barr[10];
    size =10;
    fillArr(barr,min,max,size);
    printArr(barr,size);
    cifrovaSortirovka(barr,min,max);
    printArr(barr,size);

    printf("Prqka selekciq\n");
    fillarr(arr,size);
    printArr(arr,size);
    prqkaSelekciq(arr,size);
    printArr(arr,size);

    printf("Prqko vmukvane\n");
    fillarr(arr,size);
    printArr(arr,size);
    prqkoVmukvane(arr,size);
    printArr(arr,size);
    binSearch(0,size-1,arr,5);

    printf("Prqka razmqna(mehura)\n");
    fillarr(arr,size);
    printArr(arr,size);
    prqkaRazmqnaDesc(arr,size);
    //bubble_sortAsc(arr,size);
    printArr(arr,size);
//    printf("Burza sortirovka (quickSort)\n");
//    fillarr(arr,size);
//    printArr(arr,size);
//    burzoSort(arr,0,size-1);
//    printArr(arr,size);

    printf("Nedelcho sortirovka descending\n");
    fillarr(arr,size);
    printArr(arr,size);
    Nedelcho_sort_desc(arr,size);
    printArr(arr,size);


    return 0;

}