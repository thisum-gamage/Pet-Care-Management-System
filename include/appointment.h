#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "models.h"

void addAppointment();
void updateAppointment();

void displayAppointment(const Appointment &appointment);
bool displayPetAppointments(const string &petID);

void searchByAppointmentIDOrPetID(string searchID);

void viewAppointmentList();
void viewAppointmentsByStatus();

#endif