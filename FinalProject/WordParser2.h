#ifndef WORDPARSER2_H
#define WORDPARSER2_H
#include"StopWordsHashTable.h"

class WordParser2
{
public:
    //WordParser2();
    //! Constructor that accepts the length of the stopWordList,
    //! creates the stopWordList, and creates a file for the stemmed
    //! stopped words
    WordParser2(int length = 500);
    //! Destructor, deletes the stopWordList
    //!
    ~WordParser2();

   // WordParser2(int length = 500);
    //! Function that stems and stops words passed
    //! to it
    string stopAndStem(string&);
   // void prepareStopList(void);
    //! Function that loads the stemmed stopwords into a file
    //!
    void loadStopList(void);
    //! Function that sets the source file
    //!
    void setSourceFile(char* file);

private:
    StopWordsHashTable<string>* stopWordList;
    char sourceFile[];
    string hello;

};

#endif // WORDPARSER2_H
