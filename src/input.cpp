#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>

#include "../include/input.h"

using namespace std;

//                    Input Validation
// ========================================================

void clearInput()
{
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string convertToUpper(string text)
{
  transform(
      text.begin(),
      text.end(),
      text.begin(),
      [](unsigned char character)
      {
        return static_cast<char>(toupper(character));
      });

  return text;
}

string getNonEmptyInput(const string &prompt)
{
  string input;

  while (true)
  {
    cout << prompt;
    getline(cin, input);

    if (!input.empty())
    {
      return input;
    }

    cout << "Input cannot be empty. Please try again.\n";
  }
}

int getValidAge(const string &prompt)
{
  int age;

  while (true)
  {
    cout << prompt;

    if (cin >> age && age >= 0 && age <= 100)
    {
      clearInput();
      return age;
    }

    cout << "Invalid age. Please enter a number between 0 and 100." << endl;
    cin.clear();
    clearInput();
  }
}

int getMenuChoice()
{
  int choice;

  while (true)
  {
    if (cin >> choice)
    {
      clearInput();
      return choice;
    }

    cout << "Invalid input. Please enter a number.\n";

    cin.clear();
    clearInput();
  }
}

bool isValidMobileNumber(const string &mobileNumber)
{
  if (mobileNumber.length() != 10)
  {
    return false;
  }

  if (mobileNumber[0] != '0')
  {
    return false;
  }

  for (char character : mobileNumber)
  {
    if (!isdigit(static_cast<unsigned char>(character)))
    {
      return false;
    }
  }

  return true;
}

string getValidMobileNumber()
{
  string mobileNumber;

  while (true)
  {
    cout << "Enter Your Mobile Number: ";
    getline(cin, mobileNumber);

    if (isValidMobileNumber(mobileNumber))
    {
      return mobileNumber;
    }

    cout << "Invalid mobile number. "
         << "Please enter a valid 10-digit mobile number.\n";
  }
}