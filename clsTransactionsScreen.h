#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionsMenueOptions
	{
		eDeposit = 1, eWithdraw = 2,
		eTotalBalances = 3, eTransfer = 4,
		eTransferLog = 5, eMainMenue = 6
	};

	static short _ReadTransactionMenueOption() {

		cout << setw(37) << left << "" << "Choose what do you want to do [1 To 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between 1 and 6 : ");

		return Choice;
	}

	static void _GoBackToTransactionMenue() {

		cout << "\n\n\tPress any kety to go back to Transaction Menue...";
		system("pause> 0");
		ShowTransactionsMenue();
	}

	static void _ShowDepositScreen() {

		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen() {

		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen() {

		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen() {

		//cout << "\nTransfer Screen Will Be Here...";
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen() {

		//cout << "\nTransfer Log Screen Will Be Here...";
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionsMenue(enTransactionsMenueOptions TransactionMenueOption) {

		switch (TransactionMenueOption) {

		case enTransactionsMenueOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eMainMenue:
			break;
		}

	}

public:

	static void ShowTransactionsMenue() {

		if (!CheckAccessRights(clsUser::enUserPermissions::pTransactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t    Transactions Screen");
		cout << setw(37) << left << "" << "=================================================\n";
		cout << setw(37) << left << "" << "\t\t\tTransactions Menue\n";
		cout << setw(37) << left << "" << "=================================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "=================================================\n";
		_PerformTransactionsMenue((enTransactionsMenueOptions)_ReadTransactionMenueOption());
	}

};

