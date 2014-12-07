#include "StressMode.h"

StressMode::StressMode()
{

}

StressMode:: ~StressMode()
{
    cout<<"END Destructor: Stress Test"<<endl;
}

void StressMode::docFileParser(string& fileName)
{

    ifstream ifs;
    ifs.open(fileName);

    if(!ifs){
        cerr << "cannot open file " << fileName << endl;
        exit(1);
    }

    string flag;

    string dummy;
    while (!ifs.eof()){
        ifs >> flag;

        if (flag == "CI"){
            cout << "clearIndex" << endl;
            interact.clearIndex();
            myParser.clearIndex();
        }

        else if(flag == "BI"){
            cout << "build index from memory" << endl;
            //choose 1 for AVL tree and 0 for HashTable
            int userChoice;
            //get the int following
            ifs>>userChoice;
            structureChoice = userChoice;
            char inputFile[80];
            strcpy(inputFile,"Index.txt");
            interact.setInputFileForIndex(inputFile);
            interact.createIndex(userChoice);
            //create the index of the XML parser of Index Handler
            myParser.createIndex(userChoice);




        }

        else if (flag == "IF"){
            cout << "store off new file" << endl;
            string newData;
            ifs>>newData;
            myParser.storeOffNewData(newData);
            char stressOutput[] = "StressTestIndex.txt";
            myParser.storeOffIndex(stressOutput);
            myParser.storeOffPageRange();

            //need to reload index into index handler of
            //interactive mode
            interact.setInputFileForIndex(stressOutput);
            interact.createIndex(structureChoice);
            interact.reloadPageRange();

            getline(ifs,dummy);
        }

        else if (flag == "SE"){
            cout << "search" << endl;
            string arguments;
            getline(ifs,arguments);
            cout<<"argument for search = "<<arguments<<endl;
            interact.processQuery(arguments);

        }

        else if (flag == "PP"){
            cout << "Pick Page" << endl;
            int userPage;
            ifs >>userPage;

            interact.displayText(userPage);

            getline(ifs,dummy);


        }
        else if (flag == "NS"){
            cout<< "new Search"<<endl;
            interact.clearAllCurrAndFinalMembers();

            getline(ifs,dummy);

        }

        else if (flag == "ST"){
            cout << "start time" << endl;
            startTime();

            getline(ifs,dummy);
        }

        else if (flag == "ET"){
            cout << "stop time" << endl;
            stopTime();

            getline(ifs,dummy);
        }

        else if (flag == "PT"){
            cout << "print time" << endl;
            printTime();

            getline(ifs,dummy);
        }

        else {
            cout << "invalid" << endl;
        }
    }

}

void StressMode::stressUI()
{
    string fileName;
    cout << "Enter file name: ";
    getline(cin, fileName);

    docFileParser(fileName);
}

void StressMode::startTime()
{
    start = std::chrono::system_clock::now();
}

void StressMode::stopTime()
{
    end = std::chrono::system_clock::now();
}

void StressMode::printTime()
{
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "Duration: " << elapsed_seconds.count() << " seconds" << endl;
}
