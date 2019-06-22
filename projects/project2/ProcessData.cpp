#include "ProcessData.h"
#include <fstream>

ProcessData::ProcessData(Agency agency, ManageClients clients, ManagePacks packs)
{
	if (clients.wasChanged())
	{
		clientsChanged = true;
	}
	else
	{
		clientsChanged = false;
	}

	if (packs.wasChanged())
	{
		packsChanged = true;
	}
	else
	{
		packsChanged = false;
	}

	ClientsFileName = agency.getClients();
	PacksFileName = agency.getPacks();
}

void ProcessData::WriteToFiles(ManageClients clients, ManagePacks packs)
{
	if (clientsChanged)
	{
		vector<Client> clientsVec = clients.getClients();
		fstream clients(ClientsFileName, std::ofstream::out | std::ofstream::trunc);
		int size = clientsVec.size();
		int control = 0;

		for (int i = 0; i < size; i++)
		{
			clients << clientsVec[i].getName() << endl;
			clients << clientsVec[i].getVATnumber() << endl;
			clients << clientsVec[i].getFamilySize() << endl;

			clients << clientsVec[i].getAddress().getStreet() << " / ";
			clients << clientsVec[i].getAddress().getNumber() << " / ";
			clients << clientsVec[i].getAddress().getFloor() << " / ";
			clients << clientsVec[i].getAddress().getZipCode() << " / ";
			clients << clientsVec[i].getAddress().getLocation() << endl;

			if (clientsVec[i].getPackList().size() == 0)
			{
				clients << endl;
			}
			else
			{
				int ctr = 0;
				for (int j = 0; j < clientsVec[i].getPackList().size(); j++)
				{
					if (ctr != clientsVec[i].getPackList().size() - 1)
					{
						clients << clientsVec[i].getPackList()[j] << " ; ";
					}
					else clients << clientsVec[i].getPackList()[j] << endl;
					ctr++;
				}
			}

			clients << clientsVec[i].getTotalPurchased() << endl;

			if (control != size - 1) clients << "::::::::::\n";
			control++;
		}
		clients.close();
	}

	if (packsChanged)
	{
		vector<Pack> packsVec = packs.getPacks();
		fstream packs(PacksFileName, std::ofstream::out | std::ofstream::trunc);
		int size = packsVec.size();
		int control = 0;

		packs << packsVec[size - 1].getId() << endl;

		for (int i = 0; i < size; i++)
		{
			int avail = packsVec[i].getMaxTickets() - packsVec[i].getSoldTickets();
			if (avail <= 0) packs << "-" + to_string(packsVec[i].getId()) << endl;
			else packs << packsVec[i].getId() << endl;

			packs << packsVec[i].getSites().getFullLocation() << endl;
			packs << packsVec[i].getBeginDate().getFullDate() << endl;
			packs << packsVec[i].getEndDate().getFullDate() << endl;
			packs << packsVec[i].getPricePerPerson() << endl;
			packs << packsVec[i].getMaxTickets() << endl;
			packs << packsVec[i].getSoldTickets();

			if (control != size - 1) packs << "\n::::::::::\n";
			control++;
		}
		packs.close();
	}
}

