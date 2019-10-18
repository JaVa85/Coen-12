/*	Jake Vargas
	  Lab 1
       Thursday 9:15	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 30

void read_file(char*);		//prototype the function

/* The main function either runs the function to read or prints an error message if no file name used. */
int main (int argc, char *argv[])	
{
        if (argc == 1)	//check to see if a file is given
        {
                printf("The name of the file is missing!\n");
                exit(1);
        }
        else
                read_file(argv[1]);
}

/* This file is used to open and count the number of words in the text file. The funtcion should also check to make sure there is an actual file being used. */ 
void read_file (char *x)
{
	FILE *fp;
	char words[max];
	int cnt = 0;

        if ((fp = fopen(x, "r")) == NULL)	//check to make sure the file used is an actual file
	{
		printf("Error, no such file.\n");
		exit(1);
	}

        while (fscanf(fp, "%s", words) == 1)	//read string by string from file and increase counter
                cnt++;

        printf("%d total words\n", cnt);

        fclose (fp);
        return;
}

