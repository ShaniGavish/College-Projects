#include <iostream>
#include "SelectionInsertionSortAlgorithm.h"
#include "SelectionAlgorithm.h"
#include "MedianSelectionAlgorithm.h"
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
    int arr[] = { 10,12,-8,-7}; 
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 2;
    cout << SelectAlgorithm(arr, n, i) << endl;
    cout << selectionProblemUsingInsertionSort(arr, n, i) << endl;
    cout<< MedianSelectionAlgorithm(arr,n,i) << endl;
    printArray(arr, n);

    return 0;
}