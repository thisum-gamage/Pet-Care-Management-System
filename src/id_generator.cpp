#include "../include/id_generator.h"

#include "../include/models.h"
#include "../include/parser.h"

#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

//                      ID generators
// ========================================================

string generateNextPrefixedID(
    const string &filename,
    const string &prefix)
{
  int highestID = 0;

  ifstream file(filename);
  string line;

  while (getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }

    stringstream ss(line);
    string id;

    getline(ss, id, ',');

    if (!id.empty() && id.length() > prefix.length())
    {
      int currentID = stoi(id.substr(prefix.length()));

      if (currentID > highestID)
      {
        highestID = currentID;
      }
    }
  }

  file.close();

  ostringstream output;
  output << prefix << setfill('0') << setw(3) << highestID + 1;

  return output.str();
}

string generateOwnerID()
{
  return generateNextPrefixedID("data/owners.txt", "OWN");
}

string generatePetID()
{
  return generateNextPrefixedID("data/pets.txt", "PET");
}

string generateAppointmentID()
{
  return generateNextPrefixedID("data/appointments.txt", "APP");
}

int generateUserID()
{
  ifstream file("data/users.txt");
  string line;

  int highestID = 0;

  while (getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }

    User user = parseUser(line);

    if (user.userID > highestID)
    {
      highestID = user.userID;
    }
  }
  file.close();

  return highestID + 1;
}
