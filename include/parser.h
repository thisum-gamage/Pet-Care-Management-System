#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "models.h"

using namespace std;

Appointment parseAppointment(const string &line);

Pet parsePet(const string &line);

Owner parseOwner(const string &line);

User parseUser(const string &line);

string appointmentToCSV(const Appointment &appointment);

string petToCSV(const Pet &pet);

string ownerToCSV(const Owner &owner);

string userToCSV(const User &user);

#endif