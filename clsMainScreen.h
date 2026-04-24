#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "clsUser.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMenue.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

private:

	enum enMainMenueOptions {

		eListClient = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eTransactionMenue = 6,
		eManageUsersMenue = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10

	};

	static short ReadMainMenueOption() {

		cout << setw(37) << left << "" << "Choose what do you want to do [1 To 10]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Please Enter Number Between 1 and 10 : ");

		return Choice;
	}

	static void _GoBackToMainMenue() {

		cout << "\n\n\tPress any key to go back to Main Menue...";
		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientScreen() {

		clsClientListScreen::ShowClientListScreen();
	}

	static void _ShowAddNewClientScreen() {

		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen() {

		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen() {

		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen() {

		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue() {
		
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue() {

		//cout << "\nManage Users Menue Will be here...";
		clsManageUsers::ShowManageUsersMenue();
	}

	static void _ShowCurrencyExchangeMenue() {

		//cout << "\nCurrency Exchange Menue Will Be Here...";
		clsCurrencyExchangeMenue::ShowCurrencyExchangeMenue();
	}

	/*static void _ShowEndScreen() {

		cout << "\nEnd Screen Will Be here...";
	}*/

	static void _Logout() {

		CurrentUser = clsUser::Find("", "");

	}

	static void _ShowLoginRegisterScreen() {

		//cout << "\nLogin Register Screen Will Be Here...";
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _PerformMainMenueOption(enMainMenueOptions MainMenueOption) {

		switch (MainMenueOption) {

		case enMainMenueOptions::eListClient:
			system("cls");
			_ShowAllClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eTransactionMenue:
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eManageUsersMenue:
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eExit:
			system("cls");
			_Logout();
			break;
		}

	}

public:

	static void ShowMainMenue() {

		system("cls");
		_DrawScreenHeader("\t\tMain Screen");
		cout << setw(37) << left << "" << "=================================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "=================================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "=================================================\n";
		_PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
	}

};

