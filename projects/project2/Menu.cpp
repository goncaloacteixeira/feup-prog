#include "Menu.h"
#include <fstream>

bool checkStartDate1(string sdate)
{
	Date date = Date::Date(sdate);

	if (date.getMonth() > 12 || date.getMonth() < 1)
	{
		return false;
	}
	if (date.getDay() > 31 || date.getDay() < 1)
	{
		return false;
	}
	return true;
}

bool checkEndDate1(string sdate, string edate)
{
	if (!checkStartDate1(edate)) return false;

	Date startDate = Date::Date(sdate);
	Date endDate = Date::Date(edate);

	vector<unsigned int> sDateVec = { startDate.getYear() , startDate.getMonth() , startDate.getDay() };
	vector<unsigned int> eDateVec = { endDate.getYear() , endDate.getMonth() , endDate.getDay() };

	if (sDateVec[0] > eDateVec[0]) return false;
	if (sDateVec[0] == eDateVec[0])
	{
		if (sDateVec[1] > eDateVec[1]) return false;
		if (sDateVec[1] == eDateVec[1])
		{
			if (sDateVec[2] > eDateVec[2]) return false;
		}
	}
	return true;
}

void printPacks1(vector<Pack> packsVec)
{
	cout << endl;

	printf("%-27s%-50s%-17s%-17s%-10s%-13s%-10s\n", "   ID", "Destination", "Start Date", "End Date", "Price", "Max Tickets", "Sold Tickets");
	cout << "   -----------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < packsVec.size(); i++)
	{
		string destination;
		string startDate, endDate;

		destination = packsVec[i].getSites().getFullLocation();

		startDate = packsVec[i].getBeginDate().getFullDate();
		endDate = packsVec[i].getEndDate().getFullDate();

		cout << "   ";

		int alpha = packsVec[i].getMaxTickets() - packsVec[i].getSoldTickets();
		if (alpha > 0) printf("%-12s%-62s%-16s%-17s%-13.02f%-13s%-10s\n", to_string(packsVec[i].getId()).c_str(), destination.c_str(), startDate.c_str(), endDate.c_str(), packsVec[i].getPricePerPerson(), to_string(packsVec[i].getMaxTickets()).c_str(), to_string(packsVec[i].getSoldTickets()).c_str());
		else printf("%-12s%-62s%-16s%-17s%-13.02f%-13s%-10s\n", ("-" + to_string(packsVec[i].getId())).c_str(), destination.c_str(), startDate.c_str(), endDate.c_str(), packsVec[i].getPricePerPerson(), to_string(packsVec[i].getMaxTickets()).c_str(), to_string(packsVec[i].getSoldTickets()).c_str());
	}

	cout << "\n* The (-) on the ID indicates that the pack is not available anymore.\n\n";
}

Menu::Menu(Agency agency)
{
	fstream clients;
	clients.open(agency.getClients());
	
	if (clients.is_open())
	{
		CTRLClientsMenu = true;
	}
	else CTRLClientsMenu = false;

	clients.close();

	fstream packs;
	packs.open(agency.getPacks());

	if (packs.is_open())
	{
		CTRLPacksMenu = true;
	}
	else CTRLPacksMenu = false;

	packs.close();
}

void Menu::ClientsMenu(Agency agency, ManageClients& clients, ManagePacks& packs)
{
	system("CLS");
	cout << endl;

	cout << "\t\t---- MANAGE CLIENTS MENU ----\n\n";

	string choice;

	cout << "\t[1] Show Clients Info\n";
	cout << "\t[2] Add a client\n";
	cout << "\n\t[3] back";
	cout << "\n\t[0] exit\n\t";


	getline(cin, choice, '\n');

	if (choice == "1")
	{
		system("CLS");
		
		clients.ShowAllClients();

		cout << "\n  [1] Show a client \n\n";
		cout << "  [2] Back\n";
		cout << "  [0] Exit\n";

		string choiceA;
		getline(cin, choiceA, '\n');

		if (choiceA == "1") 
		{
			cout << "\t\t\tShow a Client" << endl;

			string nif;

			cout << "\t\tVAT:";
			getline(cin, nif, '\n');

			clients.ShowAClient(stoi(nif));

			cout << endl << endl;

			cout << "  [1] Change INFO         [2] Remove Client			[3] View Bought Packs" << endl;
			cout << "                                                                    [0] back" << endl;

			string choice2;
			getline(cin, choice2, '\n');

			if (choice2 == "1")
			{
				clients.ChangeClient(stoi(nif));
				Menu::ClientsMenu(agency, clients, packs);
			}
			if (choice2 == "2")
			{
				clients.RemoveClient(stoi(nif));
				Menu::ClientsMenu(agency, clients, packs);
			}
			if (choice2 == "3")
			{
				Client target;
				vector<Pack> toPrint;

				cout << endl;

				for (int i = 0; i < clients.getClients().size(); i++)
				{
					if (clients.getClients()[i].getVATnumber() == stoi(nif))
					{
						target = clients.getClients()[i];
						break;
					}
				}

				for (int i = 0; i < target.getPackList().size(); i++)
				{
					for (int j = 0; j < packs.getPacks().size(); j++)
					{
						if (target.getPackList()[i] == packs.getPacks()[j].getId() || "-" + to_string(target.getPackList()[i]) == to_string(packs.getPacks()[j].getId())) toPrint.push_back(packs.getPacks()[j]);
					}
				}
				printPacks1(toPrint);
				system("pause");
				Menu::ClientsMenu(agency, clients, packs);
			}

			if (choice2 == "0")
			{
				Menu::ClientsMenu(agency, clients, packs);
			}
		}
		
		if (choiceA == "2")
		{
			Menu::ClientsMenu(agency, clients, packs);
		}
		if (choiceA == "0")
		{
			if (clients.wasChanged() || packs.wasChanged())
			{
			label1:
				system("CLS");
				cout << "\n\n\t\t\tDo you want to save the data? (y/n): ";
				string decision;
				getline(cin, decision, '\n');

				while (decision != "y" && decision != "n")
				{
					cout << "Type 'y' for YES or 'n' for NO: ";
					getline(cin, decision, '\n');
				}

				if (decision == "y")
				{
					ProcessData data = ProcessData::ProcessData(agency, clients, packs);
					data.WriteToFiles(clients, packs);
					exit(EXIT_SUCCESS);
				}

				if (decision == "n")
				{
					system("CLS");
					cout << "\n\n\t\t\tAre you sure? (y/n): ";
					string decision1;
					getline(cin, decision1, '\n');

					while (decision1 != "y" && decision1 != "n")
					{
						cout << "Type 'y' for YES or 'n' for NO: ";
						getline(cin, decision1, '\n');
					}

					if (decision1 == "y")
					{
						exit(EXIT_SUCCESS);
					}
					if (decision1 == "n")
					{
						goto label1;
					}
				}
			}
			else
			{
				exit(EXIT_SUCCESS);
			}
		}
	}

	if (choice == "2")
	{
		clients.AddClient();
		Menu::ClientsMenu(agency, clients, packs);
	}
	if (choice == "3")
	{
		// this returns to the mainMenu !! 
	}
	if (choice == "0")
	{
		if (clients.wasChanged() || packs.wasChanged()) 
		{
		label2:
			system("CLS");
			cout << "\n\n\t\t\tDo you want to save the data? (y/n): ";
			string decision;
			getline(cin, decision, '\n');

			while (decision != "y" && decision != "n")
			{
				cout << "Type 'y' for YES or 'n' for NO: ";
				getline(cin, decision, '\n');
			}

			if (decision == "y")
			{
				ProcessData data = ProcessData::ProcessData(agency, clients, packs);
				data.WriteToFiles(clients, packs);
				exit(EXIT_SUCCESS);
			}

			if (decision == "n")
			{
				system("CLS");
				cout << "\n\n\t\t\tAre you sure? (y/n): ";
				string decision1;
				getline(cin, decision1, '\n');

				while (decision1 != "y" && decision1 != "n")
				{
					cout << "Type 'y' for YES or 'n' for NO: ";
					getline(cin, decision1, '\n');
				}

				if (decision1 == "y")
				{
					exit(EXIT_SUCCESS);
				}
				if (decision1 == "n")
				{
					goto label2;
				}
			}
		}
		else
		{
			exit(EXIT_SUCCESS);
		}
	}
}

void Menu::PacksMenu(Agency agency, ManageClients& clients, ManagePacks& packs)
{
	system("CLS");
	cout << endl;

	cout << "\t\t---- MANAGE PACKS MENU ----\n\n";

	string choice;

	cout << "\t[1] Show all* packs\n";
	cout << "\t[2] Show all* packs between dates\n";
	cout << "\t[3] Show all* packs for a destination\n";
	cout << "\t[4] Show all* packs for a destination between dates\n";
	cout << "\t[5] Add a pack\n";
	cout << "\t[6] Show the N-top packs!\n";
	cout << "\n\t[7] back";
	cout << "\n\t[0] exit\n\t";


	getline(cin, choice, '\n');

	if (choice == "1")
	{
		packs.ShowAllPacks();

		cout << endl << endl;

		cout << "  [1] Change a Pack         [2] Make a Pack unavailable" << endl;
		cout << "                                               [0] back" << endl;

		string choice2;
		getline(cin, choice2, '\n');

		if (choice2 == "1")
		{
			cout << endl << "\t\tID: ";
			string id;
			getline(cin, id, '\n');
			packs.ShowAPack(stoi(id));
			packs.ChangePack(stoi(id));
			Menu::PacksMenu(agency, clients, packs);
		}
		if (choice2 == "2")
		{
			cout << endl << "\t\tID: ";
			string id;
			getline(cin, id, '\n');
			packs.MakeUnavailable(stoi(id));
			Menu::PacksMenu(agency, clients, packs);
		}
		if (choice2 == "0")
		{
			Menu::PacksMenu(agency, clients, packs);
		}
	}
	if (choice == "2")
	{
		system("CLS");
		cout << endl;

		string a, b;

		cout << "\t\tShow Pack between Dates\n";

		bool ctrSDate = false;
		while (!ctrSDate)
		{
			cout << "\n\tStart Date (YYYY/MM/DD): ";
			getline(cin, a, '\n');
			ctrSDate = checkStartDate1(a);
			if (!ctrSDate) cout << "\n\tInsert a correct date (YYYY/MM/DD).\n";
		}

		bool ctrEDate = false;
		while (!ctrEDate)
		{
			cout << "\n\tEnd Date (YYYY/MM/DD): ";
			getline(cin, b, '\n');
			ctrEDate = checkEndDate1(a, b);
			if (!ctrEDate) cout << "\n\tInsert a valid end date (YYYY/MM/DD).\n";
		}

		Date begin = Date::Date(a);
		Date end = Date::Date(b);

		packs.ShowPacksDates(a, b);
		Menu::PacksMenu(agency, clients, packs);
	}
	if (choice == "3")
	{
		string loc;

		system("CLS");
		cout << endl;

		cout << "\t\tShow Pack for a location\n";
		cout << "\n\tLocation: ";
		getline(cin, loc, '\n');

		packs.ShowPacksPlace(loc);
		Menu::PacksMenu(agency, clients, packs);
	}
	if (choice == "4")
	{
		string loc, a, b;

		system("CLS");
		cout << endl;

		cout << "\t\tShow Pack for a location between dates\n";

		cout << "\n\tLocation: ";
		getline(cin, loc, '\n');

		bool ctrSDate = false;
		while (!ctrSDate)
		{
			cout << "\n\tStart Date (YYYY/MM/DD): ";
			getline(cin, a, '\n');
			ctrSDate = checkStartDate1(a);
			if (!ctrSDate) cout << "\n\tInsert a correct date (YYYY/MM/DD).\n";
		}

		bool ctrEDate = false;
		while (!ctrEDate)
		{
			cout << "\n\tEnd Date (YYYY/MM/DD): ";
			getline(cin, b, '\n');
			ctrEDate = checkEndDate1(a, b);
			if (!ctrEDate) cout << "\n\tInsert a valid end date (YYYY/MM/DD).\n";
		}

		Date begin = Date::Date(a);
		Date end = Date::Date(b);

		packs.ShowPacksDatesPlace(begin, end, loc);
		Menu::PacksMenu(agency, clients, packs);
	}
	if (choice == "5")
	{
		packs.AddPack();
		Menu::PacksMenu(agency, clients, packs);
	}
	if (choice == "6")
	{
		system("CLS");
		cout << "\n\n\t\t\tShow the N-Top places to travel ! " << endl;
		string n;
		cout << "           N = ";
		getline(cin, n, '\n');

		packs.ShowNMostVisited(stoi(n));
		cout << endl << "Type the ID of a Pack to see the clients who haven't traveled there! ";

		string foo;
		getline(cin, foo, '\n');

		vector<Client> clientsVec;

		for (int i = 0; i < clients.getClients().size(); i++)
		{
			for (int j = 0; j < clients.getClients()[i].getPackList().size(); j++)
			{
				if (clients.getClients()[i].getPackList()[j] == stoi(foo))
				{
					break;
				}
				if (j == clients.getClients()[i].getPackList().size() - 1 && clients.getClients()[i].getPackList()[j] != stoi(foo))
				{
					clientsVec.push_back(clients.getClients()[i]);
				}
			}
			
		}


		cout << endl;

		printf("%-33s%-8s%-30s%-35s%-19s%-80s\n", "   Name", "VAT", "Household", "Address", "Packs Bought", "Money Spent");
		cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 0; i < clientsVec.size(); i++)
		{
			string address;
			string bpacks;

			for (int j = 0; j < clientsVec[i].getPackList().size(); j++)
			{
				if (j != clientsVec[i].getPackList().size() - 1)
				{
					bpacks += to_string(clientsVec[i].getPackList()[j]) + ", ";
				}
				else
				{
					bpacks += to_string(clientsVec[i].getPackList()[j]);
				}
			}
			address = clientsVec[i].getAddress().getStreet() + ", " + to_string(clientsVec[i].getAddress().getNumber()) + ", " + clientsVec[i].getAddress().getFloor() + ", " + clientsVec[i].getAddress().getZipCode() + " " + clientsVec[i].getAddress().getLocation();

			printf("%-30s%-15s%-10s%-53s%-20s%-30s\n", ("  " + clientsVec[i].getName()).c_str(), to_string(clientsVec[i].getVATnumber()).c_str(), to_string(clientsVec[i].getFamilySize()).c_str(), address.c_str(), bpacks.c_str(), to_string(clientsVec[i].getTotalPurchased()).c_str());
		}

		cout << "\n*ID 0 (zero) means the client has no bought packs yet.\n";
		system("pause");
		Menu::PacksMenu(agency, clients, packs);
	}
	if (choice == "7")
	{
		// this returns to the mainMenu !! 
	}
	if (choice == "0")
	{
		if (clients.wasChanged() || packs.wasChanged())
		{
		label1:
			system("CLS");
			cout << "\n\n\t\t\tDo you want to save the data? (y/n): ";
			string decision;
			getline(cin, decision, '\n');

			while (decision != "y" && decision != "n")
			{
				cout << "Type 'y' for YES or 'n' for NO: ";
				getline(cin, decision, '\n');
			}

			if (decision == "y")
			{
				ProcessData data = ProcessData::ProcessData(agency, clients, packs);
				data.WriteToFiles(clients, packs);
				exit(EXIT_SUCCESS);
			}

			if (decision == "n")
			{
				system("CLS");
				cout << "\n\n\t\t\tAre you sure? (y/n): ";
				string decision1;
				getline(cin, decision1, '\n');

				while (decision1 != "y" && decision1 != "n")
				{
					cout << "Type 'y' for YES or 'n' for NO: ";
					getline(cin, decision1, '\n');
				}

				if (decision1 == "y")
				{
					exit(EXIT_SUCCESS);
				}
				if (decision1 == "n")
				{
					goto label1;
				}
			}
		}
		else
		{
			exit(EXIT_SUCCESS);
		}
	}
}

void Menu::BuyAPack(ManageClients& clients, ManagePacks& packs)
{
	string nif;
	Client target;

	system("CLS");
	cout << endl;

	cout << "\t\t\tBUY A PACK FOR A CLIENT\n\n";

	clients.ShowAllClients();

	cout << "\n\tClient's VAT number: ";
	getline(cin, nif, '\n');

	vector<int> info = clients.BuyAPack(stoi(nif), packs);
	system("pause");
	packs.BuyAPack(info);

}

void Menu::IncomeMenu(ManagePacks& packs)
{
	system("CLS");
	cout << endl;

	cout << "\t\t---- INCOME ----\n";


	int nPacksSold = 0;
	double income = 0.0;

	for (int i = 0; i < packs.getPacks().size(); i++)
	{
		nPacksSold += packs.getPacks()[i].getSoldTickets();
		income += packs.getPacks()[i].getSoldTickets() * packs.getPacks()[i].getPricePerPerson();
	}

	cout << "\n\n\t\tTotal Packs Sold: " << nPacksSold << endl;
	cout << "\n\t\tIncome: " << income << " euro" << endl << endl;

	system("pause");
}