/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/

#include "myCLUE.h"

/* Constructor for Clue_t */
Clue_t *
Clue(
    char* censusYear, char* blockID, char* propertyID, char* basePropertyID,
    char* clueSmallArea, char* tradingName, char* industryCode, char* industryDescription, 
    char* xCoord, char* yCoord, char *location
    ){
    
    Clue_t *this = (Clue_t*)malloc(sizeof(Clue_t));
    assert(this != NULL);
    
    this -> censusYear = censusYear;
    this -> blockID = blockID;
    this -> propertyID = propertyID;
    this -> basePropertyID = basePropertyID;
    
    this -> clueSmallArea = clueSmallArea;
    this -> tradingName = tradingName;
    this -> industryCode = industryCode;
    this -> industryDescription = industryDescription;
    
    this -> xCoord = xCoord;
    this -> yCoord = yCoord;
    this -> location = location;
    return this;
}

/**
* Put a Clue_t type object to a given file
* if clue is NULL, put keyword not found
* param clue -A Clue_t pointer points to CLUE information
* param fp -A file pointer point to the output file
*/
void 
putClueInfo(Clue_t *clue, FILE * fp, char *keyWord){

    if(clue==NULL){
        fprintf(
            fp,
            "%s −− >NOTFOUND\n\n",
            keyWord
        );
    
    }else{
        fprintf(
            fp,
            "%s --> Census year: %s || Block ID: %s || "
            "Property ID: %s || Base property ID: %s || "
            "CLUE small area: %s || "
            "Industry (ANZSIC4) code: %s || "
            "Industry (ANZSIC4) description: %s || "
            "x coordinate: %s || y coordinate: %s || "
            "Location: %s || \n",
            clue -> tradingName,
            clue -> censusYear, clue -> blockID,
            clue -> propertyID, clue -> basePropertyID, 
            clue -> clueSmallArea, 
            clue -> industryCode, 
            clue -> industryDescription, 
            clue -> xCoord, clue -> yCoord, 
            clue->location
        );
    }
}

/**
* param fields -A 2D array that store the information of one line of csv file
* return clue -A pointer to a Clue_t data which store the line
*/
Clue_t * 
storeFields(char *fields[]){
    // Call the Clue_t constructor, return its address
    Clue_t * clue = Clue(
    
        fields[FIELD_CENSUS_YEAR], 
        fields[FIELD_BLOCK_ID],
        fields[FIELD_PROPERTY_ID], 
        fields[FIELD_BASE_PROPERTY_ID], 
        
        fields[FIELD_CLUE_SMALL_AREA], 
        fields[FIELD_TRADING_NAME], 
        fields[FIELD_INDUSTRY_CODE], 
        fields[FIELD_INDUSTRY_DESCRIPTION],
        
        fields[FIELD_X_COORD], 
        fields[FIELD_Y_COORD], 
        fields[FIELD_LOCATION]
    
    );
    
    return clue;
}
