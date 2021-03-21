#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono> 
#include <iomanip>
#include <regex>
#include "SelectionInsertionSortAlgorithm.h"
#include "SelectionAlgorithm.h"
#include "MedianSelectionAlgorithm.h"
#include "utilities.h"

void getInputArrFromUsr(double* arr, int arrLen);
void validateIndexInput(int index, int arrLen);