#pragma once

#include "Agency.h"
#include "ManageClients.h"
#include "ManagePacks.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class ProcessData
{
private:
	bool clientsChanged;
	bool packsChanged;
	string ClientsFileName;
	string PacksFileName;

public:
	ProcessData(Agency agency, ManageClients clients, ManagePacks packs);
	void WriteToFiles(ManageClients clients, ManagePacks packs);
};

