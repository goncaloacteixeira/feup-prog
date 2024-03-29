#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Pack.h"
#include "Address.h"

using namespace std;

class Client
{
private:
	string name;				// name of the client
	unsigned VATnumber;			// VAT number of client
	unsigned short familySize;  // number of family members
	Address address;			// client's address
	vector<int> packs;			// vector to store client's packs bought
	unsigned  totalPurchased;	// total value spent by the client

public:
	Client();
	Client(string name, unsigned VATnumber, unsigned short familySize, Address address);												// for a new client
	Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<int> packs, unsigned totalPurchased);  // client read from file

	// GET methods

	string getName() const;
	unsigned getVATnumber() const;
	unsigned short getFamilySize() const;
	Address getAddress() const;
	vector<int> getPackList() const;
	unsigned getTotalPurchased() const;

	// SET methods

	void setName(string name);
	void setVATnumber(unsigned VATnumber);
	void setFamilySize(unsigned short familySize);
	void setAddress(Address address);
	void setPackList(vector<int> packs);
	void setTotalPurchased(unsigned totalPurchased);
};

