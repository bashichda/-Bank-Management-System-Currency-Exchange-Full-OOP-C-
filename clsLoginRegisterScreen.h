#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterRecordLine(const clsUser::stLoginRegisterRecord& vLoginRegisterRecords) {

		cout << setw(8) << left << "" << "| " << left << setw(35) << vLoginRegisterRecords.DateTime;
		cout << "| " << left << setw(20) << vLoginRegisterRecords.UserName;
		cout << "| " << left << setw(20) << vLoginRegisterRecords.Password;
		cout << "| " << left << setw(10) << vLoginRegisterRecords.Permissions;

	}

public:

	static void ShowLoginRegisterScreen() {

		if (!CheckAccessRights(clsUser::enUserPermissions::pLoginRegister))
		{
			return;
		}

		vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecords = clsUser::GetLoginRegisterList();
		string Title = "\t    Login Register list Screen";
		string Subtitle = "\t       (" + to_string(vLoginRegisterRecords.size()) + ") Record(s).";

		_DrawScreenHeader(Title, Subtitle);

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_____________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date&Time";
		cout << "| " << left << setw(20) << "User Name";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_____________________________\n" << endl;


		if (vLoginRegisterRecords.empty())
		{
			cout << "\n\t\tNo Login Register Record Available In System";
		}
		else
		{
			for (const clsUser::stLoginRegisterRecord& L : vLoginRegisterRecords) {

				_PrintLoginRegisterRecordLine(L);
				cout << endl;
			}
		}


		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_____________________________\n" << endl;

	}
};

