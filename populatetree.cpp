#include "populatetree.h"

void populatetree::threadMain(void * VoidPtr) { //thread controller
    EXEC_STATUS *sharedData;
    sharedData = (EXEC_STATUS *) VoidPtr;

    root = sharedData->dictRootNode;
    prevNode = root;
    readDict(sharedData->filePath[DICTSRCFILEINDEX]); //read in dictionary words to vector

    for (auto & i : dictionaryStore) { //loop through vector
        long temp = add(i.c_str(), i.c_str()); //Add words to dictionary
        if (temp == -1) {
            cout << "failed to insert word" << endl; //handles not accepted characters
            exit(EXIT_FAILURE);
        } else {
            *sharedData->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] += temp; //increment chars processed
            sharedData->wordCountInFile[DICTSRCFILEINDEX]++; //increment word count
        }
    }
    sharedData->taskCompleted[DICTSRCFILEINDEX] = true; //set task as complete
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
        cout << "Unable to open <<" << file << ">>" << endl;
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
    if (nextIndex < 0 || nextIndex > 26)
        return -1;
    if (prevNode->next[nextIndex] == nullptr) { //create new node if missing
        prevNode->next[nextIndex] = new dictentry();
    }
    prevNode = prevNode->next[nextIndex]; //increment prevNode
    if (*remainingChars == '\0') { //check if end of word
        prevNode->isWord = true;
        prevNode = root;
        return 2; //add 1 for first letter and 1 for the extra per line
    } else { //recurse with next char
        return 1 + add(remainingChars, wordBeingInserted); //add 1 for each char
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
