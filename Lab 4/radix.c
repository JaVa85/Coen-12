/* Jake Vargas
 * COEN 12 Project 4
 * Professor Atkinson
 * Lab Section: Thursday 9:15

   Decription: In this lab we will create a main function that takes inputs from users and sorts integers using a radix sorting algorithm.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

int divisor = 1;
void sortrad(DEQUE* *dp, DEQUE *user, int dig); 

int main (void)
{
	int i;
	int j;
	int k;
	int count;
	int tempdig;
	int temp;
	int tempcount;
	int max = 0;
	int maxDig = 0;
	int divisor =1;
	DEQUE *rArray[10];
	DEQUE *user;	

	user = createDeque();	//O(1) runtime
	for (i=0; i<10; i++)
		rArray[i] = createDeque();	//O(1) runtime

	printf("Please input 10 integer values to be sorted. Input a character if you would like to run the program early.\n");

	while (scanf("%d\n",&tempdig) == 1)	//while user inputs integers
	{
		if (tempdig > max)	//update max
			max = tempdig;
		addFirst(user, tempdig);	//O(1) runtime
	}
	
	maxDig = ceil((log(max+1))/(log(10)));
	count = numItems(user);	//O(1) runtime
	
	for (i=0; i<maxDig; i++)	//this goes through the digits of the inputted numbers
	{
		for (j=0; j<count; j++)	//this sorts the digits
		{
			temp = removeLast(user);
			addFirst(rArray[(temp/divisor)%10], temp);	//O(1) runtime
		}
		
		for (j=0; j<10; j++)	//puts back into main deque with new ordered digits and goes through another iteration
		{
			tempcount = numItems(rArray[j]);	//O(1) runtime
			for (k=0; k<tempcount; k++)
				addFirst(user, removeLast(rArray[j]));	//O(1) runtime
			
		}
		
		divisor *= 10;	//update digit to move to next digit
	}

	for (j=0; j<count; j++)	//print the sorted deque
	{
		printf("%d\n", getFirst(user));	//O(1) runtime
		addLast(user, removeFirst(user));	//O(1) runtime
	}

	destroyDeque(user);	//O(L) , L = length of list

	for (i=0; i<10; i++)	//deallocate all memory
		destroyDeque(rArray[i]);	//O(1) runtime
	
	return 0;
}


