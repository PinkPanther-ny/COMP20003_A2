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

    FILE * fp;
    fp = fopen(outputFile, "w");
    fp=freopen(NULL,"w",fp);
    assert(fp!=NULL);


    KDT_t * root = NULL;
    Point_t key;
    KDT_t * keyParent;
    KDT_t * result;
    int compareTime;
    double nearest;

    root = readFileToTree(root, dataFile);
    while (scanf("%lf%*c%lf%*c", &(key.x), &(key.y))!=EOF) {

        keyParent = NULL;
        result = NULL;
        compareTime = 0;

        keyParent = searchKDT(root, key);
        printf("After searchKDT, key's parent is %s\n", keyParent->listData->head->data->location);
        nearest = distanceTo(
                        key,
                        getClueLocation(keyParent->listData->head->data)
                  );
        keyParent = compute_nearest(keyParent, key, &nearest);
        printf("After compute nearest, highest key's parent is %s at depth %d\n", keyParent->listData->head->data->location, keyParent->depth);
        result = VLR_search(keyParent, key, &nearest, result, &compareTime);
        fwriteLinkedList(result->listData, fp, key);
        
        printf("%.6f %.6f --> %d\n", key.y, key.x, compareTime);
        printf("%s\n",result->listData->head->data->location);
    }

    LRV_Free(root);
    free(root);
    fclose(fp);
    return 0;
}
