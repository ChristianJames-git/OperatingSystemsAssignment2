/*
 * Christian James
 * 823672623
 */
#include "EXEC_STATUS.h"
#include "dictentry.h"
#include <cstring>

#ifndef OPERATINGSYSTEMSASSIGNMENT2_COUNTWORDS_H
#define OPERATINGSYSTEMSASSIGNMENT2_COUNTWORDS_H


class countwords {
public:
    void threadMain(void*);
    void readWords(const char *wordsFile);
    vector<string> testfileStore;
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~"; //delimiters string
    void searchCount(const string&, int);
    void closeOut();
private:
    ifstream inStream;
    ofstream outStream;
    void openFile(const char *file);
    void openOut();
    void closeIn();
    dictentry* findEndingNodeOfAStr(const char *remainingStr, const char *strBeingSearched);
    void countWordsStartingFromANode(dictentry *currNode, int &count);
    static int ASCIItoIndex(char);
    dictentry *prevNode{}; //temp node
    dictentry root;
};


#endif //OPERATINGSYSTEMSASSIGNMENT2_COUNTWORDS_H
