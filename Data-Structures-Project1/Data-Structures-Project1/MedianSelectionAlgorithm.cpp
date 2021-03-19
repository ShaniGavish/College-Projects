#include "MedianSelectionAlgorithm.h"
#include "SelectionAlgorithm.h"

int PARTS = 5;

void swap2(int& num1, int& num2) {
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

void bubbleSort(int* arr, int left, int right)
{
    int i, j,n;
    n = right - left + 1;
    for (i = 0; i < n ; i++)

        // Last i elements are already in place  
        for (j = left; j < right - i; j++)
            if (arr[j] > arr[j + 1])
                swap2(arr[j], arr[j + 1]);
}


int MedianSelectionAlgorithm(int* arr, int arrLen, int index) {
    if (arrLen <= PARTS) {
        bubbleSort(arr, 0,arrLen-1);
        return arr[index-1];
    }
    else {
        int right,pivot, k;
        for (int i = 0; i < arrLen; i+= PARTS) {
            right = i + PARTS < arrLen ? i + PARTS : arrLen;
            bubbleSort(arr, i, right-1);
        }
        pivot = getMedianOfMediansIndex(arr, arrLen);
        swap2(arr[0], arr[pivot]);
        k = Partition(arr, 0, arrLen-1);
        if (index == k) {
            return index;
        }
        if (index < k) {
            return SelectAlgorithmRecursive(arr, 0, k - 1, index);
        }
        return SelectAlgorithmRecursive(arr, k, arrLen - 1, index-k);
    }
}

int getMedianOfMediansIndex(int* arr, int arrLen) {
    int i;
    int size = arrLen % PARTS > 0 ? arrLen / PARTS + 1 : arrLen / PARTS;
    int* medians_arr = new int[size];
    for (i = 0; i < size; i ++) {
        medians_arr[i] = arr[i * PARTS + PARTS/2];
    }
    int median_of_medians = SelectAlgorithm(medians_arr, size, size / 2);
    for (i = 0; i < arrLen; i++) {
        if (arr[i] == median_of_medians) {
            delete[] medians_arr;
            return i;
        }
    }
}
