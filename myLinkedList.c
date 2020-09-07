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
push(List_t *list, Clue_t *data){
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


int 
linearSearch(char *keyWord, List_t *src, List_t *result){
    int found = 0;
    Node_t * ptr = src->head;
    while(ptr != NULL){
    
        if (strcmp(ptr->data->tradingName, keyWord)==0){
            push(result, ptr->data);
            found++;
        }
        ptr = ptr->next;
    }
    return found;
    
}
