#include "populatetree.h"

void populatetree::readDict(const char *dictFile) { //read in dictionary file to vector and call populateTree
    openFile(dictFile); //open file
    string nextLine;
    while (inStream.good()) { //read in each line until eof
        getline(inStream, nextLine);
        if (nextLine.empty()) //skip over blank lines
            continue;
        nextLine = nextLine;
        dictionaryStore.emplace_back(nextLine.c_str()); //add each line to given storage vector
    }
    closeIn(); //close file
}

void populatetree::openFile(const char *file) { //open file helper method
    inStream.open(file);
    if (!inStream.is_open()) { //check if file was opened successfully
        cout << "file not found" << endl;
        exit(EXIT_FAILURE);
    }
}

void populatetree::closeIn() { //close file helper method
    if (inStream.is_open())
        inStream.close();
    else {
        cout << "Input not open" << endl;
        exit(EXIT_FAILURE);
    }
}