#include "SelectionInsertionSortAlgorithm.h"

void insertionSortAlgorithm(double* arr, int arr_len)
{
    int i, j;
    double currentVal;
    for (int i = 1; i < arr_len; i++)
    {
        currentVal = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > currentVal)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = currentVal;
    }
}

double selectionProblemUsingInsertionSort(double* arr, int arr_len, int index)
{
    insertionSortAlgorithm(arr, arr_len);
    return arr[index - 1];
}