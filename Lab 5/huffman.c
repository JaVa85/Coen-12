/* Coen 12 Project 5
 * Professor Atkinson
 * Lab Section: Thursday 9:15
   
   Description: In this lab we will be writing a code to compress a file. This is the basic structure of Huffman coding.
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "pack.h"
#include "tree.c"
#include "pack.c"

#define l(i) (2*i+1)
#define r(i) (2*i+2)
#define p(i) ((i-1)/2)

int counts[257];
struct tree *leaves[257];
struct tree *heap[257];


int main(int argc, char *argv[])
{
	FILE *fp;
	int c;
	int hcount = 0;

	if (argc < 2)		//make sure two arguments
	{
		printf("ERROR, NOT ENOUGH ARGUMENTS.\n");
		return -1;
	}

	fp = fopen(argv[1], "r");

	for (i=0; i<257; i++)	//initialie the array
		counts[i] = 0;

	while (c = getc(fp) != EOF)	//while in read file, count number of character occurences
		counts[c]++;

	fclose(fp);

	for (j=0; j<257; j++)	//go through total amount of possible elements
	{
		if (counts[j] > 0)	//start to create leaves for huffman tree
			leaves[j] = createTree(count[j], NULL, NULL);
			insert(leaves[j], heap, hcount);	//put into heap
			hcount++;
	}
	leaves[256] = createTree(0, NULL, NULL);	//EOF
	insert(leaves[256], heap, hcount);
	hcount++;
	
	while (hcount > 1)	//huffman tree, remove smallest and create new tree with the sum of the two data, then put back into heap 
	{
		TREE *left = delete(heap, hcount);
		hcount--;
		TREE *right = delete(heap, hcount);
		hcount--;
		TREE *newtree = createTree(getData(left) + getData(right), left, right);
		insert(newtree, heap, hcount);
		hcount++;
	}

			
	

}
/* Description: A function that inserts given nodes into a tree 
 * Runtime: O(
 * */
void insert(TREE *node, TREE *heap[], int hcount)
{


}

/* Description: A function that deletes minimum value of the heap while also returning that value to be used to create the new tree from the data values
 * Runtime: O(
 * */ 
void delete(TREE *heap[], int count)
{


}	
