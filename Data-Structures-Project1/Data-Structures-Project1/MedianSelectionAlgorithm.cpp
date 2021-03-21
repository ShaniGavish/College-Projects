#include "MedianSelectionAlgorithm.h"

int PARTS = 5;

double MedianSelectionAlgorithm(double* arr, int arr_len, int index) {
    return MedianSelectionAlgorithmRecursion(arr, 0, arr_len - 1, index);
}

double MedianSelectionAlgorithmRecursion(double* arr, int left, int right, int index) {
    int arr_len = right - left + 1;
    if (arr_len <= PARTS) {
        bubbleSort(arr, left, right);
        return arr[left + index -1];
    }
    else {
        int pivot, pivotIndex;
        divideArrays(arr, arr_len);
        pivot = getMedianOfMediansIndex(arr, left,right);
        pivotIndex = findPivotIndexByPartition(arr, left, right, pivot);
        if (index-1 == pivotIndex) {
            return arr[left + pivotIndex];
        }
        if (index < pivotIndex) {
            return MedianSelectionAlgorithmRecursion(arr, left, pivotIndex - 1, index);
        }
        return MedianSelectionAlgorithmRecursion(arr, pivotIndex, right , index- pivotIndex);
    }
}

int getMedianOfMediansIndex(double* arr, int left, int right) {
    int i, arr_len = right - left + 1;
    int amountOfMedians = arr_len % PARTS > 0 ? arr_len / PARTS + 1 : arr_len / PARTS;

    double* medians_arr = createMediansArr(arr, amountOfMedians, left);

    int medianIdent = arr_len % PARTS != 0 ? arr_len % PARTS / 2 : PARTS / 2;
    medians_arr[amountOfMedians - 1] = arr[left + (amountOfMedians - 1) * PARTS + medianIdent];

    double median_of_medians = MedianSelectionAlgorithm(medians_arr, amountOfMedians, amountOfMedians / 2);
    
    for (i = left; i < right; i++) {
        if (arr[i] == median_of_medians) {
            delete[] medians_arr;
            return i;
        }
    }
}

void bubbleSort(double* arr, int left, int right)
{
    int i, j, n;
    n = right - left + 1;
    for (i = 0; i < n; i++) {
        for (j = left; j < right - i; j++) {
            if (arr[j] > arr[j + 1])
                Utilities<double>::swap(arr[j], arr[j + 1]);
        }
    }
}

void divideArrays(double* arr, int arr_len) {
    int right_edge;
    for (int i = 0; i < arr_len; i += PARTS) {
        right_edge = i + PARTS < arr_len ? i + PARTS : arr_len;
        bubbleSort(arr, i, right_edge - 1);
    }
}

double* createMediansArr(double* arr, int amountOfMedians, int left) {
    double* medians_arr = new double[amountOfMedians];
    for (int i = 0; i < amountOfMedians - 1; i++) {
        medians_arr[i] = arr[left + i * PARTS + PARTS / 2];
    }
    return medians_arr;
}

int findPivotIndexByPartition(double* arr, int left, int right, int pivot) {
    Utilities<double>::swap(arr[left], arr[pivot]);
    return Utilities<double>::Partition(arr, left, right);
}