#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

	 static void _ReadClientInfo(clsBankClient& Client) {
		
		cout << "\nEnter First Name : ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name : ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode : ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Balance : ";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();
	}

public:

	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enUserPermissions::pUpdateClient))
		{
			return;
		}

		_DrawScreenHeader("\t    Update Client Screen");

		short Trial = 3;

		string AccountNumber = "";
		cout << "\nPlease enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (Trial > 0 && !clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount Number is not Found, Choose another one: ";
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

		cout << "\nAre you sure you want to update this client y/n ? ";
		
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\nUpdate Client : ";
			cout << "\n------------------------";

			_ReadClientInfo(Client);

			clsBankClient::enSaveResult SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult) {

			case clsBankClient::enSaveResult::svSucceeded:
				cout << "\nClient Updated Successfully :-)\n";
				_PrintClient(Client);
				break;
			case clsBankClient::enSaveResult::svFaildEmptyObject:
				cout << "\nError Account was not saved because it's empty.\n";
				break;
			}
		}

		

	}
};

