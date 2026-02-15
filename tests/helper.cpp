#include "helper.h"

// Char helpers
bool charComparator(char &lhs, char &rhs) { 
    return lhs == rhs; 
}

string vertex2str(char &v) {
    stringstream os;
    os << v;
    return os.str();
}

string vertex2str2(char &v) {
    stringstream os;
    os << v << "-";
    return os.str();
}

// String helpers
bool stringComparator(string &lhs, string &rhs) {
    return lhs == rhs;
}

string stringVertex2str(string &v) {
    return v;
}

// Int helpers
bool intComparator(int &lhs, int &rhs) {
    return lhs == rhs;
}

string intVertex2str(int &v) {
    stringstream os;
    os << v;
    return os.str();
}

// Float helpers
bool floatComparator(float &lhs, float &rhs) {
    return fabs(lhs - rhs) < 1e-6;
}

string floatVertex2str(float &v) {
    stringstream os;
    os << v;
    return os.str();
}