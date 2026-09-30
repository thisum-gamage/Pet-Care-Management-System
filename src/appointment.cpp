#include <iostream>
#include <fstream>
#include <cstdio>

#include "../include/appointment.h"
#include "../include/config.h"
#include "../include/parser.h"
#include "../include/input.h"
#include "../include/id_generator.h"
#include "../include/pet.h"

using namespace std;

void addAppointment()
{
  Appointment appointment;
  appointment.appointmentNumber = generateAppointmentID();

  cout << "Enter Pet ID: ";
  getline(cin, appointment.petID);

  appointment.petID = convertToUpper(appointment.petID);

  if (!petExists(appointment.petID))
  {
    cout << "Pet ID does not exist. Please register the pet first." << endl;
    return;
  }

  appointment.appointmentDate = getValidDate(
      "Enter Appointment Date (YYYY-MM-DD): ");

  appointment.serviceType = getNonEmptyInput(
      "Enter Service Type: ");

  appointment.symptoms = getNonEmptyInput(
      "Enter Pet Symptoms (do not use commas): ");

  appointment.treatmentNotes = "None";
  appointment.appointmentStatus = "Pending";

  appointment.lastUpdatedDate = getValidDate(
      "Enter Last Updated Date (YYYY-MM-DD): ");

  ofstream file(APPOINTMENTS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the appointments file." << endl;
    return;
  }

  file << appointmentToCSV(appointment) << endl;

  file.close();

  cout << "Appointment details inserted successfully." << endl;
}

void updateAppointment()
{
  string updateID;
  string line;
  int statusChoice;
  bool found = false;

  cout << "\n===== Update Appointment =====" << endl;
  cout << "Enter Appointment Number to update (0 to cancel): ";
  cin >> updateID;

  if (updateID == "0")
  {
    return;
  }

  updateID = convertToUpper(updateID);

  ifstream inputFile(APPOINTMENTS_FILE);
  ofstream tempFile1(TEMP_FILE_1);

  if (!inputFile || !tempFile1)
  {
    cout << "Unable to open the required file." << endl;
    return;
  }

  while (getline(inputFile, line))
  {
    Appointment appointment = parseAppointment(line);

    if (appointment.appointmentNumber == updateID)
    {
      clearInput();

      appointment.treatmentNotes = getNonEmptyInput(
          "Enter New Treatment Notes (do not use commas): ");

      cout << "Enter New Appointment Status" << endl;

      cout << "1. Pending" << endl;
      cout << "2. Completed" << endl;
      cout << "Enter Status: ";
      statusChoice = getMenuChoice();

      if (statusChoice == 1)
      {
        appointment.appointmentStatus = "Pending";
      }

      else if (statusChoice == 2)
      {
        appointment.appointmentStatus = "Completed";
      }

      else
      {
        cout << "Invalid status choice." << endl;

        inputFile.close();
        tempFile1.close();

        remove(TEMP_FILE_1.c_str());

        return;
      }

      appointment.lastUpdatedDate = getValidDate(
          "Enter Last Updated Date (YYYY-MM-DD): ");

      tempFile1 << appointmentToCSV(appointment) << endl;

      found = true;
    }

    else
    {
      tempFile1 << line << endl;
    }
  }
  inputFile.close();
  tempFile1.close();

  if (found)
  {
    remove(APPOINTMENTS_FILE.c_str());
    rename(TEMP_FILE_1.c_str(), APPOINTMENTS_FILE.c_str());

    cout << "Appointment record updated successfully." << endl;
  }

  else
  {
    remove(TEMP_FILE_1.c_str());
    cout << "Appointment record not found." << endl;
  }
}

void displayAppointment(const Appointment &appointment)
{
  cout << "\n----------------------------------------" << endl;
  cout << "Appointment Number : " << appointment.appointmentNumber << endl;
  cout << "Pet ID             : " << appointment.petID << endl;
  cout << "Appointment Date   : " << appointment.appointmentDate << endl;
  cout << "Service Type       : " << appointment.serviceType << endl;
  cout << "Symptoms           : " << appointment.symptoms << endl;
  cout << "Treatment Notes    : " << appointment.treatmentNotes << endl;
  cout << "Appointment Status : " << appointment.appointmentStatus << endl;
  cout << "Last Updated Date  : " << appointment.lastUpdatedDate << endl;
  cout << "----------------------------------------" << endl;
}

bool displayPetAppointments(const string &petID)
{
  ifstream appointmentFile(APPOINTMENTS_FILE);

  if (!appointmentFile)
  {
    cout << "Unable to open appointments file.\n";
    return false;
  }

  string line;
  bool found = false;

  while (getline(appointmentFile, line))
  {
    if (line.empty())
    {
      continue;
    }

    Appointment appointment = parseAppointment(line);

    if (appointment.petID == petID)
    {
      found = true;

      cout << "\n----- Appointment Details -----" << endl;

      displayAppointment(appointment);
    }
  }

  appointmentFile.close();

  if (!found)
  {
    cout << "No appointments found for this pet.\n";
  }

  return found;
}

void searchByAppointmentIDOrPetID(string searchID)
{
  string upperSearchID = convertToUpper(searchID);

  ifstream file(APPOINTMENTS_FILE);

  if (!file)
  {
    cout << "No appointment records are available." << endl;
    return;
  }

  bool found = false;
  string line;

  while (getline(file, line))
  {
    Appointment appointment = parseAppointment(line);

    if (searchID == appointment.appointmentNumber ||
        searchID == appointment.petID)
    {
      cout << "\n----- Appointment Found! -----" << endl;

      displayAppointment(appointment);

      found = true;
    }
  }

  if (!found)
  {
    cout << "No appointment found for given ID!" << endl;
  }

  file.close();
}

void viewAppointmentList()
{
  ifstream file(APPOINTMENTS_FILE);
  string line;
  bool recordsAvailable = false;

  cout << "\n===== Appointment Records =====" << endl;

  if (!file)
  {
    cout << "No appointment records are available." << endl;
    return;
  }

  while (getline(file, line))
  {
    Appointment appointment = parseAppointment(line);

    displayAppointment(appointment);

    recordsAvailable = true;
  }
  file.close();

  if (!recordsAvailable)
  {
    cout << "No appointment records are available." << endl;
  }
}

void viewAppointmentsByStatus()
{
  string line;
  int choice;
  string status = "";
  bool recordsAvailable = false;

  cout << "\n1. View Pending Appointments" << endl;
  cout << "2. View Completed Appointments" << endl;
  cout << "3. Back to Main Menu" << endl;

  cout << "Enter Your Choice: " << endl;
  choice = getMenuChoice();

  if (choice == 1)
  {
    status = "Pending";
  }

  else if (choice == 2)
  {
    status = "Completed";
  }

  else if (choice == 3)
  {
    return;
  }

  else
  {
    cout << "\nInvalid Choice!" << endl;
    return;
  }

  ifstream file(APPOINTMENTS_FILE);

  if (!file)
  {
    cout << "No appointment records are available.\n";
    return;
  }

  while (getline(file, line))
  {
    Appointment appointment = parseAppointment(line);

    if (appointment.appointmentStatus == status)
    {
      displayAppointment(appointment);

      recordsAvailable = true;
    }
  }

  if (!recordsAvailable)
  {
    cout << "No matching appointments are available." << endl;
  }
}
