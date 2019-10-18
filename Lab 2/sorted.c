/* Jake Vargas
 * COEN 12 Project 2 Part 2
 * Professor Atkinson
 * Lab Section: Thursday 9:15
 
  Description:
  	This will be very similar to Part 1; however, in this implementation, we will be using a sorted array to hold a certain amount of strings in ascending order. Because of this, we will be using a binary search instead of sequential search to try and cut back on the time needed to run.
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

/* Allocate memory to create set, then initializes each variable within set. Returns a pointer to the set that was created.
 * Run time: O(1)
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

/* This function finds an element in the set, and returns the position when called. A binary search is used to compete this, where at each step, half of the remaining possibilities are eliminated.
 * Run time:O(logn)
*/ 
int findElement(SET *sp, char *elt, bool *found)
{
	int lo, hi, mid, diff;
	lo = 0;
	hi = sp->count-1;

	assert(sp != NULL && elt != NULL);
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		diff = strcmp(elt, sp->elts[mid]);
		if (diff<0)
			hi = mid-1;
		else if (diff>0)
			lo = mid+1;
		else
		{
			*found = true;
			return mid;
		}
	}
	
	*found = false;
	return lo;
}

/* Deallocate memory to destroy a set. Make sure to deallocate in steps, from element to array to set.
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
	assert (sp != NULL);
	return sp->count;
}

/* Returns whether element is part of a set or not, returning a boolean value.
 * Run time: O(logn)
*/
bool hasElement(SET *sp, char *elt)
{
	bool found;
	assert(sp != NULL && elt != NULL);

	findElement(sp, elt, &found);
	if (found == true)
		return true;
	else
		return false;
}	

/*Inserts elements into set; however, must check to make sure array is not full or the element is not already in the array. Remember to increase count and to make the elements shift over when inserting.
 * Run time: O(n)
*/
bool addElement(SET *sp, char *elt)
{
	bool found;
	int x, i;
	
	assert(sp != NULL && elt != NULL);
	
	x = findElement(sp, elt, &found);
	if (sp->count == sp->length || found == true)
		return false;
	else
	{
		for (i=sp->count-1; i>=x; i--)
			sp->elts[i+1] = sp->elts[i];
		sp->elts[x] = strdup(elt);
		sp->count++;
		return true;
	}
}

/* Remove element from array; however, remember to check that the array is not empty or that the element being removed is actually there. Remember to shift elements when removing. 
 * Run time: O(n)
*/ 
bool removeElement(SET *sp, char *elt)
{
	int x, i;
	bool found;

	assert(sp != NULL && elt != NULL);
	if (sp->count == 0)
		return false;
	x = findElement(sp, elt, &found);
	if (found == true)
	{
		free(sp->elts[x]);
		for (i=x; i<sp->count; i++)
			sp->elts[i] = sp->elts[i+1];
		sp->count--;
		return true;
	}
	else
	{
		return false;
	}
}
