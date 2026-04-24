#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private:

	static int _ReadPermissionToSet() {

		int Permissions = 0;
		char Answer = 'n';

		cout << "\nDo you want to give full access Y/N ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to Access to : \n";
		cout << "\nShow Client List ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions |= clsUser::enUserPermissions::pShowClientList;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions |= clsUser::enUserPermissions::pAddNewClient;
		}

		cout << "\nDelete Client ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions |= clsUser::enUserPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions |= clsUser::enUserPermissions::pUpdateClient;
		}

		cout << "\nFind Client ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions |= clsUser::enUserPermissions::pFindClient;
		}

		cout << "\nTransactions ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions |= clsUser::enUserPermissions::pTransactions;
		}

		cout << "\nManage Users ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions |= clsUser::enUserPermissions::pManageUsers;
		}

		cout << "\nLogin Register ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions |= clsUser::enUserPermissions::pLoginRegister;
		}

		return Permissions;

	}

	static void _ReadUserInfo(clsUser& User) {

		cout << "\nEnter FirstName : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions : ";
		User.Permissions = _ReadPermissionToSet();

	}

	static void _PrintUser(const clsUser& User) {

		cout << "\nUser Card:";
		cout << "\n-------------------------------------------";
		cout << "\nFirst Name : " << User.FirstName;
		cout << "\nLast Name  : " << User.LastName;
		cout << "\nFull Name  : " << User.FullName();
		cout << "\nEmail      : " << User.Email;
		cout << "\nPhone      : " << User.Phone;
		cout << "\nUserName   : " << User.UserName;
		cout << "\nPassword   : " << User.Password;
		cout << "\nPermissions: " << User.Permissions;
		cout << "\n-------------------------------------------";
	}

public:

	static void ShowUpdateUserScreen() {

		_DrawScreenHeader("\t    Update User Screen");

		string UserName = "";
		cout << "\nPlease Enter User Name : ";
		UserName = clsInputValidate::ReadString();

		short Trial = 3;

		while (Trial > 0 && !clsUser::IsUserExist(UserName)) {

			cout << "\nUser Name is Not Found, Choose Another One: ";
			UserName = clsInputValidate::ReadString();
			Trial--;
		}

		if (Trial == 0)
		{
			cout << "\nToo many failed attempts.\n";
			return;
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'n';

		cout << "\nAre you sure you want to update this User? Y/N? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\nUser Update Info :";
			cout << "\n------------------------------";
			_ReadUserInfo(User);

			clsUser::enSaveResutl SaveResult;
			SaveResult = User.Save();

			switch (SaveResult) {
			case clsUser::enSaveResutl::svSucceeded:
				cout << "\nUser Updated Successfully.\n";
				_PrintUser(User);
				break;
			case clsUser::enSaveResutl::svFailedEmptyObject:
				cout << "\nError! User was Not Saved Because It's Empty.\n";
				break;
			case clsUser::enSaveResutl::svFailedUserNameExist:
				cout << "\nError! UserName Already Used.";
				break;
			}
		}
		else
		{
			cout << "\nUpdate Users Canceld.\n";
		}
	}
};

