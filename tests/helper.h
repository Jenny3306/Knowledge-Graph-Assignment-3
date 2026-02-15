#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <vector>
#include "src/KnowledgeGraph.h"

using namespace std;

// Char comparators and converters
bool charComparator(char &lhs, char &rhs);
string vertex2str(char &v);
string vertex2str2(char &v);

// String comparators and converters
bool stringComparator(string &lhs, string &rhs);
string stringVertex2str(string &v);

// Int comparators and converters
bool intComparator(int &lhs, int &rhs);
string intVertex2str(int &v);

// Float comparators and converters
bool floatComparator(float &lhs, float &rhs);
string floatVertex2str(float &v);

#endif