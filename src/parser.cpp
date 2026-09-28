#include <sstream>

#include "../include/parser.h"

using namespace std;

//                      Parsers
// ========================================================

Appointment parseAppointment(const string &line)
{
  Appointment appointment;

  stringstream ss(line);

  getline(ss, appointment.appointmentNumber, ',');
  getline(ss, appointment.petID, ',');
  getline(ss, appointment.appointmentDate, ',');
  getline(ss, appointment.serviceType, ',');
  getline(ss, appointment.symptoms, ',');
  getline(ss, appointment.treatmentNotes, ',');
  getline(ss, appointment.appointmentStatus, ',');
  getline(ss, appointment.lastUpdatedDate, ',');

  return appointment;
}

Pet parsePet(const string &line)
{
  Pet pet;
  stringstream ss(line);
  string tempAge;

  getline(ss, pet.petID, ',');
  getline(ss, pet.ownerID, ',');
  getline(ss, pet.petName, ',');
  getline(ss, pet.petType, ',');
  getline(ss, pet.breed, ',');
  getline(ss, tempAge, ',');
  getline(ss, pet.gender, ',');
  getline(ss, pet.specialNotes, ',');

  pet.age = stoi(tempAge);

  return pet;
}

Owner parseOwner(const string &line)
{
  Owner owner;

  stringstream ss(line);

  getline(ss, owner.ownerID, ',');
  getline(ss, owner.firstName, ',');
  getline(ss, owner.lastName, ',');
  getline(ss, owner.mobileNumber, ',');
  getline(ss, owner.address, ',');
  getline(ss, owner.registeredDate, ',');

  return owner;
}

User parseUser(const string &line)
{
  User user;

  stringstream ss(line);
  string tempUserID;

  getline(ss, tempUserID, ',');
  getline(ss, user.username, ',');
  getline(ss, user.password, ',');
  getline(ss, user.role, ',');

  user.userID = stoi(tempUserID);

  return user;
}

string appointmentToCSV(const Appointment &appointment)
{
  return appointment.appointmentNumber + "," +
         appointment.petID + "," +
         appointment.appointmentDate + "," +
         appointment.serviceType + "," +
         appointment.symptoms + "," +
         appointment.treatmentNotes + "," +
         appointment.appointmentStatus + "," +
         appointment.lastUpdatedDate;
}

string petToCSV(const Pet &pet)
{
  return pet.petID + "," +
         pet.ownerID + "," +
         pet.petName + "," +
         pet.petType + "," +
         pet.breed + "," +
         to_string(pet.age) + "," +
         pet.gender + "," +
         pet.specialNotes;
}

string ownerToCSV(const Owner &owner)
{
  return owner.ownerID + "," +
         owner.firstName + "," +
         owner.lastName + "," +
         owner.mobileNumber + "," +
         owner.address + "," +
         owner.registeredDate;
}

string userToCSV(const User &user)
{
  return to_string(user.userID) + "," +
         user.username + "," +
         user.password + "," +
         user.role;
}
