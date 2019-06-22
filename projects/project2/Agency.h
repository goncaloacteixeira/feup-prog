#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Address.h"
#include "Client.h"
#include "Pack.h"

using namespace std;

class Agency
{
private:
	string name;						// name of the  agency
	unsigned int VATnumber;				// VAT number of the agency
	Address address;					// address of the agency
	string URL;							// URL of the agency Web site
	string clients;
	string packs;

public:
	Agency(string fileName);

	// methods GET
	string getName() const;
	unsigned getVATnumber() const;
	Address getAddress() const;
	string getURL() const;
	string getClients() const;
	string getPacks() const;


	// methods SET
	void setName(string name);
	void setVATnumber(unsigned VATnumber);
	void setAddress(Address address);
	void setURL(string url);
	void setClients(string clients);
	void setPacks(string packs);
};

