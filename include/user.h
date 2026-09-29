#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

bool usernameExists(const string &username);

void addUserAccount();
void viewUserList();

#endif