#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H
#include<string>

class LookUpTable
{
public:
    LookUpTable();

    ~LookUpTable();
    //functions to retrieve info from table based on ID of page

    char* getFileName(int ID);

    std::string* getTitle(int ID);

    std::string* getAuthor(int ID);

    void addMultiplePages(std::string** author, std::string** title,
                    std::string** fileName, int* ID);
    void addPage(std::string* author, std::string* title,
               std::string* fileName, int ID);

    //getters and setters
    void setTableFile(char* passedFile);

    char* getTableFile(void);

    void setNumberOfFiles(int passedNumb);

    int getNumberOfFiles(void);

private:
    char* tableFile;
    int numberOfFiles;
};

#endif // LOOKUPTABLE_H
