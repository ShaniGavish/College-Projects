#pragma once
#include "utilities.h"

extern int PARTS;

double MedianSelectionAlgorithm(double* arr, int arr_len, int index); //Median selection algorithm
double MedianSelectionAlgorithmRecursion(double* arr, int arr_len, int index); //Median selection algorithm recursive
void bubbleSort(double* arr, int left, int right); // Buuble sort algorithm
double* divideArrayAndGetMediansArr(double* arr, int arr_len); //Divide array and get medians arr
int findMedianOfMediansIndexInArr(double* arr, int arr_len, double median_of_medians); //Find median of medians index in arr