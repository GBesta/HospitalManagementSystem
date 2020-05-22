#include "Doctor.h"



Doctor ::Doctor(int id, string firstName, string lastName, string gender, int age, long int contact,  string specialisation)
	:Person(id, firstName,lastName, gender, age, contact) 
{
	this->specialisation = specialisation;

}

void Doctor::addPatient(Patient * pat)
{	
	patients.push_back(pat);
}

string Doctor::personInfo() const
{
	string infoLine;
	infoLine = to_string(id) + " " + firstName+ " "+ lastName + " " + gender + " " + to_string(age) + " " +
		to_string(contact) + " " + specialisation;
	return infoLine;
}

void Doctor::patientVisits() {// returns patients list who visited the doctor
	for (unsigned int i = 0; i < patients.size(); i++) {
		cout << patients[i]->personInfo()<<endl;
		
	}
	
}

void Doctor::docHoliday(vector<Doctor*>& docList) {//fire doctor means to delete all his data
	for (unsigned int i = 0; i < docList.size(); i++) {
		if ( docList[i]->id == id) {
			Doctor* doc = docList[i];
			docList.erase(docList.begin() + i);
			i--;
			delete doc;
		}
	}

}

