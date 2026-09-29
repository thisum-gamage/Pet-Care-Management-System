#ifndef OWNER_H
#define OWNER_H

#include "models.h"

bool ownerExists(const string &ownerID);
bool mobileExists(const string &mobileNumber);
bool duplicateMobileCheck(const Owner &owner);

void displayOwner(const Owner &owner);
void addPetOwner();
void updatePetOwner();
void viewOwnerList();

#endif