#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

// primeiro ler os metodos;
void merge(int array[], int low, int mid, int high);
void mergesort(int array[], int low, int high);

int main()
{
    #pragma omp parallel num_threads(4){}
    int *a, num = 25, i, v = 1000, j;


    srand(time(NULL));
    // malloc = memoria
    a = (int *)malloc(sizeof(int) * num);

    for (i = 0; i <= num; i++)
    {
        for (j = 1; j <= v; j++)
        {
            a[i] = rand() % 100;
        }

        clock_t t;
        t = clock();
        mergesort(a, 0, num - 1);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC;

        // mostrar o tempo calculado e os elementos;
        printf("\nElements: %d     =>    %f ", v, time_taken);

        v = v * 2;
    }
        return 0;
    

}

void merge(int array[], int low, int mid, int high)
{
    int temp[1000];
    int i, j, k, m;
    j = low;
    m = mid + 1;
    for (i = low; j <= mid && m <= high; i++)
    {
        if (array[j] <= array[m])
        {
            temp[i] = array[j];
            j++;
        }
        else
        {
            temp[i] = array[m];
            m++;
        }
    }
    if (j > mid)
    {
        for (k = m; k <= high; k++)
        {
            temp[i] = array[k];
            i++;
        }
    }
    else
    {
        for (k = j; k <= mid; k++)
        {
            temp[i] = array[k];
            i++;
        }
    }
    for (k = low; k <= high; k++)
        array[k] = temp[k];
}

void mergesort(int array[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;

//
#pragma omp parallel num_threads(4)
{
#pragma omp parallel sections num_threads(4)
        {
            #pragma omp section
            {
                mergesort(array,low,mid);
            }

            #pragma omp section
            {
                mergesort(array,mid+1,high);
            }
        }
        merge(array,low,mid,high);
    }
}
}