#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static void _PrintCurrencyCard(const clsCurrency& Currency) {

		cout << "\nCurrency Card : ";
		cout << "\n----------------------------------------";
		cout << "\nCountry  = " << Currency.Country();
		cout << "\nCode     = " << Currency.CurrencyCode();
		cout << "\nName     = " << Currency.CurrencyName();
		cout << "\nRate(1$) = " << Currency.Rate();
		cout << "\n----------------------------------------";
	}

	static float _ReadRate() {

		float Rate = 0;

		cout << "\nEnter New Rate : ";
		Rate = clsInputValidate::ReadFloatNumber();

		return Rate;
	}

public:

	static void ShowUpdateCurrencyRateScreen() {

		_DrawScreenHeader("\t    Updatee Currency Screen");

		string CurrencyCode = "";
		cout << "\nPlease Enter Currency Code : ";
		CurrencyCode = clsInputValidate::ReadString();
		short Trail = 3;

		while (Trail > 0 && !clsCurrency::IsCurrencyExist(CurrencyCode)) {

			cout << "\nCurrency Code is Not Found, Choose Another One: ";
			CurrencyCode = clsInputValidate::ReadString();
			Trail--;
		}

		if (Trail == 0)
		{
			cout << "\nToo many faild attempts.\n";
			return;
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		_PrintCurrencyCard(Currency);

		char Answer = 'n';

		cout << "\nAre you sure you want to update rate of this currency y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\nUpdate Curency Rate: ";
			cout << "\n---------------------------";
			Currency.UpdateRate(_ReadRate());
			cout << "\nCurrency Rate Updated Successfully :-)";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nOperation Was Canceled!";
		}
		

	}
};

