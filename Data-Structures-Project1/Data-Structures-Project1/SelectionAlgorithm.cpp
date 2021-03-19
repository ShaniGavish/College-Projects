#include "SelectionAlgorithm.h"


int SelectAlgorithm(int* arr, int arrLen, int index) {
	return SelectAlgorithmRecursive(arr, 0, arrLen-1, index);
}

int SelectAlgorithmRecursive(int* arr, int left, int right, int index)
{
	int pivot = Partition(arr, left, right);
	int leftSize = pivot - left + 1;
	if (index == leftSize)
		return arr[pivot];
	if (index < leftSize)
		return SelectAlgorithmRecursive(arr,left,pivot-1,index);
	else
		return SelectAlgorithmRecursive(arr, pivot+1, right, index-leftSize);
}

int Partition(int* arr, int left, int right)
{
    int pivot = left; 
    int curr = right;
	bool is_pivot_on_left = true;
	while (pivot != curr) {
		if (is_pivot_on_left) {
			if (arr[pivot] > arr[curr]) {
				swap(arr[pivot], arr[curr]);
				swap(pivot, curr);
				curr++;
				is_pivot_on_left = false;
			}
			else {
				curr--;
			}
		}
		else {
			if (arr[pivot] < arr[curr]) {
				swap(arr[pivot], arr[curr]);
				swap(pivot, curr);
				curr--;
				is_pivot_on_left = true;
			}
			else {
				curr++;
			}
		}
	}
	return pivot;
}

void swap(int& num1, int& num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
}