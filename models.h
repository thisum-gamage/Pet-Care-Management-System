#ifndef MODELS_H
#define MODELS_H

#include <string>

using namespace std;

struct Owner
{
  string ownerID;
  string firstName;
  string lastName;
  string mobileNumber;
  string address;
  string registeredDate;
};

struct Pet
{
  string petID;
  string ownerID;
  string petName;
  string petType;
  string breed;
  string gender;
  string specialNotes;
  int age;
};

struct Appointment
{
  string appointmentNumber;
  string petID;
  string appointmentDate;
  string serviceType;
  string symptoms;
  string treatmentNotes;
  string appointmentStatus;
  string lastUpdatedDate;
};

struct User
{
  int userID;
  string username;
  string password;
  string role;
};

#endif