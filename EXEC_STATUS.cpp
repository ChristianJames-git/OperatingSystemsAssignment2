#include "EXEC_STATUS.h"

EXEC_STATUS::EXEC_STATUS(int marks, int hInterval, int minWords, const char* filenames[]) {
    if (marks == -1)
        numOfProgressMarks = DEFAULT_NUMOF_MARKS;
    else
        numOfProgressMarks = marks;
    if (hInterval == -1)
        hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
    else
        hashmarkInterval = hInterval;
    if (minWords == -1)
        minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;
    else
        minNumOfWordsWithAPrefixForPrinting = minWords;

    dictRootNode = new dictentry();

    filePath[DICTSRCFILEINDEX] = filenames[DICTSRCFILEINDEX];
    filePath[TESTFILEINDEX] = filenames[TESTFILEINDEX];

    struct stat st;
    stat(filePath[DICTSRCFILEINDEX], &st);
    totalNumOfCharsInFile[DICTSRCFILEINDEX] = st.st_size;
    numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = new long(0);
    stat(filePath[TESTFILEINDEX], &st);
    totalNumOfCharsInFile[TESTFILEINDEX] = st.st_size;
    numOfCharsProcessedFromFile[TESTFILEINDEX] = new long(0);
}
