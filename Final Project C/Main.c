#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Board.h"


void main()
{
	// Q1 - We use random for creating board and moves array
	/*char** board = initBoard();
	printboard(board);
	movesArray** array_of_moves_array = createArrayOfMovesArray();
	array_of_moves_array = fillArrayOfMovesArrayWithRandom(array_of_moves_array);
	printf("\noriginal moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	boardPosArray** board_pos_arr = validMoves(array_of_moves_array, board);
	printf("\nvalid moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	printf("\nvalid positions: \n");
	printArrayBoardPosArray(board_pos_arr);
	freeArrayOfBoardPosArray(board_pos_arr);
	freeArrayOfMovesArray(array_of_moves_array);*/

	//Q2 - We use random for creating board , start point and moves list 
	/*int counter_of_invalid_moves;
	char** board = initBoard();
	movesList moves_lst;
	boardPos* start_point = createNewBoardPos();
	insertStartPoint(&board, start_point);
	printboard(board);
	moves_lst = createRandomMovesList();
	printf("original moves: ");
	printMovesList(moves_lst);
	counter_of_invalid_moves = display(&moves_lst, *start_point, board);
	printf("\nstart point: %c%c\n",start_point[0][0],start_point[0][1]);
	printf("valid moves: ");
	printMovesList(moves_lst);
	freeBoardPos(start_point);
	freeMovesList(moves_lst);*/

	//Q3
	/*pathTree path_tr;
	char** board = initBoard();
	boardPos* start_point = createNewBoardPos();
	insertStartPoint(&board, start_point);
	printboard(board);
	char** temp_board;
	movesArray** array_of_moves_array = createArrayOfMovesArray();
	array_of_moves_array = fillArrayOfMovesArrayWithRandom(array_of_moves_array);
	printf("\noriginal moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	boardPosArray** board_pos_arr = validMoves(array_of_moves_array, board);
	printf("\nvalid moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	printf("\nvalid positions: \n");
	printArrayBoardPosArray(board_pos_arr);
	temp_board = copyBoard(board);
	path_tr = findAllPossiblePaths(*start_point, array_of_moves_array, temp_board);
	printPathTree(path_tr);
	freeArrayOfBoardPosArray(board_pos_arr);
	freeArrayOfMovesArray(array_of_moves_array);
	freePathTree(path_tr);
	freeBoard(temp_board);
	freeBoard(board);*/

	//Q3 - not recursive - check

	/*char** board = creatBoard();
	fillEmptyboard(&board);
	board[0][3] = INVALID_CHAR;
	board[1][7] = INVALID_CHAR;
	board[3][5] = INVALID_CHAR;
	board[4][0] = INVALID_CHAR;

	movesArray** array_of_moves_array = createArrayOfMovesArray();
	Move* moveA2 = (Move*)malloc(4*sizeof(Move));
	assert(moveA2);
	moveA2[0].rows = 'E' - 'A';
	moveA2[0].cols = '1' - '2';
	moveA2[1].rows = 'B' - 'A';
	moveA2[1].cols = '4' - '2';
	moveA2[2].rows = 'C' - 'A';
	moveA2[2].cols = '3' - '2';
	moveA2[3].rows = 'C' - 'A';
	moveA2[3].cols = '1' - '2';
	array_of_moves_array[0][1].size = 4;
	array_of_moves_array[0][1].moves = moveA2;
	Move* moveC3 = (Move*)malloc(3 * sizeof(Move));
	assert(moveC3);
	moveC3[0].rows = 'A' - 'C';
	moveC3[0].cols = '2' - '3';
	moveC3[1].rows = 'B' - 'C';
	moveC3[1].cols = '8' - '3';
	moveC3[2].rows = 'D' - 'C';
	moveC3[2].cols = '6' - '3';
	array_of_moves_array[2][2].size = 3;
	array_of_moves_array[2][2].moves = moveC3;
	Move* moveB4 = (Move*)malloc(6 * sizeof(Move));
	assert(moveB4);
	moveB4[0].rows = 'C' - 'B';
	moveB4[0].cols = '2' - '4';
	moveB4[1].rows = 'D' - 'B';
	moveB4[1].cols = '3' - '4';
	moveB4[2].rows = 'D' - 'B';
	moveB4[2].cols = '5' - '4';
	moveB4[3].rows = 'C' - 'B';
	moveB4[3].cols = '6' - '4';
	moveB4[4].rows = 'A' - 'B';
	moveB4[4].cols = '6' - '4';
	moveB4[5].rows = 'E' - 'B';
	moveB4[5].cols = '1' - '4';
	array_of_moves_array[1][3].size = 6;
	array_of_moves_array[1][3].moves = moveB4;
	Move* moveC1 = (Move*)malloc(5 * sizeof(Move));
	assert(moveC1);
	moveC1[0].rows = 'E' - 'C';
	moveC1[0].cols = '2' - '1';
	moveC1[1].rows = 'D' - 'C';
	moveC1[1].cols = '3' - '1';
	moveC1[2].rows = 'B' - 'C';
	moveC1[2].cols = '3' - '1';
	moveC1[3].rows = 'C' - 'C';
	moveC1[3].cols = '1' - '1';
	moveC1[4].rows = 'D' - 'C';
	moveC1[4].cols = '6' - '1';
	array_of_moves_array[2][0].size = 5;
	array_of_moves_array[2][0].moves = moveC1;
	Move* moveC6 = (Move*)malloc(3 * sizeof(Move));
	assert(moveC6);
	moveC6[0].rows = 'B' - 'C';
	moveC6[0].cols = '4' - '6';
	moveC6[1].rows = 'A' - 'C';
	moveC6[1].cols = '4' - '6';
	moveC6[2].rows = 'C' - 'C';
	moveC6[2].cols = '8' - '6';
	array_of_moves_array[2][5].size = 3;
	array_of_moves_array[2][5].moves = moveC6;
	pathTree path_tr;
	boardPos* start = createNewBoardPos();
	start[0][0] = 'A';
	start[0][1] = '2';
	board[0][1] = START_POINT;
	printboard(board);
	char** temp_board;
	printf("\noriginal moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	boardPosArray** board_pos_arr = validMoves(array_of_moves_array, board);
	printf("\nvalid moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	printf("\nvalid positions: \n");
	printArrayBoardPosArray(board_pos_arr);
	temp_board = copyBoard(board);
	path_tr = findAllPossiblePaths(*start, array_of_moves_array, temp_board);
	printPathTree(path_tr);
	freeArrayOfBoardPosArray(board_pos_arr);
	freeArrayOfMovesArray(array_of_moves_array);
	freePathTree(path_tr);
	freeBoard(temp_board);
	freeBoard(board);*/

	//Q4
	/*pathTree path_tr;
	char** board = initBoard();
	boardPos* start_point = createNewBoardPos();
	insertStartPoint(&board, start_point);
	printboard(board);
	char** temp_board;
	movesArray** array_of_moves_array = createArrayOfMovesArray();
	array_of_moves_array = fillArrayOfMovesArrayWithRandom(array_of_moves_array);
	printf("\noriginal moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	boardPosArray** board_pos_arr = validMoves(array_of_moves_array, board);
	printf("\nvalid moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	printf("\nvalid positions: \n");
	printArrayBoardPosArray(board_pos_arr);
	temp_board = copyBoard(board);
	movesList* move_list_covering_all_board = findPathCoveringAllBoard(*start_point, array_of_moves_array, temp_board);
	if (move_list_covering_all_board)
	printMovesList(*move_list_covering_all_board);
	else
	printf("There is no path covering_all_board");*/

	//Q4 - not recursive - check (3X3 , 2 invalid char)
	/*int count_invalid_char = 0;
	char** board = creatBoard();
	fillEmptyboard(&board);
	board[0][1] = INVALID_CHAR;
	board[2][0] = INVALID_CHAR;
	movesArray** array_of_moves_array = createArrayOfMovesArray();
	Move* moveA1 = (Move*)malloc(3*sizeof(Move));
	assert(moveA1);
	moveA1[0].rows = 'B' - 'A';
	moveA1[0].cols = '1' - '1';
	moveA1[1].rows = 'C' - 'A';
	moveA1[1].cols = '1' - '1';
	moveA1[2].rows = 'C' - 'A';
	moveA1[2].cols = '3' - '1';
	array_of_moves_array[0][0].size = 3;
	array_of_moves_array[0][0].moves = moveA1;

	Move* moveB1 = (Move*)malloc(2 * sizeof(Move));
	assert(moveB1);
	moveB1[0].rows = 'B' - 'B';
	moveB1[0].cols = '2' - '1';
	moveB1[1].rows = 'A' - 'B';
	moveB1[1].cols = '2' - '1';
	array_of_moves_array[1][0].size = 2;
	array_of_moves_array[1][0].moves = moveB1;

	Move* moveB2 = (Move*)malloc(1 * sizeof(Move));
	assert(moveB2);
	moveB2[0].rows = 'C' - 'B';
	moveB2[0].cols = '2' - '2';
	array_of_moves_array[1][1].size = 1;
	array_of_moves_array[1][1].moves = moveB2;

	Move* moveC2 = (Move*)malloc(2 * sizeof(Move));
	assert(moveC2);
	moveC2[0].rows = 'C' - 'C';
	moveC2[0].cols = '3' - '2';
	moveC2[1].rows = 'B' - 'C';
	moveC2[1].cols = '2' - '2';
	array_of_moves_array[2][1].size = 2;
	array_of_moves_array[2][1].moves = moveC2;

	Move* moveC3 = (Move*)malloc(1 * sizeof(Move));
	assert(moveC3);
	moveC3[0].rows = 'B' - 'C';
	moveC3[0].cols = '3' - '3';
	array_of_moves_array[2][2].size = 1;
	array_of_moves_array[2][2].moves = moveC3;

	Move* moveB3 = (Move*)malloc(1 * sizeof(Move));
	assert(moveB3);
	moveB3[0].rows = 'A' - 'B';
	moveB3[0].cols = '3' - '3';
	array_of_moves_array[1][2].size = 1;
	array_of_moves_array[1][2].moves = moveB3;

	boardPos* start = createNewBoardPos();
	start[0][0] = 'A';
	start[0][1] = '1';
	board[0][0] = START_POINT;
	printboard(board);
	char** temp_board;
	printf("\noriginal moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	boardPosArray** board_pos_arr = validMoves(array_of_moves_array, board);
	printf("\nvalid moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	printf("\nvalid positions: \n");
	printArrayBoardPosArray(board_pos_arr);
	temp_board = copyBoard(board);
	movesList* move_list_covering_all_board = findPathCoveringAllBoard(*start, array_of_moves_array, temp_board);
	if (move_list_covering_all_board)
		printMovesList(*move_list_covering_all_board);
	else
		printf("There is no path covering_all_board");*/

	

	////Q5
	/*boardPosArray board_pos_arr = creatNewBoardPosArray(6);
	boardPosArray board_pos_arr_after;
	board_pos_arr.positions[0][0] = 'C';
	board_pos_arr.positions[0][1] = '5';
	board_pos_arr.positions[1][0] = 'A';
	board_pos_arr.positions[1][1] = '4';
	board_pos_arr.positions[2][0] = 'C';
	board_pos_arr.positions[2][1] = '5';
	board_pos_arr.positions[3][0] = 'B';
	board_pos_arr.positions[3][1] = '3';
	board_pos_arr.positions[4][0] = 'D';
	board_pos_arr.positions[4][1] = '1';
	board_pos_arr.positions[5][0] = 'E';
	board_pos_arr.positions[5][1] = '3';
	saveListToBinFile("BoardposArr.bin", &board_pos_arr);
	board_pos_arr_after = readBoardPosesFromBinaryFile("BoardposArr.bin");
	for (int k = 0; k < board_pos_arr_after.size; k++)
	{
		printBoardPos(board_pos_arr_after.positions[k]);
	}*/

	////Q5-2
		/*boardPosArray board_pos_arr = creatNewBoardPosArray(7);
		boardPosArray board_pos_arr_after;
		board_pos_arr.positions[0][0] = 'A';
		board_pos_arr.positions[0][1] = '1';
		board_pos_arr.positions[1][0] = 'B';
		board_pos_arr.positions[1][1] = '1';
		board_pos_arr.positions[2][0] = 'B';
		board_pos_arr.positions[2][1] = '2';
		board_pos_arr.positions[3][0] = 'C';
		board_pos_arr.positions[3][1] = '2';
		board_pos_arr.positions[4][0] = 'C';
		board_pos_arr.positions[4][1] = '3';
		board_pos_arr.positions[5][0] = 'B';
		board_pos_arr.positions[5][1] = '3';
		board_pos_arr.positions[6][0] = 'A';
		board_pos_arr.positions[6][1] = '3';
		saveListToBinFile("BoardposArr.bin", &board_pos_arr);
		board_pos_arr_after = readBoardPosesFromBinaryFile("BoardposArr.bin");
		for (int k = 0; k < board_pos_arr_after.size; k++)
		{
			printBoardPos(board_pos_arr_after.positions[k]);
		}*/


	//Q5-3
	//boardPosArray board_pos_arr = creatNewBoardPosArray(0);
	//boardPosArray board_pos_arr_after;
	//saveListToBinFile("BoardposArr.bin", &board_pos_arr);
	//board_pos_arr_after = readBoardPosesFromBinaryFile("BoardposArr.bin");
	//for (int k = 0; k < board_pos_arr_after.size; k++)
	//{
	//	printBoardPos(board_pos_arr_after.positions[k]);
	//}


	// Q6
	/*int count_invalid_char = 0;
	char** board = creatBoard();
	fillEmptyboard(&board);
	board[0][1] = INVALID_CHAR;
	board[2][0] = INVALID_CHAR;
	boardPos* start = createNewBoardPos();
	start[0][0] = 'C';
	start[0][1] = '5';
	board[2][4] = START_POINT;
	movesArray** array_of_moves_array = createArrayOfMovesArray();
	Move* moveC5 = (Move*)malloc(3 * sizeof(Move));
	assert(moveC5);
	moveC5[0].rows = 'A' - 'C';
	moveC5[0].cols = '4' - '5';
	moveC5[1].rows = 'C' - 'C';
	moveC5[1].cols = '1' - '5';
	moveC5[2].rows = 'C' - 'C';
	moveC5[2].cols = '3' - '5';
	array_of_moves_array[2][4].size = 3;
	array_of_moves_array[2][4].moves = moveC5;

	Move* moveA4 = (Move*)malloc(2 * sizeof(Move));
	assert(moveA4);
	moveA4[0].rows = 'B' - 'A';
	moveA4[0].cols = '3' - '4';
	moveA4[1].rows = 'A' - 'A';
	moveA4[1].cols = '2' - '4';
	array_of_moves_array[0][3].size = 2;
	array_of_moves_array[0][3].moves = moveA4;
	
	Move* moveB3 = (Move*)malloc(1 * sizeof(Move));
	assert(moveB3);
	moveB3[0].rows = 'D' - 'B';
	moveB3[0].cols = '1' - '3';
	array_of_moves_array[1][2].size = 1;
	array_of_moves_array[1][2].moves = moveB3;

	Move* moveD1 = (Move*)malloc(2 * sizeof(Move));
	assert(moveD1);
	moveD1[0].rows = 'E' - 'D';
	moveD1[0].cols = '3' - '1';
	moveD1[1].rows = 'B' - 'D';
	moveD1[1].cols = '2' - '1';
	array_of_moves_array[3][0].size = 2;
	array_of_moves_array[3][0].moves = moveD1;

	printboard(board);
	char** temp_board;
	printf("\noriginal moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	boardPosArray** board_pos_arr = validMoves(array_of_moves_array, board);
	printf("\nvalid moves:\n");
	printArrayOfMovesArray(array_of_moves_array);
	printf("\nvalid positions: \n");
	printArrayBoardPosArray(board_pos_arr);
	temp_board = copyBoard(board);
	int num = checkAndDisplayPathFromFile("BoardposArr.bin", array_of_moves_array, temp_board);
	printf("\n%d", num);*/
}

