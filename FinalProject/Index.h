#ifndef INDEX_H
#define INDEX_H
#include<string>
#include<vector>
#include<iostream>
class Index
{
public:
    //!
    //! Constructor
    //!
    Index(){
       wordCount = 0;
    }

    //!
    //! Destructor
    ~Index(){
            std::cout<<"END destructor: Index"<<std::endl;
    }

    //! Getter
    //!
    int getWordCount(void);
    //! Setter
    //!
    void setWordCount(int);
    void incrementWordCount(void);

    //! Function that finds the page numbers where
    //! word is present
    virtual std::vector<int>* findWord(std::string&)=0;
    //! Function that empties the structure
    //!
    virtual void makeEmpty()=0;
    //! Function that inserts a word into the structure
    //!
    virtual bool insert(std::string&,int&)=0;
    //virtual void addWords(std::string*, int*);
    //! Function that checks if a word is present.
    virtual bool contains(std::string&)=0;
    //!Overloaded insert function that has frequency along
    //!with page number
    virtual bool insert(std::string&,std::vector<int>*) = 0;
    //! Function that prints contents to a file
    //!
    virtual void printToFile(char*)= 0;

private:
    int wordCount;
};

#endif // INDEX_H
