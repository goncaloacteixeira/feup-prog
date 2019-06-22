#pragma once

#include "ManageClients.h"
#include "ManagePacks.h"
#include "ProcessData.h"
#include "Agency.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Menu
{
private:
	bool CTRLClientsMenu;
	bool CTRLPacksMenu;
	
	
public:
	Menu(Agency agency);
	void ClientsMenu(Agency agency, ManageClients &clients, ManagePacks &packs);
	void PacksMenu(Agency agency, ManageClients& clients, ManagePacks& packs);
	void BuyAPack(ManageClients& clients, ManagePacks& packs);
	void IncomeMenu(ManagePacks& packs);


};

