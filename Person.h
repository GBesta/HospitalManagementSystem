#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<stdio.h> 
#include <string>
#include <vector>

using namespace std;
/*
	this is the base class person, and both patient and docotor have these values, 
	because in general
*/
class Person
{	
protected:	
	string firstName; 
	string lastName;
	string gender; 
	int age;
	long int contact; 
public:
	int id; 
	Person(int id, string firstName,string lastName, string gender, int age, long int contact)
		: id(id), firstName(firstName), lastName(lastName), gender(gender), age(age), contact(contact){}

	virtual string personInfo() const = 0;

};