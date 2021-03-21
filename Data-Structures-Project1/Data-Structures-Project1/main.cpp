#include "main.h"
using namespace std;

int main()
{
	int arr_len, index;

	cin >> arr_len;
	cin >> index;

	validateIndexInput(index, arr_len);

	double* arr = new double[arr_len];
	getInputArrFromUsr(arr, arr_len);

	double* arr1 = Utilities<double>::duplicateArr(arr, arr_len);
	double* arr2 = Utilities<double>::duplicateArr(arr, arr_len);

	std::cout << std::fixed;
	std::cout << std::setprecision(4);


	auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cout << selectionProblemUsingInsertionSort(arr, arr_len, index) << endl;
	auto end = chrono::high_resolution_clock::now();
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure.txt");
	myfile << "Time taken by function lselectionProblemUsingInsertionSort is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;

	start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cout << SelectAlgorithm(arr1, arr_len, index) << endl;
	end = chrono::high_resolution_clock::now();
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	myfile << "Time taken by function SelectAlgorithm is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;

	start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cout << MedianSelectionAlgorithm(arr, arr_len, index) << endl;
	end = chrono::high_resolution_clock::now();
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	myfile << "Time taken by function MedianSelectionAlgorithm is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	
	myfile.close();

	delete[] arr;
	delete[] arr1;
	delete[] arr2;
}

void getInputArrFromUsr(double* arr, int arr_len) {
	string input;
	getline(cin, input);
	for (int i = 0; i < arr_len; i++) {
		getline(cin, input);
		regex pattern("^[-+]?[0-9]+(\.[0-9]{1,4})$");
		if (regex_match(input, pattern)) {
			arr[i] = stod(input);
		}
		else {
			cout << "wrong input";
			exit(1);
		}
	}
}

void validateIndexInput(int index, int arrLen) {
	if (index<1 || index > arrLen) {
		cout << "wrong input";
		exit(1);
	}
}
