#include "StressMode.h"

StressMode::StressMode()
{

}

StressMode:: ~StressMode()
{

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

            //need to reload index into index handler of
            //interactive mode
            interact.setInputFileForIndex(stressOutput);
            interact.buildIndexFromMemory(structureChoice);
        }

        else if (flag == "SE"){
            cout << "search" << endl;

            getline(ifs,arguments);
            interact.processQuery(arguments);
        }

        else if (flag == "PP"){
            cout << "Pick Page" << endl;
            int userPage;
            ifs >>userPage;

            interact.displayText(userPage);


        }
        else if (flag == "NS"){
            cout<< "new Search"<<endl;
            interact.clearAllCurrAndFinalMembers();

        }

        else if (flag == "ST"){
            cout << "start time" << endl;
            startTime();
        }

        else if (flag == "ET"){
            cout << "stop time" << endl;
            stopTime();
        }

        else if (flag == "PT"){
            cout << "print time" << endl;
            printTime();
        }

        else {
            cout << "invalid" << endl;
        }
        //make sure goes to next line
        string dummy;
        getline(ifs,dummy);
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
