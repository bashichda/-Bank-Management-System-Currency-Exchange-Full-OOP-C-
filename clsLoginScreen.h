#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "Global.h"


using namespace std;

class clsLoginScreen : protected clsScreen
{
private:


	static bool _Login() {

		bool LoginFaild = false;
		short FaildLoginCounter = 0;

		string UserName, Password;

		do
		{
			if (LoginFaild)
			{
				FaildLoginCounter++;

				cout << "\nInvalide UserName/Password!";
				cout << "\nYou have " << 3-FaildLoginCounter << " Trials to login.\n";
			}

			if (FaildLoginCounter == 3)
			{
				cout << "\nYou are Locekd after 3 faild Trails\n\n";
				return false;
			}

			cout << "\nEnter UserName : ";
			cin >> UserName;

			cout << "Enter Password : ";
			cin >> Password;

			 CurrentUser = clsUser::Find(UserName, Password);

			 LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen() {

		system("cls");
		_DrawScreenHeader("\t    Login Screen");
		return _Login();
	}
};

