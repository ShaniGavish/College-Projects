#pragma once

double SelectAlgorithm(double* arr, int arrLen, int index);
double SelectAlgorithmRecursive(double* arr, int right, int left, int index);
int Partition(double* arr, int left, int right);
bool isSwap(double* arr, int pivot, int curr, bool is_pivot_on_left);
void swapd(double& num1, double& num2);
void swap(int& num1, int& num2);