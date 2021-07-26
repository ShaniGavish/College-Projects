#include "MedianSelectionAlgorithm.h"

int PARTS = 5;

double MedianSelectionAlgorithm(double* arr, int arr_len, int index) {
    return MedianSelectionAlgorithmRecursion(arr, arr_len, index - 1);
}

double MedianSelectionAlgorithmRecursion(double* arr, int arr_len, int index) {

    if (arr_len <= PARTS) {
        bubbleSort(arr, 0, arr_len - 1);
        return arr[index];
    }
    int right_edge, medians_arr_len = (arr_len + PARTS - 1) / PARTS;
    double* medians_arr = new double[medians_arr_len];

    medians_arr = divideArrayAndGetMediansArr(arr, arr_len);
    double median_of_medians = MedianSelectionAlgorithmRecursion(medians_arr, medians_arr_len, (medians_arr_len + 1) / 2);
    delete[] medians_arr;

    int median_of_medians_index = findMedianOfMediansIndexInArr(arr, arr_len, median_of_medians);
    int median_of_medians_position = Utilities<double>::Partition(arr, 0, arr_len - 1);

    if (index < median_of_medians_position)
        return MedianSelectionAlgorithmRecursion(arr, median_of_medians_position, index);
    if (index > median_of_medians_position)
        return MedianSelectionAlgorithmRecursion(arr + median_of_medians_position, arr_len - median_of_medians_position, index - median_of_medians_position);
    return median_of_medians;
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

double* divideArrayAndGetMediansArr(double* arr, int arr_len) {
    int right_edge, medians_arr_len = (arr_len + PARTS - 1) / PARTS;
    double* medians_arr = new double[medians_arr_len];

    for (int i = 0, j = 0; i < arr_len; i += PARTS, j++) {
        right_edge = i + PARTS < arr_len ? i + PARTS : arr_len;
        bubbleSort(arr, i, right_edge - 1);
        medians_arr[j] = arr[i + (right_edge - i) / 2];
    }
    return medians_arr;
}

int findMedianOfMediansIndexInArr(double* arr, int arr_len, double median_of_medians) {
    int median_of_medians_index = 0;
    for (int i = 0; i < arr_len; i++) {
        if (arr[i] == median_of_medians) {
            median_of_medians_index = i;
        }
    }
    if (median_of_medians_index != 0) {
        Utilities<double>::swap(arr[0], arr[median_of_medians_index]);
    }
    return median_of_medians_index;
}
