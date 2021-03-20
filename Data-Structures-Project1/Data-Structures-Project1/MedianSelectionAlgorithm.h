#pragma once

double MedianSelectionAlgorithm(double* arr, int arrLen, int index);
double MedianSelectionAlgorithmRecursion(double* arr, int left, int right, int index);
int getMedianOfMediansIndex(double* arr, int left, int right);
void bubbleSort(double* arr, int left, int right);
void swap2(double& num1, double& num2);

extern int PARTS;