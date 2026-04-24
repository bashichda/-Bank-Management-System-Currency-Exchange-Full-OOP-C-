// Project 4 : Currency Calculator Screen

#include <iostream>
#include <string>
#include "clsLoginScreen.h"

using namespace std;


int main() {

	while (true) {

		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}

	return 0;
}