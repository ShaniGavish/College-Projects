#pragma once

int SelectAlgorithm(int* arr, int arrLen, int index);
int SelectAlgorithmRecursive(int* arr, int right, int left, int index);
int Partition(int* arr, int left, int right);
void swap(int& num1, int& num2);