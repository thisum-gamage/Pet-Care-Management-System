#include <iostream>
#include <fstream>

#include "../include/search.h"
#include "../include/config.h"
#include "../include/parser.h"
#include "../include/input.h"
#include "../include/owner.h"
#include "../include/pet.h"
#include "../include/appointment.h"

using namespace std;

void searchByOwnerID(string searchID)
{
  searchID = convertToUpper(searchID);

  string line;
  Owner owner;
  bool found = false;

  ifstream file(OWNERS_FILE);

  if (!file)
  {
    cout << "No owner records are available." << endl;
    return;
  }

  while (getline(file, line))
  {
    Owner owner = parseOwner(line);

    if (searchID == owner.ownerID)
    {
      cout << "\n----- Owner Found! -----" << endl;

      displayOwner(owner);

      found = true;
    }
  }
  file.close();

  if (!found)
  {
    cout << "No owner records are available." << endl;
  }
}

void searchByMobileNumber(string searchID)
{
  ifstream ownersFile(OWNERS_FILE);

  string ownerLine;
  string foundOwnerID = "";
  bool ownerFound = false;

  if (!ownersFile)
  {
    cout << "No owner records available!" << endl;
    return;
  }

  while (getline(ownersFile, ownerLine))
  {
    Owner owner = parseOwner(ownerLine);

    if (searchID == owner.mobileNumber)
    {
      foundOwnerID = owner.ownerID;
      ownerFound = true;

      cout << "\n----- Owner Details Found -----" << endl;

      displayOwner(owner);

      break;
    }
  }
  ownersFile.close();

  if (!ownerFound)
  {
    cout << "No owner found with this mobile number!" << endl;
    return;
  }

  // --------------------------------------------------------

  ifstream petsFile(PETS_FILE);

  string petLine;
  bool appointmentFound = false;

  if (!petsFile)
  {
    cout << "No pet records available!" << endl;
    return;
  }

  while (getline(petsFile, petLine))
  {
    Pet pet = parsePet(petLine);

    if (foundOwnerID == pet.ownerID)
    {
      if (displayPetAppointments(pet.petID))
      {
        appointmentFound = true;
      }
    }
  }
  petsFile.close();

  if (!appointmentFound)
  {
    cout << "No appointments found for this owner's pets!" << endl;
  }
}

void searchAppointmentsByOwnerID(string searchID)
{
  searchID = convertToUpper(searchID);

  ifstream ownerFile(OWNERS_FILE);

  if (!ownerFile)
  {
    cout << "No owner records available!" << endl;
    return;
  }

  string ownerLine;
  string foundOwnerID = "";
  bool ownerFound = false;

  while (getline(ownerFile, ownerLine))
  {
    Owner owner = parseOwner(ownerLine);

    if (searchID == owner.ownerID)
    {
      foundOwnerID = owner.ownerID;
      ownerFound = true;
    }
  }
  ownerFile.close();

  if (!ownerFound)
  {
    cout << "No owner found with this Owner ID!" << endl;
    return;
  }

  ifstream petFile(PETS_FILE);

  if (!petFile)
  {
    cout << "No pet records available!" << endl;
    return;
  }

  string petLine;
  bool appointmentFound = false;

  while (getline(petFile, petLine))
  {
    Pet pet = parsePet(petLine);

    if (foundOwnerID == pet.ownerID)
    {
      if (displayPetAppointments(pet.petID))
      {
        appointmentFound = true;
      }
    }
  }
  petFile.close();

  if (!appointmentFound)
  {
    cout << "No appointments found for this owner's pets!" << endl;
  }
}
