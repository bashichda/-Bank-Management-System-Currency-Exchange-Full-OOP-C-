#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
{
private:

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

	static void _PrinClientCard(const clsBankClient& Client) {

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

	static void ShowAddNewClientScreen() {

		if (!CheckAccessRights(clsUser::enUserPermissions::pAddNewClient))
		{
			return;
		}

		string AccountNumber = "";
		cout << "\nPlease Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount Number is already used, Chosse another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResutl;

		SaveResutl = NewClient.Save();

		switch (SaveResutl) {

		case clsBankClient::enSaveResult::svSucceeded:
			cout << "\nClient Added Successfully :-).\n";
			_PrinClientCard(NewClient);
			break;
		case clsBankClient::enSaveResult::svFaildEmptyObject:
			cout << "\nError Account is not saved Because It's Empty";
			break;
		case clsBankClient::enSaveResult::svFaildAccountNumberExists:
			cout << "\nError Account Number is Already Used.";
			break;
		}
	}

};

