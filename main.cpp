#include <getopt.h>
#include "populatetree.h"
#include "countwords.h"
#include <pthread.h>

using namespace std;

extern "C" void * populateTreeThread( void * VoidPtr )
{
    auto *popTree = new populatetree();
    popTree->threadMain(VoidPtr);
    return nullptr;
}

extern "C" void * countWordsThread( void * VoidPtr )
{
    auto *countWords = new countwords();
    countWords->threadMain(VoidPtr);
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
        maxProgressMarks = (long)(sharedData->numOfProgressMarks * ((double) *sharedData->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] / (double) sharedData->totalNumOfCharsInFile[DICTSRCFILEINDEX]));
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
        maxProgressMarks = (long)(sharedData->numOfProgressMarks * ((double) *sharedData->numOfCharsProcessedFromFile[TESTFILEINDEX] / (double) sharedData->totalNumOfCharsInFile[TESTFILEINDEX]));
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
