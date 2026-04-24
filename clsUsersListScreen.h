#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsUsersListScreen : protected clsScreen
{
private:

	static void _PrintUserRecordLine(const clsUser& User) {

		cout << setw(8) << left << "" << "| " << left << setw(12) << User.UserName;
		cout << "| " << left << setw(25) << User.FullName();
		cout << "| " << left << setw(12) << User.Phone;
		cout << "| " << left << setw(20) << User.Email;
		cout << "| " << left << setw(10) << User.Password;
		cout << "| " << left << setw(12) << User.Permissions;
	}
public:

	static void ShowUsersList() {

		vector <clsUser> vUsers = clsUser::GetUsersList();
		string Title = "\t    User List Screen";
		string Subtitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

		_DrawScreenHeader(Title, Subtitle);

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(12) << "User Name";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vUsers.empty())
		{
			cout << "\n\t\tNo Users Available In System";
		}
		else
		{
			for (const clsUser& U : vUsers) {

				_PrintUserRecordLine(U);
				cout << endl;
			}
		}


		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

};

