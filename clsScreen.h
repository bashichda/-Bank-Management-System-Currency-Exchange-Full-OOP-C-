#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{

protected:


	static void _DrawScreenHeader(string Title, string Subtitle = "") {

		//
		cout << "\n\t\t\t\t\t-------------------------------------------";
		cout << "\n\n\t\t\t\t\t" << Title;
		if (Subtitle != "")
		{
			cout << "\n\t\t\t\t\t" << Subtitle;
		}
		cout << "\n\n\t\t\t\t\t-------------------------------------------\n";		
		cout << "\n\t\t\t\t\tUser : " << CurrentUser.UserName;
		cout << "\n\t\t\t\t\tDate : " << clsDate::DateToString(clsDate());
		cout << "\n\n\t\t\t\t\t-------------------------------------------\n";

	}

	static bool CheckAccessRights(clsUser::enUserPermissions Permission) {

		if (!CurrentUser.CheckAccessPermission(Permission))
		{
			cout << "\t\t\t\t\t-------------------------------------------";
			cout << "\n\n\t\t\t\t\t    Access Denied! Contact Your Admin.";
			cout << "\n\n\t\t\t\t\t-------------------------------------------";
			return false;
		}
		else
		{
			return true;
		}
	}
};

