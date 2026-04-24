#pragma once

#include <iostream>
#include <vector>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

using namespace std;

class clsClientListScreen : protected clsScreen
{

private:

	static void _PrintClientRecordLine(const clsBankClient& Client) {

		cout << setw(8) << left << "" << "| " << left << setw(15) << Client.AccountNumber();
		cout << "| " << left << setw(20) << Client.FullName();
		cout << "| " << left << setw(12) << Client.Phone;
		cout << "| " << left << setw(30) << Client.Email;
		cout << "| " << left << setw(10) << Client.PinCode;
		cout << "| " << left << setw(12) << Client.AccountBalance;


	}

public:

	static void ShowClientListScreen() {


		if (!CheckAccessRights(clsUser::enUserPermissions::pShowClientList))
		{
			return;
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t    Client List Screen";
		string Subtitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, Subtitle);

		cout << setw(8)<<left<<""<< "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(30) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		
		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (vClients.empty())
		{
			cout << "\n\t\tNo Client Available In System";
		}
		else
		{
			for (const clsBankClient& C : vClients) {

				_PrintClientRecordLine(C);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

	}

};

