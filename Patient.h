#pragma once
#include "Person.h"

class Patient : public Person
{
protected:
	string inDate;
	string bloodType;
public:
	Patient(int id, string firstName, string lastName, string gender, int age, long int contact, string inDate,
		string bloodType);
	string personInfo() const;	

};
