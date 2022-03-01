#include "EXEC_STATUS.h"

EXEC_STATUS::EXEC_STATUS(int marks, int hInterval, int minWords) {
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
}
