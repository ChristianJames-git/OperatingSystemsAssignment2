#include "populatetree.h"

populatetree::populatetree(dictentry *rootNode) {
    root = rootNode;
    prevNode = root;
}

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

int populatetree::add(const char *remainingChars, const char *wordBeingInserted) { //adds word to dictionary tree
    int nextIndex = ASCIItoIndex(remainingChars++[0]); //convert current char to ASCII and increment to next char
    if (prevNode->next[nextIndex] == nullptr) { //create new node if missing
        prevNode->next[nextIndex] = new dictentry();
    }
    prevNode = prevNode->next[nextIndex]; //increment prevNode
    if (*remainingChars == '\0') { //check if end of word
        prevNode->isWord = true;
        prevNode = root;
        return 2;
    } else { //recurse with next char
        return 1 + add(remainingChars, wordBeingInserted);
    }
}

int populatetree::ASCIItoIndex(char character) { //ASCII to Index helper method
    int temp = character - '\0'; //get ASCII value of character
    if (temp == 0) //check if null
        return -1;
    else if (temp == 39) //check if '
        return 26;
    else if (temp >= 65 && temp <= 90) //check if upper case
        return temp - 65;
    else if (temp >= 97 && temp <= 122) //check if lower case
        return temp - 97;
    else {
        cout << "invalid character found" << endl;
        exit(EXIT_FAILURE);
    }
}
