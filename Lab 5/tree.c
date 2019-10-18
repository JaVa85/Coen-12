/* Jake Vargas
 * COEN 12 Project 5
 * Professor Atkinson
 * Lab Section: Thursday 9:15
 
   Description: This ADT will be used in our huffman codes, and consists of some functions that will prove helpful in the next part of the lab.
*/



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
};

typedef struct tree TREE;


/* Description: create a new tree pointer with a left and right subtree. Initialize its data as well. Return the pointer.
 * Runtime: O(1)
 * */
struct tree *createTree(int data, struct tree *left, struct tree *right)
{
	TREE *tp;
	
	tp = malloc(sizeof(struct tree));
	assert (tp != NULL);

	tp->parent = NULL;
	tp->data = data;
	tp->left = left;
	tp->right = right;

	if (right != NULL)
		right->parent = tp;
	
	if (left != NULL)
		left->parent = tp;

	return tp;
}

/* Description: Recursively deallocate memory
 * Runtime: O(n)
 * */
void destroyTree(struct tree *root)
{
	if (root == NULL)
		return;

	if (root->left != NULL)
		destroyTree(root->left);
	if (root->right != NULL)
		destroyTree(root->right);
	
	free(root);
}

/* Description: Return the value of the data in the tree
 * Runtime: O(1)
 * */
int getData(struct tree *root)
{
	return root->data;
}

/* Description: Return pointer to left child
 * Runtime: O(1)
 * */
struct tree *getLeft(struct tree *root)
{
	TREE *tp;

	tp = root->left;

	return tp;
}

/* Description: Return pointer to right child
 * Runtime: O(1)
 * */
struct tree *getRight(struct tree *root)
{
	TREE *tp;

	tp = root->right;

	return tp;
}

/* Description: Return pointer to parent
 * Runtime: O(1)
 * */
struct tree *getParent(struct tree *root)
{
	TREE *tp;

	tp = root->parent;

	return tp;
}

/* Description: Update left subtree
 * Runtime: O(1)
 * */
void setLeft(struct tree *root, struct tree *left)
{
	assert(root != NULL);
	assert(left != NULL);

	root->left = left;
	left->parent = root;
}

/* Description: Update right subtree
 * Runtime: O(1)
 * */
void setRight(struct tree *root, struct tree *right)
{
	assert(root != NULL);
	assert(right != NULL);

	root->right = right;
	right->parent = root;
}
