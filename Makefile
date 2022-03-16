# Christian James 823672623

# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb
CXXFLAGS=-std=c++11 -g -pthread

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target

# $^ is an example of a special variable.  It substitutes all dependencies
dicttest : main.o populatetree.o countwords.o dictentry.o EXEC_STATUS.o
	$(CXX) $(CXXFLAGS) -o dicttest $^

main.o : countwords.h populatetree.h main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

countwords.o : dictentry.h EXEC_STATUS.h countwords.h countwords.cpp
	$(CXX) $(CXXFLAGS) -c countwords.cpp

populatetree.o : dictentry.h EXEC_STATUS.h populatetree.h populatetree.cpp
	$(CXX) $(CXXFLAGS) -c populatetree.cpp

EXEC_STATUS.o : dictentry.h EXEC_STATUS.h EXEC_STATUS.cpp
	$(CXX) $(CXXFLAGS) -c EXEC_STATUS.cpp

dictentry.o : dictentry.h dictentry.cpp
	$(CXX) $(CXXFLAGS) -c dictentry.cpp

clean :
	rm *.o