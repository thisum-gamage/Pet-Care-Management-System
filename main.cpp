#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

struct Owner
{
  string owner_id, first_name, last_name, mobile_num, address;
  int registered_date;
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

void administratorMenu()
{
  cout << "\n------Welcome to Administrator Section------" << endl;
  cout << "1. Pet Owners" << endl;
  cout << "2. Pet Records" << endl;
  cout << "3. Appoinments" << endl;
  cout << "4. Appoinments Updates" << endl;
  cout << "5. Reports" << endl;
  cout << "6. User Accounts" << endl;
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