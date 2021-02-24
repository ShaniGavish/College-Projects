#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h> 

char** initBoard()
{
	char** board;
	board = creatBoard();
	fillEmptyboard(&board);
	fillRandomBlockersBoard(&board);
	return board;
}

char** creatBoard()
{
	int i;
	char** board = (char**)malloc(N * sizeof(char*));
	assert(board);
	for (i = 0; i < N; i++)
	{
		board[i] = (char*)malloc(M * sizeof(char));
		assert(board[i]);
	}
	return board;
}

void fillEmptyboard(char*** board)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			*(*(*board + i) + j) = VALID_CHAR;
		}
	}
}

void fillRandomBlockersBoard(char*** board)
{
	int i;
	char row = rand() % N;
	char col = rand() % M;
	srand((unsigned)time(0));

	for (i = 0; i < (rand() % MAX_SIZE_OF_INVALID_CHAR) + 1; i++)
	{
		while ((*(*(*board + row) + col)) == INVALID_CHAR)
		{
			row = rand() % N;
			col = rand() % M;
		}
		*(*(*board + row) + col) = INVALID_CHAR;
	}
}

int countBlockersBoard(char** board)
{
	int i, j, count = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (board[i][j] == INVALID_CHAR)
				count++;
		}
	}
	return count;
}

void insertStartPoint(char*** board, boardPos* start_point)
{
	char row = rand() % N;
	char col = rand() % M;
	srand((unsigned)time(0));

	while ((*(*(*board + row) + col)) == INVALID_CHAR)
	{
		row = rand() % N;
		col = rand() % M;
	}

	*(*(*board + row) + col) = START_POINT;
	start_point[0][0] = START_ROW + row;
	start_point[0][1] = START_COL + col;
}

char** copyBoard(char** board)
{
	int i, j;
	char** temp_board = creatBoard();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			temp_board[i][j] = board[i][j];
		}
	}
	return temp_board;
}

void freeBoard(char** board)
{
	int i;
	for (i = 0; i < N; i++)
	{
		free(*(board + i));
	}
	free(board);
}

void printboard(char** board)
{
	//clearScreen();
	printf(" ");
	char ch = 'A';
	for (int i = 1; i <= M; i++)
	{
		printf("    %d", i);
	}
	for (int j = 1; j <= N; j++)
	{
		printf("\n%c", ch);
		ch++;
		for (int i = 1; i <= M; i++)
		{
			printf("    %c", getCell(board, j, i));
		}
	}
	printf("\n");
}

void printBoardWithPath(char** board)
{
	clearScreen();
	printf(" ");
	char ch = 'A';
	for (int i = 1; i <= M; i++)
	{
		printf("    %d", i);
	}
	for (int j = 1; j <= N; j++)
	{
		printf("\n%c", ch);
		ch++;
		for (int i = 1; i <= M; i++)
		{
			if (getCell(board, j, i) != INVALID_CHAR && getCell(board, j, i) != VALID_CHAR && getCell(board, j, i) != START_POINT)
				printf("    %d", getCell(board, j, i));
			else
				printf("    %c", getCell(board, j, i));
		}
	}
	printf("\n");
}


char getCell(char** board, int row, int col)
{
	return board[row - 1][col - 1];
}

void clearScreen()
{
	system("cls");
}


boardPosArray** validMoves(movesArray** moves, char** board)
{
	int i, j;
	boardPosArray** boardPos_arr = createArrayOfboardPosArray();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			moves[i][j] = validMovesByCell(moves[i][j], board, i, j, &(boardPos_arr[i][j]));
		}
	}
	return boardPos_arr;
}

movesArray validMovesByCell(movesArray moves_arr, char** board, int curr_row, int curr_col, boardPosArray* pos_array)
{
	unsigned int i, size_of_valid_moves = 0, idx_of_valid_pos = 0;
	char dest_col, dest_row;

	movesArray new_valid_moves_array = createNewMovesArray(moves_arr.size);
	Move* new_moves_arr;

	if (board[curr_row][curr_col] == INVALID_CHAR && moves_arr.moves != NULL)
	{
		freeMovesArray(&moves_arr);
		new_valid_moves_array.size = 0;
		new_moves_arr = (Move*)realloc(new_valid_moves_array.moves, sizeof(Move) * size_of_valid_moves);
		new_valid_moves_array.moves = new_moves_arr;
		pos_array->positions = NULL;
		pos_array->size = 0;
	}
	else
	{
		for (i = 0; i < moves_arr.size; i++)
		{
			dest_row = curr_row + (moves_arr.moves + i)->rows;
			dest_col = curr_col + (moves_arr.moves + i)->cols;

			if ((dest_row >= 0 && dest_row < N) && (dest_col >= 0 && dest_col < M))
			{
				if (ISVALIDCELL(board[dest_row][dest_col]))
				{
					new_valid_moves_array.moves[size_of_valid_moves].rows = (moves_arr.moves + i)->rows;
					new_valid_moves_array.moves[size_of_valid_moves].cols = (moves_arr.moves + i)->cols;
					size_of_valid_moves++;

					pos_array->positions[idx_of_valid_pos][0] = START_ROW + dest_row;
					pos_array->positions[idx_of_valid_pos][1] = START_COL + dest_col;
					idx_of_valid_pos++;
				}
			}
		}
		freeMovesArray(&moves_arr);
		new_valid_moves_array.size = size_of_valid_moves;
		new_moves_arr = (Move*)realloc(new_valid_moves_array.moves, sizeof(Move) * size_of_valid_moves);
		new_valid_moves_array.moves = new_moves_arr;
		pos_array->size = idx_of_valid_pos;
	}
	return new_valid_moves_array;
}

int display(movesList* moves_list, boardPos start, char** board)
{
	int counter_valid = 1, counter_invalid = 0;
	char dest_row, dest_col;
	char** temp_board = copyBoard(board);
	boardPos* curr_board_pos = createNewBoardPos();
	curr_board_pos[0][0] = start[0];
	curr_board_pos[0][1] = start[1];
	moveCell* current_move = moves_list->head;
	while (current_move != NULL)
	{
		dest_row = curr_board_pos[0][0] + current_move->move.rows;
		dest_col = curr_board_pos[0][1] + current_move->move.cols;
		if (ISVALIDMOVE(dest_row, dest_col) && ISVALIDCELL(temp_board[dest_row - START_ROW][dest_col - '0' - 1]))
		{
			temp_board[dest_row - START_ROW][dest_col - '0' - 1] = (char)counter_valid;
			curr_board_pos[0][0] = dest_row;
			curr_board_pos[0][1] = dest_col;
			counter_valid++;
			current_move = current_move->next;
		}
		else
		{
			current_move = removeMoveCell(moves_list, current_move);
			counter_invalid++;
		}
	}
	printBoardWithPath(temp_board);
	freeBoard(temp_board);
	freeBoardPos(curr_board_pos);
	return counter_invalid;
}

pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board)
{
	pathTree path_tree;
	path_tree.head = createNewTreeNode(start);
	boardPosArray** valid_pos_array = createArrayOfboardPosArray();
	assert(valid_pos_array);
	valid_pos_array = validMoves(moves, board);
	path_tree.head = findAllPossiblePathsRec(start, board, valid_pos_array);
	return path_tree;
}

treeNode* findAllPossiblePathsRec(boardPos start, char** board, boardPosArray** valid_pos_array)
{
	int i, size_pos_array;
	size_pos_array = valid_pos_array[start[0] - START_ROW][start[1] - '0' - 1].size;
	boardPos curr_position;
	treeNode* head = createNewTreeNode(start);
	char** temp_board;
	for (i = 0; i < size_pos_array; i++)
	{
		curr_position[0] = valid_pos_array[start[0] - START_ROW][start[1] - '0' - 1].positions[i][0];
		curr_position[1] = valid_pos_array[start[0] - START_ROW][start[1] - '0' - 1].positions[i][1];
		if (ISVALIDCELL(board[curr_position[0] - START_ROW][curr_position[1] - '0' - 1]) && !((start[0] == curr_position[0]) && (start[1] == curr_position[1])))
		{
			temp_board = copyBoard(board);
			temp_board[start[0] - START_ROW][start[1] - '0' - 1] = INVALID_CHAR;
			treeNode* new_node_to_insert = createNewTreeNode(curr_position);
			head->next_possible_positions = insertTreeNodeCell(head->next_possible_positions, new_node_to_insert);
			head->next_possible_positions->node = findAllPossiblePathsRec(head->next_possible_positions->node->position, temp_board, valid_pos_array);
			free(temp_board);
		}
	}
	return head;
}

movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board)
{
	int height;
	movesList* move_list_covering_all_board = (movesList*)malloc(sizeof(movesList));
	assert(move_list_covering_all_board);
	*move_list_covering_all_board = makeEmptyMovesList();

	pathTree path_tr = findAllPossiblePaths(start, moves, board);
	height = createMoveListCoveringAllBoard(path_tr, move_list_covering_all_board);

	if (isMovesListCoveringAllBoard(height, board))
		return move_list_covering_all_board;
	else
		freeMovesList(*move_list_covering_all_board);
	return NULL;
}

int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board)
{
	int num_of_invalid_moves, len_moves_list = 0;
	FILE* fp;
	boardPosArray board_pos_arr , board_pos_arr_distinct;
	pathTree pt;
	boardPos* start = createNewBoardPos();
	movesList* valid_path;
	fp = fopen(file_name, "rb");
	if (!fp)
		return FILE_NOT_FOUND;
	else
	{
		board_pos_arr = readBoardPosesFromBinaryFile(file_name);
		board_pos_arr_distinct = reduceArrToDistincArr(board_pos_arr);
		freeBoardPosArray(&board_pos_arr);
		if (board_pos_arr_distinct.size == 0)
		{
			freeBoardPosArray(&board_pos_arr_distinct);
			return NOT_PATH_COVERING_ALL_BOARD;;
		}
		start[0][0] = board_pos_arr_distinct.positions[0][0];
		start[0][1] = board_pos_arr_distinct.positions[0][1];
		pt = findAllPossiblePaths(*start, moves, board);
		valid_path = searchValidPathByPosArr(pt, board_pos_arr_distinct, &len_moves_list);
		if (!valid_path)
		{
			freeBoardPos(start);
			freeBoardPosArray(&board_pos_arr_distinct);
			freePathTree(pt);
			return NOT_VALID_PATH;
		}
		else
		{
			num_of_invalid_moves = display(valid_path, *start, board);
			if (isMovesListCoveringAllBoard(len_moves_list, board))
			{
				freeBoardPos(start);
				freeBoardPosArray(&board_pos_arr_distinct);
				freePathTree(pt);
				freeMovesList(*valid_path);
				return PATH_COVERING_ALL_BOARD;
			}
			else
			{
				freeBoardPos(start);
				freeBoardPosArray(&board_pos_arr_distinct);
				freePathTree(pt);
				freeMovesList(*valid_path);
				return NOT_PATH_COVERING_ALL_BOARD;
			}
		}
	}
}

boardPosArray reduceArrToDistincArr(boardPosArray board_pos_arr)
{
	boardPosArray board_pos_arr_distinct = creatNewBoardPosArray(board_pos_arr.size);
	boardPos* temp_positions;
	int i , j, distinct_index = 0;
	bool found = false;
	for (i = 0; i < board_pos_arr.size; i++)
	{
		for (j = 0; j < distinct_index; j++)
		{
			if (board_pos_arr_distinct.positions[j][0] == board_pos_arr.positions[i][0] && board_pos_arr_distinct.positions[j][1] == board_pos_arr.positions[i][1])
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			board_pos_arr_distinct.positions[distinct_index][0] = board_pos_arr.positions[i][0];
			board_pos_arr_distinct.positions[distinct_index][1] = board_pos_arr.positions[i][1];
			distinct_index++;
		}
		found = false;
	}

	temp_positions = (boardPos*)realloc(board_pos_arr_distinct.positions, distinct_index*sizeof(boardPos));
	board_pos_arr_distinct.positions = temp_positions;
	board_pos_arr_distinct.size = distinct_index;
	return board_pos_arr_distinct;
}

movesList* searchValidPathByPosArr(pathTree pt, boardPosArray board_pos_arr, int* len_moves_list)
{
	movesList* valid_path = (movesList*)malloc(sizeof(movesList));
	assert(valid_path);
	*valid_path = makeEmptyMovesList();
	searchValidPathByPosArrRec(pt.head, board_pos_arr, valid_path, len_moves_list);
	if (*len_moves_list == (board_pos_arr.size) - 1)
		return valid_path;
	else
		return NULL;
}

void searchValidPathByPosArrRec(treeNode* head, boardPosArray board_pos_arr, movesList* valid_path, unsigned int* index)
{
	treeNode* find_next_pos = NULL;
	movesList* temp_moves_list = (movesList*)malloc(sizeof(movesList));
	assert(temp_moves_list);
	movesList* valid_path_moves_list = (movesList*)malloc(sizeof(movesList));
	assert(valid_path_moves_list);
	*valid_path_moves_list = makeEmptyMovesList();
	if (*index >= board_pos_arr.size)
		return;
	if (!head->next_possible_positions)
		return;
	else
	{
		treeNodeListCell* temp = head->next_possible_positions;
		find_next_pos = findNextPos(temp, board_pos_arr.positions[*index + 1]);
		if (find_next_pos)
		{
			*temp_moves_list = makeEmptyMovesList();
			temp_moves_list->head = createMoveCellFromHeadToTemp(head, find_next_pos);
			temp_moves_list->tail = temp_moves_list->head;
			freeMovesList(*valid_path_moves_list);
			valid_path_moves_list->head = temp_moves_list->head;
			valid_path_moves_list->tail = temp_moves_list->tail;
			*index = *index + 1;
			searchValidPathByPosArrRec(find_next_pos, board_pos_arr, temp_moves_list, index);
		}

	}
	if (!valid_path)
		valid_path = valid_path_moves_list;
	else if (isEmptyMovesList(*valid_path))
	{
		freeMovesList(*valid_path);
		*valid_path = *valid_path_moves_list;
	}
	else
	{
		valid_path->tail->next = valid_path_moves_list->head;
		valid_path->tail = valid_path_moves_list->tail;
	}
}


treeNode* findNextPos(treeNodeListCell* tree_node_list_cell, boardPos board_pos_to_find)
{
	treeNode* find_next_pos = NULL;
	treeNodeListCell* temp = tree_node_list_cell;
	while (temp)
	{
		if (temp->node->position[0] == board_pos_to_find[0] &&
			temp->node->position[1] == board_pos_to_find[1])
		{
			find_next_pos = temp->node;
		}
		temp = temp->next;
	}
	return find_next_pos;
}