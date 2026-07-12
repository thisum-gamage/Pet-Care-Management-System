#include <iostream>
#include <string>
using namespace std;

struct owner
{
  string owner_id, first_name, last_name, mobile_num, address;
  int registered_date;
};

struct pet
{
  string pet_id, owner_id, pet_name, pet_type, breed, gender, special_notes;
  int age;
};

struct appointment
{
  int appo_num, appo_date, last_update_date;
  string pet_id, service_type, symptoms, treatment_notes, appo_status;
};

int main()
{
  int choice;

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
    cout << "3. Vet staff Member" << endl;
  }
  else
  {
    return 0;
  }

  return 0;
}