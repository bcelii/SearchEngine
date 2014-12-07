#ifndef STRESSMODE_H
#define STRESSMODE_H
#include "MaintMode.h"
#include "InteractiveMode.h"
#include <chrono>
#include <ctime>

using namespace std;

/* Function Flags:
 * CI: clearIndex()
 * BI: buildIndexFromMemory(int)
 * IF: storeOffNewData(string)
 * SE: processQuery(string)
 * PP: pickPage(int)
 * ST: startTime
 * ET: stopTime
 * PT: printTime
 */

class StressMode
{
private:
    MaintMode maint;
    InteractiveMode interact;
    XMLParser myParser;
    int structureChoice;

    std::chrono::time_point<std::chrono::system_clock> start, end;

public:
    StressMode();
    ~StressMode();

    //! reads file and execute commands, displaying times
    void docFileParser(string& fileName);

    //! Interact with user asking for fileName to stress test
    void stressUI();

    //! Start Timer
    void startTime();

    //! Stop Timer
    void stopTime();

    //! Print Duration
    void printTime();

};

#endif // STRESSMODE_H
