#pragma once

#include <iostream>
#include <string>
#include <vector> 
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _AccountNumber = "";
	string _PinCode = "";
	double _AccountBalance = 0;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(const string Line, string Separator = "#//#") {

		vector <string> vClientData = clsString::Split(Line, Separator);


		if (vClientData.size() < 7)
			return _GetEmptyClientObject();

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3]
			, vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(const clsBankClient& Client, string Separator = "#//#") {

		string DataLine = "";

		DataLine += Client.FirstName + Separator;
		DataLine += Client.LastName + Separator;
		DataLine += Client.Email + Separator;
		DataLine += Client.Phone + Separator;
		DataLine += Client.AccountNumber() + Separator;
		DataLine += Client.PinCode + Separator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile() {

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientDataToFile(const vector <clsBankClient>& vClients) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out); // override Mode

		string DataLine = "";

		if (MyFile.is_open())
		{
			for (const clsBankClient& C : vClients) {
				if (C.MarkForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update() {

		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientDataToFile(_vClients);
	}

	static clsBankClient  _GetEmptyClientObject() {

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	static void _AddDataLineToFile(const string& Line) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	string _PrepareTransferLogInRecord(const double& Amount, const clsBankClient& DestinationClient, const string& UserName,
		const string Separator = "#//#") {

		string TransferLogInRecord = "";

		TransferLogInRecord += clsDate::GetSystemDateTimeString() + Separator;
		TransferLogInRecord += AccountNumber() + Separator;
		TransferLogInRecord += DestinationClient.AccountNumber() + Separator;
		TransferLogInRecord += to_string(Amount) + Separator;
		TransferLogInRecord += to_string(AccountBalance) + Separator;
		TransferLogInRecord += to_string(DestinationClient.AccountBalance) + Separator;
		TransferLogInRecord += UserName;


		return TransferLogInRecord;
	}

	void _RegisterTransferLog(const double& Amount, const clsBankClient& DestinationClient,  const string& UserName) {

		string stDataLine = _PrepareTransferLogInRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}

	}
	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(const string& Line, const string Separator = "#//#") {

		stTransferLogRecord TransferLogRecord;

		vector <string> vTrasferLogRecord = clsString::Split(Line, Separator);

		TransferLogRecord.DateTime = vTrasferLogRecord[0];
		TransferLogRecord.SourceAccount = vTrasferLogRecord[1];
		TransferLogRecord.DestinationAccount = vTrasferLogRecord[2];
		TransferLogRecord.Amount = stod(vTrasferLogRecord[3]);
		TransferLogRecord.SourceBalance = stod(vTrasferLogRecord[4]);
		TransferLogRecord.DestinationBalance = stod(vTrasferLogRecord[5]);
		TransferLogRecord.User = vTrasferLogRecord[6];

		return TransferLogRecord;
	}

public:

	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccount;
		string DestinationAccount;
		double Amount = 0;
		double SourceBalance = 0;
		double DestinationBalance = 0;
		string User;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber,
		string PinCode, double AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	bool MarkForDelete() const {

		return _MarkForDelete;
	}

	string AccountNumber() const {

		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {

		_PinCode = PinCode;
	}

	string GetPinCode() const {

		return _PinCode;
	}


	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance) {

		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance() const {

		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;


	static clsBankClient Find(string AccountNumber) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists };

	enSaveResult Save() {

		switch (_Mode) {

		case enMode::EmptyMode:
		{
			return enSaveResult::svFaildEmptyObject;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFaildAccountNumberExists;
			}

			_AddNew();

			_Mode = enMode::UpdateMode;
			return enSaveResult::svSucceeded;
		}

		}

		return enSaveResult::svFaildEmptyObject;
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {

		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {

		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
		bool Found = false;

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == AccountNumber())
			{
				C._MarkForDelete = true;
				Found = true;
				break;
			}
		}

		if (!Found) {
			return false;
		}

		_SaveClientDataToFile(_vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList() {

		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (const clsBankClient& C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount) {

		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {

		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	bool Transfer(const double& Amount, clsBankClient& DestinationClient,const string& UserName) {

		if (Amount >  AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient,UserName);
		return true;
	}

	static vector <stTransferLogRecord> GetTransferLogList() {

		vector <stTransferLogRecord> vTrasferLogRecords;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line = "";

			stTransferLogRecord TransferLogRecord;

			while (getline(MyFile, Line)) {

				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
				vTrasferLogRecords.push_back(TransferLogRecord);
			}

			MyFile.close();
		}

		return vTrasferLogRecords;
	}
};

