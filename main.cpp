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

struct appoinment
{
  int appo_num, appo_date, last_update_date;
  string pet_id, service_type, symptoms, treatment_notes, appo_status;
};


int main()
{

  return 0;
}