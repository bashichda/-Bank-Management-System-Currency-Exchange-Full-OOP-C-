#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <vector>
#include <iomanip>


using namespace std;

class clsCurreniesListScreen : protected clsScreen
{
private:

	static void _PrintCurrencyRecordLine(const clsCurrency& Currency) {

		cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.Country();
		cout << "| " << left << setw(8) << Currency.CurrencyCode();
		cout << "| " << left << setw(50) << Currency.CurrencyName();
		cout << "| " << left << setw(10) << Currency.Rate();
	}

public:

	static void ShowCurrenciesListScreen() {

		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Title = "\t    Currencies List Screen";
		string Subtitle = "\t    (" + to_string(vCurrencies.size()) + ") Currency.";

		_DrawScreenHeader(Title, Subtitle);

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(50) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (vCurrencies.empty())
		{
			cout << "\n\t\tNo Client Available In System";
		}
		else
		{
			for (const clsCurrency& C : vCurrencies) {

				_PrintCurrencyRecordLine(C);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

};

