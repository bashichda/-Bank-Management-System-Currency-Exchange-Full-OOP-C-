#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
{

private:

	static void _PrintClient(const clsBankClient& Client) {

		cout << "\nClient Info: ";
		cout << "\n-----------------------------------";
		cout << "\nFirstName  : " << Client.FirstName;
		cout << "\nLastName   : " << Client.LastName;
		cout << "\nFullName   : " << Client.FullName();
		cout << "\nEmail      : " << Client.Email;
		cout << "\nPhone      : " << Client.Phone;
		cout << "\nAcc.Number : " << Client.AccountNumber();
		cout << "\nPassword   : " << Client.PinCode;
		cout << "\nBalance    : " << Client.AccountBalance;
		cout << "\n-----------------------------------\n";
	}

public:

	static void ShowWithdrawScreen() {

		_DrawScreenHeader("\t    Withdraw Screen");

		short Trial = 3;

		string AccountNumber = "";

		cout << "\nPlease enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (Trial > 0 && !clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nClient with [" << AccountNumber << "] is not exist.\n";
			AccountNumber = clsInputValidate::ReadString();
			Trial--;
		}

		if (Trial == 0)
		{
			cout << "\nToo many Failed attempts.";
			return;
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		cout << "\nPlease enter Withdraw amount: ";
		Amount = clsInputValidate::ReadDblNumber();

		cout << "\nAre you sure you want to perform this Transaction? y/n ";
		char  Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client.Withdraw(Amount)) 
			{
				cout << "\nAmount withdraw Successfully.\n";
				cout << "\nNew Balance is : " << Client.AccountBalance;
			}
			else
			{
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmount to withdraw is: " << Amount << endl;
				cout << "\nYour Balance is : " << Client.AccountBalance;
			} 
		}
	}

};

