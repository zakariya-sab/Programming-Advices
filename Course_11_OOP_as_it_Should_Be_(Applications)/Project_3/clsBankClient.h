#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
// #include "../Clients.txt"
using namespace std;
const string ClientsFileName = "Clients.txt";

class clsBankClient : public ClsPerson
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1
    };
    enMode _Mode;
    string _AccountNumber;
    string _Pincode;
    float _AccountBalance;
    static vector<string> _SplitString(string S1, string Delim)
    {
        vector<string> vString;
        short pos = 0;
        string sWord; // define a string variable
        // use find() function to get the position of the delimiters
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "")
            {
                vString.push_back(sWord);
            }
            S1.erase(0, pos + Delim.length());
        }
        if (S1 != "")
        {
            vString.push_back(S1); // it adds last word of the string.
        }
        return vString;
    }
    static clsBankClient _convertLineToClientObject(string line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsBankClient::_SplitString(line, Seperator);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, " ", " ", " ", " ", " ", " ", 0);
    }

public:
    static clsBankClient Find(string AccountNumber)
    {
        vector<clsBankClient> vClients;
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::in); // read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _convertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    static clsBankClient Find(string AccountNumber, string PassWord)
    {
        vector<clsBankClient> vClients;
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::in); // read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _convertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.GetPincode() == PassWord)
                {
                    MyFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient client = clsBankClient::Find(AccountNumber);
        return !(client.IsEmpty());
    }

    // constructer:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string Pincode, float AccountBalance)
        : ClsPerson(FirstName, LastName, Email, Phone)

    {
        _AccountNumber = AccountNumber;
        _Pincode = Pincode;
        _AccountBalance = AccountBalance;
        _Mode = Mode;
    }

    // only get
    string AccountNumber()
    {
        return _AccountNumber;
    }

    // property set and get :
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    // __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    // property set and get :
    string GetPincode()
    {
        return _Pincode;
    }
    void SetPincode(string Pincode)
    {
        _Pincode = Pincode;
    }
    // __declspec(property(get = GetPincode, put = SetPincode)) string Pincode;
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFirstName          :" << GetFirstName();
        cout << "\nLastName           :" << GetLastName();
        cout << "\nFull Name          :" << FullName();
        cout << "\nEmail              :" << GetEmail();
        cout << "\nPhone              :" << GetPhone();
        cout << "\nAcc. Number        :" << _AccountNumber;
        cout << "\nPassword           :" << GetPincode();
        cout << "\nBalance            :" << GetAccountBalance();
        cout << "\n______________________\n";
    }
};