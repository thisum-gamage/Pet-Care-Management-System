#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <limits>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

const string OWNERS_FILE = "D:\\Pet Care Management System Files\\owners.txt";

const string PETS_FILE = "D:\\Pet Care Management System Files\\pets.txt";

const string APPOINTMENTS_FILE = "D:\\Pet Care Management System Files\\appointments.txt";

const string TEMP_FILE = "D:\\Pet Care Management System Files\\temp.txt";

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
  string appo_num, pet_id, service_type, symptoms, treatment_notes, appo_status, last_updated_date, appo_date;
};

void clearInput()
{
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string generateOwnerID()
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
      int currentID = stoi(id.substr(3));

      if (currentID > highestID)
      {
        highestID = currentID;
      }
    }
  }
  file.close();

  int nextID = highestID + 1;
  ostringstream ss;
  ss << "OWN" << setfill('0') << setw(3) << nextID;
  return ss.str();
}

string generatePetID()
{
  ifstream file(PETS_FILE);
  string line;
  int highestID = 0;

  while (getline(file, line))
  {
    stringstream ss(line);
    string id;

    getline(ss, id, ',');

    if (!id.empty())
    {
      int currentID = stoi(id.substr(3));

      if (currentID > highestID)
      {
        highestID = currentID;
      }
    }
  }
  file.close();

  int nextID = highestID + 1;
  ostringstream ss;
  ss << "PET" << setfill('0') << setw(3) << nextID;
  return ss.str();
}

string generateAppointmentID()
{
  ifstream file(APPOINTMENTS_FILE);
  string line;
  int highestID = 0;

  while (getline(file, line))
  {
    stringstream ss(line);
    string id;

    getline(ss, id, ',');

    if (!id.empty())
    {
      int currentID = stoi(id.substr(3));

      if (currentID > highestID)
      {
        highestID = currentID;
      }
    }
  }
  file.close();

  int nextID = highestID + 1;
  ostringstream ss;
  ss << "APP" << setfill('0') << setw(3) << nextID;
  return ss.str();
}

void addPetOwner()
{
  Owner owner;
  owner.owner_id = generateOwnerID();

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

  file << owner.owner_id << "," << owner.first_name << "," << owner.last_name << "," << owner.mobile_num << "," << owner.address << "," << owner.registered_date << endl;

  file.close();

  cout << "Owner details inserted successfully." << endl;
}

void addPetRecord()
{
  Pet pet;
  pet.pet_id = generatePetID();

  clearInput();

  cout << "Enter Owner ID: ";
  getline(cin, pet.owner_id);

  cout << "Enter Your Pet Name: ";
  getline(cin, pet.pet_name);

  cout << "Enter Your Pet Type: ";
  getline(cin, pet.pet_type);

  cout << "Enter Your Pet Breed: ";
  getline(cin, pet.breed);

  cout << "Enter Your Pet Age: ";
  cin >> pet.age;
  clearInput();

  cout << "Enter Pet Gender: ";
  getline(cin, pet.gender);

  cout << "Enter Pet Special Notes: ";
  getline(cin, pet.special_notes);

  ofstream file(PETS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the pets file." << endl;
    return;
  }

  file << pet.pet_id << "," << pet.owner_id << "," << pet.pet_name << "," << pet.pet_type << "," << pet.breed << "," << pet.age << "," << pet.gender << "," << pet.special_notes << endl;

  file.close();

  cout << "Pet details inserted successfully." << endl;
}

void addAppointment()
{
  Appointment appointment;
  appointment.appo_num = generateAppointmentID();

  clearInput();

  cout << "Enter Pet ID: ";
  getline(cin, appointment.pet_id);

  cout << "Enter Appointment Date: ";
  getline(cin, appointment.appo_date);

  cout << "Enter Service Type: ";
  getline(cin, appointment.service_type);

  cout << "Enter Pet Symptoms: ";
  getline(cin, appointment.symptoms);

  appointment.treatment_notes = "None";
  appointment.appo_status = "Pending";

  cout << "Enter Last Updated Date: ";
  getline(cin, appointment.last_updated_date);

  ofstream file(APPOINTMENTS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the appointments file." << endl;
    return;
  }

  file << appointment.appo_num << "," << appointment.pet_id << "," << appointment.appo_date << "," << appointment.service_type << "," << appointment.symptoms << "," << appointment.treatment_notes << "," << appointment.appo_status << "," << appointment.last_updated_date << endl;

  file.close();

  cout << "Appointment details inserted successfully." << endl;
}

void trackAppointment()
{
  clearInput();
  string searchID;
  string prefix;
  string line;
  bool found = false;

  cout << "Enter Appointment ID/Pet ID/Owner ID/Mobile Number: " << endl;
  cin >> searchID;

  prefix = searchID.substr(0, 3);

  if (prefix == "APP" || prefix == "PET")
  {

    ifstream file(APPOINTMENTS_FILE);

    if (!file)
    {
      cout << "No appointment records are available." << endl;
      return;
    }

    while (getline(file, line))
    {
      stringstream ss(line);
      Appointment appointment;

      getline(ss, appointment.appo_num, ',');
      getline(ss, appointment.pet_id, ',');
      getline(ss, appointment.appo_date, ',');
      getline(ss, appointment.service_type, ',');
      getline(ss, appointment.symptoms, ',');
      getline(ss, appointment.treatment_notes, ',');
      getline(ss, appointment.appo_status, ',');
      getline(ss, appointment.last_updated_date, ',');

      if (searchID == appointment.appo_num || searchID == appointment.pet_id)
      {
        cout << "\n--- Appointment Found! ---" << endl;
        cout << "Appointment ID: " << appointment.appo_num << endl;
        cout << "Pet ID: " << appointment.pet_id << endl;
        cout << "Date: " << appointment.appo_date << endl;
        cout << "Service Type: " << appointment.service_type << endl;
        cout << "Symptoms: " << appointment.symptoms << endl;
        cout << "Status: " << appointment.appo_status << endl;
        cout << "Treatment Notes: " << appointment.treatment_notes << endl;
        cout << "Last Updated: " << appointment.last_updated_date << endl;

        found = true;
      }
    }

    if (!found)
    {
      cout << "No appointment found for given ID!" << endl;
    }

    file.close();
  }

  else if (prefix == "OWN")
  {
    
  }
}

void updateAppointment()
{
  string updateID;
  string line;
  bool found = false;

  cout << "\n===== Update Appointment =====" << endl;
  cout << "Enter Pet ID/Appointment ID to update: ";
  cin >> updateID;

  ifstream inputFile(APPOINTMENTS_FILE);
  ofstream tempFile(TEMP_FILE);

  if (!inputFile || !tempFile)
  {
    cout << "Unable to open the required file." << endl;
    return;
  }

  while (getline(inputFile, line))
  {
    stringstream ss(line);
    Appointment appointment;

    getline(ss, appointment.appo_num, ',');
    getline(ss, appointment.pet_id, ',');
    getline(ss, appointment.appo_date, ',');
    getline(ss, appointment.service_type, ',');
    getline(ss, appointment.symptoms, ',');
    getline(ss, appointment.treatment_notes, ',');
    getline(ss, appointment.appo_status, ',');
    getline(ss, appointment.last_updated_date, ',');

    if (appointment.appo_num == updateID || appointment.pet_id == updateID)
    {
      clearInput();

      cout << "Enter New Treatment Notes: ";
      getline(cin, appointment.treatment_notes);

      cout << "Enter New Appoinment Status: ";
      getline(cin, appointment.appo_status);

      cout << "Enter New Last Updated Date: ";
      getline(cin, appointment.last_updated_date);

      tempFile << appointment.appo_num << "," << appointment.pet_id << "," << appointment.appo_date << "," << appointment.service_type << "," << appointment.symptoms << "," << appointment.treatment_notes << "," << appointment.appo_status << "," << appointment.last_updated_date << endl;
      found = true;
    }
    else
    {
      tempFile << line << endl;
    }
  }
  inputFile.close();
  tempFile.close();

  if (found)
  {
    remove(APPOINTMENTS_FILE.c_str());
    rename(TEMP_FILE.c_str(), APPOINTMENTS_FILE.c_str());

    cout << "Appointment record updated successfully." << endl;
  }
  else
  {
    remove(TEMP_FILE.c_str());
    cout << "Appointment record not found." << endl;
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
    stringstream ss(line);
    Owner owner;

    getline(ss, owner.owner_id, ',');
    getline(ss, owner.first_name, ',');
    getline(ss, owner.last_name, ',');
    getline(ss, owner.mobile_num, ',');
    getline(ss, owner.address, ',');
    getline(ss, owner.registered_date, ',');

    cout << "\nOwner ID : " << owner.owner_id << endl;
    cout << "First Name: " << owner.first_name << endl;
    cout << "Last Name: " << owner.last_name << endl;
    cout << "Mobile Number: " << owner.mobile_num << endl;
    cout << "Address: " << owner.address << endl;
    cout << "Registered Date: " << owner.registered_date << endl;
    cout << "------------------------------" << endl;

    recordsAvailable = true;
  }
  file.close();

  if (!recordsAvailable)
  {
    cout << "No owner records are available." << endl;
  }
}

void viewPetList()
{
  ifstream file(PETS_FILE);
  string line;
  string tempAge;
  bool recordsAvailable = false;

  cout << "\n===== Pets Records =====" << endl;

  if (!file)
  {
    cout << "No pet records are available." << endl;
    return;
  }

  while (getline(file, line))
  {
    stringstream ss(line);
    Pet pet;

    getline(ss, pet.pet_id, ',');
    getline(ss, pet.owner_id, ',');
    getline(ss, pet.pet_name, ',');
    getline(ss, pet.pet_type, ',');
    getline(ss, pet.breed, ',');
    getline(ss, tempAge, ',');
    pet.age = stoi(tempAge);
    getline(ss, pet.gender, ',');
    getline(ss, pet.special_notes, ',');

    cout << "\nPet ID: " << pet.pet_id << endl;
    cout << "Owner ID : " << pet.owner_id << endl;
    cout << "Pet Name: " << pet.pet_name << endl;
    cout << "Pet Type: " << pet.pet_type << endl;
    cout << "Breed: " << pet.breed << endl;
    cout << "Age: " << pet.age << endl;
    cout << "Gender: " << pet.gender << endl;
    cout << "Special Note: " << pet.special_notes << endl;
    cout << "------------------------------" << endl;

    recordsAvailable = true;
  }
  file.close();

  if (!recordsAvailable)
  {
    cout << "No pet records are available." << endl;
  }
}

void administratorMenu()
{
  int option;
  int choice;

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
    addPetRecord(); // Add pet records 🐾
    break;
  case 3:
    addAppointment(); // Add appointments 📅
    break;
  case 4:
    updateAppointment(); // Track appointments 🔍
    break;
  case 5:
    cout << "1. Owners" << endl;
    cout << "2. Pets" << endl;
    cout << "\nEnter Your Choice: ";
    cin >> choice;

    if (choice == 1)
    {
      viewOwnerList();
    }
    else if (choice == 2)
    {
      viewPetList();
    }
    else
    {
      cout << "Invalid Choice!";
    }
    break;

  default:
    cout << "Invalid option!" << endl;
  }
}

void receptionistMenu()
{
  int choice;
  int subChoice;

  cout << "\n------Welcome to Receptionist Section------" << endl;

  cout << "1. Add & update pet owner details" << endl;
  cout << "2. Add pet records" << endl;
  cout << "3. Add appointments" << endl;
  cout << "4. Track appoinments" << endl;
  cout << "5. View owner & pet lists" << endl;

  cout << "\nEnter your choice: ";
  cin >> choice;

  switch (choice)
  {
  case 1:
    addPetOwner();
    break;

  case 2:
    addPetRecord();
    break;

  case 3:
    addAppointment();
    break;

  case 4:
    trackAppointment();
    break;

  case 5:
    cout << "1. Owners" << endl;
    cout << "2. Pets" << endl;
    cout << "\nEnter Your Choice: ";
    cin >> subChoice;

    if (subChoice == 1)
    {
      viewOwnerList();
    }
    else if (subChoice == 2)
    {
      viewPetList();
    }
    else
    {
      cout << "Invalid Choice!";
    }
    break;

  default:
    cout << "Invalid option!" << endl;
  }
}

void vetStaffMenu()
{
  int option;
  cout << "\n------Welcome to Vet Staff Member Section------" << endl;
  cout << "1. Update appoinments details" << endl;
  cout << "2. Track appoinments" << endl;

  cout << "\nEnter your choice: ";
  cin >> option;

  switch (option)
  {
  case 1:
    updateAppointment();
    break;

  case 2:
    trackAppointment();
    break;

  default:
    cout << "Invalid option!" << endl;
  }
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