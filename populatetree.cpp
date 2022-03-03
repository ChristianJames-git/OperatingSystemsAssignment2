#include "populatetree.h"

void populatetree::readDict(const char *dictFile) { //read in dictionary file to vector and call populateTree
    openFile(dictFile); //open file
    readIn(&dictionaryStore); //read in dictionary file
    closeIn(); //close file
}