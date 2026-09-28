#ifndef AUTH_H
#define AUTH_H

#include "models.h"

//                      Initializing
// ========================================================

bool login(User &loggedInUser);

void initializeUserFile();

#endif