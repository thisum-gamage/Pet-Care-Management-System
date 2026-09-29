#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <limits>
#include <algorithm>
#include <cctype>
#include <iomanip>

#include "include/models.h"
#include "include/input.h"
#include "include/parser.h"
#include "include/id_generator.h"
#include "include/config.h"
#include "include/auth.h"
#include "include/owner.h"
#include "include/pet.h"
#include "include/appointment.h"
#include "include/search.h"

using namespace std;

bool usernameExists(const string &username)
{
  ifstream file(USERS_FILE);
  string line;

  while (getline(file, line))
  {
    User user = parseUser(line);

    if (user.username == username)
    {
      return true;
    }
  }

  return false;
}

//                         Adding
// ========================================================

void addUserAccount()
{
  int tempRole;

  User user;
  user.userID = generateUserID();

  cout << "\n===== Add User Account =====" << endl;

  cout << "Enter Username: ";
  getline(cin, user.username);

  if (usernameExists(user.username))
  {
    cout << "Username already exists." << endl;
    return;
  }

  cout << "Enter Password: ";
  getline(cin, user.password);

  while (true)
  {
    cout << "---- Select Role ----" << endl;

    cout << "\n1. Administrator" << endl;
    cout << "2. Receptionist" << endl;
    cout << "3. Vet Staff Member" << endl;

    cout << "\nEnter Role: ";

    tempRole = getMenuChoice();

    if (tempRole == 1)
    {
      user.role = "Administrator";
      break;
    }

    else if (tempRole == 2)
    {
      user.role = "Receptionist";
      break;
    }

    else if (tempRole == 3)
    {
      user.role = "Vet Staff Member";
      break;
    }

    else
    {
      cout << "Invalid Choice. Please select 1, 2, or 3." << endl;
    }
  }
  ofstream file(USERS_FILE, ios::app);

  if (!file)
  {
    cout << "Unable to open the user file." << endl;
    return;
  }

  file << userToCSV(user) << endl;

  file.close();

  cout << "User account created successfully." << endl;
  cout << "User ID: " << user.userID << endl;
}

//                    Update & Tracking
// ========================================================

void trackAppointment()
{
  int choice;
  string searchID;

  while (true)
  {
    cout << "\n========== Track Appointment ==========" << endl;
    cout << "1. Search by Appointment Number" << endl;
    cout << "2. Search by Owner ID" << endl;
    cout << "3. Search by Pet ID" << endl;
    cout << "4. Search by Mobile Number" << endl;
    cout << "5. Back" << endl;

    cout << "Enter Your Choice: ";
    choice = getMenuChoice();

    switch (choice)
    {
    case 1:
      cout << "Enter Appointment Number: ";
      cin >> searchID;
      searchByAppointmentIDOrPetID(searchID);
      break;

    case 2:
      cout << "Enter Owner ID: ";
      cin >> searchID;
      searchAppointmentsByOwnerID(searchID);
      break;

    case 3:
      cout << "Enter Pet ID: ";
      cin >> searchID;
      searchByAppointmentIDOrPetID(searchID);
      break;

    case 4:
      cout << "Enter Mobile Number: ";
      cin >> searchID;
      searchByMobileNumber(searchID);
      break;

    case 5:
      return;

    default:
      cout << "Invalid Choice!" << endl;
    }
  }
}

//                         Viewing
// ========================================================

void viewUserList()
{
  ifstream file(USERS_FILE);
  string line;
  bool recordsAvailable = false;

  cout << "\n===== User Accounts List =====" << endl;

  if (!file)
  {
    cout << "No user records are available." << endl;
    return;
  }

  while (getline(file, line))
  {
    User user = parseUser(line);

    cout << "\nUser ID  : " << user.userID << endl;
    cout << "Username : " << user.username << endl;
    cout << "Role     : " << user.role << endl;
    cout << "------------------------------" << endl;

    recordsAvailable = true;
  }
  file.close();

  if (!recordsAvailable)
  {
    cout << "No user records are available." << endl;
  }
}

void viewOwnerPetMenu()
{
  int choice;

  while (true)
  {
    cout << "\n========== View Owners & Pets ==========" << endl;
    cout << "1. View All Owners" << endl;
    cout << "2. View All Pets" << endl;
    cout << "3. View Owners & Their Pets" << endl;
    cout << "4. Back" << endl;

    cout << "\nEnter Your Choice: ";
    choice = getMenuChoice();

    switch (choice)
    {
    case 1:
      viewOwnerList();
      break;

    case 2:
      viewPetList();
      break;

    case 3:
      viewPetsByOwner();
      break;

    case 4:
      return;

    default:
      cout << "Invalid Choice!" << endl;
    }
  }
}

//                         Menus
// ========================================================

void reportsMenu()
{
  int choice;
  while (true)
  {
    cout << "\n========== Reports ==========" << endl;
    cout << "\n1. View All Owners" << endl;
    cout << "2. View All Pets" << endl;
    cout << "3. View Owners & Their Pets" << endl;
    cout << "4. View All Appointments" << endl;
    cout << "5. View Pending/Completed Appointments" << endl;
    cout << "6. Back" << endl;

    cout << "\nEnter Your Choice: ";
    choice = getMenuChoice();

    switch (choice)
    {
    case 1:
      viewOwnerList();
      break;

    case 2:
      viewPetList();
      break;

    case 3:
      viewPetsByOwner();
      break;

    case 4:
      viewAppointmentList();
      break;

    case 5:
      viewAppointmentsByStatus();
      break;

    case 6:
      return;

    default:
      cout << "Invalid Choice!" << endl;
      break;
    }
  }
}

void userManagementMenu()
{
  int choice;

  while (true)
  {
    cout << "\n========== User Account Management ==========" << endl;
    cout << "1. Add User" << endl;
    cout << "2. View Users" << endl;
    cout << "3. Back" << endl;

    cout << "\nEnter Your Choice: ";
    choice = getMenuChoice();

    switch (choice)
    {
    case 1:
      addUserAccount();
      break;

    case 2:
      viewUserList();
      break;

    case 3:
      return;

    default:
      cout << "Invalid Choice!" << endl;
      break;
    }
  }
}

void ownerManagementMenu()
{
  int choice;

  while (true)
  {
    cout << "\n========== Pet Owner Management ==========" << endl;
    cout << "1. Add Pet Owner" << endl;
    cout << "2. Update Pet Owner" << endl;
    cout << "3. Back" << endl;

    cout << "\nEnter Your Choice: ";
    choice = getMenuChoice();

    switch (choice)
    {
    case 1:
      addPetOwner();
      break;

    case 2:
      updatePetOwner();
      break;

    case 3:
      return;
    }
  }
}

void administratorMenu()
{
  int option;

  do
  {
    cout << "\n===== Welcome to Administrator Section =====" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "\n1. Pet Owner Management" << endl;
    cout << "2. Add Pet Records" << endl;
    cout << "3. Add Appointments" << endl;
    cout << "4. Update Appointments " << endl;
    cout << "5. Track Appointments" << endl;
    cout << "6. Reports" << endl;
    cout << "7. User Accounts" << endl;
    cout << "8. Logout" << endl;

    cout << "\nEnter Your Choice: ";
    option = getMenuChoice();

    switch (option)
    {
    case 1:
      ownerManagementMenu();
      break;

    case 2:
      addPetRecord();
      break;

    case 3:
      addAppointment();
      break;

    case 4:
      updateAppointment();
      break;

    case 5:
      trackAppointment();
      break;

    case 6:
      reportsMenu();
      break;

    case 7:
      userManagementMenu();
      break;

    case 8:
      cout << "Logging Out..." << endl;
      return;

    default:
      cout << "Invalid Option!!!" << endl;
      break;
    }
  } while (option != 8);
}

void receptionistMenu()
{
  int choice;

  do
  {
    cout << "\n========== Welcome to Receptionist Section ==========" << endl;

    cout << "\n1. Pet Owner Management" << endl;
    cout << "2. Add Pet Records" << endl;
    cout << "3. Add Appointments" << endl;
    cout << "4. Track Appointments" << endl;
    cout << "5. View Owner & Pet Lists" << endl;
    cout << "6. Logout" << endl;

    cout << "\nEnter Your Choice: ";
    choice = getMenuChoice();

    switch (choice)
    {
    case 1:
      ownerManagementMenu();
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
      viewOwnerPetMenu();
      break;

    case 6:
      cout << "Logging Out..." << endl;
      return;

    default:
      cout << "Invalid Option!!!" << endl;
      break;
    }
  } while (choice != 6);
}

void vetStaffMenu()
{
  int option;

  do
  {
    cout << "\n======= Welcome to Vet Staff Member Section =======" << endl;
    cout << "1. Update appointments details" << endl;
    cout << "2. Track appointments" << endl;
    cout << "3. Logout" << endl;

    cout << "\nEnter your choice: ";
    option = getMenuChoice();

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
      return;

    default:
      cout << "Invalid option!" << endl;
      break;
    }
  } while (option != 3);
}

//                       Main Program
// ========================================================

void startLogin()
{
  User loggedInUser;

  if (login(loggedInUser))
  {
    if (loggedInUser.role == "Administrator")
    {
      administratorMenu();
    }

    else if (loggedInUser.role == "Receptionist")
    {
      receptionistMenu();
    }

    else if (loggedInUser.role == "Vet Staff Member")
    {
      vetStaffMenu();
    }

    else
    {
      cout << "\nAccess Denied: Unrecognized User Role!" << endl;
    }
  }

  else
  {
    cout << "\nLogin Failed. Please try again." << endl;
  }
}

int main()
{
  initializeUserFile();

  int choice;

  do
  {
    cout << "\n========================================" << endl;
    cout << "       PET CARE MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "\n1. Login" << endl;
    cout << "2. Exit" << endl;

    cout << "\nEnter Your Choice: ";
    choice = getMenuChoice();

    switch (choice)
    {
    case 1:
      startLogin();
      break;

    case 2:
      cout << "\nExiting System..." << endl;
      break;

    default:
      cout << "\nInvalid Choice!!! Please select 1 or 2." << endl;
      break;
    }
  } while (choice != 2);

  cout << "\nThank You for using the Pet Care Management System!" << endl;
  cout << "" << endl;

  return 0;
}