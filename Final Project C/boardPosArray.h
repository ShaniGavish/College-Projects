#ifndef BOARDPOSARRAY
#define BOARDPOSARRAY

#define _CRT_SECURE_NO_WARNINGS

//Structs
typedef char boardPos[2];
typedef unsigned char BYTE;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos* positions;
} boardPosArray;

//boardPosArray Statements
boardPos* createNewBoardPos(); // create new board pos
boardPosArray creatNewBoardPosArray(unsigned int size); //creat new board pos array
boardPosArray** createArrayOfboardPosArray(); // create array of board pos array
void freeBoardPos(boardPos* board_pos); // free board pos
void freeBoardPosArray(boardPosArray* board_pos_array); // free board pos array
void freeArrayOfBoardPosArray(boardPosArray** array_of_boardPos_array); // free array of board pos array
void printBoardPos(boardPos board_pos); // print board pos
void printArrayBoardPosArray(boardPosArray** array_of_boardPos_array); // print array board pos array

//Q5
void saveListToBinFile(char* file_name, boardPosArray* pos_arr); // save list to bin file
BYTE* createBytesArray(boardPosArray* pos_arr, unsigned int* bytes_arr_size); // create bytes array of pos_arr
BYTE posToByte(boardPos pos); // convert board pos to byte
int isBitISet(char ch, int i); // check if specific bit in byte is set
char setBit(char ch, int i); // set specific bit in byte
boardPosArray readBoardPosesFromBinaryFile(char* file_name); // read board poses from binar file and create and returns board pos array
#endif
