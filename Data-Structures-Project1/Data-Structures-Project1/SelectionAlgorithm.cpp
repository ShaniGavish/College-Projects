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
    int pivot = left, curr = right, direction = -1;
	bool is_pivot_on_left = true;

	while (pivot != curr) {
		if (isSwap(arr, pivot, curr, is_pivot_on_left)) {
			swap(arr[pivot], arr[curr]);
			swap(pivot, curr);
			direction = direction * -1;
			is_pivot_on_left = !is_pivot_on_left;
		}
		curr += direction;
	}
	return pivot;
}

void swap(int& num1, int& num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
}

bool isSwap(int* arr, int pivot, int curr, bool is_pivot_on_left) {
	if (is_pivot_on_left) {
		return arr[pivot] > arr[curr];
	}
	return	arr[pivot] < arr[curr];
}