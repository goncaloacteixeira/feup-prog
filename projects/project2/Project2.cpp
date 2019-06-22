#include <iostream>
#include <tchar.h>
#include <Windows.h>

#include "Address.h"
#include "Date.h"
#include "Pack.h"
#include "Agency.h"
#include "Client.h"
#include "ManageClients.h"
#include "ManagePacks.h"
#include "ProcessData.h"
#include "Menu.h"


using namespace std;

void mainMenu(Agency agency, ManageClients &clients, ManagePacks &packs)
{
	string choice;

	Menu menu = Menu::Menu(agency);

	system("CLS");
	cout << endl;

	cout << "\t\t------ " << agency.getName() << " ------" << endl << endl;

	cout << "\tURL: " << agency.getURL() << endl;
	cout << "\tAddress: " << agency.getAddress().getStreet() << ", " << agency.getAddress().getNumber() << ", " << agency.getAddress().getFloor() << ", " << agency.getAddress().getZipCode() << " " << agency.getAddress().getLocation() << endl << endl;

	cout << "\t[1] Manage Clients\n";
	cout << "\t[2] Manage Packs\n";
	cout << "\t[3] Buy a pack for a client\n";
	cout << "\t[4] View income from packs\n\n";	

	cout << "\t[0] exit\n\n";

	getline(cin, choice, '\n');

	if (choice == "1")
	{
		menu.ClientsMenu(agency, clients, packs);
		mainMenu(agency, clients, packs);
	}
	if (choice == "2")
	{
		menu.PacksMenu(agency, clients, packs);
		mainMenu(agency, clients, packs);
	}
	if (choice == "3")
	{
		menu.BuyAPack(clients, packs);
		mainMenu(agency, clients, packs);
	}
	
	if (choice == "4")
	{
		menu.IncomeMenu(packs);
		mainMenu(agency, clients, packs);
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

int main()
{
	_tsetlocale(LC_ALL, _T("portuguese"));													//			  UTF-8

	HWND console = GetConsoleWindow();														//		Alterar as dimensoes
	RECT ConsoleRect;																		//				da		
	GetWindowRect(console, &ConsoleRect);													//			consola do
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1400, 800, TRUE);				//			  Windows

	string agencyFileName;

	system("CLS");
	cout << endl;

	cout << "\t ___________________________________________________________\n";
	cout << "\t|                                                           |\n";
	cout << "\t|                     AGENCY MANAGEMENT                     |\n";
	cout << "\t|                         SOFTWARE                          |\n";
	cout << "\t|___________________________________________________________|\n\n";

	cout << "\t\tAgency's file name: ";
	getline(cin, agencyFileName, '\n');

	// Testar a validade dos ficheiros
	Agency agency = Agency::Agency(agencyFileName);
	ManageClients clients = ManageClients::ManageClients(agency);
	ManagePacks packs = ManagePacks::ManagePacks(agency);

	mainMenu(agency, clients, packs);

	return 0;
}
