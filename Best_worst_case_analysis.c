#include<stdio.h>
#include <stdlib.h>
#include <time.h>
// sorting functions
int bubble_sort(int *arr, int size,int choice);
int selection_sort(int *arr, int size, int choice);
int insertion_sort(int *arr, int size, int choice);
void swap(int *a, int *b);
void display(int *arr, int size);
int swap_count=0;
// random function
int *gen_arr(int size);

// time function
double time_sort(int (*sort)(int *, int,int), int size,int ch);
double tell_time(int *arr,int size,int choice,char sort);
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "$ sort start end steps");
        exit(1);
    }

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int steps = atoi(argv[3]);

    
    FILE *fh=fopen("Assign.csv","w");

    fprintf(fh,"Best case\n");

    fprintf(fh,"%s","n,bubble,swaps,selection,swaps,insertion,swaps\n");

    //best case
    for (int i = start; i < end; i = i + steps)
    { 
        int *data=gen_arr(i);
        insertion_sort(data,i,1);
    
        fprintf(fh,"%d,%.3f,%d,%.3f,%d,%.3f,%d\n",i,
        time_sort(bubble_sort,i,1),bubble_sort(data,i,1),
        time_sort(selection_sort,i,1),selection_sort(data,i,1),
        time_sort(insertion_sort,i,1),insertion_sort(data,i,1));
    }

    fprintf(fh,"Worst case\n");
    //worst case
    fprintf(fh,"%s","n,bubble,swaps,selection,swaps,insertion,swaps\n");
    for (int i = start; i < end; i = i + steps)
    { 
       int *data=gen_arr(i); 
       insertion_sort(data,i,0);
       
       int *data1=calloc(i,sizeof(int));
       int *data2=calloc(i,sizeof(int));
       int *data3=calloc(i,sizeof(int));
       int *data4=calloc(i,sizeof(int));
       int *data5=calloc(i,sizeof(int));
       int *data6=calloc(i,sizeof(int));
      for(int j=0;j<i;j++)
       {
        *(data1+j)=*(data+j);
        *(data2+j)=*(data+j);
        *(data3+j)=*(data+j);
        *(data4+j)=*(data+j);
        *(data5+j)=*(data+j);
        *(data6+j)=*(data+j);
       }
       fprintf(fh,"%d,%.3f,%d,%.3f,%d,%.3f,%d\n",i,
       tell_time(data1,i,1,'b'),bubble_sort(data2,i,1),
       tell_time(data3,i,1,'s'),selection_sort(data4,i,1),
       tell_time(data5,i,1,'i'),insertion_sort(data6,i,1));
       free(data1);
       free(data2);
       free(data3);
       free(data4);
       free(data5);
       free(data6);
    }
    //Best case
    /*fprintf(fh,"%s","Best case\n");
    int size;
    printf("Enter size of dataset: ");
    scanf("%d",&size);
    int *data=gen_arr(size);
    insertion_sort(data,size,1);
    display(data,size);
    fprintf(fh,"Bubble,  selection,  insertion\n");
    fprintf(fh,"%.3f, %d  %.3f, %d   %.3f, %d\n",
    time_sort(bubble_sort,size,1),bubble_sort(data,size,1),
    time_sort(selection_sort,size,1),selection_sort(data,size,1),
    time_sort(insertion_sort,size,1),insertion_sort(data,size,1));
    //worst case
    fprintf(fh,"%s","Worst case\n");
    insertion_sort(data,size,0);
    display(data,size);
    int *data1=calloc(size,sizeof(int));
    int *data2=calloc(size,sizeof(int));
    int *data3=calloc(size,sizeof(int));
    int *data4=calloc(size,sizeof(int));
    int *data5=calloc(size,sizeof(int));
    int *data6=calloc(size,sizeof(int));
    for(int i=0;i<size;i++)
    {
        *(data1+i)=*(data+i);
        *(data2+i)=*(data+i);
        *(data3+i)=*(data+i);
        *(data4+i)=*(data+i);
        *(data5+i)=*(data+i);
        *(data6+i)=*(data+i);
    }
    fprintf(fh,"Bubble,  selection,  insertion\n");
    fprintf(fh,"%.3f, %d  %.3f, %d   %.3f, %d\n",
    tell_time(data1,size,1,'b'),bubble_sort(data2,size,1),
    tell_time(data3,size,1,'s'),selection_sort(data4,size,1),
    tell_time(data5,size,1,'i'),insertion_sort(data6,size,1));
    //for worst case analysis
    /*int n;
    printf("Enter size\n");
    scanf("%d",&n);
    int *arr1;
    arr1=(int *)calloc(n,sizeof(int));
    int arr2[n],arr3[n];
    printf("Enter an array in descending order\n");
    for(int i=0;i<n;i++)
    {
    scanf("%d",&arr1[i]);
    arr2[i]=arr3[i]=arr1[i];
    }
    fprintf(fh,"%s","Data set used for Worst case analysis\n");
    for(int i=0;i<n;i++)
    fprintf(fh,"%d ",arr1[i]);
    fprintf(fh,"\n");
    fprintf(fh,"%s","Bubble time no_swap,\t Selection time no_swap,\t Insertion time no_swap\n");
    fprintf(fh,"%.10f, %d,         %.10f, %d,           %.10f, %d\n",
    time_sort(bubble_sort,n),bubble_sort(arr1,n),
    time_sort(selection_sort,n),selection_sort(arr2,n),
    time_sort(insertion_sort,n),insertion_sort(arr3,n));
    //For best case analysis
    fprintf(fh,"%s","Data set used for Best case analysis\n");
    for(int i=0;i<n;i++)
    fprintf(fh,"%d ",arr1[i]);
    fprintf(fh,"\n");
    fprintf(fh,"%s","Bubble time no_swap,\tSelection time no_swap,\tInsertion time no_swap\n");
    fprintf(fh,"%.10f, %d,        %.10f, %d,        %.10f, %d\n",
    time_sort(bubble_sort,n),bubble_sort(arr1,n),
    time_sort(selection_sort,n),selection_sort(arr2,n),
    time_sort(insertion_sort,n),insertion_sort(arr3,n));*/
    fclose(fh);
    return 0;
}

/* sorting functions */

int bubble_sort(int *arr, int size,int choice)
{
    swap_count=0;
    int swapped;
    for (int i = 0; i < size; i++)
    {
        swapped = 0;
        for (int j = 0; j < size - i - 1; j++)
        {
            if(choice==1)
            {
            if (arr[j] > arr[j + 1])
            {
                swap(arr + j, arr + j + 1);
                swap_count++;
                swapped = 1;
            }
            }
            else
            {
                if(arr[j]<arr[j+1])
                {
                    swap(arr+j+1,arr+j);
                    swap_count++;
                    swapped=1;
                }
            }
        }
        if (!swapped)
            break;
    }
    return swap_count;
}

int insertion_sort(int *arr, int size,int choice)
{
    swap_count=0;
    for (int i = 1; i < size; i++)
    {
        int j = i - 1;
        int temp = arr[i];
        if(choice==1)
        {
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            swap_count++;
            j--;
        }
        arr[j + 1] = temp;
        }
        else
        {
        while (j >= 0 && arr[j] < temp)
        {
            arr[j+1] = arr[j];
            swap_count++;
            j--;
        }
        arr[j+1] = temp;
        }
    }
    return swap_count;
}

int selection_sort(int *arr, int size,int choice)
{
    swap_count=0;
    for (int i = 0; i < size - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < size; j++)
        {
            if(choice==1)
            {
             if (arr[j] < arr[min_idx])
              {
                min_idx = j;
              }
            }
            else
            {
              if (arr[j] > arr[min_idx])
               {
                min_idx = j;
               }
            }
            
        }
        if(min_idx!=i)
        {
        swap(arr + i, arr + min_idx);
        ++swap_count;
        }
    }
    return swap_count;
}

// swap two variables
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// displays the integer array
void display(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d, ", arr[i]);
    putchar('\n');
}



// random number generator
int *gen_arr(int size)
{
    srand(time(NULL));
    int *ptr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        ptr[i] = (rand()%100)+1;
    }
    return ptr;
}

// returns the time taken by the sorting function
double time_sort(int (*sort)(int *, int, int), int size,int ch)
{
    int *arr = gen_arr(size);
    double start, end;
    start = clock();

    sort(arr, size,1);

    end = clock();

    free(arr);

    return ((end - start) / CLOCKS_PER_SEC)*(1000);
}
double tell_time(int *arr,int size,int choice,char sort)
{
   double start=clock();
   double end=0.0;
   switch(sort)
   {
    case 'b': bubble_sort(arr,size,choice);
              end=clock();
              return ((end - start) / CLOCKS_PER_SEC)*(1000);
              break;
    case 'i': insertion_sort(arr,size,choice);
              end=clock();
              return ((end - start) / CLOCKS_PER_SEC)*(1000);
              break;
    case 's': selection_sort(arr,size,choice);
              end=clock();
              return ((end - start) / CLOCKS_PER_SEC)*(1000);
              break;
   }
}