/*
 * Christian James
 * 823672623
 */
#ifndef OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H
#define OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H

#include "EXEC_STATUS.h"
#include "dictentry.h"

class populatetree {
public:
    void threadMain(void*);
    void readDict(const char *dictionaryFile);
    int add(const char *, const char *);
    vector<string> dictionaryStore;
private:
    ifstream inStream;
    void openFile(const char *file);
    void closeIn();
    static int ASCIItoIndex(char);
    dictentry *prevNode; //temp node
    dictentry *root;
};
#endif //OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H
