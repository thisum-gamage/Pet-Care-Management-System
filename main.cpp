#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

const string OWNERS_FILE = "D:\\Pet Care Management System Files\\owners.txt";

struct Owner
{
  string owner_id, first_name, last_name, address, registered_date, mobile_num;
};

struct Pet
{
  string pet_id, owner_id, pet_name, pet_type, breed, gender, special_notes;
  int age;
};

struct Appointment
{
  int appo_num, appo_date, last_update_date;
  string pet_id, service_type, symptoms, treatment_notes, appo_status;
};

void clearInput()
{
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int generateOwnerID()
{
  ifstream file(OWNERS_FILE);
  string line;
  int highestID = 0;

  while (getline(file, line))
  {
    stringstream ss(line);
    string id;

    getline(ss, id, ',');

    if (!id.empty())
    {
      int currentID = stoi(id);

      if (currentID > highestID)
      {
        highestID = currentID;
      }
    }
  }
  file.close();
  return highestID + 1;
}

void addPetOwner()
{
  Owner owner;

  clearInput();

  cout << "Enter Your First Name: ";
  getline(cin, owner.first_name);

  cout << "Enter Your Last Name: ";
  getline(cin, owner.last_name);

  cout << "Enter Your Mobile Number: ";
  getline(cin, owner.mobile_num);

  cout << "Enter Your Address: ";
  getline(cin, owner.address);

  cout << "Enter Registered Date: ";
  getline(cin, owner.registered_date);

  ofstream file(OWNERS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the owners file." << endl;
    return;
  }

  file << owner.first_name << "," << owner.last_name << "," << owner.mobile_num << "," << owner.address << "," << owner.registered_date << endl;

  file.close();

  cout << "Owner details inserted successfully." << endl;
}

void administratorMenu()
{
  int option;
  cout << "\n------Welcome to Administrator Section------" << endl;
  cout << "1. Pet Owners" << endl;
  cout << "2. Pet Records" << endl;
  cout << "3. Appoinments" << endl;
  cout << "4. Appoinments Updates" << endl;
  cout << "5. Reports" << endl;
  cout << "6. User Accounts" << endl;

  cout << "\nEnter your choice: ";
  cin >> option;

  switch (option)
  {
  case 1:
    addPetOwner(); // Add & update pet owner details 👤
    break;
  case 2:
    // Add pet records 🐾
    break;
  case 3:
    // Add appointments 📅
    break;
  case 4:
    // Track appointments 🔍
    break;
  case 5:
    // View owner & pet lists 📋
    break;
  default:
    cout << "Invalid option!" << endl;
  }
}

void receptionistMenu()
{
  cout << "\n------Welcome to Receptionist Section------" << endl;
  cout << "1. Add & update pet owner details" << endl;
  cout << "2. Add pet records" << endl;
  cout << "3. Add appointments" << endl;
  cout << "4. Track appoinments" << endl;
  cout << "5. View owner & pet lists" << endl;
}

void vetStaffMenu()
{
  cout << "\n------Welcome to Vet Staff Member Section------" << endl;
  cout << "1. Update appoinments details" << endl;
  cout << "2. Track appoinments" << endl;
}

int main()
{
  int choice, num;
  do
  {
    cout << "\n===== Pet Care Management System =====" << endl;
    cout << "\n1. Login";
    cout << "\n2. Exit" << endl;
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
      cout << "\n   Login as," << endl;
      cout << "\n1. Administrator" << endl;
      cout << "2. Receptionist" << endl;
      cout << "3. Vet Staff Member" << endl;
      cout << "\nEnter your choice: ";
      cin >> num;

      if (num == 1)
      {
        administratorMenu(); // to admin login function.
      }
      else if (num == 2)
      {
        receptionistMenu(); // to recep login function.
      }
      else if (num == 3)
      {
        vetStaffMenu(); // to vet staff login function.
      }
    }
  } while (choice != 2);

  return 0;
}