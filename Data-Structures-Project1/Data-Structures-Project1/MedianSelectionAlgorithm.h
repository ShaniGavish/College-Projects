#pragma once
#include "utilities.h"

extern int PARTS;

double MedianSelectionAlgorithm(double* arr, int arrLen, int index);
double MedianSelectionAlgorithmRecursion(double* arr, int left, int right, int index);
int getMedianOfMediansIndex(double* arr, int left, int right);
void bubbleSort(double* arr, int left, int right);

