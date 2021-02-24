#include "boardPosArray.h"
#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h> 

boardPos* createNewBoardPos() 
{
	boardPos* new_board_pos = (boardPos*)malloc(sizeof(boardPos));
	assert(new_board_pos);
	return new_board_pos;
}

boardPosArray creatNewBoardPosArray(unsigned int size)
{
	boardPosArray new_boardPos_array;
	boardPos* new_board_pos_arr = (boardPos*)malloc(size * sizeof(boardPos));
	assert(new_board_pos_arr);
	new_boardPos_array.size = size;
	new_boardPos_array.positions = new_board_pos_arr;
	return new_boardPos_array;
}

boardPosArray** createArrayOfboardPosArray()
{
	int i, j;
	boardPosArray** new_array_of_board_pos_array = (boardPosArray**)malloc(N * sizeof(boardPosArray*));
	assert(new_array_of_board_pos_array);
	for (i = 0; i < N; i++)
	{
		new_array_of_board_pos_array[i] = (boardPosArray*)malloc(M * sizeof(boardPosArray));
		assert(new_array_of_board_pos_array[i]);
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
			new_array_of_board_pos_array[i][j] = creatNewBoardPosArray(N*M);
	}
	return new_array_of_board_pos_array;
}

void freeBoardPos(boardPos* board_pos) {
	free(board_pos);
}

void freeBoardPosArray(boardPosArray* board_pos_array)
{
	free(board_pos_array->positions);
}

void freeArrayOfBoardPosArray(boardPosArray** array_of_boardPos_array)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			freeBoardPosArray(&(array_of_boardPos_array[i][j]));
		}
		free(array_of_boardPos_array[i]);
	}
	free(array_of_boardPos_array);
}

void printArrayBoardPosArray(boardPosArray** array_of_boardPos_array)
{
	int i, j;
	unsigned int k;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			printf("Position: %c%d = cell: (%d,%d): ", i + START_ROW, j + 1, i, j);
			for (k = 0; k < array_of_boardPos_array[i][j].size; k++)
			{
				printBoardPos(array_of_boardPos_array[i][j].positions[k]);
				printf(" ");
				//printf("%c", array_of_boardPos_array[i][j].positions[k][0]);
				//printf("%c ", array_of_boardPos_array[i][j].positions[k][1]);
			}
			printf("\n");
		}
	}
}

void printBoardPos(boardPos board_pos)
{
	printf("%c%c", board_pos[0], board_pos[1]);
	printf(" ");
}

void saveListToBinFile(char *file_name, boardPosArray *pos_arr)
{
	FILE* fb;
	BYTE* bytes_arr;
	unsigned int bytes_arr_size = 0;

	fb = fopen(file_name, "wb");
	assert(fb);
	short pos_arr_size = (short)(pos_arr->size);
	fwrite(&pos_arr_size, sizeof(short), 1, fb);
	bytes_arr = createBytesArray(pos_arr, &bytes_arr_size);
	fwrite(bytes_arr, sizeof(BYTE), bytes_arr_size, fb);
	free(bytes_arr);

	if (fclose(fb))
		exit(1);
}

BYTE* createBytesArray(boardPosArray* pos_arr, unsigned int* bytes_arr_size)
{
	unsigned int i, j, shift = 2;
	BYTE* bytes_arr, encoded_pos1, encoded_pos2;
	*bytes_arr_size = (((pos_arr->size) * 6) / 8) + ((((pos_arr->size) * 6) % 8) != 0);	//the bits arr size in bytes

	bytes_arr = (BYTE*)malloc(sizeof(BYTE) * (*bytes_arr_size));
	assert(bytes_arr);
	for (i = 0; i < *bytes_arr_size; i++)	//set all bits to 0
		*(bytes_arr + i) = 0;

	for (i = 0, j = 0; i < *bytes_arr_size; j++, shift += 2)
	{
		encoded_pos1 = posToByte(pos_arr->positions[j]);
		encoded_pos2 = (j < (pos_arr->size) - 1) ? posToByte(pos_arr->positions[j + 1]) : 0;
		*(bytes_arr+i) = (encoded_pos1 << shift) | (encoded_pos2 >> (6 - shift) % 6);
		if (shift == 8)
			shift = 0;
		else 
			i++;
	}
	return bytes_arr;
}

BYTE posToByte(boardPos pos)
{
	BYTE encoded_pos;
	encoded_pos = (pos[0] - START_ROW) << 3;
	encoded_pos = encoded_pos | (pos[1] - START_COL);
	return encoded_pos;
}

int isBitISet(char ch, int i)
{
	char mask = 1 << i;
	return mask & ch;
}

char setBit(char ch, int i)
{
	char mask = 1 << i;
	return ch | mask;
}

boardPosArray readBoardPosesFromBinaryFile(char* file_name)
{
	unsigned int pos_index = 0 , total_bytes_count;
	int bit_in_byte_index = 7, bit_in_char_index = 2;
	short board_pos_arr_size;
	char pos_temp_char = 0;
	bool is_reading_row = true;
	FILE* fb;
	BYTE current_byte;
	boardPosArray board_pos_arr;
	
	fb = fopen(file_name, "rb");
	assert(fb);
	fread(&board_pos_arr_size, sizeof(short), 1, fb);
	board_pos_arr = creatNewBoardPosArray((unsigned int)board_pos_arr_size);
	total_bytes_count = (((board_pos_arr.size) * 6) / 8) + ((((board_pos_arr.size) * 6) % 8) != 0);
	
	while(pos_index < board_pos_arr.size)
	{
		if (bit_in_byte_index == 7)
			fread(&current_byte, sizeof(BYTE), 1, fb);
		if (isBitISet(current_byte, bit_in_byte_index))
			pos_temp_char = setBit(pos_temp_char, bit_in_char_index);
		bit_in_char_index--;

		if (bit_in_char_index < 0)
		{
			if (is_reading_row) {
				board_pos_arr.positions[pos_index][0] = pos_temp_char + START_ROW;
				is_reading_row = false;
				pos_temp_char = 0;
			}
			else {
				board_pos_arr.positions[pos_index][1] = pos_temp_char + START_COL;
				is_reading_row = true;
				pos_temp_char = 0;
				pos_index++;
			}
			bit_in_char_index = 2;
		}
		bit_in_byte_index--;
		if (bit_in_byte_index < 0) {
			bit_in_byte_index = 7;
		}
	}
	if (fclose(fb))
		exit(1);
	return board_pos_arr;
}
