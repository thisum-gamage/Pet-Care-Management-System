#ifndef INPUT_H
#define INPUT_H

#include <string>

using namespace std;

//                     Input Validation
// ========================================================

void clearInput();

string convertToUpper(string text);

string getNonEmptyInput(const string &prompt);

int getValidAge(const string &prompt);

int getMenuChoice();

bool isValidMobileNumber(const string &mobileNumber);

string getValidMobileNumber();

#endif