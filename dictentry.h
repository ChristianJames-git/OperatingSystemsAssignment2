#include <iostream>
#include <fstream>
#include <vector>

#ifndef OPERATINGSYSTEMSASSIGNMENT2_DICTENTRY_H
#define OPERATINGSYSTEMSASSIGNMENT2_DICTENTRY_H

using namespace std;

class dictentry {
public:
    dictentry();
    dictentry *next[27]{};
    bool isWord;
};


#endif //OPERATINGSYSTEMSASSIGNMENT2_DICTENTRY_H
