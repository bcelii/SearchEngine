#include "LookUpTable.h"
#include<string>
LookUpTable::LookUpTable()
{
}

LookUpTable::~LookUpTable(){
    delete[] tableFile;
}

//setters, getters
int LookUpTable::getNumberOfFiles(void){
    return numberOfFiles;
}

void LookUpTable::setNumberOfFiles(int passedNumb){
    numberOfFiles = passedNumb;
}

char* LookUpTable::getTableFile(void){
    return tableFile;
}

void LookUpTable::setTableFile(char* passedFile){
    tableFile = passedFile;
}

//will add XML page just processed to external lookup table in memory
/*void LookUpTable::addPage(string* author, string* title,
               string* fileName, int ID){

}*/
//add multiple XML pages to external lookup table in memory
/*void LookUpTable::addMultiplePages(string** author, string** title,
                        string** fileName, int* ID){

}*/

//functions to retrieve info from table based on ID of page
/*string* LookUpTable::getAuthor(int ID){

}*/

/*string* LookUpTable::getTitle(int ID){

}

char* LookUpTable::getFileName(int ID){

}

*/

