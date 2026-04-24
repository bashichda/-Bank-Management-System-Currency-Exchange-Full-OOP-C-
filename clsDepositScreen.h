#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen() {

		_DrawScreenHeader("\t    Deposit Screen");

		short Trial = 3;

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (Trial > 0 && !clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nClient With [" << AccountNumber << "] does not exist.\n";
			AccountNumber = clsInputValidate::ReadString();
			Trial--;
		}

		if (Trial == 0) {

			cout << "\nToo many failed attempts.\n";
			return;
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		cout << "\nPlease enter deposit amount? ";
		double Amount = clsInputValidate::ReadDblNumber();

		cout << "\nAre you sure you want to perform this transaction? y/n : ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Client.Deposit(Amount);
			cout << "\nAmount Deposit Successfully.\n";
			cout << "\nNew Balance is : " << Client.AccountBalance;
		}
		else
		{
			cout << "\nOperation was Cancelled.\n";
		}


	}
};

