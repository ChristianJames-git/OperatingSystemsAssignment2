#include "countwords.h"

void countwords::threadMain(void * VoidPtr) {
    EXEC_STATUS *sharedData;
    sharedData = (EXEC_STATUS *) VoidPtr;

    while (!sharedData->taskCompleted[DICTSRCFILEINDEX]) {

    }

    root = *sharedData->dictRootNode;
    prevNode = &root;
    readWords(sharedData->filePath[TESTFILEINDEX]);

    for (auto & i : testfileStore) {
        *sharedData->numOfCharsProcessedFromFile[TESTFILEINDEX] += (long)(i.length() + 1);
        int temp = 0;
        char *word = strtok((char *)i.c_str(), delimiters); //separate first word by using delimiters
        while (word != nullptr) { //loop through each word in line
            temp++;
            searchCount(word, sharedData->minNumOfWordsWithAPrefixForPrinting);
            word = strtok(NULL, delimiters); //next word
        }
        sharedData->wordCountInFile[TESTFILEINDEX] += temp;
    }
    closeOut();

    sharedData->taskCompleted[TESTFILEINDEX] = true;

    /* If we wanted to return something, we would return a pointer
     * to the data that we wanted to return.
     *
     * Instead of simply using return, we could also call
     * pthread_exit.
     */
    pthread_exit(sharedData);
}

void countwords::readWords(const char *wordsFile) { //reads in each line of words, splits into words and calls searchCount on each word
    openFile(wordsFile); //open file
    string line;
    while (getline(inStream, line)) { //read in each line
        testfileStore.emplace_back(line);
    }
    closeIn(); //close file
    openOut();
}

void countwords::searchCount(const string& str, int minInstances) { //uses helper methods and outputs count
    dictentry *temp = findEndingNodeOfAStr(str.c_str(), str.c_str()); //find end of string
    int count = 0;
    if (temp != nullptr) {
        countWordsStartingFromANode(temp, count); //count words that start with string
    }
    if (count >= minInstances) {
        outStream << str << " " << count << endl; //output
    }
}

dictentry *countwords::findEndingNodeOfAStr(const char *remainingStr, const char *strBeingSearched) { //finds node at end of string or null if not in the dictionary
    int index = ASCIItoIndex(remainingStr++[0]); //convert current char to ASCII and increment to next char
    dictentry *toReturn;
    if (index == -1) //if character was null then end of string
        toReturn = prevNode;
    else if (prevNode->next[index] == nullptr) //if next[index] is null, return null as string isn't in dictionary
        toReturn = nullptr;
    else { //else recurse to next character
        prevNode = prevNode->next[index];
        toReturn = findEndingNodeOfAStr(remainingStr, strBeingSearched);
    }
    prevNode = &root;
    return toReturn;
}

void countwords::countWordsStartingFromANode(dictentry *currNode, int &count) { //count from last letter of string
    if (currNode->isWord) //check if current char completes a word
        count++;
    for (auto & i : currNode->next) //search through all words that start with the given word, counting
        if (i != nullptr)
            countWordsStartingFromANode(i, count);
}

void countwords::openFile(const char *file) { //open file helper method
    inStream.open(file);
    if (!inStream.is_open()) { //check if file was opened successfully
        cout << "file not found" << endl;
        exit(EXIT_FAILURE);
    }
}

void countwords::closeIn() { //close file helper method
    if (inStream.is_open())
        inStream.close();
    else {
        cout << "Input not open" << endl;
        exit(EXIT_FAILURE);
    }
}

void countwords::openOut() {
    outStream.open("countwords_output.txt");
    if (!outStream.is_open()) {
        cout << "output not created" << endl;
        exit(EXIT_FAILURE);
    }
}

void countwords::closeOut() {
    if (outStream.is_open())
        outStream.close();
    else {
        cout << "Output not open" << endl;
        exit(EXIT_FAILURE);
    }
}

int countwords::ASCIItoIndex(char character) { //ASCII to Index helper method
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
