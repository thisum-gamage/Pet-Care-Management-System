#include <iostream>
#include <fstream>

#include "../include/auth.h"
#include "../include/config.h"
#include "../include/parser.h"

using namespace std;

//                      Initializing
// ========================================================

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

    if (enteredUsername.empty())
    {
      cout << "Username cannot be empty." << endl;
      return false;
    }

    cout << "Password: ";
    cin >> enteredPassword;

    if (enteredPassword.empty())
    {
      cout << "Password cannot be empty." << endl;
      return false;
    }

    ifstream file(USERS_FILE);

    if (!file)
    {
      cout << "\nUnable to open the user file." << endl;
      return false;
    }

    string line;

    while (getline(file, line))
    {
      User user = parseUser(line);

      if (enteredUsername == user.username &&
          enteredPassword == user.password)
      {
        loggedInUser = user;

        cout << "\nLogin Successful..." << endl;
        cout << "\nWelcome, " << loggedInUser.username << "!" << endl;
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

  outputFile << "1,admin,123,Administrator" << endl;
  outputFile << "2,receptionist,456,Receptionist" << endl;
  outputFile << "3,vetstaffmember,789,Vet Staff Member" << endl;

  outputFile.close();

  cout << "Default user accounts were created." << endl;
}
