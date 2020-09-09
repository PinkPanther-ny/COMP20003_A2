/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/

#ifndef myLinkedList
#define myLinkedList

#include <assert.h>
#include "myCLUE.h"

#define K 2
typedef struct Node Node_t;
struct Node{
    
    Clue_t * data;
    Node_t * next;
    
};

typedef struct List{
    
    Node_t * head;
    Node_t * foot;
    
}List_t;

typedef struct Point{
    double x;
    double y;
}Point_t;


typedef struct KDT KDT_t;
struct KDT{
    KDT_t * left;
    KDT_t * right;
    Clue_t * data;
};

// Function prototypes
void Node(Node_t *this, Clue_t *data, Node_t *next);
List_t *creatLinkedList();
List_t *pushToLinearList(List_t *list, Clue_t *data);
int linearSearch(char *keyWord, List_t *src, List_t *result);
void putLinkedList(List_t *src, FILE *fp);
void freeLinkedList(List_t *list);
void freeListNode(List_t *list);


// Function prototypes
Point_t * Point(double x, double y);
KDT_t * createKDT(Clue_t * data);
KDT_t * addToKDT(KDT_t * root, KDT_t * newNode, int axis);

List_t *pushToKDT(List_t *list, Clue_t *data);
Point_t getClueLocation(Clue_t *data);
int cmp(KDT_t * a, KDT_t * b, int axis);
#endif
