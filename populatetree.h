#ifndef OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H
#define OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H

#include "EXEC_STATUS.h"
#include "dictentry.h"
#include "threadHelper.h"

class populatetree {
public:
    void readDict(const char *dictionaryFile);
private:
    ifstream inStream;
    void openFile(const char *file);
    void closeIn();
    void populateTree();
    static int ASCIItoIndex(char);
    bool add(const char *, const char *);
    vector<string> dictionaryStore;
    dictentry *prevNode; //temp node
};
#endif //OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H
