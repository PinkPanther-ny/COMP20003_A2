/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/

#ifndef myLinkedList
#define myLinkedList

#include <assert.h>
#include "myCLUE.h"

typedef struct Node Node_t;
struct Node{
    
    Clue_t * data;
    Node_t * next;
    
};

typedef struct List{
    
    Node_t * head;
    Node_t * foot;
    
}List_t;

// Function prototypes
void Node(Node_t *this, Clue_t *data, Node_t *next);
List_t *creatLinkedList();
List_t *push(List_t *list, Clue_t *data);
int linearSearch(char *keyWord, List_t *src, List_t *result);
void putLinkedList(List_t *src, FILE *fp);
void freeLinkedList(List_t *list);
void freeListNode(List_t *list);
#endif
