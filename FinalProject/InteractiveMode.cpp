#include "InteractiveMode.h"
using namespace std;
#include<vector>
#include<iterator>
#include<cmath>
#include<cstring>
void andFunction(vector<string>& nextWords);
void orFunction(vector<string>& nextWords);
void ltFunction(vector<string>& nextWords);
void usernameFunction(vector<string>& nextWords);
void notFunction(vector<string>& nextWords);
void gtFunction(vector<string>& nextWords);

InteractiveMode::InteractiveMode()
{
    myXMLParser = new XMLParser();
    IMHandler = new IndexHandler(2);
    finalPages.clear();
    finalTF.clear();
    finalTitles.clear();
    currAuthor = "";
    currMaxDate = "";
    currMinDate = "";
}

InteractiveMode::~InteractiveMode(){
    delete myXMLParser;
}

void InteractiveMode::setTotalDocs(int x ){
    IMHandler->setTotalDocs(x);
}

void InteractiveMode::setInputFileForIndex(char* input){
   IMHandler->setInputFile(input);
}

/*void InteractiveMode::insertionSort(vector<int>* passedVec, int start, int end){
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


}*/

//will create Index of Avl or Hash Table
void InteractiveMode::createIndex(int choice){
    if(choice == 1){
        IMHandler->createIndex(1);
    }
    else{

        IMHandler->createIndex(0);

    }

    IMHandler->buildIndexFromMemory(0);
    //cout<<"builtIndexFromMemory"<<endl;
    //IMHandler->printIndex();
}

void InteractiveMode::interactiveUI(){
    //big loop that keeps going until user enters end
    while(1){
        int userChoice;
        //cout<<"Output file is"<<IMHandler->getInputfile()<<endl;
        if(IMHandler->isIndexNULL()){
            while(1){

                cout<<"Pick Which Data Structure to Load index into:"<<endl;
                cout<<"Enter 0 for Hash Table"<<endl;
                cout<<"Enter 1 for AVL Tree"<<endl;

                cout<<"User Choice: ";
                cin>>userChoice;
                if(userChoice != 1 && userChoice != 0){
                    cout<<"Invalid Number!"<<endl;
                    cout<<endl;
                    continue;
                }
                else{
                    createIndex(userChoice);
                    cin.ignore();
                    break;
                }
            }
        }


        //beginning of loop that
        cout<<"Please Enter Query (or END to Quit):";
        string userQuery;
        getline(cin,userQuery);

        bool end = processQuery(userQuery);
        if(end == true){
            break;
        }

        //sort the pages according to frequency
        //insertion_sort(totalPages,totalTF,0,totalPages.size()-1);
        //print out the total page numbers
        /*cout<<"Total Pages after query:"<<endl;
        for(int i = 0;i<totalPages.size();i++){
            cout<<totalPages.at(i)<<endl;
        }

        cout<<"TFIDF after query:"<<endl;
        for(int i = 0;i<totalTF.size();i++){
            cout<<totalTF.at(i)<<endl;
        }

        cout<<"DATEGT after query: "<<currMinDate<<endl;
        cout<<"DATELT after query: "<<currMaxDate<<endl;
        cout<<"USERNAME after query: "<<currAuthor<<endl;
        //after query need to clear all of vectors
        */
        while(1){

            displayPagesToUser();
            //ask user if wants to see another page from same search
            cout<<"Enter 1 to continue viewing pages from this search: ";
            string keepSeeing;
            cin>>keepSeeing;
            //getline(cin,keepSeeing);
            if(keepSeeing.substr(0,1).compare("1") != 0){
                //cin.ignore();
                getline(cin,keepSeeing);
                break;
            }

        }
        clearAllCurrAndFinalMembers();

    }

}

void InteractiveMode::clearAllCurrAndFinalMembers(){
    //need to reset the curr and total data members
    finalTitles.clear();
    finalPages.clear();
    finalTF.clear();
    totalPages.clear();
    totalTF.clear();
    totalTitles.clear();

    currMinDate = "";
    currMaxDate = "";
    currAuthor = "";
}

void InteractiveMode::displayPagesToUser(){
    //cout<<"size of finalPages = "<<finalPages.size()<<endl;
    //cout<<"size of finalTF = "<<finalTF.size()<<endl;
    //cout<<"size of finalTitles = "<<finalTitles.size()<<endl;

    if(finalPages.size() <= 0){
        cout<<"Unfortunately there were not pages with those filters"<<endl;
        return;
    }
    cout<<"Please Enter a number between 1 and "
       <<finalPages.size()<<" to return the full text of"
         <<" one of the following pages"<<endl;

    //loop through and print out title, TF, and page number
    for(int i = 0;i<finalPages.size();i++){
        cout<<"\n"<<i+1<<") Page "<<finalPages.at(i)<<endl;
        cout<<"Title = "<<finalTitles.at(i)<<endl;
        cout<<"TF/IDF = "<<finalTF.at(i)<<endl;
    }

    string userChoice;
    int userChoiceInt;
    while(1){
        cout<<"\nPlease Enter Page Choice: ";
        cin>>userChoice;
        //cout<<"UserChoice after entering it = "<<userChoice<<endl;
        //cout<<endl;

        string userChoiceSub = userChoice.substr(0,1);
        userChoiceInt = atoi(userChoiceSub.c_str());
        //verify choice within range
        if(userChoiceInt>=1 && userChoiceInt<= finalPages.size()){
            break;
        }
        else{
            cout<<"\nInvalid Page Rank!"<<endl;
            //clear out rest of invalid entry
            string dummy;
            getline(cin,dummy);
            cout<<endl;
        }
    }

    //display the text, title, and page number for choice
    displayText(userChoiceInt);

}

void InteractiveMode::displayText(int choice){
    int pageNumber = finalPages.at(choice-1);
    myXMLParser->navigateToPage(pageNumber);

    //get text of that page
    string pageText = myXMLParser->getText();

    //print out
    cout<<"Page Number: "<<pageNumber<<endl;
    cout<<"Title: "<<finalTitles.at(choice-1)<<endl;
    cout<<pageText<<endl;
}

void InteractiveMode::pickTop15(){
    //clear final vectors
    finalPages.clear();
    finalTF.clear();
    finalTitles.clear();
    int counter = 0;
    //cout<<"TotalPages size = "<<totalPages.size();
    while(finalPages.size()<15 && counter<totalPages.size()){
        int currPage = totalPages.at(counter);

        myXMLParser->navigateToPage(currPage);
        //if there was a specified author check and see if it is the same
        cout<<"After navigate to page"<<endl;
        string delimiter = " ";
        if(currAuthor.compare("") != 0){
            string pageAuthor = myXMLParser->getAuthor();
            cout<<"After get author"<<endl;
            //eliminate any leading white space
            while(pageAuthor.size()>=1){
               if(delimiter.compare(pageAuthor.substr(0,1)) == 0){
                   pageAuthor= pageAuthor.substr(1,pageAuthor.size()-1);
               }
               else{
                   break;
               }
            }
            cout<<"After eliminating leading white space"<<endl;

            //eliminate trailing white space
            while(pageAuthor.size()>=1){
                if(delimiter.compare(pageAuthor.substr(pageAuthor.size()-1,
                                                    1)) == 0){
                    pageAuthor= pageAuthor.substr(0,pageAuthor.size()-1);
                }
                else{
                    break;
                }
            }

            cout<<"After eliminating trailing white space"<<endl;
            //compare author requested and page author and if the same then
            //keep checking
            if(currAuthor.compare(pageAuthor) != 0){
                counter++;
                continue;
            }
            cout<<"Done Author Analysis"<<endl;
        }
        //get date of page
        string pageDate = myXMLParser->getDate();
        //eliminate any leading whitespace

        //eliminate any leading white space
        while(1){
           if(delimiter.compare(pageDate.substr(0,1)) == 0){
               pageDate= pageDate.substr(1,pageDate.size()-1);
           }
           else{
               break;
           }
        }
        //cout<<"PageDate for Page "<<currPage<<" = "<<pageDate<<endl;
        //get the substring for t
        int index = pageDate.find("T");

        pageDate = pageDate.substr(0,index);

        //check and see if Date specified is in date range
        if(currMaxDate.compare("") != 0){
            //check that maxDate is greater or equal
            if(currMaxDate.compare(pageDate)<0){
                counter++;
                continue;
            }
        }
        if(currMinDate.compare("") != 0){
            //check that maxDate is greater or equal
            if(currMinDate.compare(pageDate)>0){
                counter++;
                continue;
            }
        }

        //if the username matches and the date of page
        //is in date range then add to final page list
        finalPages.push_back(totalPages.at(counter));
        finalTF.push_back(totalTF.at(counter));

        //getTitle of page
        string pageTitle = myXMLParser->getTitle();
        finalTitles.push_back(pageTitle);
        counter++;


    }
}

//http://mycodinglab.com/insertion-sort-algorithm/
void InteractiveMode::insertion_sort(vector<int>& passedPages,
                                        vector<double>& passedTFs,
                                        int start,int end){
     //cout<<"made it inside insertion_sort"<<endl;
     int i, j;
     int tempPage;
     double tempTF;
     int length = end - start + 1;

     for (i = start + 1; i < start + length; i++) {
         j = i;
         while(j>start && (passedTFs.at(j-1)<passedTFs.at(j))){
            tempPage = passedPages.at(j);
            tempTF  = passedTFs.at(j);
            passedPages.at(j) = passedPages.at(j-1);
            passedTFs.at(j) = passedTFs.at(j-1);
            passedPages.at(j-1) = tempPage;
            passedTFs.at(j-1) = tempTF;

             j--;
         }//end of while loop

    }

}

void InteractiveMode::insertionSortStacked(vector<int>* passedVec, int start, int end){
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



//will return true if user entered "EXIT" so loop will stop

bool InteractiveMode::processQuery(string userQuery){
        string delimiter = " ";
        //cout<<"userQuery at beginning of processQuery "<<userQuery<<endl;

        //eliminate any leading white space
        while(1){
           if(delimiter.compare(userQuery.substr(0,1)) == 0){
               userQuery = userQuery.substr(1,userQuery.size()-1);
           }
           else{
               break;
           }
        }
        //get first string of user keyword
        string firstCommand = userQuery.substr(0,userQuery.find(delimiter));


        //check that the first word is not END
        if(firstCommand.compare("END") == 0){
            cout<<"ProcessQuery:Selected to End program";
            return true;
        }

        vector<string> keyWords;
        keyWords.push_back("AND");
        keyWords.push_back("OR");
        keyWords.push_back("NOT");
        keyWords.push_back("DATEGT");
        keyWords.push_back("DATELT");
        keyWords.push_back("USERNAME");

       //make sure first commmand is either AND or OR
       //RULE must start wiht AND or OR!!!!
        bool correctStart = false;
        for(int i = 0;i<2;i++){
            if(firstCommand.compare(keyWords.at(i)) == 0){
                correctStart = true;
            }
        }

        if(correctStart != true){
            cout<<"Need to Enter AND or OR as first word in Query!"<<endl;
            return false;
        }

        //gets rid of first word from user string
        userQuery = userQuery.substr(userQuery.find(delimiter)+1,userQuery.size());

        //cout<<"NewUserQuery "<<userQuery<<endl;
        //cout<<"size = "<<userQuery.size()<<endl;

        //cout<<"First Command"<<firstCommand;
        string currKeyWord = firstCommand;

        //get all words until next keyword
        vector<string> nextWords;
        string currWord;

        //need loop that checks userQuery not empty
        while(!currKeyWord.empty()){
            //cout<<"\nCurrKeyWord = "<<currKeyWord<<endl;
            //while loop that collects all following words after keyword;
            while(1){
                //eliminate whitespace
                while(1){
                   if(delimiter.compare(userQuery.substr(0,1)) == 0){
                       userQuery = userQuery.substr(1,userQuery.size()-1);
                   }
                   else{
                       break;
                   }
                }
                //check that userQuery string not empty
                if(userQuery.empty()){
                   currWord = "";
                   break;
                }
                else{
                    //cout<<"UserQuery = "<<userQuery<<endl;
                    //get next word
                    currWord = userQuery.substr(0,userQuery.find(delimiter));
                    //cout<<"CurrWord collected = "<<currWord<<endl;
                    //take off processed word from userQuery
                    if(userQuery.size() <= currWord.size()+1){
                        userQuery = "";
                    }
                    else{
                     userQuery = userQuery.substr(userQuery.find(delimiter)+1,userQuery.size());
                    //cout<<"UserQuery after deletion = "<<userQuery<<endl;

                    }
                }

                //cout<<"inside loop"<<endl;
                bool breakFlag = 0;
                //check nextWord not match any of key words
                for(int i = 0;i<keyWords.size();i++){
                    if(currWord.compare(keyWords.at(i)) == 0){
                        breakFlag = 1;

                        break;
                    }
                }


                if(breakFlag == 1){
                    break;
                }

                //haven't encountered keyword yet
                nextWords.push_back(currWord);

            }

            //once break and have keyword

            //verify that at least got one argument
            if(nextWords.size()<1){
                cout<<"Keyword was followed by no arguments so just ignoring"<<endl;
                currKeyWord = currWord;
                //cout<<"currKeyWord inside empty list catcher = "<<currKeyWord;
                continue;

            }

            //call the keyword function
            if(currKeyWord.compare("AND") == 0){
                //create vectors to pass by reference
                vector<int>* andPagesList = NULL;
                vector<double>* andTFIDFList = NULL;
                andPages(nextWords,andPagesList,andTFIDFList);
                totalPages = *(andPagesList);
                totalTF = *(andTFIDFList);

            }
            else if(currKeyWord.compare("OR") == 0){
                vector<int>* orPagesList = NULL;
                vector<double>* orTFIDFList = NULL;

                orPages(nextWords,orPagesList,orTFIDFList);
                totalPages = *(orPagesList);
                totalTF = *(orTFIDFList);

            }
            else if(currKeyWord.compare("NOT") == 0){
                vector<int>* totalPagesPtr = &totalPages;
                vector<double>* totalTFPtr = &totalTF;
                notPages(nextWords,totalPagesPtr,totalTFPtr);

            }else if(currKeyWord.compare("DATEGT") == 0){
                gtFunction(nextWords);

            }
            else if(currKeyWord.compare("DATELT") == 0){
                ltFunction(nextWords);
            }
            else if(currKeyWord.compare("USERNAME") == 0){
                usernameFunction(nextWords);
            }


            //set next key word to what was currently stored in currWord
            currKeyWord = currWord;
            //cout<<currKeyWord<<endl;

            //clear next words
            nextWords.clear();

            //cout<<"NextWords at end of Loop:"<<endl;
            /*for(int i = 0;i<nextWords.size();i++){
                cout<<nextWords.at(i);
            }*/
            //cout<<"DoneNextWords"<<endl;
        }

        //order the pages TFs

        //sort the pages according to frequency
        insertion_sort(totalPages,totalTF,0,totalPages.size()-1);

        pickTop15();
        return false;
}

/*
void InteractiveMode::printPages(string word){
    vector<int>* pageNumbers = IModeHandler->findWord(word);

    cout<<"Page Numbers for "<<word<<":"<<endl;
    for(int i = 0;i<pageNumbers.size();i++){
        cout<<"Page "<<pageNumbers.at(i)<<endl;
    }

}
*/

//finds intersection of all vectors in list

void andFunction(vector<string>& nextWords){
        cout<<"AND function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){
            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

void orFunction(vector<string>& nextWords){
        cout<<"OR function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){
            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

void notFunction(vector<string>& nextWords){
        cout<<"NOT function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){

            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

void InteractiveMode::gtFunction(vector<string>& nextWords){

    /*cout<<"DATEGT function:"<<endl;
    cout<<"Collected next words"<<endl;
    //print out all following words
    for(int y = 0;y<nextWords.size();y++){
        cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
    }*/
    //set min date
    if(nextWords.size() > 1){
        cout<<"Error: more than one 'DATEGT' argument"<<endl;
        cout<<"Will just use first argument"<<endl;
    }
    if(nextWords.size()<1){
        cout<<"ERROR: no arguments for DATEGT"<<endl;
        return;
    }
    currMinDate = nextWords.at(0);
}

void InteractiveMode::ltFunction(vector<string>& nextWords){
    /*cout<<"DATELT function:"<<endl;
    cout<<"Collected next words"<<endl;
    //print out all following words
    for(int y = 0;y<nextWords.size();y++){
        cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
    }
    */
    if(nextWords.size()<1){
        cout<<"ERROR: no arguments for DATELT"<<endl;
        return;
    }
    if(nextWords.size() > 1){
        cout<<"Error: more than one 'DATELT' argument"<<endl;
        cout<<"Will just use first argument"<<endl;
    }
    currMaxDate = nextWords.at(0);

}

void InteractiveMode::usernameFunction(vector<string>& nextWords){

    /*cout<<"USERNAME function:"<<endl;
    cout<<"Collected next words"<<endl;
    //print out all following words
    for(int y = 0;y<nextWords.size();y++){
        cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
    }*/
    //check words passed are more 1 or more
    if(nextWords.size()<1){
        cout<<"ERROR: no arguments for username"<<endl;
        return;
    }
    if(nextWords.size() > 1){
        cout<<"username was longer than 1 word, will concatenate"<<endl;
    }


    string catString = nextWords.at(0);
    for(int i = 1;i<nextWords.size();i++){
        catString = " " + nextWords.at(i);
    }
    currAuthor = catString;

}
/*
//will loop through and add up all frequencies of all pages
int getTotalOccurances(std::vector<int> & passedList){
    int total = 0;
    for(int i = 0;i<passedList.size();i++){
        total = total + passsedList(i+1);
        i++;
    }

    return total;
}
*/
/**************NEED to Calculate Term frequency before combine*********/
void InteractiveMode::orPages(std::vector<string> & passedWords,
                              vector<int>* & orPageList,
                              vector<double>*& orTFList){
    /*cout<<"WordsSentTo OrPages:"<<endl;
    for(int y = 0;y<passedWords.size();y++){
        cout<<passedWords.at(y)<<endl;
    }
    cout<<"DoneWithPassedWords\n\n"<<endl;*/
    //create vectors to hold pages and TFIDF
    if(orPageList == NULL){
        orPageList = new vector<int>();
    }
    else{
        cout<<"Page List passed was not null in orPages"<<endl;
    }
    if(orTFList == NULL){
        orTFList = new vector<double>();
    }
    else{
        cout<<"TFIDF List passed was not null in orPages"<<endl;
    }

    double totalDocs =  IMHandler->getTotalDocs();
    for(int i = 0;i<passedWords.size();i++){

        //get list of pages for word
        vector<int>* pageList = IMHandler->findUserWord(passedWords.at(i));

        //check that not NULL

        if(pageList != NULL){
            //calculate IDF for word
            double numberDocs = (pageList->size())/2;
            double IDF = log10(totalDocs/(1.0+numberDocs));

            //for each page in list, add to total list or add frequency
            //to already existing index of page

            for(int j = 0;j<pageList->size();j++){
                //get total time word occured in whole corpus

                //calculate TF/IDF for specific page
                double TF = pageList->at(j+1);
                double TFIDF =  TF*IDF;


                //cout<<"For word "<<passedWords.at(i)<<" and after page "<<pageList->at(j)<<endl;
                //cout<<"number Docs = "<<numberDocs<<endl;
                //cout<<"IDF = "<<IDF<<endl;

                //cout<<"TF = "<<TF<<endl;
                //cout<<"TFIDF = "<<TFIDF<<endl;

                //check if page already exist
                int index = totalContainsPage(orPageList,pageList->at(j));
                if(index >= 0){
                    //add term frequency if already exists
                    orTFList->at(index) = orTFList->at(index) + TFIDF;
                    //cout<<"orTFList after combining "<<orTFList->at(index)<<endl;
                }
                else{
                    orPageList->push_back(pageList->at(j));
                    orTFList->push_back(TFIDF);

                }

                /*cout<<"For word "<<passedWords.at(i)<<" and after page "<<pageList->at(j)<<endl;
                cout<<"AT END OF OR PAGES page list"<<endl;
                for(int h = 0;h<orPageList->size();h++){
                   cout<<orPageList->at(h)<<endl;
                 }
                */
                //increment so go to next even index
                j++;
            }
        }
        else{
            cout<<"OR: empty list for = "<<passedWords.at(i)<<endl;
        }

    }

    //once processed all words the vectors have already been changed
    //by reference so not need to return anything

    //verify that pageList and TFIDF list same size
    if(orPageList->size() != orTFList->size()){
        cout<<"ERROR: At end of orpages the TF and Pages list of different size"<<endl;
    }

    //cout<<"AT END OF OR PAGES page list"<<endl;
    /*for(int h = 0;h<orPageList->size();h++){
        cout<<orPageList->at(h)<<endl;
    }
    cout<<"END\n\n"<<endl;*/

}
/**************NEED to Calculate Term frequency before combine*********/
/*vector<int>* InteractiveMode::orPagesAndReturn(std::vector<vector<int>*>* allList){
    vector<int>* mytotalPages = new vector<int>();
    for(int i = 0;i<allList->size();i++){
        for(int j = 0;j<allList->at(i)->size();j++){
            int index = containsPageAnd(mytotalPages,allList->at(i)->at(j));

        }
        /*for(int j = 0;j<pageList->size();j++){
            //check if page already exist
            int index = totalContainsPage(pageList->at(j));
            if(index > 0){
                //add term frequency if already exists
                totalTF.at(index) = totalTF.at(index) + pageList->at(j+1);
            }
            else{
                totalPages.push_back(pageList->at(j));
                totalTF.push_back(pageList->at(j+1));
            }

        }

    }
}*/


void InteractiveMode::andPages(std::vector<string> & passedWords,
                               vector<int>* & andPageList,
                               vector<double>* &andTFIDFList ){
    /*cout<<"WordsSentToAndPages:"<<endl;
    for(int y = 0;y<passedWords.size();y++){
        cout<<passedWords.at(y)<<endl;
    }
    cout<<"DoneWithPassedWords\n\n"<<endl;*/
    //send words, pageLIst and TFIDF list to get or function
    orPages(passedWords,andPageList,andTFIDFList);

    //assemble vector of page numbers of all words
    //vector<vector<int>*>* allLists = new vector<vector<int>*>();

    //cycle through all words in passed list
    for(int i = 0;i<passedWords.size();i++){
        //get page list and term frequency
        vector<int>* currPageList = IMHandler->findUserWord(passedWords.at(i));
        //cycles through all pages in large index and checks it is
        //in currPageList, and if not then deletes it
        if(currPageList == NULL){
           currPageList = new vector<int>();
           currPageList->clear();
        }
        //check to see if currPageList is NULL

        int vecSize = andPageList->size();
        for(int pageIndex = 0;pageIndex<vecSize;pageIndex++){
           //check if currPageList has number in andPageLIst
            //cout<<"For word "<<passedWords.at(i)<<" checking for "<<andPageList->at(pageIndex)<<endl;
            int result = totalContainsPageStacked(currPageList,andPageList->at(pageIndex));
            if(result<0){
                //cout<<"was not found"<<endl;
                //remove index from vector if

                andPageList->erase(andPageList->begin() + pageIndex);
                andTFIDFList->erase(andTFIDFList->begin() + pageIndex);

                //adjust counters
                vecSize--;
                pageIndex--;

            }
            else{
                //cout<<"WAS FOUND"<<endl;
            }
            //if it is contained then let the index remain
        }

        /*cout<<"after looking at word <<"<<passedWords.at(i)<<" remaining pages are "<<endl;
        for(int h = 0;h<andPageList->size();h++){
           cout<<andPageList->at(h)<<endl;
         }*/

    }

    /*cout<<"AT END OF AND PAGES page list"<<endl;
    for(int h = 0;h<andPageList->size();h++){
        cout<<andPageList->at(h)<<endl;
    }
    cout<<"END\n\n"<<endl;*/

}

//will remove page numbers from lists that were sent
void InteractiveMode::notPages(std::vector<string> & passedWords,
                               vector<int>* & notPageList,
                               vector<double>* & notTFList){

    /*cout<<"WordsSentToNotPages:"<<endl;
    for(int y = 0;y<passedWords.size();y++){
        cout<<passedWords.at(y)<<endl;
    }
    cout<<"DoneWithPassedWords\n\n"<<endl;*/
    //cycle through all words
    for(int wordCounter = 0;wordCounter<passedWords.size();wordCounter++){
        //get page list of each word
        vector<int>* currPageList = IMHandler->findUserWord(passedWords.at(wordCounter));
        //cycle through all pages of currPageList

        if(currPageList != NULL){
            for(int pageCounter = 0;pageCounter<currPageList->size();pageCounter++){
                //compare if large list has page numbers
                int pageIndex = totalContainsPage(notPageList,currPageList->at(pageCounter));
                //if page number in big list then remove
                if(pageIndex>0){
                    notPageList->erase(notPageList->begin() + pageIndex);
                    notTFList->erase(notTFList->begin() + pageIndex);
                }
                //move to next even index
                pageCounter++;
            }
        }
        else{
            cout<<"NOT: Empty pages for "<<passedWords.at(wordCounter)<<endl;
        }
    }


}


int InteractiveMode::totalContainsPage(vector<int>* passedPages,int page){
    for(int i = 0;i<passedPages->size();i++){
        if(passedPages->at(i) == page){
            //cout<<"\nReturnedIndex from totalContainsPage = "<<i<<endl;
            return i;

        }

    }

    //if didn't find it
    return -1;
}


int InteractiveMode::totalContainsPageStacked(vector<int>* passedPages,int page){

    for(int i = 0;i<passedPages->size();i++){
        if(passedPages->at(i) == page){
            return i;
        }
        //increment so checks every even index
        i++;

    }

    //if didn't find it
    return -1;
}

/*
int InteractiveMode::containsPageAnd(vector<int>* myList,int page){
    for(int i = 0;i<myList->size();i++){
        if(myList->at(i) == page){
            return i;
        }

    }

    //if didn't find it
    return -1;
}
*/

