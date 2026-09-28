#ifndef PET_H
#define PET_H

#include "models.h"

bool petExists(const string &petID);

void addPetRecord();
void viewPetList();
void viewPetsByOwner();

#endif