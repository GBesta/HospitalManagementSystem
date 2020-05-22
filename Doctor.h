#pragma once
#include "Person.h"
#include "Patient.h"

class Doctor : public Person
{
protected:
	string specialisation;	
public:
	vector<Patient*> patients;
	Doctor(int id, string firstName, string lastName, string gender, int age, long int contact, 
		 string specialisation);
	void addPatient(Patient * pat);
	string personInfo() const;
	void patientVisits();// returns patients list who visited the doctor	
	void docHoliday(vector<Doctor*> &docList);
	
};