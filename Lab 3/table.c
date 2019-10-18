/* COEN 12 Project 3
 * Professor Atkinson
 * Lab Section: Thursday 9:15

   Description: In this lab, we will still be using a set ADT with different functions; however, we will be using hashing instead of sequential or binary searching. The type of hashing resolution technique being used will be linear probing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define DELETED -1


struct set
{
        int count;
        int length;
        char* *elts;
        char *flag;
};


/* Description: create a set with a maximum size of maxElts. Return a pointer to this new set that was created. Make sure to initialize the set to empty when created.
 * Runtime: O(1)
 */
SET *createSet(int maxElts)
{
        SET *sp;
	int i;
	
        sp = malloc(sizeof(SET));
        assert(sp != NULL);

        sp->count = 0;
        sp->length = maxElts;

        sp->elts = malloc(sizeof(char*)*maxElts);
        assert(sp->elts != NULL);
        sp->flag = malloc(sizeof(char)*maxElts);
        assert(sp->flag != NULL);

        for (i=0; i<sp->length; i++)	//Newly created sets are initialized to EMPTY 
                sp->flag[i] = EMPTY;

        return sp;
}


/* Description: Hash function given to minimize collisions. Returns the position where string hashes to.
 * Runtime O(m) (m = string length)
 */
unsigned hashString(char *s)
{
        unsigned hash = 0;

        while (*s != '\0')
                hash = 31 * hash + *s++;

        return hash;
}


/* Description: This function uses linear probing to find an element within the set and returns if the element in the array was found and the location of where it is or where it should be. This is done by checking the flags in the array at the hash location that was recieved from another function. Remember to check three different cases, EMPTY, FILLED, DELETED.
 * Runtime: O(1) (this is the best case, but could be O(n) in the worst case)
 */
int findElement(SET *sp, char *elt, bool *found)
{
        unsigned start;
        int i, hashpos;
        int del = 2;

        start = hashString(elt)%sp->length;	//Find the initial hash position

        for (i=0; i<sp->length; i++)		//Check the entirety of the set
        {
                hashpos = (start+i)%sp->length;		//Linear Probing

                if (sp->flag[hashpos] == EMPTY)
		{
			*found = false;
			if (del == 2)
				return hashpos;
			return del;
		}
                else if (sp->flag[hashpos] == FILLED)
                {
                        if (strcmp(sp->elts[hashpos], elt) == 0)
                        {
                                *found = true;
                                return hashpos;
                        }
                }
		else if (sp->flag[hashpos] == DELETED)
		{
			if (del == 2)
				del = hashpos;
		}
        }

        *found = false;
        return hashpos;
}


/* Description: Deallocate all memory that is involved with the set.
 * Runtime: O(n)
 */
void destroySet(SET *sp)
{
        int i;

        assert(sp != NULL);

        for (i=0; i<sp->length; i++)		//Check entirety of set
                if (sp->flag[i] == FILLED)	//Only those with elements get deleted
                        free(sp->elts[i]);
        free(sp->flag);
        free(sp->elts);
        free(sp);
}


/* Description: Return the number of elements in set.
 * Runtime: O(1)
 */
int numElements(SET *sp)
{
        assert(sp != NULL);

        return sp->count;
}


/* Description: Returns whether element has been found in the set or not.
 * Runtime: O(1) (this depends of findElement)
 */
bool hasElement(SET *sp, char *elt)
{
        bool found;

        findElement(sp, elt, &found);
	return found;
}


/* Description: Adds element to the set if not previously found or if the array is already full. The hash position is given by findElement and the flag must be changed to filled.
 * Runtim: O(1) (depends on findElement)
 */
bool addElement(SET *sp, char *elt)
{
	bool found;
	int hashpos;

	hashpos = findElement(sp, elt, &found);
	if (sp->count == sp->length)
		return false;

	if (found == true)
		return false;

	if (found == false)
	{
		sp->elts[hashpos] = strdup(elt);
	}

	sp->flag[hashpos] = FILLED;
	sp->count++;
	return true;
}


/* Description: Remove an element whose position is given by findElement and whose flag must be changed to DELETED.
 * Runtime: O(1) (depends on findElement)
 */ 
bool removeElement(SET *sp, char *elt)
{
	bool found;
	int hashpos;

	hashpos = findElement(sp, elt, &found);

	if (found == false)
		return false;
	else
	{
		free(sp->elts[hashpos]);
		sp->flag[hashpos] = DELETED;			
		sp->count--;
		return true;
	}
}
