#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
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

	static void ShowFindClientScreen() {

		if (!CheckAccessRights(clsUser::enUserPermissions::pFindClient))
		{
			return;
		}

		_DrawScreenHeader("\t    Find Client Screen");

		short Trial = 3;

		string AccoutnNumber = "";

		cout << "\nPlease Enter Account Number : ";
		AccoutnNumber = clsInputValidate::ReadString();

		while (Trial > 0 && !clsBankClient::IsClientExist(AccoutnNumber)) {

			cout << "\nAccount Number is not Found, Choose Another One: ";
			AccoutnNumber = clsInputValidate::ReadString();
			Trial--;
		}

		if (Trial == 0)
		{
			cout << "\nToo many failed attempts.\n";
			return;
		}

		clsBankClient Client = clsBankClient::Find(AccoutnNumber);

		if (!Client.IsEmpty())
		{
			cout << "\nClient Found. :-)\n";
		}
		else
		{
			cout << "\nClient Was Not Found. :-(\n";
		}
		_PrintClient(Client);
	}
};

