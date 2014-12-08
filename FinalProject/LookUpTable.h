#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H
#include<string>

class LookUpTable
{
public:
    //! Constructor
    //!
    LookUpTable();
    //! Destructor
    //!
    ~LookUpTable();
    //functions to retrieve info from table based on ID of page
    //! Tester Function
    //!
    char* getFileName(int ID);
    //! Tester Function
    //!
    std::string* getTitle(int ID);
    //! Tester Function
    //!
    std::string* getAuthor(int ID);
    //! Tester Function
    //!
    void addMultiplePages(std::string** author, std::string** title,
                    std::string** fileName, int* ID);
    //! Tester Function
    //!
    void addPage(std::string* author, std::string* title,
               std::string* fileName, int ID);

    //! Setter; sets the table file
    //!
    void setTableFile(char* passedFile);
    //! Getter; gets the table file
    //!
    char* getTableFile(void);
    //! Setter; sets the number of files
    //!
    void setNumberOfFiles(int passedNumb);
    //! Getter; gets the number of files
    //!
    int getNumberOfFiles(void);

private:
    char* tableFile;
    int numberOfFiles;
};

#endif // LOOKUPTABLE_H
