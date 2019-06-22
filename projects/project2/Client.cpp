#include "Client.h"

Client::Client()
{
	name = "";
	VATnumber = 0;
	familySize = 0;
	address = Address::Address();
	packs = { 0 };
	totalPurchased = 0;
}


Client::Client(string NAME, unsigned VAT, unsigned short FAMSIZE, Address ADDR) 
{
	name = NAME;
	VATnumber = VAT;
	familySize = FAMSIZE;
	address = ADDR;
	packs = { 0 };
	totalPurchased = 0;
}

Client::Client(string NAME, unsigned VAT, unsigned short FAMSIZE, Address ADDR, vector<int> PACKS, unsigned TOTAL)
{
	name = NAME;
	VATnumber = VAT;
	familySize = FAMSIZE;
	address = ADDR;
	packs = PACKS;
	totalPurchased = TOTAL;
}

// GET methods

string Client::getName() const 
{
	return name;
}

unsigned Client::getVATnumber() const 
{
	return VATnumber;
}

unsigned short Client::getFamilySize() const
{
	return familySize;
}

Address Client::getAddress() const
{
	return address;
}

vector<int> Client::getPackList() const 
{
	return packs;
}

unsigned Client::getTotalPurchased() const 
{
	return totalPurchased;
}

// SET methods

void Client::setName(string name) 
{
	this->name = name;
}

void Client::setVATnumber(unsigned VATnumber)
{
	this->VATnumber = VATnumber;
}

void Client::setFamilySize(unsigned short familySize)
{
	this->familySize = familySize;
}
void Client::setAddress(Address address) 
{
	this->address = address;
}
void Client::setPackList(vector<int> packs)
{
	this->packs = packs;
}
void Client::setTotalPurchased(unsigned totalPurchased)
{
	this->totalPurchased = totalPurchased;
}
