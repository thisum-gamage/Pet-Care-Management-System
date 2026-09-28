#include <fstream>
#include <iostream>
#include <cstdio>

#include "../include/owner.h"
#include "../include/config.h"
#include "../include/parser.h"
#include "../include/input.h"
#include "../include/id_generator.h"

using namespace std;

bool ownerExists(const string &ownerID)
{
  ifstream file(OWNERS_FILE);
  string line;

  while (getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }

    Owner owner = parseOwner(line);

    if (convertToUpper(owner.ownerID) == convertToUpper(ownerID))
    {
      return true;
    }
  }

  return false;
}

bool mobileExists(const string &mobileNumber)
{
  ifstream file(OWNERS_FILE);
  string line;

  while (getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }

    Owner owner = parseOwner(line);

    if (owner.mobileNumber == mobileNumber)
    {
      return true;
    }
  }

  return false;
}


void displayOwner(const Owner &owner)
{
  cout << "\n----------------------------------------" << endl;
  cout << "Owner ID        : " << owner.ownerID << endl;
  cout << "First Name      : " << owner.firstName << endl;
  cout << "Last Name       : " << owner.lastName << endl;
  cout << "Mobile Number   : " << owner.mobileNumber << endl;
  cout << "Address         : " << owner.address << endl;
  cout << "Registered Date : " << owner.registeredDate << endl;
  cout << "----------------------------------------" << endl;
}

void addPetOwner()
{
  Owner owner;

  owner.ownerID = generateOwnerID();
  owner.firstName = getNonEmptyInput("Enter Your First Name: ");
  owner.lastName = getNonEmptyInput("Enter Your Last Name: ");
  owner.mobileNumber = getValidMobileNumber();

  if (mobileExists(owner.mobileNumber))
  {
    cout << "An owner with this mobile number already exists." << endl;
    return;
  }

  cout << "Enter Your Address (do not use commas): ";
  getline(cin, owner.address);

  cout << "Enter Registered Date (YYYY-MM-DD): ";
  getline(cin, owner.registeredDate);

  ofstream file(OWNERS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the owners file." << endl;
    return;
  }

  file << ownerToCSV(owner) << endl;

  file.close();

  cout << "Owner details inserted successfully." << endl;
}

void updatePetOwner()
{
  string updateID;
  string line;
  bool found = false;

  cout << "\n===== Update Pet Owner =====" << endl;
  cout << "Enter Owner ID to update (0 to cancel): ";
  cin >> updateID;

  if (updateID == "0")
  {
    return;
  }

  updateID = convertToUpper(updateID);

  ifstream inputFile(OWNERS_FILE);
  ofstream tempFile2(TEMP_FILE_2);

  if (!inputFile || !tempFile2)
  {
    cout << "Unable to open the required file." << endl;
    return;
  }

  while (getline(inputFile, line))
  {
    Owner owner = parseOwner(line);

    if (owner.ownerID == updateID)
    {

      clearInput();

      cout << "Enter New First Name: ";
      getline(cin, owner.firstName);

      cout << "Enter New Last Name: ";
      getline(cin, owner.lastName);

      cout << "Enter New Mobile Number: ";
      getline(cin, owner.mobileNumber);

      cout << "Enter New Address: ";
      getline(cin, owner.address);

      cout << "Enter New Registered Date (YYYY-MM-DD): ";
      getline(cin, owner.registeredDate);

      tempFile2 << ownerToCSV(owner) << endl;

      found = true;
    }

    else
    {
      tempFile2 << line << endl;
    }
  }
  inputFile.close();
  tempFile2.close();

  if (found)
  {
    remove(OWNERS_FILE.c_str());
    rename(TEMP_FILE_2.c_str(), OWNERS_FILE.c_str());

    cout << "Owner record updated successfully." << endl;
  }

  else
  {
    remove(TEMP_FILE_2.c_str());

    cout << "Owner record not found." << endl;
  }
}

void viewOwnerList()
{
  ifstream file(OWNERS_FILE);
  string line;
  bool recordsAvailable = false;

  cout << "\n===== Owners Records =====" << endl;

  if (!file)
  {
    cout << "No owner records are available." << endl;
    return;
  }

  while (getline(file, line))
  {
    Owner owner = parseOwner(line);

    displayOwner(owner);

    recordsAvailable = true;
  }
  file.close();

  if (!recordsAvailable)
  {
    cout << "No owner records are available." << endl;
  }
}
