#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*Trabalho de Thiago Barcellos Mattos*/

void merge(int *array, int start, int middle, int end)
{
    int *temp, i, j, k;
    int vector1Ended = 0, vector2Ended = 0;
    int vector1Position = start, vector2Position = middle + 1;
    int size = end - start + 1;
    temp = (int *)malloc(size * sizeof(int));
    if (temp != NULL)
    {
        for (i = 0; i < size; i++){
            if (!vector1Ended && !vector2Ended){
                if (array[vector1Position] < array[vector2Position])
                    temp[i] = array[vector1Position++];
                else
                    temp[i] = array[vector2Position++];
                if (vector1Position > middle)
                    vector1Ended = 1;
                if (vector2Position > end)
                    vector2Ended = 1;
            }
            else{
                if (!vector1Ended)
                    temp[i] = array[vector1Position++];
                else
                    temp[i] = array[vector2Position++];
            }
        }
        for (j = 0, k = start; j < size; j++, k++)
        {
            array[k] = temp[j];
        }
    }
    free(temp);
}

void mergeSort(int *array, int start, int end)
{
    int middle;
    if (start < end){
        middle = (start + end) / 2;
        mergeSort(array, start, middle);
        mergeSort(array, middle + 1, end);
        merge(array, start, middle, end);
    }
}

int main()
{
    int entrySize = 11;
    int *arr = (int *)malloc(sizeof(int) * entrySize);
    int i = 0, j = 0;
    int temp;
    while(!feof(stdin)){

        if(scanf("%d", &temp) == 1){
            arr[i++] = temp;        
        }
        if (i >= entrySize){
            entrySize *= 2;
            arr = realloc(arr, entrySize * sizeof(int));
        }
    }

    mergeSort(arr, 0, i-1);

    for (j = 0; j < i; j++)
        printf("%d\n", arr[j]);

    free(arr);
    return 0;
}