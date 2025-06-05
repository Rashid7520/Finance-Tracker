#ifndef UTILS_H
#define UTILS_H

#include<string>
using namespace std;

string sha256(const string &input);
string generateSaltedhash(const string& password);

#endif // UTILS_H