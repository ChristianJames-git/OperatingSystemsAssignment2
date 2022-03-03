#include <getopt.h>
#include "populatetree.h"
#include "countwords.h"
#include <pthread.h>
#include <unistd.h>

using namespace std;

extern "C" void * populateTreeThread( void * VoidPtr ) //populatetree thread intermediate method
{
    auto *popTree = new populatetree();
    popTree->threadMain(VoidPtr); //calls populatetree thread controller
    pthread_exit(popTree);
    return nullptr;
}

extern "C" void * countWordsThread( void * VoidPtr ) //countwords thread intermediate method
{
    auto *countWords = new countwords();
    countWords->threadMain(VoidPtr); //calls countwords thread controller
    pthread_exit(countWords);
    return nullptr;
}

int main(int argc, char **argv) {
    if (argc < 3) { //make sure correct args amount
        cout << "Please input correct number of inputs" << endl;
        exit(EXIT_FAILURE);
    }
    int p=-1, h=-1, n=-1, c, temp = 1;
    const char* filenames[2];
    while (temp < argc) { //iterate through arguments
        if ((c = getopt(argc, argv, "p:h:n:")) != -1) {
            temp += 2; //skip 2 when a flag is found
            switch (c) {
                case 'p': //handle -p
                    p = strtol(optarg, nullptr, 10);
                    if (p < 10) { //must be at least 10
                        cout << "Number of progress marks must be a number and at least 10" << endl;
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'h': //handle -h
                    h = strtol(optarg, nullptr, 10);
                    if (h <= 0 || h > 10) { //must be at least 0, less than 10
                        cout << "Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10" << endl;
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'n': //handle -n
                    n = strtol(optarg, nullptr, 10);
                    break;
                default:
                    break;
            }
        } else {
            filenames[temp-1] = argv[temp]; //handle non-flagged arguments (file names)
            temp++;
            optind++;
        }
    }
    auto *sharedData = new EXEC_STATUS(p, h, n, filenames); //instantiate shared struct

    pthread_t populatetreethread, countwordsthread;

    pthread_create(&populatetreethread, nullptr, &populateTreeThread, sharedData); //create thread 1
    pthread_create(&countwordsthread, nullptr, &countWordsThread, sharedData); //create thread 2

    long currProgressMarks = 0, maxProgressMarks;
    char toOutput;
    while (currProgressMarks < sharedData->numOfProgressMarks-1) { //loop though until only one dash is missing
        maxProgressMarks = (long)(sharedData->numOfProgressMarks * ((double) *sharedData->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] / (double) sharedData->totalNumOfCharsInFile[DICTSRCFILEINDEX]));
        //^ determine how many dashes should be printed by now
        if (maxProgressMarks > sharedData->numOfProgressMarks) { //verify that there will not be more dashes than allowed
            cout << "Progress Mark math incorrect" << endl;
            exit(EXIT_FAILURE);
        }
        while (currProgressMarks < maxProgressMarks) { //print dashes up to the current amount
            toOutput = '-';
            if ((currProgressMarks+1) % sharedData->hashmarkInterval == 0) //print # on determined interval
                toOutput = '#';
            cout << toOutput << flush;
            currProgressMarks++;
        }
    }
    while (!sharedData->taskCompleted[DICTSRCFILEINDEX]) { //wait until populate tree thread finishes

    }
    toOutput = '-';
    if ((currProgressMarks+1) % sharedData->hashmarkInterval == 0) //print last dash or hash
        toOutput = '#';
    cout << toOutput << endl;
    cout << "There are " << sharedData->wordCountInFile[DICTSRCFILEINDEX] << " words in " << sharedData->filePath[DICTSRCFILEINDEX] << "." << endl; //print word count

    currProgressMarks = 0; //repeat above process for countwords
    while (currProgressMarks < sharedData->numOfProgressMarks-1) {
        maxProgressMarks = (long)(sharedData->numOfProgressMarks * ((double) *sharedData->numOfCharsProcessedFromFile[TESTFILEINDEX] / (double) sharedData->totalNumOfCharsInFile[TESTFILEINDEX]));
        if (maxProgressMarks > sharedData->numOfProgressMarks) {
            cout << "Progress Mark math incorrect" << endl;
            exit(EXIT_FAILURE);
        }
        while (currProgressMarks < maxProgressMarks) {
            toOutput = '-';
            if ((currProgressMarks+1) % sharedData->hashmarkInterval == 0)
                toOutput = '#';
            cout << toOutput << flush;
            currProgressMarks++;
        }
    }
    while (!sharedData->taskCompleted[TESTFILEINDEX]) { //wait for count words thread to finish

    }
    toOutput = '-';
    if ((currProgressMarks+1) % sharedData->hashmarkInterval == 0)
        toOutput = '#';
    cout << toOutput << endl;
    cout << "There are " << sharedData->wordCountInFile[TESTFILEINDEX] << " words in " << sharedData->filePath[TESTFILEINDEX] << "." << endl; //print word count
}
