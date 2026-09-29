#include <iostream>
#include <fstream>

#include "../include/user.h"
#include "../include/config.h"
#include "../include/parser.h"
#include "../include/input.h"
#include "../include/id_generator.h"
#include "../include/models.h"

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
