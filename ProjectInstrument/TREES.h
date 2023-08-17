#ifndef TREES_H
#define TREES_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define COLS 150
#define ROWS 13// num of instrumnet in instrument tree
#define NOTINSTRUMENT -1


// Trees's Struct
typedef struct treeNode {
	char* instrument;
	short unsigned insId;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	TreeNode* root;
} InstrumentTree;

// Tree's Functions
TreeNode* createNewTNode(char* str, TreeNode* left, TreeNode* right);

void freeTree(InstrumentTree tr);

void freeTreeHelper(TreeNode* root);

InstrumentTree Build_Binari_Instrument_Tree_By_Lexicography(char* File_Name, int* number_of_instruments);

TreeNode* Build_Binari_Instrument_Tree_By_Lexicography_Helper(TreeNode* root, TreeNode* NewNode);

int findInsId(InstrumentTree tree, char* instrument);


#endif // !TREES_H


