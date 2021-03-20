#include "MedianSelectionAlgorithm.h"

int PARTS = 5;

double MedianSelectionAlgorithm(double* arr, int arrLen, int index) {
    return MedianSelectionAlgorithmRecursion(arr, 0, arrLen - 1, index);
}

double MedianSelectionAlgorithmRecursion(double* arr, int left, int right, int index) {
    int arrLen = right - left + 1;
    if (arrLen <= PARTS) {
        bubbleSort(arr, left, right);
        return arr[left + index -1];
    }
    else {
        int right_edge ,pivot, k;
        for (int i = 0; i < arrLen; i+= PARTS) {
            right_edge = i + PARTS < arrLen ? i + PARTS : arrLen;
            bubbleSort(arr, i, right_edge-1);
        }
        pivot = getMedianOfMediansIndex(arr, left,right);
        Utilities<double>::swap(arr[left], arr[pivot]);
        k = Utilities<double>::Partition(arr, left, right);
        if (index-1 == k) {
            return arr[left + k];
        }
        if (index < k) {
            return MedianSelectionAlgorithmRecursion(arr, left, k - 1, index);
        }
        return MedianSelectionAlgorithmRecursion(arr, k, right , index-k);
    }
}

int getMedianOfMediansIndex(double* arr, int left, int right) {
    int i;
    int size = right - left + 1;
    int amountOfMedians= size % PARTS > 0 ? size / PARTS + 1 : size / PARTS;
    double* medians_arr = new double[amountOfMedians];
    for (i = 0; i < amountOfMedians-1; i ++) {
        medians_arr[i] = arr[left + i * PARTS + PARTS/2];
    }
    int medianIdent = size % PARTS != 0 ? size % PARTS / 2 : PARTS / 2;
    medians_arr[i] = arr[left + i * PARTS + medianIdent];
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