/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/

#include "myCLUE.h"
#include "myLinkedList.h"
#include "myCSV_Parser.h"

int
main(int argc, char *argv[]) {
    assert(argc==3);
    char *dataFile = argv[1], *outputFile = argv[2];
    
    List_t * list = creatLinkedList();
    readFileToList(list, dataFile);
    
    /* Clear file content if not empty */
    FILE * fp;
    fp = fopen(outputFile, "w");
    fp=freopen(NULL,"w",fp);
    assert(fp!=NULL);
    
    int foundNum;
    char keyWord[MAX_FIELD_LEN+1];
    List_t * result;
    
    char log[MAX_LOG_LEN];
    printf("\nEnter Trading Name to search(^D return results):\n");
    /* Read a line because keyword could contains space */
    while(scanf("%[^\n]%*c", keyWord)!=EOF){
    
        result = creatLinkedList();
        // Temperary keep track of each keyword's matches
        // Cannot do freeLinkedList() since the function also free the data
        // and data address is the same to data in the storage list
        // free whole result will cause missing data in the main storage list.
        // Only need to free each node here
        // takes me 3 days to solve this one haha
        
        foundNum = linearSearch(keyWord, list, result);
        if(!foundNum){
            putClueInfo(NULL, fp, keyWord);
            
            memset(log, 0, sizeof(log));
            strcat(log, NOT_FOUND);
            printf("%28s\t%s\n",log, keyWord);
        }else{
            putLinkedList(result, fp);
            
            char tmp[5];
            sprintf(tmp, "%d", foundNum);
            memset(log, 0, sizeof(log));
            strcat(log, FOUND1);
            strcat(log, tmp);
            strcat(log, FOUND2);
            printf("%28s\t%s\n", log, keyWord);
        }
        freeListNode(result);
        
    }
    fclose(fp);
    
    /* Free the linked list that stores whole data */
    freeLinkedList(list);
    
    printf("\n\n");
    
    return 0;
}

