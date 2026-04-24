#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsCurreniesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMenue : protected clsScreen
{
private:

	enum enCurrencyExchangeMenueOptions
	{
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, 
		eCurrencyCalculator = 4, eShowMainMenue = 5
	};

	static short _ReadCurrencyExchangeMenueOtption() {

		short Choice = 0;

		cout << setw(37) << left << "" << "Choose what you want to do [1 To 5]? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number Between 1 and 5 : ");

		return Choice;
	}

	static void _GoBackToCurrencyExchangeMenue() {

		cout << "\n\n\tPress any key to go back to Currency Exchange Menue...";
		system("pause>0");
		ShowCurrencyExchangeMenue();

	}

	static void _ShowCurrenciesListScreen() {

		//cout << "\nList Currencies Screen Will Be Here...";
		clsCurreniesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen() {

		//cout << "\nFind Currency Screen Will Be Here...";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen() {

		//cout << "\nUpdate Rate Screen Will Be Here...";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen() {

		//cout << "\nCurrency Calculator Screen Will Be Here...";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}
		
	static void _PerformCurrencyExchangeMenueOptions(enCurrencyExchangeMenueOptions CurrencyExchangeMenueOption) {

		switch (CurrencyExchangeMenueOption) {

		case enCurrencyExchangeMenueOptions::eListCurrencies:
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		case enCurrencyExchangeMenueOptions::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		case enCurrencyExchangeMenueOptions::eUpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		case enCurrencyExchangeMenueOptions::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		case enCurrencyExchangeMenueOptions::eShowMainMenue:
			break;
		}
	}

public:

	static void ShowCurrencyExchangeMenue() {

		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Screen");
		cout << setw(37) << left << "" << "=================================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "=================================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "=================================================\n";
		_PerformCurrencyExchangeMenueOptions((enCurrencyExchangeMenueOptions)_ReadCurrencyExchangeMenueOtption());
	}
};

