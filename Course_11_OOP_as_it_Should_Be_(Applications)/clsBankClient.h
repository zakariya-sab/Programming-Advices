#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "Global.h"
// this file contain all client
// const string Client_file = "Clients.txt";

class clsBankClient : public clsPerson
{
private:
	//
	enum enMode
	{
		EmptyMode = 0,
		UpdateMode = 1,
		AddNewMode = 2
	};
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{

		vector<string> Client = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, Client[0], Client[1], Client[2], Client[3], Client[4], Client[5], stod(Client[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{

		vector<clsBankClient> vClients;
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
			return vClients;
		}
		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string ClientRecords;
		ClientRecords = Client.GetFirstName() + Seperator;
		ClientRecords += Client.GetLastName() + Seperator;
		ClientRecords += Client.GetEmail() + Seperator;
		ClientRecords += Client.GetPhone() + Seperator;
		ClientRecords += Client.AccountNumber() + Seperator;
		ClientRecords += Client.GetPinCode() + Seperator;
		ClientRecords += to_string(Client._AccountBalance) + Seperator;

		return ClientRecords;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{

		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line;
			for (const clsBankClient &Client : vClients)
			{
				if (Client._MarkedForDelete == false)
				{
					Line = _ConvertClientObjectToLine(Client);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{

		vector<clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient &C : vClients)
		{

			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(clsBankClient &DestinationClient, float amount, string UserName = CurrentUser.GetUserName(), string Seperator = "#//#")
	{
		// to use less memori we take the refrences &
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += _AccountNumber + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(amount) + Seperator;
		TransferLogRecord += to_string(_AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.GetAccountBalance()) + Seperator;
		TransferLogRecord += CurrentUser.GetUserName();
		return TransferLogRecord;
	}

	void _RegisterTransferLog(float amount, clsBankClient &DestinationClient, string UserName = CurrentUser.GetUserName())
	{

		string stDataLine = _PrepareTransferLogRecord(DestinationClient, amount, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}
	//

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
		_MarkedForDelete = false;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	static clsBankClient Find(string AccountNumber)
	{

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

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

	static clsBankClient Find(string AccountNumber, string PinCode)
	{

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{

		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	// void Print()
	// {
	// 	cout << "\nClient Card:";
	// 	cout << "\n___________________";
	// 	cout << "\nFirstName   : " << GetFirstName();
	// 	cout << "\nLastName    : " << GetLastName();
	// 	cout << "\nFull Name   : " << FullName();
	// 	cout << "\nEmail       : " << GetEmail();
	// 	cout << "\nPhone       : " << GetPhone();
	// 	cout << "\nAcc. Number : " << _AccountNumber;
	// 	cout << "\nPassword    : " << _PinCode;
	// 	cout << "\nBalance     : " << _AccountBalance;
	// 	cout << "\n___________________\n";
	// }

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	enum enSaveResults
	{
		svFaildEmptyObject = 0,
		svSucceeded = 1,
		svFaildAccountNumberExists = 2
	};

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}

		case enMode::AddNewMode:
		{
			// This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				// We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}
	}

	bool Delete()
	{
		vector<clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient &C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients)
		{

			TotalBalances += Client.GetAccountBalance();
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (_AccountBalance < Amount)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
		return false;
	}

	bool Transfer(float Amount, clsBankClient &DestinationClient)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, CurrentUser.GetUserName());
		return true;
	}
	//
	struct stTrnsferLogRecord;

	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;
	};

	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;

		vector<string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;
	}

	static vector<stTrnsferLogRecord> GetTransfersLogList()
	{
		vector<stTrnsferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in); // read Mode

		if (MyFile.is_open())
		{

			string Line;

			stTrnsferLogRecord TransferRecord;

			while (getline(MyFile, Line))
			{

				TransferRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}
};