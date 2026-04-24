#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsers : protected clsScreen
{
private:
	enum enManageUsersMenueOptions
	{
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eShowMainMenue = 6
	};

	static short _ReadManageUsersMenueOption() {

		short Choice = 0;

		cout << setw(37) << left << "" << "Choose what do you want to do [1 To 6]? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between 1 and 6 : ");

		return Choice;
	}

	static void _GoBackToManageUsersMenue() {

		cout << "\n\n\tPress any key to go back to Manage Users Menue...";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen() {

		//cout << "\nList Users Screen Will Be Here...";
		clsUsersListScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen() {

		//cout << "\nAdd New User Screen Will Be Here...";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen() {

		//cout << "\nDelete User Screen Will Be Here...";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen() {

		//cout << "\nUpdate User Screen Will Be Here...";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen() {

		//cout << "\nFind User Screen Will Be Here...";
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenueOptions(enManageUsersMenueOptions ManageUsersMenueOption) {

		switch (ManageUsersMenueOption) {

		case enManageUsersMenueOptions::eListUsers:
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		case enManageUsersMenueOptions::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenue();
			break;
		case enManageUsersMenueOptions::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;
		case enManageUsersMenueOptions::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;
		case enManageUsersMenueOptions::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;
		case enManageUsersMenueOptions::eShowMainMenue:
			break;
		}
	}
public:

	static void ShowManageUsersMenue() {

		if (!CheckAccessRights(clsUser::enUserPermissions::pManageUsers))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t    Manage Users Screen");
		cout << setw(37) << left << "" << "=================================================\n";
		cout << setw(37) << left << "" << "\t\t    Manage Users Menue\n";
		cout << setw(37) << left << "" << "=================================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "=================================================\n";
		_PerformManageUsersMenueOptions(enManageUsersMenueOptions(_ReadManageUsersMenueOption()));
	}

};

