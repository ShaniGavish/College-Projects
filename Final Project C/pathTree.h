#ifndef PATHTREE
#define PATHTREE

#include "boardPosArray.h"

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode 
{
	boardPos position;
	treeNodeListCell *next_possible_positions; 
} treeNode;

typedef struct _treeNodeListCell
{
	treeNode * node;
	struct _treeNodeListCell * next;
} treeNodeListCell;

typedef struct _pathTree 
{
	treeNode * head;
} pathTree;

treeNode* createNewTreeNode(boardPos position); // create new tree node
treeNodeListCell* creatNewTreeNodeListCell(treeNode* node, treeNodeListCell* next); // creat new tree node list cell
treeNodeListCell* insertTreeNodeCell(treeNodeListCell* tree_node_list_cell, treeNode* new_node); // insert tree node cell to list
void printPathTree(pathTree tree); //print path tree
void printPathTreeRec(treeNode* tree_node); //print path tree rec
void printAllPathTreeChildren(treeNodeListCell* tree_node_list_cell); //print all path tree children
void printPositionOfTreeNode(treeNode* tree_node); //print position of treeNode
void freePathTree(pathTree path_tree); //free path tree
void freePathTreeRec(treeNode* tree_node); //free path tree rec
void freeTreeNode(treeNode* tree_node); //free tree node
void freeTreeNodeListCellRec(treeNodeListCell* tree_node_list_cell); //free tree node list cell

#endif