#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<stdio.h> 
#include "Doctor.h"
#include "Patient.h"
#include <vector>
#include <sstream>
#include <stdlib.h>



using namespace std;
vector<Patient*> patientList;
vector<Doctor*> doctorList;

/*
	The splitWords function gets the string, 
	cuts into words and saves each word in string vector.
*/
void splitWords(string str,vector<string> &val)
{	
	int i = 0;
	string word = "";
	for (auto x : str)
	{
		if (x == ' ')
		{	
			val.push_back(word);
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	val.push_back(word);
}

/*
	checkPatId function gets the integer(which is patient's ID number),
	searchs this Id value in patientLis above, and returns poiner on that object if finds,
	if can't fin the object for following Id number returns NULL
*/
Patient* checkPatId(int a) {
	for (unsigned int i = 0; i < patientList.size(); ++i) {
		if (a == patientList[i]->id) {
			return patientList[i];
		}
	}
	return NULL;
}
/*
	checkDocId does the same as checkPatId, but for doctors. 
*/
Doctor* checkDocId(int a) {
	for (unsigned int i = 0; i < doctorList.size(); ++i) {
		if (a == doctorList[i]->id) {
			return doctorList[i];
		}
	}
	return NULL;
}
/*
	load function is to load all information back to patientList, doctorList 
	and to add patients to doctors.  
*/
void load(string filename){
	try {
		string line;
		ifstream file(filename.c_str());
		file.exceptions(ifstream::badbit);
		while (getline(file, line)) {
			if (line == "")
				break;
			vector<string> values;
			splitWords(line, values);
			if (filename == "patients.txt") {

				Patient* loadPat = new Patient(stoi(values[0]), values[1], values[2], values[3],
					stoi(values[4]), stoi(values[5]), values[6], values[7]);
				patientList.push_back(loadPat);				
			}
			else if (filename == "doctors.txt") {

				Doctor* loadDoc = new Doctor(stoi(values[0]), values[1], values[2],
					values[3], stoi(values[4]), stoi(values[5]), values[6]);
				doctorList.push_back(loadDoc);
			}
			else if (filename == "patientsVisits.txt") {	
					Doctor* doc = checkDocId(stoi(values[0]));
					Patient* pat = checkPatId(stoi(values[2]));					
					doc->addPatient(pat);				
			}

		}
	}
	catch (std::exception const &e) {
		cout << "Program can't open file with name:" + filename<<endl;
		system("pause");
		exit(1);
	}	

}


void menu() //general menu for user
{
	cout << "1. Login to patient page"<<endl;
	cout << "2. Register new patient" << endl;
	cout << "3. Get patient's hospital record" << endl;
	cout << "4. Login to doctors page" << endl;
	cout << "5. Hire new doctor" << endl;
	cout << "6. Check doctor's information with the ID" << endl;
	cout << "7. Show information of all doctors" << endl;
	cout << "8: close the program " << endl;
	cout << "Choose service number: ";
}

/*
	ifNumber function is to check if the entered value is numeric,
	if it's not it continues to ask user to enter numeric value until user ernters numeric.
*/
int ifNumber() 
{
	int num;
	while (!(cin >>num))
	{
		cout << "Please enter the number: ";		
		cin.clear();	
		cin.ignore(100, '\n');
	}
	return num;
}

string persGender() {
	string gen;
	while (cin >>gen)
	{	
		if (gen != "m" && gen != "f") {
			cout << "Please enter m - for Male, f - for female: ";
			cin.clear();
			cin.ignore(100, '\n');
		}
		else
		{
			break;
		}
	}
	return gen;
}

/*
	registerPatient is a function to register new patient to hospital, 
	this means that it asks user to enter all the information to create Patient class object,
	then function adds this object to patientList, and to the patients.txt
*/
void registerPatient() {
	int id; string firstName; string lastName; 
	string gender; int age; long int contact;
	string inDate;
	string bloodType;
	cout << "Enter the ID number: ";
	id = ifNumber();
	cout << "Enter the first name: ";
	cin >> firstName;
	cout << "Enter the last name: ";
	cin >> lastName;
	cout << "Enter the gender: ";
	gender = persGender();
	cout << "Enter the age: ";
	age = ifNumber();
	cout << "Enter the mobile number: +36 ";
	contact = ifNumber();
	cout << "Enter the inDate: ";
	cin >> inDate;
	cout << "Enter the blood type: ";
	cin >> bloodType;
	Patient* patient;
	patient = new Patient(id, firstName, lastName, 
		gender, age, contact, inDate, bloodType);
	patientList.push_back(patient);
	ofstream pfile;
	pfile.open("patients.txt", ios::app);
	pfile << patient->personInfo();
	cout << "Patient registered successfullly!"<<endl<<"\n\n";
	pfile.close();
	delete patient;
}

/*
	registerDoctor is a function to register new doctot to hospital,
	this means that it asks user to enter all the information to create Doctor class object,
	then function adds this object to doctorList, and to the doctors.txt
*/
void registerDoctor() {
	int id; string firstName; string lastName; 
	string gender; int age; long int contact;
	string specialisation;
	cout << "Enter the Id: ";
	id = ifNumber();
	cout << "Enter doctor's first name: ";
	cin >> firstName;
	cout << "Enter the last name: ";
	cin >> lastName;
	cout << "Enter the gender: ";
	gender = persGender();
	cout << "Enter the age: ";
	age = ifNumber();
	cout << "Enter the mobile number: +36 ";
	contact = ifNumber();
	cout << "Enter the blood type: ";
	cin >> specialisation;
	Doctor* doctor;
	doctor = new Doctor(id, firstName, lastName,
		gender, age, contact, specialisation);
	doctorList.push_back(doctor);
	ofstream dfile;
	
	dfile.open("doctors.txt", ios::app);
	dfile << doctor->personInfo()<<endl;//adding to the file
	cout << "Doctor registered successfully!"<<endl<<"\n\n";
	dfile.close();	
	delete doctor;
}

void start() {
	int id; 
	int i = 0;
	while (i != 8)
	{
		system("CLS");
		menu();
		cin >> i;
		if (i == 1) //login to patient so choose 1.
		{
			system("cls");
			cout << "Type your ID number: ";
			cin >> id;
			Patient* pat = checkPatId(id);//check if there is such patient  in vector patientList 
			if (pat != NULL)//if there is such patient registerred then continues
			{
				while (i != 0)
				{
					system("CLS");
					cout << "1. Visit the doctor" << endl;
					cout << "0. back to menu" << endl;
					cout << "Choose service number: ";
					cin >> i;
					if (i == 1)//visit the doctor
					{
						cout << "Enter the ID of doctor u want to visit: ";
						cin >> id;
						Doctor* doc = checkDocId(id);//checks if in doctorList is such doctor available,
						if (doc != NULL) //if exists continues in following
						{
							cout << "you successfully consulted with doctor!" << endl;
							doc->addPatient(pat);//adds consulted patient to doctors patients
							ofstream vfile;
							vfile.exceptions( ofstream::badbit);
							try {
								vfile.open("patientsVisits.txt", ios::app);
								vfile << doc->id << " : " << pat->id << endl;
								vfile.close();
							}
							catch (std::exception const& exx) {
								cout << "error opening file!" << endl;
							}
							system("pause");
						}
						else //if the doctor isn't available, shows following message below
						{
							cout << "Doctor is on a holiday, please check other doctor" << endl;
							system("pause");
						}
					}					
					else //if the user enters the value for which there is no service, ask user to enter the valid value
					{
						cout << "Enter valid service  number: ";
					}
				}
			}
			else//if inpatientList doesn't exist Patient with this id, tells user the following message below
				cout << "register the patient first "<<endl;
				system("CLS");
				start();
		}
		else if (i == 2) {//register new patient
			system("CLS");
			registerPatient();
			system("pause");			
		}
		else if (i == 3) {//get patients hospital record
			system("cls");
			cout << "Enter Patients ID: ";
			id = ifNumber();
			if (checkPatId(id) != NULL) {
				cout << "Patients information: ";
				cout << checkPatId(id)->personInfo();//search the object with id and 
			}                                        //return information as a string and show it on console
			else
			{
				cout << "No patient with this ID number is registerred in hospital" << endl;
			}			
			system("pause");

		}
		else if (i == 4) {//enter docotrs page
			system("CLS");
			cout << "Type your ID number: ";
			cin >> id;			
			if (checkDocId(id) != NULL) {	//checks if in doctorList is such doctor available,				
				while (i != 0) {
					system("CLS");
					cout << "1. Show cured patients list "<<endl;
					cout << "2. Doctor goes on pansion "<<endl;
					cout << "0. Back to menu "<< endl;
					cout << "Enter number of your choice: ";
					cin >> i;
					if (i == 1) {
						checkDocId(id)->patientVisits();
						system("pause");
					}
					else if (i == 2) {
						checkDocId(id)->docHoliday(doctorList);
					}
					else 
					{
						cout << "Enter valid service number: " << endl;
						system("pause");
					}
				}
			}
			else
			{
				cout << "No such doctor found!"<<endl;
				system("pause");
			}
		}
		else if (i == 5) {//register new doctor
			system("CLS");
			registerDoctor();			
			system("pause");
		}
		else if (i == 6) {//get doctors info
			system("CLS");
			cout << "Enter doctor ID number: ";
			cin >> id;
			Doctor* doc = checkDocId(id);//checks if in doctorList is such doctor available, if yes returns pointer to that doctor
			if (doc != NULL) {
				cout << doc->personInfo()<<endl;
				if (checkDocId(id)->patients.size() != NULL) {//displays the patients who visited the doctor 
					cout << "list of patients who visited this doctor: " << endl;
					checkDocId(id)->patientVisits();
				}
				else
				{
					cout << "No patients visited this doctor yet " << endl;
				}
				system("pause");
			}
			else {
				cout << "No such Doctor found" << endl;
				system("pause");
			}		
		}
		else if (i == 7) {// show all doctors information
			system("CLS");
			for (unsigned int i = 0; i < doctorList.size(); i++) {
				cout << doctorList[i]->personInfo() << endl;
			}
			system("pause");
		}
		else
		{
		cout << "Enter valid service number! ";
		system("pause");
		}
	}
}
void freeData(vector<Patient*> patList) {
	for (unsigned int i = 0; i <patList.size(); i++)
	{
		delete patList[i];
	}
}
void freeData(vector < Doctor*> docList) {
	for (unsigned int i = 0; i < docList.size(); i++)
	{
		delete docList[i];
	}

}
int main()
{
	load("patients.txt");
	load("doctors.txt");
	load("patientsVisits.txt");	
	start();
	freeData(patientList);
	freeData(doctorList);
}


