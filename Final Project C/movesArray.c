#include "movesArray.h"
#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h> 


movesArray createNewMovesArray(unsigned int size)
{
	movesArray new_moves_array;
	Move* new_moves = (Move*)malloc(size * sizeof(Move));
	assert(new_moves);
	new_moves_array.size = size;
	new_moves_array.moves = new_moves;
	return new_moves_array;
}

void fillRandomMovesArray(movesArray* moves_array)
{
	unsigned int i;
	for (i = 0; i < moves_array->size; i++)
	{
		moves_array->moves[i].rows = rand() % 7 - 3;
		moves_array->moves[i].cols = rand() % 8 - 4;
	}
}

movesArray** createArrayOfMovesArray()
{
	int i, j;
	movesArray** new_array_of_moves_array = (movesArray**)malloc(N * sizeof(movesArray*));
	assert(new_array_of_moves_array);
	for (i = 0; i < N; i++)
	{
		new_array_of_moves_array[i] = (movesArray*)malloc(M * sizeof(movesArray));
		assert(new_array_of_moves_array[i]);
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
			new_array_of_moves_array[i][j] = createNewMovesArray(N*M);
	}
	return new_array_of_moves_array;
}

movesArray** fillArrayOfMovesArrayWithRandom(movesArray** array_of_moves_array)
{
	int i, j;
	srand((unsigned)time(0));
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			array_of_moves_array[i][j] = createNewMovesArray(rand() % MAX_SIZE_OF_MOVES_ARR + 1);
			fillRandomMovesArray(&(array_of_moves_array[i][j]));
		}
	}
	return array_of_moves_array;
}

void freeMovesArray(movesArray* moves_array)
{
	free(moves_array->moves);
}

void freeArrayOfMovesArray(movesArray** array_of_moves_array)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			freeMovesArray(&(array_of_moves_array[i][j]));
		}
		free(array_of_moves_array[i]);
	}
	free(array_of_moves_array);
}

void printArrayOfMovesArray(movesArray** array_of_moves_array)
{
	int i, j;
	unsigned int k;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			printf("cell (%d,%d): ", i, j);
			for (k = 0; k < array_of_moves_array[i][j].size; k++)
			{
				printf("%d,", array_of_moves_array[i][j].moves[k].rows);
				printf("%d ", array_of_moves_array[i][j].moves[k].cols);
			}
			printf("\n");
		}
	}
}
