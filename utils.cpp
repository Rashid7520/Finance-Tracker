#include "utils.h"
#include "db.h"
#include<iostream>
#include<openssl/sha.h>
#include<sstream>
#include<iomanip>
#include<random>

string sha256(const string &str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)str.c_str(), str.size(), hash);

    stringstream ss;
    for(int i = 0; i<SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

string generateSaltedhash(const string& password)
{
    string salt = "random$%salt123"; //Generate a random salt
    return sha256(password + salt);  
}