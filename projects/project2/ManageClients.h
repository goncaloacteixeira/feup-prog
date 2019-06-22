#pragma once

#include "Agency.h"
#include "Client.h"
#include "Pack.h"
#include "ManagePacks.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class ManageClients
{
private:
	bool changesMade;
	vector<Client> clientsVec;

public:
	ManageClients();
	ManageClients(Agency agency);

	void RemoveClient(unsigned int VATnumber);
	void ChangeClient(unsigned int VATnumber);
	void AddClient();

	vector<int> BuyAPack(unsigned int VATnumber, ManagePacks& packs);

	vector<Client> getClients();

	void ShowAllClients();
	void ShowAClient(unsigned int VATnumber);

	void WriteToFile(Agency agency);

	bool wasChanged();
	void wasChanged(bool opt);
};

