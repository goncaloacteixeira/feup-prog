#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Address
{
private:
	string street;
	unsigned short int number;
	string floor;
	string zipCode;
	string local;

public:
	Address();
	Address(string address);
	Address(string STREET, unsigned short int NUMBER, string FLOOR, string ZIPCODE, string LOCAL);

	// GET methods
	string getStreet() const;
	unsigned short int getNumber() const;
	string getFloor() const;
	string getZipCode() const;
	string getLocation() const;

	// SET methods
	void setStreet(string street);
	void setNumber(unsigned short int number);
	void setFloor(string floor);
	void setZipCode(string zipCode);
	void setLocation(string local);

};

