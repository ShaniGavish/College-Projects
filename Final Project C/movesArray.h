#ifndef MOVESARRAY
#define MOVESARRAY

#define MAX_SIZE_OF_MOVES_ARR 5

typedef struct _move {
	char rows, cols;
} Move;

typedef struct _movesArray {
	unsigned int size;
	Move* moves;
} movesArray;

//movesArray Statements
movesArray createNewMovesArray(unsigned int size); // create new moves array, return moves array
void fillRandomMovesArray(movesArray* moves_array); // fill random moves array
movesArray** createArrayOfMovesArray(); // create array of moves array, return array of moves array
movesArray** fillArrayOfMovesArrayWithRandom(movesArray** array_of_moves_array); // fill array of moves arra with random
void freeMovesArray(movesArray* moves_array); // free moves array
void freeArrayOfMovesArray(movesArray** array_of_moves_array); // free array of moves array
void printArrayOfMovesArray(movesArray** array_of_moves_array); // print array of moves array

#endif
