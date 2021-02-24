#ifndef BOARD
#define BOARD
#include "movesArray.h"
#include "boardPosArray.h"
#include "movesList.h"
#include "pathTree.h"

//Consts
#define N 8
#define M 8
#define MAX_SIZE_OF_INVALID_CHAR 5
#define INVALID_CHAR '*'
#define VALID_CHAR ' '
#define START_POINT '#'
#define START_ROW 'A'
#define END_ROW (N-1)+ START_ROW
#define START_COL '1'
#define END_COL M + '0'
#define ISVALIDCELL(a) (((a)==VALID_CHAR) ? (true): (false))
#define ISVALIDMOVE(a,b) (((a)>=START_ROW && ((a)<=END_ROW) && ((b)>= START_COL) && ((b)<= END_COL)) ? (true): (false))
#define FILE_NOT_FOUND -1
#define NOT_VALID_PATH 1
#define PATH_COVERING_ALL_BOARD 2
#define NOT_PATH_COVERING_ALL_BOARD 3

//board Statements
char** initBoard(); // init board
char** creatBoard(); // creat board
void fillEmptyboard(char*** board); // fill empty board
void fillRandomBlockersBoard(char*** board); // fill random blockers board
int countBlockersBoard(char** board); // count blockers board
void insertStartPoint(char*** board, boardPos* start_point); // insdert start point
char getCell(char** board, int row, int col); // get cell
char** copyBoard(char** board); // copy board
void freeBoard(char** board); // free board
void printboard(char** board); // print board
void printBoardWithPath(char** board); // print board with path
void clearScreen(); // clear screen

//Q1
boardPosArray** validMoves(movesArray** moves, char** board); // gets array of moves array and board, check valid moves and return array of board pos array by valid moves
movesArray validMovesByCell(movesArray moves_arr, char** board, int curr_row, int curr_col, boardPosArray* pos_array); // get moves array and return valid moves
//Q2
int display(movesList *moves_list, boardPos start, char **board); // This function gets moves_list, board and start point, remove invalid moves of list, and print board with path by moves.
//Q3
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board); // find and return tree with all possible paths by moves and board
treeNode* findAllPossiblePathsRec(boardPos start, char** board, boardPosArray** valid_pos_array); // rec function for findAllPossiblePaths function
//Q4
movesList* findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board); // find and return move list by path covering all board
// Q5 in boardPosArray.h - file
//Q6
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board); // read board pos array from bin file, check and display path by poses in file- return status by Q6  
boardPosArray reduceArrToDistincArr(boardPosArray board_pos_arr); //reduce arr to distinc arr
movesList* searchValidPathByPosArr(pathTree pt, boardPosArray board_pos_arr, int* len_moves_list); //search valid path by pos array
void searchValidPathByPosArrRec(treeNode* head, boardPosArray board_pos_arr, movesList* valid_path, unsigned int* index); // rec function for searchValidPathByPosArr function
treeNode* findNextPos(treeNodeListCell* tree_node_list_cell, boardPos board_pos_to_find); // get tree node list cell and board pos to file, check and return find board pos 

#endif
