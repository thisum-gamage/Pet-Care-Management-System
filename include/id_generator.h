#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include <string>

using namespace std;

//                        ID generators
// ========================================================

string generateNextPrefixedID(
    const string &filename,
    const string &prefix);

string generateOwnerID();

string generatePetID();

string generateAppointmentID();

int generateUserID();

#endif