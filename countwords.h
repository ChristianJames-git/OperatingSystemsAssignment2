#include "EXEC_STATUS.h"
#include "dictentry.h"

#ifndef OPERATINGSYSTEMSASSIGNMENT2_COUNTWORDS_H
#define OPERATINGSYSTEMSASSIGNMENT2_COUNTWORDS_H


class countwords {
public:
    explicit countwords(dictentry);
    void readWords(const char *wordsFile);
    vector<string> testfileStore;
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~"; //delimiters string
    void searchCount(const string&);
private:
    ifstream inStream;
    void openFile(const char *file);
    void closeIn();
    dictentry* findEndingNodeOfAStr(const char *remainingStr, const char *strBeingSearched);
    void countWordsStartingFromANode(dictentry *currNode, int &count);
    static int ASCIItoIndex(char);
    dictentry *prevNode{}; //temp node
    dictentry root;
};


#endif //OPERATINGSYSTEMSASSIGNMENT2_COUNTWORDS_H
