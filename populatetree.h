#include "EXEC_STATUS.h"
#include "dictentry.h"

#ifndef OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H
#define OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H

class populatetree {
public:
    void readDict(const char *dictionaryFile);
private:
    ifstream inStream;
    void openFile(const char *file);
    void closeIn();
    void readIn(vector<string> *storage);
    void populateTree();
    static int ASCIItoIndex(char);
    bool add(const char *, const char *);
    vector<string> dictionaryStore;
    dictentry *prevNode; //temp node
};
#endif //OPERATINGSYSTEMSASSIGNMENT2_POPULATETREE_H
