#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static string _ReadCurrencyCode(const string& Message) {

		string CurrencyCode = "";
		cout << "\n" << Message;
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

			cout << "\nCurrency Code is Not found, Choose Another One : ";
			CurrencyCode = clsInputValidate::ReadString();
		}


		return CurrencyCode;
	}

	static  void _PrintCurrencyCard(const clsCurrency& Currency, string Title = "Currency Card:")
	{

		cout << "\n" << Title << "\n";
		cout << "_____________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCode          : " << Currency.CurrencyCode();
		cout << "\nName          : " << Currency.CurrencyName();
		cout << "\nRate(1$) =    : " << Currency.Rate();
		cout << "\n_____________________________\n\n";

	}

public:

	static void ShowCurrencyCalculatorScreen() {


		char Answer = 'n';
		float Amount = 0;
		float AmountInUSD = 0;
		float AmountInOtherCurrency = 0;

		do
		{
			system("cls");
			_DrawScreenHeader("\t    Currency Calculator Screen");
			string CurrencyCode = "";
			CurrencyCode = _ReadCurrencyCode("Please Enter Currency1 Code : ");
			clsCurrency CurrencyFrom = clsCurrency::FindByCode(CurrencyCode);

			CurrencyCode = _ReadCurrencyCode("Please Enter Currency2 Code : ");
			clsCurrency CurrencyTo = clsCurrency::FindByCode(CurrencyCode);

			cout << "\nEnter Amount To Exchange : ";
			Amount = clsInputValidate::ReadFloatNumber();

			AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
			_PrintCurrencyCard(CurrencyFrom, "Convert From:");
			cout << Amount << CurrencyFrom.CurrencyCode() << " = " << AmountInUSD << " USD" << endl;

			if (CurrencyTo.CurrencyCode() == "USD")
			{
				return;
			}
			
			AmountInOtherCurrency = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);
			_PrintCurrencyCard(CurrencyFrom, "To:");
			cout << Amount << CurrencyFrom.CurrencyCode() << " = " << AmountInOtherCurrency << " " << CurrencyTo.CurrencyCode() << endl;

			cout << "\nDo you want to perform another calculation? y/n? ";
			cin >> Answer;

		} while (Answer == 'y' || Answer == 'Y');
	}
};

