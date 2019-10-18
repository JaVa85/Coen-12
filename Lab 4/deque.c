/* Jake Vargas
 * COEN 12 Project 4
 * Professor Atkinson
 * Lab Section: Thursday 9:15
 
   Description: In this lab we will create an abstract data type using a circular, doubly-linked list with a dummy node. This will be used together with a given program to complete a maze.
*/

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h> 
#include "deque.h"

typedef struct node NODE;

struct node
{
	int data;
	struct node *next;
	struct node *prev;
};

struct deque
{
	int count;
	struct node *head;
};

/* Description: create new deque pointer and head node. Return the pointer to the deque.
 * Runtime: O(1)
 * */
DEQUE *createDeque()
{
	DEQUE *dp;

	dp = malloc(sizeof(DEQUE));
	assert(dp != NULL);
	dp->head = malloc(sizeof(NODE));
	assert(dp->head != NULL);

	dp->head->next = dp->head;
	dp->head->prev = dp->head;

	dp->count = 0;

	return dp;	
}

/* Description: deallocate memory in the linked list using a temp node pointer.
 * Runtime: O(L), L = length of list
 * */
void destroyDeque(DEQUE *dp)
{
	NODE *dummy = dp->head->next;
	NODE *temp;
	
	while (dummy != dp->head && dummy != NULL)	//check to make sure dp->head is not the only thing in the list and also make sure that goes through the entire circular list (where head is the end of the list)
	{
		temp = dummy;
		dummy = dummy->next;
		free(temp);
	}

	free (dp->head);
	free (dp);
	
	return;
}

/* Description: Return number of items in list.
 * Runtime: O(1)
 * */
int numItems(DEQUE *dp)
{
	return dp->count;
}


/* Description: Add data at beginning of the list.
 * Runtime: O(1)
 * */
void addFirst(DEQUE *dp, int x)
{
	NODE *new = malloc(sizeof(NODE));
	assert(new != NULL);

	new->data = x;
	dp->head->next->prev = new;
	new->next = dp->head->next;
	new->prev = dp->head;
	dp->head->next = new;
	dp->count++;
}

/* Description: Add data at end of the list.
 * Runtime: O(1)
 * */
void addLast(DEQUE *dp, int x)
{
	NODE *new = malloc(sizeof(NODE));
	assert(new != NULL);

	new->data = x;
	dp->head->prev->next = new;
	new->prev = dp->head->prev;
	new->next = dp->head;
	dp->head->prev = new;
	dp->count++;
}

/* Description: Removes first node in list. Remember to return data value of node being freed.
 * Runtime: O(1)
 * */
int removeFirst(DEQUE *dp)
{
	int tempData = 0;

	if (dp->count == 0)	//make sure something is in the list
		return -1;

	tempData = dp->head->next->data;

	NODE *temp = dp->head->next;

	dp->head->next = temp->next;
	temp->next->prev = dp->head;

	free(temp);
	dp->count--;
	
	return tempData;
}

/* Description: Removes last node in list. Remember to return data value of node being freed.
 * Runtime: O(1)
 * */
int removeLast(DEQUE *dp)
{
	int tempData = 0;

	if (dp->count == 0)	//check to make sure something is in the list
		return -1;

	tempData = dp->head->prev->data;

	NODE *temp = dp->head->prev;

	dp->head->prev = temp->prev;
	temp->prev->next = dp->head;

	free(temp);
	dp->count--;

	return tempData;
}

/* Description: Return data value of first node.
 * Runtime: O(1)
 * */
int getFirst(DEQUE *dp)
{
	return dp->head->next->data;
}

/* Description: Return value of last nade.
 * Runtime: O(1)
 * */
int getLast(DEQUE *dp)
{
	return dp->head->prev->data;
}
