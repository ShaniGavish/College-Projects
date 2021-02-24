#include "movesList.h"
#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

movesList makeEmptyMovesList()
{
	movesList new_move_lst;

	new_move_lst.head = (moveCell *)malloc(sizeof(moveCell));
	new_move_lst.tail = (moveCell *)malloc(sizeof(moveCell));

	new_move_lst.head = NULL;
	new_move_lst.tail = NULL;

	return new_move_lst;
}

bool isEmptyMovesList(movesList m_lst)
{
	return (m_lst.head == NULL);
}

movesList createRandomMovesList()
{
	movesList moves_list = makeEmptyMovesList();
	int i;
	Move move;
	srand((unsigned)time(0));

	for (i = 0; i < rand() % 20 + 10; i++) //random size
	{
		move.rows = rand() % (N-3) - (2); //random value
		move.cols = rand() % (M-3) - (2); //random value
		moveCell* new_move_cell = createMoveCell(move, NULL, NULL);
		insertMoveCellToTail(&moves_list, new_move_cell);
	}
	return moves_list;
}

moveCell* createMoveCell(Move move, moveCell* next, moveCell* prev)
{
	moveCell *new_move_cell;

	new_move_cell = (moveCell*)malloc(sizeof(moveCell));
	assert(new_move_cell);
	new_move_cell->move = move;
	new_move_cell->next = next;
	new_move_cell->prev = prev;
	return new_move_cell;
}

void insertMoveCellToTail(movesList* m_lst, moveCell* new_tail)
{
	new_tail->next = NULL;

	if (isEmptyMovesList(*m_lst))
		m_lst->head = m_lst->tail = new_tail;
	else
	{
		moveCell* temp = m_lst->tail;
		m_lst->tail->next = new_tail;
		m_lst->tail = new_tail;
		m_lst->tail->prev = temp;
	}
}

moveCell* removeMoveCell(movesList* lst,moveCell* temp)
{
	moveCell* move_next;

	if (!temp->prev) //is first
	{
		temp = removeFirstMoveCell(temp);
		lst->head = temp;
		return temp;
	}
	else if (!temp->next) //is last
	{
		lst->tail = temp->prev;
		removeLastMoveCell(temp);
		return NULL;
	}
	else //is mid
	{
		move_next = temp->next;
		removeMidMoveCell(temp);
		return move_next;
	}
}

void removeMidMoveCell(moveCell* move_cell)
{
	move_cell->prev->next = move_cell->next;
	move_cell->next->prev = move_cell->prev;
	free(move_cell);
}

moveCell* removeFirstMoveCell(moveCell* head)
{
	if (head == NULL)
		return NULL;

	moveCell* temp = head;
	head = head->next;
	if (head) {
		head->prev = NULL;
	}
	free(temp);
	return head;
}

void removeLastMoveCell(moveCell* tail)
{
	if (tail == NULL)
		return;

	moveCell* temp = tail;
	tail = tail->prev;
	tail->next = NULL;
	free(temp);
}

int createMoveListCoveringAllBoard(pathTree path_tr, movesList* move_list_covering_all_board)
{
	return createMoveListCoveringAllBoardRec(path_tr.head, move_list_covering_all_board);
}

int createMoveListCoveringAllBoardRec(treeNode* root, movesList* move_list_covering_all_board)
{
	int max_depth = 0, new_depth;
	movesList* temp_moves_list = (movesList*)malloc(sizeof(movesList));
	assert(temp_moves_list);
	movesList* longest_moves_list = (movesList*)malloc(sizeof(movesList));
	assert(longest_moves_list);
	*longest_moves_list = makeEmptyMovesList();

	if (!root)
		return -1;

	if (!root->next_possible_positions)
		return max_depth;
	treeNodeListCell* temp = root->next_possible_positions;
	while (temp)
	{
		*temp_moves_list = makeEmptyMovesList();
		temp_moves_list->head = createMoveCellFromHeadToTemp(root, temp->node);
		temp_moves_list->tail = temp_moves_list->head;
		new_depth = createMoveListCoveringAllBoardRec(temp->node, temp_moves_list);
		if (max_depth <= new_depth)
		{
			max_depth = new_depth;
			freeMovesList(*longest_moves_list);
			longest_moves_list->head = temp_moves_list->head;
			longest_moves_list->tail = temp_moves_list->tail;
		}
		temp = temp->next;
	}
	if (!move_list_covering_all_board)
		move_list_covering_all_board = longest_moves_list;
	else if (isEmptyMovesList(*move_list_covering_all_board))
	{
		freeMovesList(*move_list_covering_all_board);
		*move_list_covering_all_board = *longest_moves_list;
	}
	else
	{
		move_list_covering_all_board->tail->next = longest_moves_list->head;
		move_list_covering_all_board->tail = longest_moves_list->tail;
	}

	return max_depth + 1;
}

moveCell* createMoveCellFromHeadToTemp(treeNode* root, treeNode* temp)
{
	Move* new_move = (Move*)malloc(sizeof(Move));
	assert(new_move);
	new_move->rows =  temp->position[0] - root->position[0];
	new_move->cols =  temp->position[1] - root->position[1];
	moveCell* new_move_cell = createMoveCell(*new_move, NULL, NULL);
	return new_move_cell;
}

bool isMovesListCoveringAllBoard(int len_moves_list, char** board)
{
	int count_invalid_char = 0;
	count_invalid_char = countBlockersBoard(board);
	return (N * M - count_invalid_char == len_moves_list +1);
}

void printMovesList(movesList m_lst)
{
	moveCell *p;

	for (p = m_lst.head; p != NULL; p = p->next)
	{
		printf("(%d,%d) ", p->move.rows, p->move.cols);
	}
	printf("\n");
}

void freeMovesList(movesList m_lst)
{
	freeMovesListRec(m_lst.head);
}

void freeMovesListRec(moveCell* head)
{
	if (head != NULL)
	{
		freeMovesListRec(head->next);
		free(head);
	}
}
