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

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Enter: start end steps");
        exit(1);
    }

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int steps = atoi(argv[3]);

    
    FILE *fh=fopen("Assignment.csv","w");
    fprintf(fh,"%s","n,bubble_time,no_of_swaps,selection_time,no_of_swaps,insertion_time,no_of_swaps\n");
    puts("n,bubble,selection,insertion");
    for (int i = start; i < end; i = i + steps)
    {
        printf(
            "%d,%.3f,%d,%.3f,%d,%.3f,%d\n",
            i,
            time_sort(bubble_sort, i,1),
            bubble_sort(gen_arr(i),i,1),
            time_sort(selection_sort, i,1),
            selection_sort(gen_arr(i),i,1),
            time_sort(insertion_sort, i,1),
            insertion_sort(gen_arr(i),i,1)
            );
        fprintf(fh,"%d,%.3f,%d,%.3f,%d,%.3f,%d\n",
            i,
            time_sort(bubble_sort, i,1),
            bubble_sort(gen_arr(i),i,1),
            time_sort(selection_sort, i,1),
            selection_sort(gen_arr(i),i,1),
            time_sort(insertion_sort, i,1),
            insertion_sort(gen_arr(i),i,1));
    }
    
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
