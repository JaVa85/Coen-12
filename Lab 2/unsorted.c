/* Jake Vargas
 * COEN 12 Preject 2 Part 1
 * Professor Atkinson
 * Lab Section: Thursday 9:15

  Description:
	In this lab we will be creating a set ADT for strings. In this implementation, we will be dealing with unsorted lists which will allow us to use sequential search to run different functions. These include  adding elements, removing elements, checking to see the amount of elements in the set, as well as destroying a complete set.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

struct set
{
	int count;
	int length;
	char* *elts;
};

/*Allocate memory to create a set, then  initializes each variable within set. Returns a pointer to the set that was created.
 * Run time: O(1);
*/
SET *createSet(int maxElts)
{
	SET *sp;
	
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts != NULL);
	
	return sp;
}

/* This function finds an element in the set, and returns the position when called. This is done using a sequential seach which just goes in sequential order throughout the entire set until the element is found.
 * Run time: O(n)
*/
int findElement(SET *sp, char *elt)
{
	int i;
	
	assert(sp != NULL);	
	for (i=0; i<sp->count; i++)
		if (strcmp(sp->elts[i], elt) == 0)
			return i;
	return -1;
}

/* Deallocates memore to destroy a set. Make sure to deallocate in steps, from elements to array to set.
 * Run time: O(n)
*/
void destroySet(SET *sp)
{
	int i;
	
	assert(sp != NULL);
	for (i=0; i<sp->count; i++)
		free(sp->elts[i]);
	free(sp->elts);
	free(sp);
}

/* Return number of elements in set.
 * Run time: O(1)
*/
int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->count;
}

/* Returns whether element is part of a set or not, returning a boolean value.
 * Run time: O(logn)
*/
bool hasElement(SET *sp, char *elt)
{
	int x;

	assert(sp != NULL);
	x = findElement(sp, elt);
	if (x<0)
		return false;
	else
		return true;
}	


/* Inserts elements into set; however, must check to make sure array is not full or the element is not already in the array. Remember to increase the count.
 * Run time: O(n)
*/
bool addElement(SET *sp, char *elt)
{
	assert(sp != NULL && elt != NULL);
	if (sp->count == sp->length || findElement(sp, elt) != -1)
		return false;
	elt = strdup(elt);
	assert(elt != NULL);
	sp->elts[sp->count++] = elt;
	return true;
}

/* Remove element in array, rermember to checkk that the aray is not empty or that the element being removed is actually there.
 * Run time: O(n)
*/
bool removeElement(SET *sp, char *elt)
{
	int x;

	assert(sp != NULL && elt != NULL);
	x = findElement(sp, elt);
	if (x == -1)
		return false;
	else
	{
		sp->elts[x] = strdup(sp->elts[sp->count-1]);
		free(sp->elts[sp->count-1]);
		sp->count--;
		return true;
	}
}
