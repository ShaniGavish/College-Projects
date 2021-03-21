#include "SelectionAlgorithm.h"

double SelectAlgorithm(double* arr, int arr_len, int index) {
	return SelectAlgorithmRecursive(arr, 0, arr_len - 1, index);
}

double SelectAlgorithmRecursive(double* arr, int left, int right, int index)
{
	int pivot = Utilities<double>::Partition(arr, left, right);
	int leftSize = pivot - left + 1;
	if (index == leftSize)
		return arr[pivot];
	if (index < leftSize)
		return SelectAlgorithmRecursive(arr,left,pivot-1,index);
	else
		return SelectAlgorithmRecursive(arr, pivot+1, right, index-leftSize);
}
