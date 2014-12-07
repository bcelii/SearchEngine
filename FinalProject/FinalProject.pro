TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    XMLParser.cpp \
    IndexHandler.cpp \
    XMLFileParser.cpp \
    LookUpTable.cpp \
    UserMode.cpp \
    MaintMode.cpp \
    InteractiveMode.cpp \
    StressMode.cpp \
    HashTable.cpp \
    IndexAVLNode.cpp \
    StopWordsHashTable.cpp \
    Index.cpp \
    WordParser.cpp \
    WordParser.cpp \
    WordParser2.cpp \
    FakeXMLParser.cpp \
    PagesAvlTree.cpp \
    PagesAVLNode.cpp

HEADERS += \
    rapidxml.hpp\
    rapidxml_print.hpp\
    rapidxml_utils.hpp\
    rapidxml_iterators.hpp\
    XMLParser.h \
    IndexHandler.h \
    XMLFileParser.h \
    Index.h \
    LookUpTable.h \
    UserMode.h \
    MaintMode.h \
    InteractiveMode.h \
    StressMode.h \
    HashTable.h \
    AvlTree.h \
    IndexAVLNode.h \
    StopWordsHashTable.h \
    StopWordsAvlTree.h \
    WordParser.h \
    Random.h \
    WordParser.h \
    WordParser2.h \
    FakeXMLParser.h \
    PagesAvlTree.h \
    PagesAVLNode.h

