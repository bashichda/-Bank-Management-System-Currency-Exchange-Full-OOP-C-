#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	enMode _Mode;
	string _Country = "";
	string _CurrencyCode = "";
	string _CurrencyName = "";
	float _Rate = 0;

	static clsCurrency _ConvertLineToCurrencyObject(const string& Line, const string Separator = "#//#") {

		vector <string> vCurrencyData = clsString::Split(Line, Separator);

		if (vCurrencyData.size() < 4)
		{
			return _GetEmptyCurrencyObject();
		}

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static clsCurrency _GetEmptyCurrencyObject() {

		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static string _ConvertCurrencyObjectToLine(const clsCurrency& Currency, const string Separator = "#//#") {

		string DataLine = "";

		DataLine += Currency.Country() + Separator;
		DataLine += Currency.CurrencyCode() + Separator;
		DataLine += Currency.CurrencyName() + Separator;
		DataLine += to_string(Currency.Rate());

		return DataLine;
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile() {

		vector <clsCurrency> vCurrencies;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return vCurrencies;
	}

	void _SaveCurrenciesDataInFile(const vector <clsCurrency>& vCurrencies) {

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open())
		{
			for (const clsCurrency& C : vCurrencies) {

				string Line = _ConvertCurrencyObjectToLine(C);
				MyFile << Line << endl;
			}

				MyFile.close();
		}
	}

	void _Update() {

		vector <clsCurrency> _vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : _vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}

		_SaveCurrenciesDataInFile(_vCurrencies);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {

		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty() const {

		return (_Mode == enMode::EmptyMode);
	}

	string Country() const {

		return _Country;
	}

	string CurrencyCode() const {
		
		return _CurrencyCode;
	}

	string CurrencyName() const {

		return _CurrencyName;
	}


	void UpdateRate(float NewRate) {

		_Rate = NewRate;
		_Update();
	}

	float Rate() const {
		
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode) {

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {

		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList() {

		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) {

		return Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, const clsCurrency& Currency) {

		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return AmountInUSD * Currency.Rate();
	}
};

