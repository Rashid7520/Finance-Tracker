#ifndef UTILS_H
#define UTILS_H

#include <string>

// Function to hash a string with SHA-256
std::string sha256(const std::string &str);

// Function to hash password with salt
std::string generateSaltedhash(const std::string& password);

#endif // UTILS_H
