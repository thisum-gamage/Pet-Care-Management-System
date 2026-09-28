#include <iostream>
#include <fstream>

#include "../include/pet.h"
#include "../include/config.h"
#include "../include/parser.h"
#include "../include/input.h"
#include "../include/id_generator.h"
#include "../include/owner.h"

using namespace std;

bool petExists(const string &petID)
{
  ifstream file(PETS_FILE);
  string line;

  while (getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }

    Pet pet = parsePet(line);

    if (convertToUpper(pet.petID) == convertToUpper(petID))
    {
      return true;
    }
  }

  return false;
}

void addPetRecord()
{
  int genderChoice;
  Pet pet;

  pet.petID = generatePetID();

  cout << "Enter Owner ID: ";
  getline(cin, pet.ownerID);

  pet.ownerID = convertToUpper(pet.ownerID);

  if (!ownerExists(pet.ownerID))
  {
    cout << "Owner ID does not exist. Please register the owner first." << endl;
    return;
  }

  pet.petName = getNonEmptyInput("Enter Your Pet Name: ");
  pet.petType = getNonEmptyInput("Enter Your Pet Type: ");
  pet.breed = getNonEmptyInput("Enter Your Pet Breed: ");
  pet.age = getValidAge("Enter Your Pet Age: ");

  while (true)
  {
    cout << "Pet Gender" << endl;

    cout << "1. Male" << endl;
    cout << "2. Female" << endl;

    cout << "Enter Gender: ";

    genderChoice = getMenuChoice();

    if (genderChoice == 1)
    {
      pet.gender = "Male";
      break;
    }

    else if (genderChoice == 2)
    {
      pet.gender = "Female";
      break;
    }

    else
    {
      cout << "Invalid gender choice. Please select 1 or 2." << endl;
    }
  }
  cout << "Enter Pet Special Notes (do not use commas): ";
  getline(cin, pet.specialNotes);

  ofstream file(PETS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the pets file." << endl;
    return;
  }

  file << petToCSV(pet) << endl;

  file.close();

  cout << "Pet details inserted successfully." << endl;
}

void viewPetList()
{
  ifstream file(PETS_FILE);
  string line;

  bool recordsAvailable = false;

  cout << "\n===== Pets Records =====" << endl;

  if (!file)
  {
    cout << "No pet records are available." << endl;
    return;
  }

  while (getline(file, line))
  {
    Pet pet = parsePet(line);

    cout << "\nPet ID: " << pet.petID << endl;
    cout << "Owner ID : " << pet.ownerID << endl;
    cout << "Pet Name: " << pet.petName << endl;
    cout << "Pet Type: " << pet.petType << endl;
    cout << "Breed: " << pet.breed << endl;
    cout << "Age: " << pet.age << endl;
    cout << "Gender: " << pet.gender << endl;
    cout << "Special Note: " << pet.specialNotes << endl;
    cout << "------------------------------" << endl;

    recordsAvailable = true;
  }
  file.close();

  if (!recordsAvailable)
  {
    cout << "No pet records are available." << endl;
  }
}

void viewPetsByOwner()
{
  string searchOwnerID;

  cout << "Enter Owner ID to view pets: ";
  getline(cin, searchOwnerID);
  searchOwnerID = convertToUpper(searchOwnerID);

  ifstream file(PETS_FILE);
  string line;
  bool found = false;

  if (!file)
  {
    cout << "No pet records are available." << endl;
    return;
  }

  cout << "\n===== Pets Registered Under Owner: " << searchOwnerID << " =====" << endl;

  while (getline(file, line))
  {
    Pet pet = parsePet(line);

    if (pet.ownerID == searchOwnerID)
    {
      cout << "Pet ID   : " << pet.petID << endl;
      cout << "Pet Name : " << pet.petName << endl;
      cout << "Pet Type : " << pet.petType << endl;
      cout << "Breed    : " << pet.breed << endl;
      cout << "------------------------------" << endl;
      found = true;
    }
  }
  file.close();

  if (!found)
  {
    cout << "No pets found for this Owner ID." << endl;
  }
}
