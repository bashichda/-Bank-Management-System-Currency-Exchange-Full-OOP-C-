#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:

	static void _PrintUser(const clsUser& User) {

		cout << "\nUser Card:";
		cout << "\n-------------------------------------------";
		cout << "\nFirst Name : " << User.FirstName;
		cout << "\nLast Name  : " << User.LastName;
		cout << "\nFull Name  : " << User.FullName();
		cout << "\nEmail      : " << User.Email;
		cout << "\nPhone      : " << User.Phone;
		cout << "\nUserName   : " << User.UserName;
		cout << "\nPassword   : " << User.Password;
		cout << "\nPermissions: " << User.Permissions;
		cout << "\n-------------------------------------------";
	}


public:

	static void ShowFindUserScreen() {

		_DrawScreenHeader("\t    Find User Screen");

		string UserName = "";
		cout << "\nPlease Enter User Name : ";
		UserName = clsInputValidate::ReadString();

		short Trial = 3;

		while (Trial > 0 && !clsUser::IsUserExist(UserName)) {

			cout << "\nUser Name is Not Found, Choose Another One: ";
			UserName = clsInputValidate::ReadString();
			Trial--;
		}

		if (Trial == 0)
		{
			cout << "\nToo many failed attempts.\n";
			return;
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
			_PrintUser(User);
		}
		else
		{
			cout << "\nUser Not Found :-(.\n";
		}
	}
};

