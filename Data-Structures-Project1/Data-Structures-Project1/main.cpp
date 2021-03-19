#include <iostream>
#include "SelectionInsertionSortAlgorithm.h"
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
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    
    cout << selectionProblemUsingInsertionSort(arr, n, 1) << endl;
    printArray(arr, n);

    return 0;
}