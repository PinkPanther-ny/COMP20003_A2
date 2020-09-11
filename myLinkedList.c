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

KDT_t * createKDT(Clue_t * data, int depth){
    KDT_t * root = (KDT_t *)malloc(sizeof(KDT_t));
    assert(root != NULL);
    
    root -> parent = NULL;
    root -> left = NULL;
    root -> right = NULL;
    root -> listData = creatLinkedList();
    pushToLinearList(root -> listData, data);
    root -> depth = depth;
    return root;
}

KDT_t * addToKDT(KDT_t * root, Clue_t * newNode, int * depth){
    
    *depth += 1;
    if (root == NULL){
    
        *depth -= 1;
        //printf("if (root == NULL)\n");
        return createKDT(newNode, *depth);
    }
    
    if(cmp(newNode, root, (*depth)%2) == -1){
        //printf("Equal\n");
        pushToLinearList(root -> listData, newNode);
        
    }else if (cmp(newNode, root, (*depth)%2)){
        //printf("LEFT\n");
        root->left = addToKDT(root->left, newNode, depth);
        root->left->parent = root;
        
    }else{
        //printf("Right\n");
        root->right = addToKDT(root->right, newNode, depth);
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
    
    if(point_cmp(root, key, axis?0:1) == 0){
        printf("Search direction: EQUAL\n");
        return root;
        
    }else if (point_cmp(root, key, axis?0:1) < 0){
        if(root->left == NULL){
        printf("Search direction: left == NULL\n");return root;}
        printf("Search direction: LEFT\n");
        return searchKDT(root->left, key, axis?0:1, depth);
        
    }else{
        if(root->right == NULL){
        printf("Search direction: right == NULL\n");return root;}
        printf("Search direction: RIGHT\n");
        return searchKDT(root->right, key, axis?0:1, depth);
       
    }
    
    
}

void compute_nearest(KDT_t * leaf, Point_t key, int *depth, double *nearest){

    // Find the sub tree that could contain the key point
    double a=(fabs(point_cmp(leaf, key, (*depth+1)%2)));
    double b= (*nearest);
    
    /*printf("******In compute_nearest, leaf to key axis(%d) distance:%f, \nFIRST nearest%f,leafparent %s***leaf%s***\n\n",
    (*depth+1)%2,a,b,leaf->parent->listData->head->data->location,leaf->listData->head->data->location );*/
    
    while( a < b && ((leaf->parent)!=NULL)){
        leaf = leaf->parent;
        (*depth)--;
        
        a=(fabs(point_cmp(leaf, key, (*depth+1)%2)));
        b= (*nearest);
        
        /*printf("******In compute_nearest, leaf to key axis(%d) distance:%f, \n nearest%f,leafparent %s***leaf%s***\n\n",
        (*depth+1)%2,a,b,leaf->parent->listData->head->data->location,leaf->listData->head->data->location );*/
        
    }
    
    printf("After while loop, highest node is %s\n", leaf->listData->head->data->location);
    
    
}

int point_cmp(KDT_t * curRoot, Point_t key, int axis){

    Point_t curRoot_p = getClueLocation(curRoot->listData->head->data);
    
    if((key.x == curRoot_p.x) && (key.y == curRoot_p.y)){
        return 0;
    }
    
    if(axis){
        return (key.x - curRoot_p.x);
    }else{
        return (key.y - curRoot_p.y);
    }
    
}

List_t * LRV_cmp(KDT_t * root, Point_t key, int *depth, double *nearest){
    *depth += 1;
    if (root == NULL){
        *depth -= 1;
        return NULL;
    }
    LRV_cmp(root->left, key, depth, nearest);
    LRV_cmp(root->right, key, depth, nearest);
    

    double curDistance = PointdistanceTo(key, root->listData->head->data);
    //printf("(%f,%f) to %s = %f\n", key.x,key.y,root->listData->head->data->location, curDistance);
    if (curDistance <= (*nearest)){
        *nearest = curDistance;
        printf("Found Result: %s\n", root->listData->head->data->location);
        /*
        Point_t pp= getClueLocation(root->listData->head->data);
        printf("(%.8f, %.8f)\n\n", pp.x, pp.y);*/
        return root->listData;
    }
    
    return root->listData;
}