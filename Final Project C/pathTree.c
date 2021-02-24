#include "pathTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

treeNode* createNewTreeNode(boardPos position)
{
	treeNode* new_tree_node = (treeNode*)malloc(sizeof(treeNode));
	assert(new_tree_node);
	new_tree_node->position[0] = position[0];
	new_tree_node->position[1] = position[1];
	new_tree_node->next_possible_positions = NULL;
	return new_tree_node;
}

treeNodeListCell* creatNewTreeNodeListCell(treeNode* node, treeNodeListCell* next)
{
	treeNodeListCell* new_tree_node_list_cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	assert(new_tree_node_list_cell);
	new_tree_node_list_cell->node = node;
	new_tree_node_list_cell->next = next;
	return new_tree_node_list_cell;
}

treeNodeListCell* insertTreeNodeCell(treeNodeListCell* tree_node_list_cell, treeNode* new_node)
{
	treeNodeListCell* new_head_list_cell = creatNewTreeNodeListCell(new_node, tree_node_list_cell);
	return new_head_list_cell;
}

void printPositionOfTreeNode(treeNode* tree_node)
{
	printBoardPos(tree_node->position);
	printf(" ");
}

void printPathTree(pathTree tree)
{
	printf("Tree root: ");
	printPositionOfTreeNode(tree.head);
	printf("|");
	printPathTreeRec(tree.head);
}

void printPathTreeRec(treeNode* tree_node)
{
	if (!tree_node)
		return;

	printAllPathTreeChildren(tree_node->next_possible_positions);
	treeNodeListCell* temp = tree_node->next_possible_positions;
	while (temp)
	{
		printPathTreeRec(temp->node);
		temp = temp->next;
	}
}

void printAllPathTreeChildren(treeNodeListCell* tree_node_list_cell)
{
	while (tree_node_list_cell)
	{
		printPositionOfTreeNode(tree_node_list_cell->node);
		tree_node_list_cell = tree_node_list_cell->next;
	}
}

void freePathTree(pathTree path_tree)
{
	freePathTreeRec(path_tree.head);
}

void freePathTreeRec(treeNode* tree_node)
{
	freeTreeNode(tree_node);
}

void freeTreeNode(treeNode* tree_node)
{
	if (tree_node)
	{
		freeTreeNodeListCellRec(tree_node->next_possible_positions);
		free(tree_node);
	}
}

void freeTreeNodeListCellRec (treeNodeListCell* tree_node_list_cell)
{
	if (tree_node_list_cell)
	{
		freeTreeNode(tree_node_list_cell->node);
		freeTreeNodeListCellRec(tree_node_list_cell->next);
		free(tree_node_list_cell);
	}
}

