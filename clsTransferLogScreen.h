#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include <vector>

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRecordLine(const clsBankClient::stTransferLogRecord& TransferLogRecord) {

		cout << setw(8) << left << "" << "| " << left << setw(24) << TransferLogRecord.DateTime;
		cout << "| " << left << setw(10) << TransferLogRecord.SourceAccount;
		cout << "| " << left << setw(10) << TransferLogRecord.DestinationAccount;
		cout << "| " << left << setw(10) << TransferLogRecord.Amount;
		cout << "| " << left << setw(10) << TransferLogRecord.SourceBalance;
		cout << "| " << left << setw(10) << TransferLogRecord.DestinationBalance;
		cout << "| " << left << setw(10) << TransferLogRecord.User;


	}

public:

	static void ShowTransferLogScreen() {

		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogList();
		string Title = "\t    Transfer Log List Screen";
		string Subtitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, Subtitle);

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(24) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acct";
		cout << "| " << left << setw(10) << "d.Acct";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(10) << "User";

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (vTransferLogRecord.empty())
		{
			cout << "\n\t\tNo Client Available In System";
		}
		else
		{
			for (const clsBankClient::stTransferLogRecord& T : vTransferLogRecord) {

				_PrintTransferLogRecordLine(T);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

	}

};

