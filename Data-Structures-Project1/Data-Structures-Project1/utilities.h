#pragma once
#include <iostream>
using namespace std;

template <class T>
class Utilities {
private:
	static bool isSwap(T* arr, int pivot, int curr, bool is_pivot_on_left); //This is private static function for partition
public:
	static void swap(T& num1, T& num2); // swap 2 values
	static T* duplicateArr(T* arr, int arrLen);
	static int Partition(T* arr, int left, int right);
};

template <class T>
void Utilities<T>::swap(T& num1, T& num2)
{
	T temp = num1;
	num1 = num2;
	num2 = temp;
}

template <class T>
T* Utilities<T>::duplicateArr(T* arr, int arrLen)
{
	T* res = new T[arrLen];
	for (int i = 0; i < arrLen; i++) {
		res[i] = arr[i];
	}
	return res;
}


template <class T>
int Utilities<T>::Partition(T* arr, int left, int right)
{
	int pivot = left, curr = right, direction = -1;
	bool is_pivot_on_left = true;

	while (pivot != curr) {
		if (isSwap(arr, pivot, curr, is_pivot_on_left)) {
			swap(arr[pivot], arr[curr]);
			Utilities<int>::swap(pivot, curr);
			direction = direction * -1;
			is_pivot_on_left = !is_pivot_on_left;
		}
		curr += direction;
	}
	return pivot;
}

template <class T>
bool Utilities<T>::isSwap(T* arr, int pivot, int curr, bool is_pivot_on_left) {
	if (is_pivot_on_left) {
		return arr[pivot] > arr[curr];
	}
	return	arr[pivot] < arr[curr];
}