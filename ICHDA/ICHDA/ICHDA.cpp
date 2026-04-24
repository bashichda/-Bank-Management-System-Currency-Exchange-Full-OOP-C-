//Problem #49 - ATM PIN

#include <iostream>

using namespace std;

string ReadCodePin() {

    string PinCode;

    cout << "Please Enter Pin code : ";
    cin >> PinCode;

    return PinCode;
}

bool Login() {

    string PinCode;

    do {
        PinCode = ReadCodePin();

        if (PinCode == "1234") {
            return true;
        }
        else {

            cout << "\nWrong Pin \n";
            system("color 4F");
        }

    } while (PinCode != "1234");

    return false;
}
int main() {

    if (Login()) {

        system("color 2F");
        cout<< "\nYour Account Balance = 7500"<< endl;
    }

    return 0;
}
