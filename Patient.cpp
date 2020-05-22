#include "Patient.h"

Patient::Patient(int id, string firstName,string lastName, string gender, int age, long int contact,  string inDate,
	string bloodType)
	:Person(id, firstName, lastName, gender, age, contact ) {
	this->inDate = inDate;
	this->bloodType = bloodType;
}
string Patient::personInfo() const 
{	
	string infoLine;
	infoLine = to_string(id) + " " + firstName+ " " + lastName + " " + gender + " "+ 
		to_string(age) + " " + to_string(contact)  + " " + inDate  + " " + bloodType + "\n";
	return infoLine;
}


