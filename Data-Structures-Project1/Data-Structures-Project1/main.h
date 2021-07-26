#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono> 
#include <iomanip>
#include <string>
#include "SelectionInsertionSortAlgorithm.h"
#include "SelectionAlgorithm.h"
#include "MedianSelectionAlgorithm.h"
#include "utilities.h"



extern int MAX_NUM_OF_DIGITS;
extern int MIN_NUM_OF_DIGITS;

void validateArrLenInput(int arr_len); // Validate arr len input
void validateIndexInput(int index, int arrLen); //Validate index input
void getInputArrFromUsr(double* arr, int arrLen); //Get input arr from user
bool isValidInpupt(string input); //Check if it's valid inpupt
bool isDigit(char ch); //Check if it's digit
bool isValidNumberOfDigitsAfterDPoint(string input, int d_point_index); //Check if it's valid number of digits after decimal point