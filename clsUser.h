#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsBankClient.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	struct stLoginRegisterRecord;

	enum enMode {enEmptyMode = 1, UpdateMode = 2, AddNewMode = 3};

	enMode _Mode;
	string _UserName = "";
	string _Password = "";
	int _Permissions = 0;
	bool _MarkForDelete = false;

	static clsUser _ConvertLineToUserObject(const string& Line, const string Separator = "#//#") {

		vector <string> vUserData = clsString::Split(Line, Separator);

		if (vUserData.size() < 7)
		{
			return _GetEmptyUserObject();
		}

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5])
			, stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(const clsUser& User, const string Separator = "#//#") {

		string DataLine = "";

		DataLine += User.FirstName + Separator;
		DataLine += User.LastName + Separator;
		DataLine += User.Email + Separator;
		DataLine += User.Phone + Separator;
		DataLine += User.UserName + Separator;
		DataLine += clsUtil::EncryptText(User.Password) + Separator;
		DataLine += to_string(User.Permissions);

		return DataLine;
	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enMode::enEmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector <clsUser> vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;
	}

	void _SaveDataUserInFile(const vector <clsUser>& vUsers) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open())
		{
			string DataLine = "";

			for (const clsUser& U : vUsers)
			{
				if (U._MarkForDelete == false)
				{
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update() {

		vector <clsUser> _vUsers = _LoadUsersDataFromFile();

		for (clsUser& U: _vUsers)
		{
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}
		}

		_SaveDataUserInFile(_vUsers);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	static void _AddDataLineToFile(const string& Line) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	string _PrepareLogInRecord(const string Separator = "#//#") {

		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		LoginRecord += UserName + Separator;
		LoginRecord += clsUtil::EncryptText(Password)+Separator;
		LoginRecord += to_string(Permissions);
		
		return LoginRecord;
	}

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(const string& Line,const string Separator = "#//#") {

		vector <string> vLoginRegisterRecord = clsString::Split(Line, Separator);

		stLoginRegisterRecord LoginRegisterRecord;

		LoginRegisterRecord.DateTime = vLoginRegisterRecord[0];
		LoginRegisterRecord.UserName = vLoginRegisterRecord[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterRecord[2]);
		LoginRegisterRecord.Permissions = stoi(vLoginRegisterRecord[3]);

		return LoginRegisterRecord;
	}

	

public:

	enum enUserPermissions {

		pAll = -1, pShowClientList = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32,
		pManageUsers = 64, pLoginRegister = 128
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Persmissions)
		: clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Persmissions;
	}

	bool IsEmpty() {

		return (_Mode == enMode::enEmptyMode);
	}

	bool MarkForDelete() {

		return _MarkForDelete;
	}

	void SetUserName(string UserName) {

		_UserName = UserName;
	}

	string GetUserName() const {

		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {

		_Password = Password;
	}

	string GetPassword() const {

		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions) {

		_Permissions = Permissions;
	}

	int GetPersmissions() const {
		
		return _Permissions;
	}

	__declspec(property(get = GetPersmissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(const string& UserName,const string& Password) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName) {

		clsUser User = clsUser::Find(UserName);

		return(!User.IsEmpty());
	}

	enum enSaveResutl {svSucceeded = 1, svFailedEmptyObject = 2, svFailedUserNameExist = 3};

	enSaveResutl Save() {

		switch (_Mode) {

		case enMode::enEmptyMode:
		{
			return enSaveResutl::svFailedEmptyObject;
		}
		case enMode::UpdateMode:
		{

			_Update();

			return enSaveResutl::svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(UserName))
			{
				return enSaveResutl::svFailedUserNameExist;
			}

			_AddNew();

			_Mode = enMode::UpdateMode;
			return enSaveResutl::svSucceeded;
		}

		}

	}

	bool Delete() {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		bool Found = false;

		for (clsUser& U : vUsers) {
			if (U.UserName == UserName)
			{
				U._MarkForDelete = true;
				Found = true;
				break;
			}
		}

		if (!Found)
		{
			return false;
		}

		_SaveDataUserInFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(const string& UserName) {

		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList() {

		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enUserPermissions Permission) {

		if (this->Permissions == enUserPermissions::pAll)
		{
			return true;
		}

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogIn() {

		string DataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList() {

		vector <stLoginRegisterRecord> vLoginRegisterRecords;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line = "";

			stLoginRegisterRecord Record;

			while (getline(MyFile, Line)) {

				Record = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecords.push_back(Record);
			}

			MyFile.close();
		}

		return vLoginRegisterRecords;
	}
	
	
};

