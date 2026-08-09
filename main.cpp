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

//                         Files
// ========================================================

const string OWNERS_FILE = "owners.txt";
const string PETS_FILE = "pets.txt";
const string APPOINTMENTS_FILE = "appointments.txt";
const string USERS_FILE = "users.txt";
const string TEMP_FILE_1 = "temp1.txt";
const string TEMP_FILE_2 = "temp2.txt";

//              Structures & Input Validation
// ========================================================

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

void clearInput()
{
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string convertToLower(string text)
{
  transform(
      text.begin(),
      text.end(),
      text.begin(),
      [](unsigned char character)
      {
        return static_cast<char>(tolower(character));
      });

  return text;
}

//                      ID generators
// ========================================================

string generateOwnerID()
{
  int currentID;
  int nextID;
  int highestID = 0;

  ifstream file(OWNERS_FILE);
  string line;

  while (getline(file, line))
  {
    stringstream ss(line);
    string id;
    getline(ss, id, ',');

    if (!id.empty())
    {
      currentID = stoi(id.substr(3));

      if (currentID > highestID)
      {
        highestID = currentID;
      }
    }
  }
  file.close();

  nextID = highestID + 1;

  ostringstream ss;
  ss << "OWN" << setfill('0') << setw(3) << nextID;
  return ss.str();
}

string generatePetID()
{
  int currentID;
  int nextID;
  int highestID = 0;

  ifstream file(PETS_FILE);
  string line;

  while (getline(file, line))
  {
    stringstream ss(line);
    string id;

    getline(ss, id, ',');

    if (!id.empty())
    {
      currentID = stoi(id.substr(3));

      if (currentID > highestID)
      {
        highestID = currentID;
      }
    }
  }
  file.close();

  nextID = highestID + 1;

  ostringstream ss;
  ss << "PET" << setfill('0') << setw(3) << nextID;
  return ss.str();
}

string generateAppointmentID()
{
  int nextID;
  int highestID = 0;

  ifstream file(APPOINTMENTS_FILE);
  string line;

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

  nextID = highestID + 1;

  ostringstream ss;
  ss << "APP" << setfill('0') << setw(3) << nextID;
  return ss.str();
}

int generateUserID()
{
  ifstream file(USERS_FILE);
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

// --------------------------------------------------------

bool login(User &loggedInUser)
{
  string enteredUsername;
  string enteredPassword;
  int attempts = 3;

  while (attempts > 0)
  {
    cout << "\n======== Pet System Login ========" << endl;

    cout << "Username: ";
    cin >> enteredUsername;
    cout << "Password: ";
    cin >> enteredPassword;

    ifstream file(USERS_FILE);

    if (!file)
    {
      cout << "\nUnable to open the user file." << endl;
      return false;
    }

    string line;

    while (getline(file, line))
    {
      stringstream ss(line);
      User user;
      string id;

      getline(ss, id, ',');
      getline(ss, user.username, ',');
      getline(ss, user.password, ',');
      getline(ss, user.role);

      if (id.empty())
      {
        continue;
      }

      user.userID = stoi(id);

      if (enteredUsername == user.username &&
          enteredPassword == user.password)
      {
        loggedInUser = user;

        cout << "\nLogin successful." << endl;
        cout << "Welcome, " << loggedInUser.username << "!" << endl;
        cout << "Role: " << loggedInUser.role << endl;

        return true;
      }
    }
    file.close();

    attempts--;
    cout << "\nInvalid username or password." << endl;
    cout << "Remaining attempts: " << attempts << endl;
  }
  cout << "\nAccess denied. Too many unsuccessful attempts." << endl;

  return false;
}

void initializeUserFile()
{
  ifstream inputFile(USERS_FILE);

  // If the file already exists, do not create it again
  if (inputFile)
  {
    inputFile.close();
    return;
  }
  ofstream outputFile(USERS_FILE);

  if (!outputFile)
  {
    cout << "Unable to create the user file." << endl;
    return;
  }

  // Save default users
  outputFile << "1,admin,123,Administrator" << endl;
  outputFile << "2,receptionist,456,Receptionist" << endl;
  outputFile << "3,vetstaffmember,789,Vet Staff Member" << endl;

  outputFile.close();

  cout << "Default user accounts were created." << endl;
}

//                         Adding
// ========================================================

void addPetOwner()
{
  Owner owner;
  owner.ownerID = generateOwnerID();

  clearInput();

  cout << "Enter Your First Name: ";
  getline(cin, owner.firstName);

  cout << "Enter Your Last Name: ";
  getline(cin, owner.lastName);

  cout << "Enter Your Mobile Number: ";
  getline(cin, owner.mobileNumber);

  cout << "Enter Your Address: ";
  getline(cin, owner.address);

  cout << "Enter Registered Date: ";
  getline(cin, owner.registeredDate);

  ofstream file(OWNERS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the owners file." << endl;
    return;
  }

  file << owner.ownerID << "," << owner.firstName << "," << owner.lastName << "," << owner.mobileNumber << "," << owner.address << "," << owner.registeredDate << endl;

  file.close();

  cout << "Owner details inserted successfully." << endl;
}

void addPetRecord()
{
  Pet pet;
  pet.petID = generatePetID();

  clearInput();

  cout << "Enter Owner ID: ";
  getline(cin, pet.ownerID);

  cout << "Enter Your Pet Name: ";
  getline(cin, pet.petName);

  cout << "Enter Your Pet Type: ";
  getline(cin, pet.petType);

  cout << "Enter Your Pet Breed: ";
  getline(cin, pet.breed);

  cout << "Enter Your Pet Age: ";
  cin >> pet.age;
  clearInput();

  cout << "Enter Pet Gender: ";
  getline(cin, pet.gender);

  cout << "Enter Pet Special Notes: ";
  getline(cin, pet.specialNotes);

  ofstream file(PETS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the pets file." << endl;
    return;
  }

  file << pet.petID << "," << pet.ownerID << "," << pet.petName << "," << pet.petType << "," << pet.breed << "," << pet.age << "," << pet.gender << "," << pet.specialNotes << endl;

  file.close();

  cout << "Pet details inserted successfully." << endl;
}

void addAppointment()
{
  Appointment appointment;
  appointment.appointmentNumber = generateAppointmentID();

  clearInput();

  cout << "Enter Pet ID: ";
  getline(cin, appointment.petID);

  cout << "Enter Appointment Date: ";
  getline(cin, appointment.appointmentDate);

  cout << "Enter Service Type: ";
  getline(cin, appointment.serviceType);

  cout << "Enter Pet Symptoms: ";
  getline(cin, appointment.symptoms);

  appointment.treatmentNotes = "None";
  appointment.appointmentStatus = "Pending";

  cout << "Enter Last Updated Date: ";
  getline(cin, appointment.lastUpdatedDate);

  ofstream file(APPOINTMENTS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the appointments file." << endl;
    return;
  }

  file << appointment.appointmentNumber << "," << appointment.petID << "," << appointment.appointmentDate << "," << appointment.serviceType << "," << appointment.symptoms << "," << appointment.treatmentNotes << "," << appointment.appointmentStatus << "," << appointment.lastUpdatedDate << endl;

  file.close();

  cout << "Appointment details inserted successfully." << endl;
}

void addUserAccount()
{
  int tempRole;
  User user;
  user.userID = generateUserID();
  clearInput();

  cout << "\n===== Add User Account =====" << endl;

  cout << "Enter Username: ";
  getline(cin, user.username);

  cout << "Enter Password: ";
  getline(cin, user.password);

  cout << "---- Select Role ----";
  cout << "\n1. Administrator" << endl;
  cout << "2. Receptionist" << endl;
  cout << "3. Vet Staff Member" << endl;
  cout << "\nEnter Role: ";

  cin >> tempRole;

  if (tempRole == 1)
  {
    user.role = "Administrator";
  }

  else if (tempRole == 2)
  {
    user.role = "Receptionist";
  }

  else if (tempRole == 3)
  {
    user.role = "Vet Staff Member";
  }

  else
  {
    cout << "Invalid Choice!!!" << endl;
    return;
  }

  ofstream file(USERS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the employee file." << endl;
    return;
  }

  file << user.userID << "," << user.username << "," << user.password << "," << user.role << endl;

  file.close();

  cout << "Employee inserted successfully." << endl;
  cout << "Employee ID: " << user.userID << endl;
}

//                        Searching
// ========================================================

void searchByAppointmentIDOrPetID(string searchID)
{
  string line;
  Appointment appointment;
  bool found = false;

  ifstream appointmentFile(APPOINTMENTS_FILE);

  if (!appointmentFile)
  {
    cout << "No appointment records are available." << endl;
    return;
  }

  while (getline(appointmentFile, line))
  {
    stringstream ss(line);

    getline(ss, appointment.appointmentNumber, ',');
    getline(ss, appointment.petID, ',');
    getline(ss, appointment.appointmentDate, ',');
    getline(ss, appointment.serviceType, ',');
    getline(ss, appointment.symptoms, ',');
    getline(ss, appointment.treatmentNotes, ',');
    getline(ss, appointment.appointmentStatus, ',');
    getline(ss, appointment.lastUpdatedDate, ',');

    if (searchID == appointment.appointmentNumber || searchID == appointment.petID)
    {
      cout << "\n--- Appointment Found! ---" << endl;
      cout << "Appointment ID : " << appointment.appointmentNumber << endl;
      cout << "Pet ID         : " << appointment.petID << endl;
      cout << "Date           : " << appointment.appointmentDate << endl;
      cout << "Service Type   : " << appointment.serviceType << endl;
      cout << "Symptoms       : " << appointment.symptoms << endl;
      cout << "Status         : " << appointment.appointmentStatus << endl;
      cout << "Treatment Notes: " << appointment.treatmentNotes << endl;
      cout << "Last Updated   : " << appointment.lastUpdatedDate << endl;

      found = true;
    }
  }

  if (!found)
  {
    cout << "No appointment found for given ID!" << endl;
  }

  appointmentFile.close();
}

void searchByOwnerID(string searchID)
{
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
    stringstream ss(line);

    getline(ss, owner.ownerID, ',');
    getline(ss, owner.firstName, ',');
    getline(ss, owner.lastName, ',');
    getline(ss, owner.mobileNumber, ',');
    getline(ss, owner.address, ',');
    getline(ss, owner.registeredDate, ',');

    if (searchID == owner.ownerID)
    {
      cout << "\nOwner ID     : " << owner.ownerID << endl;
      cout << "First Name     : " << owner.firstName << endl;
      cout << "Last Name      : " << owner.lastName << endl;
      cout << "Mobile Number  : " << owner.mobileNumber << endl;
      cout << "Address        : " << owner.address << endl;
      cout << "Registered Date: " << owner.registeredDate << endl;
      cout << "------------------------------" << endl;

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
  string line;
  string tempAge;
  Owner owner;
  Pet pet;
  Appointment appointment;
  string foundOwnerID = "";
  bool ownerFound = false;
  bool appointmentFound = false;

  ifstream ownerFile(OWNERS_FILE);

  if (!ownerFile)
  {
    cout << "No owner records available!" << endl;
    return;
  }

  while (getline(ownerFile, line))
  {
    stringstream ss(line);

    getline(ss, owner.ownerID, ',');
    getline(ss, owner.firstName, ',');
    getline(ss, owner.lastName, ',');
    getline(ss, owner.mobileNumber, ',');
    getline(ss, owner.address, ',');
    getline(ss, owner.registeredDate, ',');

    if (searchID == owner.mobileNumber)
    {
      foundOwnerID = owner.ownerID;
      ownerFound = true;

      cout << "\n--- Owner Details Found ---" << endl;
      cout << "Owner ID     : " << owner.ownerID << endl;
      cout << "Name         : " << owner.firstName << " " << owner.lastName << endl;
      cout << "Mobile       : " << owner.mobileNumber << endl;
      cout << "Address        : " << owner.address << endl;
      cout << "Registered Date: " << owner.registeredDate << endl;
      break;
    }
  }
  ownerFile.close();

  if (!ownerFound)
  {
    cout << "No owner found with this mobile number!" << endl;
    return;
  }

  ifstream petFile(PETS_FILE);
  if (!petFile)
  {
    cout << "No pet records available!" << endl;
    return;
  }

  while (getline(petFile, line))
  {
    stringstream ss(line);

    getline(ss, pet.petID, ',');
    getline(ss, pet.ownerID, ',');
    getline(ss, pet.petName, ',');
    getline(ss, pet.petType, ',');
    getline(ss, pet.breed, ',');
    getline(ss, tempAge, ',');
    pet.age = stoi(tempAge);
    getline(ss, pet.gender, ',');
    getline(ss, pet.specialNotes, ',');

    if (foundOwnerID == pet.ownerID)
    {
      ifstream appointmentFile(APPOINTMENTS_FILE);
      string appointmentLine;

      while (getline(appointmentFile, appointmentLine))
      {
        stringstream appointmentSS(appointmentLine);

        getline(appointmentSS, appointment.appointmentNumber, ',');
        getline(appointmentSS, appointment.petID, ',');
        getline(appointmentSS, appointment.appointmentDate, ',');
        getline(appointmentSS, appointment.serviceType, ',');
        getline(appointmentSS, appointment.symptoms, ',');
        getline(appointmentSS, appointment.treatmentNotes, ',');
        getline(appointmentSS, appointment.appointmentStatus, ',');
        getline(appointmentSS, appointment.lastUpdatedDate, ',');

        if (appointment.petID == pet.petID)
        {
          cout << "\n--- Appointment Details ---" << endl;
          cout << "Appointment ID : " << appointment.appointmentNumber << endl;
          cout << "Pet ID         : " << appointment.petID << endl;
          cout << "Pet Name       : " << pet.petName << endl;
          cout << "Date           : " << appointment.appointmentDate << endl;
          cout << "Service        : " << appointment.serviceType << endl;
          cout << "Status         : " << appointment.appointmentStatus << endl;
          appointmentFound = true;
        }
      }
      appointmentFile.close();
    }
  }
  petFile.close();

  if (!appointmentFound)
  {
    cout << "No appointments found for this owner's pets!" << endl;
  }
}

void searchByOwnerIDtoAppointmentID(string searchID)
{
  string line;
  string tempAge;
  Owner owner;
  Pet pet;
  Appointment appointment;
  string foundOwnerID = "";
  bool ownerFound = false;
  bool appointmentFound = false;

  ifstream ownerFile(OWNERS_FILE);

  if (!ownerFile)
  {
    cout << "No owner records available!" << endl;
    return;
  }

  while (getline(ownerFile, line))
  {
    stringstream ss(line);

    getline(ss, owner.ownerID, ',');
    getline(ss, owner.firstName, ',');
    getline(ss, owner.lastName, ',');
    getline(ss, owner.mobileNumber, ',');
    getline(ss, owner.address, ',');
    getline(ss, owner.registeredDate, ',');

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

  while (getline(petFile, line))
  {
    stringstream ss(line);

    getline(ss, pet.petID, ',');
    getline(ss, pet.ownerID, ',');
    getline(ss, pet.petName, ',');
    getline(ss, pet.petType, ',');
    getline(ss, pet.breed, ',');
    getline(ss, tempAge, ',');
    pet.age = stoi(tempAge);
    getline(ss, pet.gender, ',');
    getline(ss, pet.specialNotes, ',');

    if (foundOwnerID == pet.ownerID)
    {
      ifstream appointmentFile(APPOINTMENTS_FILE);
      string appointmentLine;

      while (getline(appointmentFile, appointmentLine))
      {
        stringstream appointmentSS(appointmentLine);

        getline(appointmentSS, appointment.appointmentNumber, ',');
        getline(appointmentSS, appointment.petID, ',');
        getline(appointmentSS, appointment.appointmentDate, ',');
        getline(appointmentSS, appointment.serviceType, ',');
        getline(appointmentSS, appointment.symptoms, ',');
        getline(appointmentSS, appointment.treatmentNotes, ',');
        getline(appointmentSS, appointment.appointmentStatus, ',');
        getline(appointmentSS, appointment.lastUpdatedDate, ',');

        if (appointment.petID == pet.petID)
        {
          cout << "\n--- Appointment Details ---" << endl;
          cout << "Appointment ID : " << appointment.appointmentNumber << endl;
          cout << "Pet ID         : " << appointment.petID << endl;
          cout << "Pet Name       : " << pet.petName << endl;
          cout << "Date           : " << appointment.appointmentDate << endl;
          cout << "Service        : " << appointment.serviceType << endl;
          cout << "Status         : " << appointment.appointmentStatus << endl;
          appointmentFound = true;
        }
      }
      appointmentFile.close();
    }
  }
  petFile.close();

  if (!appointmentFound)
  {
    cout << "No appointments found for this owner's pets!" << endl;
  }
}

//                         Update
// ========================================================

void trackAppointment()
{
  clearInput();

  string searchID;
  string prefix;
  string line;
  string targetOwnerID;

  cout << "Enter Appointment ID/Pet ID/Owner ID/Mobile Number: " << endl;
  cin >> searchID;

  prefix = searchID.substr(0, 3);

  if (prefix == "APP" || prefix == "PET")
  {
    searchByAppointmentIDOrPetID(searchID);
  }

  else if (prefix == "OWN")
  {
    searchByOwnerID(searchID);
    searchByOwnerIDtoAppointmentID(searchID);
  }

  else
  {
    searchByMobileNumber(searchID);
  }
}

void updatePetOwner()
{
  string updateID;
  string line;
  bool found = false;

  cout << "\n===== Update Pet Owner =====" << endl;
  cout << "Enter Owner ID to update: ";
  cin >> updateID;

  ifstream inputFile(OWNERS_FILE);
  ofstream tempFile2(TEMP_FILE_2);

  if (!inputFile || !tempFile2)
  {
    cout << "Unable to open the required file." << endl;
    return;
  }

  while (getline(inputFile, line))
  {
    stringstream ss(line);
    Owner owner;

    getline(ss, owner.ownerID, ',');
    getline(ss, owner.firstName, ',');
    getline(ss, owner.lastName, ',');
    getline(ss, owner.mobileNumber, ',');
    getline(ss, owner.address, ',');
    getline(ss, owner.registeredDate, ',');

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

      cout << "Enter New Registered Date: ";
      getline(cin, owner.registeredDate);

      tempFile2 << owner.ownerID << "," << owner.firstName << "," << owner.lastName << "," << owner.mobileNumber << "," << owner.address << "," << owner.registeredDate << endl;
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

void updateAppointment()
{
  string updateID;
  string line;
  bool found = false;

  cout << "\n===== Update Appointment =====" << endl;
  cout << "Enter Pet ID/Appointment ID to update: ";
  cin >> updateID;

  ifstream inputFile(APPOINTMENTS_FILE);
  ofstream tempFile1(TEMP_FILE_1);

  if (!inputFile || !tempFile1)
  {
    cout << "Unable to open the required file." << endl;
    return;
  }

  while (getline(inputFile, line))
  {
    stringstream ss(line);
    Appointment appointment;

    getline(ss, appointment.appointmentNumber, ',');
    getline(ss, appointment.petID, ',');
    getline(ss, appointment.appointmentDate, ',');
    getline(ss, appointment.serviceType, ',');
    getline(ss, appointment.symptoms, ',');
    getline(ss, appointment.treatmentNotes, ',');
    getline(ss, appointment.appointmentStatus, ',');
    getline(ss, appointment.lastUpdatedDate, ',');

    if (appointment.appointmentNumber == updateID || appointment.petID == updateID)
    {
      clearInput();

      cout << "Enter New Treatment Notes: ";
      getline(cin, appointment.treatmentNotes);

      cout << "Enter New Appointment Status: ";
      getline(cin, appointment.appointmentStatus);

      cout << "Enter New Last Updated Date: ";
      getline(cin, appointment.lastUpdatedDate);

      tempFile1 << appointment.appointmentNumber << "," << appointment.petID << "," << appointment.appointmentDate << "," << appointment.serviceType << "," << appointment.symptoms << "," << appointment.treatmentNotes << "," << appointment.appointmentStatus << "," << appointment.lastUpdatedDate << endl;
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

//                         Viewing
// ========================================================

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

    getline(ss, owner.ownerID, ',');
    getline(ss, owner.firstName, ',');
    getline(ss, owner.lastName, ',');
    getline(ss, owner.mobileNumber, ',');
    getline(ss, owner.address, ',');
    getline(ss, owner.registeredDate, ',');

    cout << "\nOwner ID : " << owner.ownerID << endl;
    cout << "First Name: " << owner.firstName << endl;
    cout << "Last Name: " << owner.lastName << endl;
    cout << "Mobile Number: " << owner.mobileNumber << endl;
    cout << "Address: " << owner.address << endl;
    cout << "Registered Date: " << owner.registeredDate << endl;
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

    getline(ss, pet.petID, ',');
    getline(ss, pet.ownerID, ',');
    getline(ss, pet.petName, ',');
    getline(ss, pet.petType, ',');
    getline(ss, pet.breed, ',');
    getline(ss, tempAge, ',');
    pet.age = stoi(tempAge);
    getline(ss, pet.gender, ',');
    getline(ss, pet.specialNotes, ',');

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

    cout << "Appointment ID : " << appointment.appointmentNumber << endl;
    cout << "Pet ID         : " << appointment.petID << endl;
    cout << "Date           : " << appointment.appointmentDate << endl;
    cout << "Service Type   : " << appointment.serviceType << endl;
    cout << "Symptoms       : " << appointment.symptoms << endl;
    cout << "Status         : " << appointment.appointmentStatus << endl;
    cout << "Treatment Notes: " << appointment.treatmentNotes << endl;
    cout << "Last Updated   : " << appointment.lastUpdatedDate << endl;

    recordsAvailable = true;
  }
  file.close();

  if (!recordsAvailable)
  {
    cout << "No appointment records are available." << endl;
  }
}

void viewPetsByOwner()
{
  string searchOwnerID;
  clearInput();
  cout << "Enter Owner ID to view pets: ";
  getline(cin, searchOwnerID);

  ifstream file(PETS_FILE);
  string line, tempAge;
  bool found = false;

  if (!file)
  {
    cout << "No pet records are available." << endl;
    return;
  }

  cout << "\n===== Pets Registered Under Owner: " << searchOwnerID << " =====" << endl;

  while (getline(file, line))
  {
    stringstream ss(line);
    Pet pet;

    getline(ss, pet.petID, ',');
    getline(ss, pet.ownerID, ',');
    getline(ss, pet.petName, ',');
    getline(ss, pet.petType, ',');
    getline(ss, pet.breed, ',');
    getline(ss, tempAge, ',');
    try
    {
      pet.age = stoi(tempAge);
    }
    catch (...)
    {
      pet.age = 0;
    }
    getline(ss, pet.gender, ',');
    getline(ss, pet.specialNotes, ',');

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

//                         Menus
// ========================================================

void administratorMenu(const User &currentUser)
{
  int option;
  int choice, subChoice1;
  do
  {
    cout << "\n------Welcome to Administrator Section------" << endl;
    cout << "1. Pet Owners" << endl;
    cout << "2. Pet Records" << endl;
    cout << "3. Appointments" << endl;
    cout << "4. Appointments Updates" << endl;
    cout << "5. Reports" << endl;
    cout << "6. User Accounts" << endl;
    cout << "7. Logout" << endl;

    cout << "\nEnter your choice: ";
    cin >> option;

    switch (option)
    {
    case 1:
      cout << "1. Add pet owner details" << endl;
      cout << "2. Update pet owner details" << endl;
      cout << "\nEnter Your Choice: ";
      cin >> subChoice1; // Add & update pet owner details 👤

      if (subChoice1 == 1)
      {
        addPetOwner();
      }
      else if (subChoice1 == 2)
      {
        updatePetOwner();
      }
      else
      {
        cout << "Invalid Choice!";
      }
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
      cout << "3. Appointment" << endl;
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

      else if (choice == 3)
      {
        viewAppointmentList();
      }

      else
      {
        cout << "Invalid Choice!";
      }
      break;

    case 6:
      cout << "User Accounts Management Section" << endl;
      addUserAccount();
      break;

    case 7:
      cout << "Logging out..." << endl;
      break;

    default:
      cout << "Invalid option!" << endl;
    }
  } while (option != 7);
}

void receptionistMenu(const User &currentUser)
{
  int choice;
  int subChoice;
  int subChoice2;

  do
  {
    cout << "\n------Welcome to Receptionist Section------" << endl;

    cout << "1. Add & update pet owner details" << endl;
    cout << "2. Add pet records" << endl;
    cout << "3. Add appointments" << endl;
    cout << "4. Track appointments" << endl;
    cout << "5. View owner & pet lists" << endl;
    cout << "6. Logout" << endl;

    cout << "\nEnter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "1. Add pet owner details" << endl;
      cout << "2. Update pet owner details" << endl;
      cout << "\nEnter Your Choice: ";
      cin >> subChoice2;

      if (subChoice2 == 1)
      {
        addPetOwner();
      }
      else if (subChoice2 == 2)
      {
        updatePetOwner();
      }
      else
      {
        cout << "Invalid Choice!";
      }
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

    case 6:
      cout << "Logging out..." << endl;
      break;

    default:
      cout << "Invalid option!" << endl;
    }
  } while (choice != 6);
}

void vetStaffMenu(const User &currentUser)
{
  int option;

  do
  {
    cout << "\n------Welcome to Vet Staff Member Section------" << endl;
    cout << "1. Update appointments details" << endl;
    cout << "2. Track appointments" << endl;
    cout << "3. Logout" << endl;

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

    case 3:
      cout << "Logging out..." << endl;
      break;

    default:
      cout << "Invalid option!" << endl;
    }
  } while (option != 3);
}

//                       Main Program
// ========================================================

int main()
{
  initializeUserFile();
  User loggedInUser;
  int choice, mainChoice;

  do
  {
    cout << "\n========================================" << endl;
    cout << "       PET CARE MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "\n1. Login" << endl;
    cout << "\n2. Exit" << endl;
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
      if (login(loggedInUser))
      {
        if (loggedInUser.role == "Administrator")
        {
          administratorMenu(loggedInUser);
        }

        else if (loggedInUser.role == "Receptionist")
        {
          receptionistMenu(loggedInUser);
        }

        else if (loggedInUser.role == "Vet Staff Member")
        {
          vetStaffMenu(loggedInUser);
        }
      }

      cout << "\n===== Main Menu =====" << endl;
      cout << "1. Login Again" << endl;
      cout << "2. Exit System" << endl;
      cout << "Enter your choice: ";
      cin >> mainChoice;

      if (mainChoice != 1 && mainChoice != 2)
      {
        cout << "Invalid choice. The system will close." << endl;
        mainChoice = 2;
      }
    }

    else if (choice == 2)
    {
      mainChoice = 2;
    }

    else
    {
      cout << "Invalid Choice !!!" << endl;
      mainChoice = 1;
    }

  } while (mainChoice != 2);

  cout << "\nThank you for using the Pet Management System." << endl;

  return 0;
}