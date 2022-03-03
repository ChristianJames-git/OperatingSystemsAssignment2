#include <getopt.h>
#include "populatetree.h"
#include "countwords.h"
#include <pthread.h>
#include <sched.h>

extern "C" void * populateTreeThread( void * VoidPtr )
{
    EXEC_STATUS *sharedData;
    sharedData = (EXEC_STATUS *) VoidPtr;

    auto *popTree = new populatetree(*sharedData->dictRootNode);
    popTree->readDict(sharedData->filePath[DICTSRCFILEINDEX]);

    for (auto & i : popTree->dictionaryStore) {
        int temp = popTree->add(i.c_str(), i.c_str());
        if (temp == -1) {
            cout << "failed to insert word" << endl;
            exit(EXIT_FAILURE);
        } else {
            sharedData->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] += temp;
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

    /* If we wanted to return something, we would return a pointer
     * to the data that we wanted to return.
     *
     * Instead of simply using return, we could also call
     * pthread_exit.
     */
    return sharedData;
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
    pthread_t populatetree, countwords;

    pthread_create(&populatetree, &pthread_attributes, &populateTreeThread, sharedData);
    pthread_create(&countwords, &pthread_attributes, &countWordsThread, sharedData);

    delete(&sharedData);
}
