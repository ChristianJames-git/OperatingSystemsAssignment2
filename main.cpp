#include <getopt.h>
#include "populatetree.h"
#include "countwords.h"
#include <pthread.h>
#include <cstring>

extern "C" void * populateTreeThread( void * VoidPtr )
{
    EXEC_STATUS *sharedData;
    sharedData = (EXEC_STATUS *) VoidPtr;
    while (sharedData->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] == nullptr) {

    }

    auto *popTree = new populatetree(sharedData->dictRootNode);
    popTree->readDict(sharedData->filePath[DICTSRCFILEINDEX]);

    for (auto & i : popTree->dictionaryStore) {
        long temp = popTree->add(i.c_str(), i.c_str());
        if (temp == -1) {
            cout << "failed to insert word" << endl;
            exit(EXIT_FAILURE);
        } else {
            *sharedData->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] += temp;
            sharedData->wordCountInFile[DICTSRCFILEINDEX]++;
        }
    }
    sharedData->taskCompleted[DICTSRCFILEINDEX] = true;
    /* If we wanted to return something, we would return a pointer
     * to the data that we wanted to return.
     *
     * Instead of simply using return, we could also call
     * pthread_exit.
     */
    pthread_exit(sharedData);
    return nullptr;
}

extern "C" void * countWordsThread( void * VoidPtr )
{
    EXEC_STATUS *sharedData;
    sharedData = (EXEC_STATUS *) VoidPtr;

    while (!sharedData->taskCompleted[DICTSRCFILEINDEX]) {

    }
    auto *countWords = new countwords(*sharedData->dictRootNode);
    countWords->readWords(sharedData->filePath[TESTFILEINDEX]);

    for (auto & i : countWords->testfileStore) {
        *sharedData->numOfCharsProcessedFromFile[TESTFILEINDEX] += (long)(i.length() + 1);
        int temp = 0;
        char *word = strtok((char *)i.c_str(), countWords->delimiters); //separate first word by using delimiters
        while (word != nullptr) { //loop through each word in line
            temp++;
            countWords->searchCount(word, sharedData->minNumOfWordsWithAPrefixForPrinting);
            word = strtok(NULL, countWords->delimiters); //next word
        }
        sharedData->wordCountInFile[TESTFILEINDEX] += temp;
    }
    countWords->closeOut();

    sharedData->taskCompleted[TESTFILEINDEX] = true;

    /* If we wanted to return something, we would return a pointer
     * to the data that we wanted to return.
     *
     * Instead of simply using return, we could also call
     * pthread_exit.
     */
    pthread_exit(sharedData);
    return nullptr;
}

int main(int argc, char **argv) {
    if (argc < 3) { //make sure correct args amount
        cout << "Please input correct number of inputs" << endl;
        exit(EXIT_FAILURE);
    }
    int p=-1, h=-1, n=-1, c;
    const char* filenames[2];
    while (optind < argc) {
        if ((c = getopt(argc, argv, ":p:h:n:")) != -1) {
            switch (c) {
                case 'p':
                    p = strtol(optarg, nullptr, 10);
                    if (p < 10) {
                        cout << "Number of progress marks must be a number and at least 10" << endl;
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'h':
                    h = strtol(optarg, nullptr, 10);
                    if (h <= 0 || h > 10) {
                        cout << "Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10" << endl;
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'n':
                    n = strtol(optarg, nullptr, 10);
                    break;
                default:
                    break;
            }
        } else {
            filenames[optind-1] = argv[optind];
            optind++;
        }
    }
    auto *sharedData = new EXEC_STATUS(p, h, n, filenames);

    pthread_attr_t pthread_attributes;
    pthread_t populatetreethread, countwordsthread;

    pthread_attr_init(&pthread_attributes);

    pthread_create(&populatetreethread, &pthread_attributes, &populateTreeThread, sharedData);
    pthread_create(&countwordsthread, &pthread_attributes, &countWordsThread, sharedData);

    long currProgressMarks = 0, maxProgressMarks;
    char toOutput;
    while (currProgressMarks < sharedData->numOfProgressMarks-1) {
        maxProgressMarks = sharedData->numOfProgressMarks * ((double) *sharedData->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] / (double) sharedData->totalNumOfCharsInFile[DICTSRCFILEINDEX]);
        while (currProgressMarks < maxProgressMarks && currProgressMarks < sharedData->numOfProgressMarks-1) {
            toOutput = '-';
            if ((currProgressMarks+1) % sharedData->hashmarkInterval == 0)
                toOutput = '#';
            cout << toOutput << flush;
            currProgressMarks++;
        }
    }
    while (!sharedData->taskCompleted[DICTSRCFILEINDEX]) {

    }
    toOutput = '-';
    if ((currProgressMarks+1) % sharedData->hashmarkInterval == 0)
        toOutput = '#';
    cout << toOutput << endl;
    cout << "There are " << sharedData->wordCountInFile[DICTSRCFILEINDEX] << " words in " << sharedData->filePath[DICTSRCFILEINDEX] << "." << endl;

    currProgressMarks = 0;
    while (currProgressMarks < sharedData->numOfProgressMarks-1) {
        maxProgressMarks = sharedData->numOfProgressMarks * ((double) *sharedData->numOfCharsProcessedFromFile[TESTFILEINDEX] / (double) sharedData->totalNumOfCharsInFile[TESTFILEINDEX]);
        while (currProgressMarks < maxProgressMarks) {
            toOutput = '-';
            if ((currProgressMarks+1) % sharedData->hashmarkInterval == 0)
                toOutput = '#';
            cout << toOutput << flush;
            currProgressMarks++;
        }
    }
    while (!sharedData->taskCompleted[TESTFILEINDEX]) {

    }
    toOutput = '-';
    if ((currProgressMarks+1) % sharedData->hashmarkInterval == 0)
        toOutput = '#';
    cout << toOutput << endl;
    cout << "There are " << sharedData->wordCountInFile[TESTFILEINDEX] << " words in " << sharedData->filePath[TESTFILEINDEX] << "." << endl;

    //delete(&sharedData);
}
