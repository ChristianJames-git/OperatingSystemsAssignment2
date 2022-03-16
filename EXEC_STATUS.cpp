/*
 * Christian James
 * 823672623
 */
#include "EXEC_STATUS.h"

EXEC_STATUS::EXEC_STATUS(int marks, int hInterval, int minWords, const char* filenames[]) {
    if (marks == -1) //instantiate marks
        numOfProgressMarks = DEFAULT_NUMOF_MARKS;
    else
        numOfProgressMarks = marks;
    if (hInterval == -1) //instantiate hash interval
        hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
    else
        hashmarkInterval = hInterval;
    if (minWords == -1) //instantiate min words to print
        minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;
    else
        minNumOfWordsWithAPrefixForPrinting = minWords;

    dictRootNode = new dictentry(); //create root node

    filePath[DICTSRCFILEINDEX] = filenames[DICTSRCFILEINDEX]; //store file names
    filePath[TESTFILEINDEX] = filenames[TESTFILEINDEX];

    struct stat st{}; //determine and store total numbers of chars in file and set charprocessed point to a long equal to 0
    stat(filePath[DICTSRCFILEINDEX], &st);
    totalNumOfCharsInFile[DICTSRCFILEINDEX] = st.st_size;
    numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = new long(0);
    stat(filePath[TESTFILEINDEX], &st);
    totalNumOfCharsInFile[TESTFILEINDEX] = st.st_size;
    numOfCharsProcessedFromFile[TESTFILEINDEX] = new long(0);
}
