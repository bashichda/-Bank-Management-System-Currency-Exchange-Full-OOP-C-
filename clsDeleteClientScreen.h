#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen() {


		if (!CheckAccessRights(clsUser::enUserPermissions::pDeleteClient))
		{
			return;
		}

		_DrawScreenHeader("\t    Delete Client Screen");

		short Trial = 3;

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (Trial > 0 && !clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount Number is not found, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();

			Trial--;
		}

		if (Trial == 0)
		{
			cout << "\nToo many failed attempts.\n";
			return;
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		char Answer = 'n';
		cout << "\nAre you sure you want to delete this client y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client);

			}
			else
			{
				cout << "\nClient was not Deleted.\n";
			}
		}
	}

};

