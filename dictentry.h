/*
 * Christian James
 * 823672623
 */
#ifndef OPERATINGSYSTEMSASSIGNMENT2_DICTENTRY_H
#define OPERATINGSYSTEMSASSIGNMENT2_DICTENTRY_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class dictentry {
public:
    dictentry();
    dictentry *next[27]{};
    bool isWord;
};


#endif //OPERATINGSYSTEMSASSIGNMENT2_DICTENTRY_H
