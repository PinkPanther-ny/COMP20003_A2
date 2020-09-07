/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/


#ifndef myCSV_Parser
#define myCSV_Parser

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "myLinkedList.h"
#include "myCLUE.h"

// Function prototypes
char *splitOneToken(char *line, int * lineIndex);
void readFileToList(List_t *dest, char *filename);

#endif