#include <iostream>
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
    double* dup_arr = new double[arrLen];
    for (int i = 0; i < arrLen; i++) {
        dup_arr[i] = arr[i];
    }
    insertionSortAlgorithm(dup_arr, arrLen);
    //delete
    return dup_arr[index - 1];
}