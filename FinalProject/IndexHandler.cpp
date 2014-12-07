#include "IndexHandler.h"
#include "index.h"
#include"HashTable.h"
#include<cstring>
#include<fstream>
using namespace std;


IndexHandler::IndexHandler(int structureChoice)
{
    totalDocCount = 160000;
    if(structureChoice == 1){

        myIndex = new AvlTree<string>();
    }
    if(structureChoice == 2){
        myIndex = NULL;
        //cout<<"Index of Handler set to NULL"<<endl;
    }
    else{

        myIndex = new HashTable<string>();
    }


    myWordParser = new WordParser2();
    //Want default data structure
    //Index* myIndex = new AVLTree();

    memoryInputFile = new char[80];
    memoryOutputFile = new char[80];

    //set default input and output files
    strcpy(memoryInputFile,"input.txt");
    strcpy(memoryOutputFile,"output.txt");
}

bool IndexHandler::isIndexNULL(){
    if(myIndex == NULL){
        return true;
    }
    else{
        return false;
    }
}

void IndexHandler::createIndex(int choice){
    clearIndex();
    if(myIndex == NULL){
        delete myIndex;
    }

    if(choice == 1){

        myIndex = new AvlTree<string>();
    }
    else{

        myIndex = new HashTable<string>();
    }



}


IndexHandler::~IndexHandler(){
    delete myWordParser;
    delete myIndex;
    delete[] memoryInputFile;
    delete[] memoryOutputFile;
}

int IndexHandler::getTotalDocs(){
    return totalDocCount;
}

void IndexHandler::setTotalDocs(int newTotal){
   totalDocCount = newTotal;
}

//functions to manage storing off index in hard memory
void IndexHandler::setOutputFile(char* passedFile){
    memoryOutputFile = passedFile;
}

char* IndexHandler::getOutputFile(void){
    return memoryOutputFile;
}

void IndexHandler::setInputFile(char* passedFile){
    memoryInputFile = passedFile;
}

char* IndexHandler::getInputfile(void){
    return memoryInputFile;
}

//function reads formatted saved data into whatever data structure
//indicated by argument
void IndexHandler::buildIndexFromMemory(int choice){
     //open input file
    ifstream input;
    input.open(memoryInputFile);
    cout<<"memoryInputFile = "<<memoryInputFile<<endl;
    if(!input){
        cout<<"file did not open"<<endl;
    }

    string word;
    int page;
    int freq;

    while(input>>word){
        //cout<<word<<endl;
        //need new vector for each page
        vector<int>* pageList = new vector<int>();
        while(1){
            input>>page;
            //cout<<"Page = "<<page<<endl;
            if(page == -1){
                //go to next line
                //input.getline(dummy,390);
                myIndex->insert(word,pageList);
                break;
            }
            //if not hit end of page, frequency list
            input>>freq;
            pageList->push_back(page);
            pageList->push_back(freq);
            //cout<<page<<" : "<<freq<<endl;

        }

    }
}

//writes index to hard memory specified by output file
void IndexHandler::storeOffIndexToMemory(void){

    //clear output file
    ofstream out;
    out.open(memoryOutputFile);
    out.close();

    myIndex->printToFile(memoryOutputFile);


    //Finished after 24th Deadline
}

void IndexHandler::insertionSort(vector<int>* passedVec, int start, int end){
      int i, j;
     int tempPage;
     int tempCount;
     int length = end - start + 1;

     for (i = start + 2; i < start + length; i++) {
         //cout<<"i is "<<i<<endl;
         //cout<<"j is "<<j<<endl;
         j = i;
         i++;
         while (j > start && (passedVec->at(j-1)<passedVec->at(j+1))){
             tempPage = passedVec->at(j);
             tempCount = passedVec->at(j+1);
             passedVec->at(j) = passedVec->at(j-2);
             passedVec->at(j+1) = passedVec->at(j-1);
             passedVec->at(j-2) = tempPage;
             passedVec->at(j-1) = tempCount;

             j = j-2;
         }//end of while loop

    }


}


//Will ask user for input and then will go and print out page numbers
//of the word request
void IndexHandler::findUserWordsInteractive(void){
    string userWord;
  while(1){
    cout<<"Please Enter Word: ";
    cin>>userWord;
    cout<<endl;
    cout<<"User Word collected was "<<userWord<<endl;

    cout<<"Pages with "<<userWord<<":"<<endl;

    //convert first letter of word to lowercase
    userWord[0] = tolower(userWord[0]);
    //need to stem word before searching for it:

    string userStemmed = myWordParser->stopAndStem(userWord);
    if(!userStemmed.empty()){


        //cout<<"myIndex->findWord(user) size = "<<myIndex->findWord(userWord)->size();
        //vector<int>* userWordPages = myIndex->findWord(userStemmed);
        vector<int>* userWordPages = myIndex->findWord(userWord);
        //cout<<"Made it to Index Handler"<<endl;
        if(userWordPages != NULL){
            //cout<<"right under"<<userWordPages->size();

            //cout<<"userWordPages is "<<(userWordPages == NULL? "is null": "is not null")<<endl;
            //cycle through vector and print out all words
            //cout<<"Size = "<<userWordPages->size()<<endl;
            //cout<<userWordPages->at(0)<<endl;

            //sort the vecotr received
            insertionSort(userWordPages,0,userWordPages->size()-1);
        //have sorted vector according to relavancy
            int totalCount = 0;

            for(int i = 0;i<userWordPages->size();i++){
               totalCount += userWordPages->at(i+1);
               i++;
            }


            cout<<"Total Occurances = "<<totalCount<<endl;
            for(int i = 0;i<userWordPages->size();i++){
                cout<<userWordPages->at(i)<<endl;
                cout<<"Frequency: "<<userWordPages->at(i+1)<<endl;
                i++;
            }
        }
        else{
            cout<<"There are no pages with "<<userWord<<endl<<endl;
        }
    }
    else{
        cout<<"Input is a stop word, there are no pages with "<<userWord<<endl<<endl;

    }
    //Ask user if wants to keep searching for word
    int choice;
    cout<<"Enter 1 to continue or 0 to exit:";
    cin>>choice;
    if(choice==0){
        break;
    }else{
        cout<<endl;
    }

   }

}


vector<int>* IndexHandler::findUserWord(string userWord){

    //convert first letter of word to lowercase
    userWord[0] = tolower(userWord[0]);
    //need to stem word before searching for it:
    vector<int>* userWordPages;
    //cout<<"User word searched for in findUserWord = "<<userWord;
    string userStemmed = myWordParser->stopAndStem(userWord);
    //string userStemmed = userWord;
    if(!userStemmed.empty()){

        //cout<<"myIndex->findWord(user) size = "<<myIndex->findWord(userWord)->size();
        userWordPages = myIndex->findWord(userStemmed);
        //userWordPages = myIndex->findWord(userWord);
        //cout<<"Made it to Index Handler"<<endl;
        if(userWordPages != NULL){
/*
            //sort the vecotr received
            insertionSort(userWordPages,0,userWordPages->size()-1);
            //have sorted vector according to relavancy
            int totalCount = 0;

            for(int i = 0;i<userWordPages->size();i++){
               totalCount += userWordPages->at(i+1);
               i++;
            }


            cout<<"Total Occurances = "<<totalCount<<endl;
            for(int i = 0;i<userWordPages->size();i++){
                cout<<userWordPages->at(i)<<endl;
                cout<<"Frequency: "<<userWordPages->at(i+1)<<endl;
                i++;
            }*/
        }
        else{
            cout<<"There are no pages with "<<userWord<<endl<<endl;
        }
    }
    else{
        cout<<"Input is a stop word, there are no pages with "<<userWord<<endl<<endl;

    }

    return userWordPages;
}



/*void IndexHandler::findMultipleUserWords(void){
    int numberWords;
    string* userWords = new string[10];
  while(1){
    cout<<"Please Enter Number of Words to And";
    cin>>numberWords;
    cout<<"Please Enter All words: ";
    for( int j = 0;j<numberWords;j++){
        cin>>userWords[j];
        userWords[j][0] = tolower(userWords[j][0]);

    }

    //loop through and convert all first letters to lowerCase
    //cin>>userWord;
    cout<<endl;

    cout<<"User Words collected were: "<<endl;
    for( int j = 0;j<numberWords;j++){

        cout<<userWords[j];
    }

    cout<<"Pages with "<<userWord<<":"<<endl;

    //convert first letter of word to lowercase
    //userWord[0] = tolower(userWord[0]);
    //need to stem word before searching for it:
    for (int j = 0;j<numberWords;j++){
        userWords[j] = myWordParser->stopAndStem(userWords[j]);

    }
    //string userStemmed = myWordParser->stopAndStem(userWord);
    if(!userStemmed.empty()){


        //cout<<"myIndex->findWord(user) size = "<<myIndex->findWord(userWord)->size();
        vector<int>* userWordPages = myIndex->findWord(userStemmed);
        //cout<<"Made it to Index Handler"<<endl;
        if(userWordPages != NULL){
            //cout<<"right under"<<userWordPages->size();

            //cout<<"userWordPages is "<<(userWordPages == NULL? "is null": "is not null")<<endl;
            //cycle through vector and print out all words
            //cout<<"Size = "<<userWordPages->size()<<endl;
            //cout<<userWordPages->at(0)<<endl;

            //sort the vecotr received
            insertionSort(userWordPages,0,userWordPages->size()-1);
        //have sorted vector according to relavancy
            int totalCount = 0;

            for(int i = 0;i<userWordPages->size();i++){
               totalCount += userWordPages->at(i+1);
               i++;
            }


            cout<<"Total Occurances = "<<totalCount<<endl;
            for(int i = 0;i<userWordPages->size();i++){
                cout<<userWordPages->at(i)<<endl;
                cout<<"Frequency: "<<userWordPages->at(i+1)<<endl;
                i++;
            }
        }
        else{
            cout<<"There are no pages with "<<userWord<<endl<<endl;
        }
    }
    else{
        cout<<"Input is a stop word, there are no pages with "<<userWord<<endl<<endl;

    }
    //Ask user if wants to keep searching for word
    int choice;
    cout<<"Enter 1 to continue or 0 to exit:";
    cin>>choice;
    if(choice==0){
        break;
    }else{
        cout<<endl;
    }

   }

}

*/

//functions to add or find words form index after stemming and stop
//words done

void IndexHandler::indexBodyOfText(char *body, int pageID){
    //cout<<endl;
    //cout<<endl;
    stringstream ss;
    string buffer;
    int length = strlen(body);

    //change punctuation to whitspace
    for (int i = 0; i < length; ++i){

        if (!(body[i]>=48 && body[i]<=57) //if character is not 0-9, A-Z, or a-z
             && !(body[i]>=65 && body[i]<=90) && !(body[i]>=97 && body[i]<=122))
            body[i] = ' '; //change to whitespace
    }

    ss << body;
    while (ss >> buffer ){
        //conver the first letter of the string to lower case
        buffer[0] = tolower(buffer[0]);
        string stemmed = myWordParser->stopAndStem((buffer));
        //cout<<"Stemmed Word "<<stemmed<<endl;

        //if did not send empty string then insert in index
        if(!stemmed.empty()){
            myIndex->insert(stemmed,pageID);
        }
        else{
            //cout<<"Word was stop word"<<endl;

        }

    }

    ss.flush();
}

void IndexHandler::indexBodyOfText(string& body, int pageID){
    //cout<<endl;
    //cout<<endl;
    stringstream ss;
    string buffer;
    //int length = strlen(body.c_str());

    //change punctuation to whitspace
    for (int i = 0; i < body.length(); ++i){

        if ( (body[i]!=39) && !(body[i]>=48 && body[i]<=57) //if character is not ', 0-9, A-Z, or a-z
             && !(body[i]>=65 && body[i]<=90) && !(body[i]>=97 && body[i]<=122))
            body[i] = ' '; //change to whitespace
    }

    ss << body;
    while (ss >> buffer ){
        //conver the first letter of the string to lower case
        buffer[0] = tolower(buffer[0]);
        string stemmed = myWordParser->stopAndStem((buffer));
        //cout<<"Stemmed Word "<<stemmed<<endl;

        //if did not send empty string then insert in index
        if(!stemmed.empty()){
            myIndex->insert(stemmed,pageID);
        }
        else{
            //cout<<"Word was stop word"<<endl;

        }

    }

    ss.flush();
}

/*void IndexHandler::addWord(string &singleWord, int pageID){
    //check if word is stop word
    bool result = myWordParser->isStopWord(singleWord);

    string* newStemmedWord;
    //if not stop word then stem and add to index
    if(result == false){
        newStemmedWord = myWordParser->stemWord(singleWord);
        //addWord to index
        myIndex->addWord(newStemmedWord, pageID);
    }

}*/

//same as addWord except for array of strings all on the same page
/*void IndexHandler::addWords(string word, int pageID){
    //myIndex->insert(word,pageID);
}*/

//returns all page numbers that word appeared on as stored in
//index

std::vector<int>* IndexHandler::findWord(string& passedWord){
    //cout<<"Index Handler Find Word"<<endl;
    return myIndex->findWord(passedWord);
}

//function used by MaintMode to clear entire index
void IndexHandler::clearIndex(void){
    if(myIndex != NULL){
        myIndex->makeEmpty();
    }
}

void IndexHandler::loadStopTable(){
   myWordParser->loadStopList();
}

void IndexHandler::printIndex(){
    char* newOutput = new char[80];
    strcpy(newOutput,"InteractiveModeIndex.txt");

    //clear output file
    ofstream out;
    out.open(newOutput);
    out.close();


    myIndex->printToFile(newOutput);
}
