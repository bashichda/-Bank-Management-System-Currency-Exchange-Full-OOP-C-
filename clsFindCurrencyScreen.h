#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:

	static short _ReadChoice() {

		cout << "\nFind By : [1] Code or [2] Country ? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 2, "Please Enter [1] Code or [2] Country ? ");

		return Choice;
	}

	static void _PrintCurrencyCard(const clsCurrency& Currency) {

		cout << "\nCurrency Card : ";
		cout << "\n----------------------------------------";
		cout << "\nCountry  = " << Currency.Country();
		cout << "\nCode     = " << Currency.CurrencyCode();
		cout << "\nName     = " << Currency.CurrencyName();
		cout << "\nRate(1$) = " << Currency.Rate();
		cout << "\n----------------------------------------";
	}

	static void _ShowResult(const clsCurrency& Currency) {

		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrency Not Found :-(\n";
		}


	}

public:

	static void ShowFindCurrencyScreen() {

		_DrawScreenHeader("\t    Find Currency Screen");

		short Choice = _ReadChoice();

		if (Choice == 1)
		{
			string CurrencyCode = "";
			cout << "\nPlease Enter Currency Code : ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResult(Currency);

		}
		else
		{
			string Country = "";
			cout << "\nPlease Enter Country Name : ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}
	}

};

