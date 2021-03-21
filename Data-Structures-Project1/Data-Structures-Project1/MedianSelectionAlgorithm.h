#pragma once
#include "utilities.h"

extern int PARTS;

double MedianSelectionAlgorithm(double* arr, int arr_len, int index);
double MedianSelectionAlgorithmRecursion(double* arr, int left, int right, int index);
int getMedianOfMediansIndex(double* arr, int left, int right);
void bubbleSort(double* arr, int left, int right);
void divideArrays(double* arr, int arr_len);
double* createMediansArr(double* arr, int amountOfMedians, int left);
int findPivotIndexByPartition(double* arr, int left, int right, int pivot);
