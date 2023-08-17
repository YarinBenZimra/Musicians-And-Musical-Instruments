#include "TREES.h"


TreeNode* createNewTNode(char* str, TreeNode* left, TreeNode* right) // Create Tree.
{
    TreeNode* res;
    static short unsigned insld = 0;
    res = (TreeNode*)malloc(sizeof(TreeNode));
    checkMemoryAllocation(res);
    res->instrument = strdup(str);
    res->left = left;
    res->right = right;
    res->insId = insld;
    insld++;
    return res;
}

void freeTree(InstrumentTree tr) //Shell Function Of Free Function.
{
    freeTreeHelper(tr.root);
    tr.root = NULL;
}

void freeTreeHelper(TreeNode* root) // Recursive Free Function. 
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        freeTreeHelper(root->left);
        freeTreeHelper(root->right);
        free(root->instrument);
        free(root);
    }
}

InstrumentTree Build_Binari_Instrument_Tree_By_Lexicography(char* File_Name, int* number_of_instruments) // Shell Function For Reqursive Function
{
	InstrumentTree tr;
	tr.root = NULL;
	int size = 0;
	FILE* fp = fopen(File_Name, "r");
	char temp[COLS];
	char* instru;

	fscanf(fp, "%s", temp);
	instru = strdup(temp);
	tr.root= createNewTNode(instru, NULL, NULL);
	size++;

	while (!feof(fp))
	{
		fscanf(fp, "%s", temp);
		instru = strdup(temp);
		TreeNode* NewNode= createNewTNode(instru, NULL, NULL);
		tr.root = Build_Binari_Instrument_Tree_By_Lexicography_Helper(tr.root, NewNode); // Reqursive Function.
		size++;
		
	}
	fclose(fp);
	*number_of_instruments = size;
	return tr; // Return the finsihed sorted by lexicography tree.
	
}

TreeNode* Build_Binari_Instrument_Tree_By_Lexicography_Helper(TreeNode* root, TreeNode* NewNode) // Reqursive function that build a tree by lexicography order.
{
	if (strcmp(root->instrument, NewNode->instrument) < 0)
	{
		if (root->left == NULL)
		{
			root->left = NewNode;
		}
		Build_Binari_Instrument_Tree_By_Lexicography_Helper(root->left, NewNode);
	}
	if (strcmp(root->instrument, NewNode->instrument) > 0)
	{
		if (root->right == NULL)
		{
			root->right = NewNode;
		}
		Build_Binari_Instrument_Tree_By_Lexicography_Helper(root->right, NewNode); 
	}
	return root;
}

int findInsId(InstrumentTree tree, char* instrument) // Function For Find The insId Of An Insrument In The Tree.
{
	TreeNode* curr = tree.root;
	bool flag = false;
	while (curr != NULL && flag == false)
	{
		if (strcmp(instrument, curr->instrument) == 0)
		{
			flag = true;
		}
		else if (strcmp(instrument, curr->instrument) < 0)
		{
			curr = curr->right;
		}
		else if (strcmp(instrument, curr->instrument) > 0)
		{
			curr = curr->left;
		}
	}
	
	if (flag == true)
	{
		return curr->insId;
	}
	else
	{
		return -1;
	}
}

