// include/error.h
#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>

using namespace std;

void error(int line, const string& reason, const string& suggestion) {
    cout << "❌ Error on line " << line << ":" << endl;
    cout << "Reason: " << reason << endl;
    cout << "Suggestion: " << suggestion << endl;
}

#endif
