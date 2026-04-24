#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include <iomanip>


using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void _PrintClientRecordLine(const clsBankClient& Client) {

		cout << setw(25) << left << "" << "| " << left << setw(15) << Client.AccountNumber();
		cout << "| " << left << setw(40) << Client.FullName();
		cout << "| " << left << setw(12) << Client.AccountBalance;
	}

public:

	static void ShowTotalBalances() {

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t    Balances List Screen";
		string Subtitle = "\t       (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, Subtitle);

		cout << setw(25) << left << "" << "\n\t\t_________________________________________________________________";
		cout << "_________________________\n" << endl;

		cout << setw(25) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";

		cout << setw(25) << left << "" << "\n\t\t_________________________________________________________________";
		cout << "_________________________\n" << endl;

		double TotalBalances = clsBankClient::GetTotalBalances();

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


		cout << setw(25) << left << "" << "\n\t\t_________________________________________________________________";
		cout << "_________________________\n" << endl;

		cout << setw(8) << left << "" << "\t\t\t\t\t    Total Balances = " << TotalBalances << endl;
		cout << setw(8) << left << "" << "\t\t\t\t    (" + clsUtil::NumberToText(TotalBalances) + ")" << endl;

	}


};


