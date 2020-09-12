/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 9/2020
* 2020s2 UNIMELB COMP20003 assignment 2
*/

#include "myCLUE.h"
#include "myLinkedList.h"
#include "myCSV_Parser.h"

int
main(int argc, char *argv[]) {
    assert(argc==3);
    char *dataFile = argv[1], *outputFile = argv[2];

    KDT_t * root = NULL;
    root = readFileToTree(root, dataFile);
    /*
    printf("%s, depth: %d\n",root->listData->head->data->location, root->depth);
    printf("%s, depth: %d\n",root->left->listData->head->data->location, root->left->depth);
    printf("%s, depth: %d\n",root->left->left->listData->head->data->location, root->left->left->depth);
    printf("%s, depth: %d\n",root->left->right->listData->head->data->location, root->left->right->depth);
    printf("%s, depth: %d\n",root->right->listData->head->data->location, root->right->depth);
    printf("%s, depth: %d\n",root->right->left->listData->head->data->location, root->right->left->depth);
    printf("%s, depth: %d\n\n",root->right->right->listData->head->data->location, root->right->right->depth);


    printf("LVR inorder (in key's order):\n");
    LVR_Print(root);

    printf("\nVLR insert order:\n");
    VLR_Print(root);
    printf("\n");
    */
    /**************************************************************/

    FILE * fp;
    fp = fopen(outputFile, "w");
    fp=freopen(NULL,"w",fp);
    assert(fp!=NULL);


    Point_t key = {-37.800095, 144.959522};

    KDT_t * keyParent = NULL;
    KDT_t * result = NULL;
    int compareTime = 0;
    double nearest;

    keyParent = searchKDT(root, key);
    nearest = PointdistanceTo(key, keyParent->listData->head->data);
    keyParent = compute_nearest(keyParent, key, &nearest);
    result = VLR_search(keyParent, key, &nearest, result, &compareTime);
    putLinkedList(result->listData, fp, key);

    printf("%.6f %.6f --> %d", key.y, key.x, compareTime);
    //printf("\nResult: %s, Compare %d times", result->listData->head->data->location, compareTime);

    /*


    //List_t * result = NULL;
    result = LRV_cmp(leaf, p, &depth, &nearest);

    printf("\nResult: %s", result->head->data->location);
    printf("#nearest:%f#\n", nearest);

    */



    /*
    printf("{!!!%s!!!}",root->listData->head->data->location);
    printf("%lf", nearest);
    */
    /*
    printf("\n\n");
    printf("%s", root->listData->head->data->location);
    printf("%p", root);

    printf("%s", root->left->listData->head->data->location);
    printf("%s", root->left->parent->listData->head->data->location);
    printf("%p", root->left->parent);
    printf("%p", root->left->parent->parent);

    printf("%s", root->right->listData->head->data->location);

    printf("%s", root->right->left->listData->head->data->location);
    printf("%s", root->right->left->left->listData->head->data->location);
    printf("%s", root->right->left->right->listData->head->data->location);
    printf("%s", root->right->left->right->listData->head->next->data->location);*/

    LRV_Free(root);
    free(root);
    /* Clear file content if not empty */

    // int foundNum;
    // char keyWord[MAX_FIELD_LEN+1];
    // List_t * result;
    //
    // char log[MAX_LOG_LEN];
    // printf("\nEnter Trading Name to search(^D return results):\n");
    // /* Read a line because keyword could contains space */
    // while(scanf("%[^\n]%*c", keyWord)!=EOF){
    //
    //     result = creatLinkedList();
    //     // Temperary keep track of each keyword's matches
    //     // Cannot do freeLinkedList() since the function also free the data
    //     // and data address is the same to data in the storage list
    //     // free whole result will cause missing data in the main storage list.
    //     // Only need to free each node here
    //     // takes me 3 days to solve this one haha
    //
    //     foundNum = linearSearch(keyWord, list, result);
    //     if(!foundNum){
    //         putClueInfo(NULL, fp, keyWord);
    //
    //         memset(log, 0, sizeof(log));
    //         strcat(log, NOT_FOUND);
    //         printf("%28s\t%s\n",log, keyWord);
    //     }else{
    //         putLinkedList(result, fp);
    //
    //         char tmp[5];
    //         sprintf(tmp, "%d", foundNum);
    //         memset(log, 0, sizeof(log));
    //         strcat(log, FOUND1);
    //         strcat(log, tmp);
    //         strcat(log, FOUND2);
    //         printf("%28s\t%s\n", log, keyWord);
    //     }
    //     freeListNode(result);
    //
    // }
    fclose(fp);
    //
    // /* Free the linked list that stores whole data */
    // freeLinkedList(list);

    return 0;
}
