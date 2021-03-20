#include "main.h"

using namespace std;


void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
	/*int num_of_nums, index;
	cin >> num_of_nums;
	cin >> index;
	int* arr = new int[num_of_nums];

	for (int i = 0; i < num_of_nums; i++) {
		cin >> arr[i];
	}*/

	int arr[] = { 1,12,3,200,-1,2,18};
	int num_of_nums = 7;
	int index = 4;

	cout << selectionProblemUsingInsertionSort(arr, num_of_nums, index) << endl;
	cout << SelectAlgorithm(arr, num_of_nums, index) << endl;
	cout << MedianSelectionAlgorithm(arr, num_of_nums, index) << endl;
	
	/*auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cout << selectionProblemUsingInsertionSort(arr, num_of_nums, index) << endl;
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
	cout << SelectAlgorithm(arr, num_of_nums, index) << endl;
	end = chrono::high_resolution_clock::now();
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	myfile << "Time taken by function SelectAlgorithm is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;


	start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cout << MedianSelectionAlgorithm(arr, num_of_nums, index) << endl;
	end = chrono::high_resolution_clock::now();
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	myfile << "Time taken by function MedianSelectionAlgorithm is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();*/

    
}