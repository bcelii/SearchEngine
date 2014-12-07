#ifndef INDEX_H
#define INDEX_H
#include<string>
#include<vector>

class Index
{
public:
    Index(){
       wordCount = 0;
    }

    ~Index(){}

    //getters, setters
    int getWordCount(void);
    void setWordCount(int);
    void incrementWordCount(void);

    virtual std::vector<int>* findWord(std::string&)=0;
    virtual void makeEmpty()=0;
    virtual bool insert(std::string&,int&)=0;
    //virtual void addWords(std::string*, int*);
    virtual bool contains(std::string&)=0;
    //overloaded insert function that has frequency along
    //with page number
    virtual bool insert(std::string&,std::vector<int>*) = 0;
    virtual void printToFile(char*)= 0;

private:
    int wordCount;
};

#endif // INDEX_H
