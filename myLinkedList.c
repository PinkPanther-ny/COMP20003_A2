/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 9/2020
* 2020s2 UNIMELB COMP20003 assignment 2
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


void
printList(List_t *list) {
    assert(list!=NULL);
    Node_t *cur;
    
    cur = list->head;
    while (cur) {
        printf("%s\t",cur->data->location);
        cur = cur->next;
    }
    printf("\n");
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
    
    root -> parent = NULL;
    root -> left = NULL;
    root -> right = NULL;
    root -> listData = creatLinkedList();
    pushToLinearList(root -> listData, data);
    return root;
}

KDT_t * addToKDT(KDT_t * root, Clue_t * newNode, int axis){
    if (root == NULL){
        //printf("if (root == NULL)\n");
        return createKDT(newNode);
    }
    
    if(cmp(newNode, root, axis?0:1) == -1){
        //printf("Equal\n");
        pushToLinearList(root -> listData, newNode);
        
    }else if (cmp(newNode, root, axis?0:1)){
        //printf("LEFT\n");
        root->left = addToKDT(root->left, newNode, axis?0:1);
        root->left->parent = root;
        
    }else{
        //printf("Right\n");
        root->right = addToKDT(root->right, newNode, axis?0:1);
        root->right->parent = root;
       
    }
    
    //printf("ROOT\n");
    return root;
    
}


int cmp(Clue_t * newData, KDT_t * curRoot, int axis){
    Point_t new_p = getClueLocation(newData);
    Point_t curRoot_p = getClueLocation(curRoot->listData->head->data);
    
    if(new_p.x == curRoot_p.x && new_p.y == curRoot_p.y){
        return -1;
    }
    
    if(axis){
        return new_p.x < curRoot_p.x;
    }else{
        return new_p.y < curRoot_p.y;
    }
}

void VLR_Print(KDT_t * root, int *depth){
    *depth += 1;
    if (root == NULL){
        *depth -= 1;
        return;
    }
    printf("At depth %d: ", *depth);
    printList(root->listData);
    VLR_Print(root->left, depth);
    VLR_Print(root->right, depth);
    *depth -= 1;
}

void LVR_Print(KDT_t * root, int *depth){
    *depth += 1;
    if (root == NULL){
        *depth -= 1;
        return;
    }
    
    VLR_Print(root->left, depth);
    printf("At depth %d: ", *depth);
    printList(root->listData);
    VLR_Print(root->right, depth);
    *depth -= 1;
}

void LRV_Free(KDT_t * root){
    if (root == NULL){
        return;
    }
    LRV_Free(root->left);
    LRV_Free(root->right);
    freeKDT_Node(root);
}

void freeKDT_Node(KDT_t * root){
    freeLinkedList(root->listData);
    free(root->left);
    free(root->right);
    // No need to free parent, 
    // since it will be freed as parent node call free
}

// Return the parent node of the key point as if 
// the key point is in the tree(but not).
// or Return the node if it is exactly the same to the key point
KDT_t * searchKDT(KDT_t * root, Point_t key, int axis, int *depth){

    assert(root!=NULL);
    *depth += 1;
    
    if(!point_cmp(key, root, axis?0:1)){
        printf("Equal\n");
        return root;
        
    }else if (point_cmp(key, root, axis?0:1) < 0){
        printf("LEFT\n");
        if(root->left == NULL){return root;}
        return searchKDT(root->left, key, axis?0:1, depth);
        
    }else{
        printf("Right\n");
        if(root->right == NULL){return root;}
        return searchKDT(root->right, key, axis?0:1, depth);
       
    }
    
    
}

int point_cmp(Point_t key, KDT_t * curRoot, int axis){

    Point_t curRoot_p = getClueLocation(curRoot->listData->head->data);
    
    if(key.x == curRoot_p.x && key.y == curRoot_p.y){
        return 0;
    }
    
    if(axis){
        return (key.x - curRoot_p.x);
    }else{
        return (key.y - curRoot_p.y);
    }
    
}

void compute_nearest(KDT_t * root, Point_t key, int *depth, double *nearest, KDT_t * result){

    while(point_cmp(key, root, (*depth+1)%2) <= *nearest && root->parent!=NULL){
        root = root->parent;
    }
    LRV_cmp(root, key, depth, nearest, result);
    
}

void LRV_cmp(KDT_t * root, Point_t key, int *depth, double *nearest, KDT_t * result){
    *depth += 1;
    if (root == NULL){
        *depth -= 1;
        return;
    }
    LRV_cmp(root->left, key, depth, nearest, result);
    LRV_cmp(root->right, key, depth, nearest, result);
    double curDistance = PointdistanceTo(key, root->listData->head->data);
    printf("{%s}",root->listData->head->data->location);
    if (curDistance < *nearest){
        result = root;
        *nearest = curDistance;
    }
}