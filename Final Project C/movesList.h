#ifndef MOVESLIST
#define MOVESLIST

#include "movesArray.h"
#include "pathTree.h"
#include <stdbool.h>

//Structs
typedef struct _moveCell 
{
	Move move;
	struct _moveCell *next, *prev;
} moveCell;

typedef struct _movesList 
{
	moveCell * head;
	moveCell * tail;
} movesList;

movesList makeEmptyMovesList(); // make empty moves list
bool isEmptyMovesList(movesList m_lst); // is empty moves list
movesList createRandomMovesList(); // create random moves list
moveCell* createMoveCell(Move move, moveCell* next, moveCell* prev); // create move cell
void insertMoveCellToTail(movesList* m_lst, moveCell* new_tail); // insert move cell to tail
moveCell* removeMoveCell(movesList* m_lst,moveCell* temp); // remove move cell
void removeMidMoveCell(moveCell* move_cell); // remove mid move cell
moveCell* removeFirstMoveCell(moveCell* head); // remove first move cell
void removeLastMoveCell(moveCell* tail); // remove last move cell
int createMoveListCoveringAllBoard(pathTree path_tr, movesList* move_list_covering_all_board); //create move list covering all board
int createMoveListCoveringAllBoardRec(treeNode* root, movesList* move_list_covering_all_board); //create move list covering all board rec
moveCell* createMoveCellFromHeadToTemp(treeNode* root, treeNode* temp); //create move cell from head to temp
bool isMovesListCoveringAllBoard(int len_moves_list, char** board); // is moves list covering all board
void printMovesList(movesList m_lst); // print moves list
void freeMovesList(movesList m_lst); // free moves list
void freeMovesListRec(moveCell* head); // free moves list rec

#endif
