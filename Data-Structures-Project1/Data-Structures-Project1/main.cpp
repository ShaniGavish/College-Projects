#include "main.h"

using namespace std;

int MAX_NUM_OF_DIGITS = 4;
int MIN_NUM_OF_DIGITS = 1;

int main()
{
	int arr_len, index;

	cin >> arr_len;
	validateArrLenInput(arr_len);

	cin >> index;
	validateIndexInput(index, arr_len);
	
	double* arr = new double[arr_len];
	getInputArrFromUsr(arr, arr_len);
	
	double* arr1 = Utilities<double>::duplicateArr(arr, arr_len);
	double* arr2 = Utilities<double>::duplicateArr(arr, arr_len);

	cout << fixed;
	cout << setprecision(4);

	auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cout << "Insertion sort i'th element: " << selectionProblemUsingInsertionSort(arr1, arr_len, index) << endl;
	auto end = chrono::high_resolution_clock::now();
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure.txt");
	myfile << "Time taken by function selectionProblemUsingInsertionSort is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;

	start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cout << "Selection i'th element: " << SelectAlgorithm(arr2, arr_len, index) << endl;
	end = chrono::high_resolution_clock::now();
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	myfile << "Time taken by function SelectAlgorithm is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;

	start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cout << "Quintuplet algorithm i'th element: " << MedianSelectionAlgorithm(arr, arr_len, index) << endl;
	end = chrono::high_resolution_clock::now();
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	myfile << "Time taken by function MedianSelectionAlgorithm is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	
	myfile.close();

	if (arr) {
		delete[] arr;
		delete[] arr1;
		delete[] arr2;
	}
}

void getInputArrFromUsr(double* arr, int arr_len) {
	string input;

	for (int i = 0; i < arr_len; i++) {
		cin >> input;
		if (!isValidInpupt(input)) {
			cout << "wrong input";
			exit(1);
		}
		arr[i] = stod(input);
	}
}

void validateArrLenInput(int arr_len) {
	if (arr_len <= 0) {
		cout << "wrong input";
		exit(1);
	}
}

void validateIndexInput(int index, int arrLen) {
	if (index<1 || index > arrLen) {
		cout << "wrong input";
		exit(1);
	}
}

bool isValidInpupt(string input) {

	if (!isDigit(input[0]) && input[0] != '-')
		return false;
	for (int i = 1; i < input.length(); i++)
	{
		if (!isDigit(input[i]) && input[i] != '.')
			return false;
		if (input[i] == '.') {
			return isValidNumberOfDigitsAfterDPoint(input, i);
		}
	}
	return true;
}

bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

bool isValidNumberOfDigitsAfterDPoint(string input, int d_point_index) {
	int num_of_digits_after_d_point = 0;
	for (int i = d_point_index + 1; i < input.length(); i++)
	{
		if (!isDigit(input[i]))
			return false;
		num_of_digits_after_d_point++;
	}
	return (num_of_digits_after_d_point >= MIN_NUM_OF_DIGITS) && (num_of_digits_after_d_point <= MAX_NUM_OF_DIGITS);
}