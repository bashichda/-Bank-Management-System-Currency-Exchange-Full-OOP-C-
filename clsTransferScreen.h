#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:

	static void _PrinClientCard(const clsBankClient& Client) {

		cout << "\nClient Info: ";
		cout << "\n-----------------------------------";
		cout << "\nFullName   : " << Client.FullName();
		cout << "\nAcc.Number : " << Client.AccountNumber();
		cout << "\nBalance    : " << Client.AccountBalance;
		cout << "\n-----------------------------------\n";
	}

	static string _ReadAccountNumber(string Message) {

		string AccountNumber = "";

		cout << "\n" << Message;
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount Number is not found, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static double _ReadAmount(const clsBankClient& SourceClient) {

		double Amount = 0;

		cout << "\nEnter Transfer Amount : ";

		Amount = clsInputValidate::ReadDblNumber();

		while (Amount > SourceClient.AccountBalance) {

			cout << "\nAmount Exceeds the available Balance, Enter another Amount? : ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}

public:

	static void ShowTransferScreen() {

		_DrawScreenHeader("\t    Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("Please Enter Accoun Number to Transfer From : "));

		_PrinClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("Please Enter Accoun Number to Transfer To : "));

		_PrinClientCard(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Answer = 'n';
		cout << "\nAre you sure you want to perform this operation? Y/N : ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName);
			cout << "\nTransfer done successfully.\n";
			
		}
		else
		{
			cout << "\nOperation was canceld!\n";
		}

		_PrinClientCard(SourceClient);
		_PrinClientCard(DestinationClient);

	}
};

