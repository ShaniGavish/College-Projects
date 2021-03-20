#include "SelectionInsertionSortAlgorithm.h"

void insertionSortAlgorithm(double* arr, int arrLen)
{
    int i, j;
    double currentVal;
    for (int i = 1; i < arrLen; i++)
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

double selectionProblemUsingInsertionSort(double* arr, int arrLen, int index)
{
    insertionSortAlgorithm(arr, arrLen);
    return arr[index - 1];
}