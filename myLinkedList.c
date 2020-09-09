/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/

#include "myLinkedList.h"

/* Constructor for Node_t */
void 
Node(Node_t *this, Clue_t *data, Node_t *next){
    
    assert(this != NULL);
    this -> data = data;
    this -> next = next;
}


List_t *
creatLinkedList(){
    List_t * list = (List_t *)malloc(sizeof(List_t));
    assert(list != NULL);
    list -> head = NULL;
    list -> foot = NULL;
    return list;
}


void
freeLinkedList(List_t *list) {
    assert(list!=NULL);
    Node_t *cur, *pre;
    
    cur = list->head;
    while (cur) {
        pre = cur;
        cur = cur->next;

        free(pre->data->censusYear);
        free(pre->data->blockID);
        free(pre->data->propertyID);
        free(pre->data->basePropertyID);
        
        free(pre->data->clueSmallArea);
        free(pre->data->tradingName);
        free(pre->data->industryCode);
        free(pre->data->industryDescription);
        
        free(pre->data->xCoord);
        free(pre->data->yCoord);
        free(pre->data->location);
        free(pre->data);
        
        free(pre);
    }
    free(list);
    
}


void
freeListNode(List_t *list) {
    assert(list!=NULL);
    Node_t *cur, *pre;
    
    cur = list->head;
    while (cur) {
        pre = cur;
        cur = cur->next;

        free(pre);
    }
    free(list);
    
}


void 
putLinkedList(List_t *src, FILE * fp){
    Node_t * ptr = src->head;
    while(ptr != NULL){
        putClueInfo(ptr->data, fp, NULL);
        ptr = ptr->next;
        
    }
}


/* Push an CLUE item to the head of the list */
List_t *
pushToLinearList(List_t *list, Clue_t *data){
    Node_t *newNode = (Node_t*)malloc(sizeof(Node_t));
    assert(newNode != NULL);
    
    // The first item
    if(list->head == NULL){
        Node(newNode, data, NULL);
        list -> foot = newNode;
    }else{
        Node(newNode, data, list -> head);
    }
    
    list -> head = newNode;
    return list;
    
}



/**************************************************************/

Point_t * Point(double x, double y){
    Point_t * this = (Point_t *)malloc(sizeof(Point_t));
    this -> x = x;
    this -> y = y;
    return this;
}

KDT_t * createKDT(Clue_t * data){
    KDT_t * root = (KDT_t *)malloc(sizeof(KDT_t));
    assert(root != NULL);
    root -> left = NULL;
    root -> right = NULL;
    root -> data = data;
    return root;
}

KDT_t * addToKDT(KDT_t * root, KDT_t * newNode, int axis){
    if (root == NULL){
        printf("if (root == NULL)\n");
        return newNode;
    }
    
    if (cmp(newNode, root, axis?0:1)){
        printf("LEFT\n");
        root->left = addToKDT(root->left, newNode, axis?0:1);
    }else{
        printf("Right\n");
        root->right = addToKDT(root->right, newNode, axis?0:1);
    }
    
    printf("ROOOT\n");
    return root;
    
}


int cmp(KDT_t * a, KDT_t * b, int axis){
    Point_t p1 = getClueLocation(a->data);
    Point_t p2 = getClueLocation(b->data);
    if(axis){
        return p1.x < p2.x;
    }else{
        return p1.y < p2.y;
    }
}


Point_t getClueLocation(Clue_t *data){
    Point_t p;
    char* str = data->location;
    char* pEnd;
    double d1, d2;
    d1 = strtod (str+1, &pEnd);
    d2 = strtod (pEnd+1, NULL);
    p.x = d1;
    p.y = d2;
    return p;

}
