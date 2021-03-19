#include <iostream>
#include "SelectionInsertionSortAlgorithm.h"
#include "SelectionAlgorithm.h"
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
    int arr[] = { 45, 3, 69, 97, 82, 16, 73, 40, 88 }; 
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << SelectAlgorithm(arr, n, 6) << endl;
    cout << selectionProblemUsingInsertionSort(arr, n, 6) << endl;
    printArray(arr, n);

    return 0;
}