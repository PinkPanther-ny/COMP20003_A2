/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 9/2020
* 2020s2 UNIMELB COMP20003 assignment 2
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

typedef struct KDT KDT_t;
struct KDT{
    KDT_t * parent;
    KDT_t * left;
    KDT_t * right;
    List_t * listData;
    int depth;
};

// Function prototypes
void Node(Node_t *this, Clue_t *data, Node_t *next);
List_t *creatLinkedList();
List_t *pushToLinearList(List_t *list, Clue_t *data);
int linearSearch(char *keyWord, List_t *src, List_t *result);
void putLinkedList(List_t *src, FILE *fp);
void freeLinkedList(List_t *list);
void freeListNode(List_t *list);
void printList(List_t *list);


// Function prototypes
Point_t * Point(double x, double y);
KDT_t * createKDT(Clue_t * data, int depth);
KDT_t * addToKDT(KDT_t * root, Clue_t * newNode, int * depth);

List_t *pushToKDT(List_t *list, Clue_t *data);
int cmp(Clue_t * newData, KDT_t * curRoot, int axis);
void LVR_Print(KDT_t * root);
void VLR_Print(KDT_t * root);
void LRV_Free(KDT_t * root);
void freeKDT_Node(KDT_t * root);
KDT_t * searchKDT(KDT_t * root, Point_t key);
int point_cmp(KDT_t * curRoot, Point_t key);
KDT_t * compute_nearest(KDT_t * keyParent, Point_t key, double *nearest);
void VLR_search(KDT_t * keyParent, Point_t key, double *nearest, KDT_t * result);
List_t * LRV_cmp(KDT_t * root, Point_t key, int *depth, double *nearest);
#endif
