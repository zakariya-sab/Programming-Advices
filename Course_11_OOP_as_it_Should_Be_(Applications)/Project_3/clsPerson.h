#pragma once
#include <iostream>
#include <string>
using namespace std;

class ClsPerson
{
private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:
    ClsPerson(string FirstName, string LastName, string Email, string Phone)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }
    
    // property set & get
    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }
    string GetFirstName()
    {
        return _FirstName;
    }
    __declspec(property(get = GetFirstName , put = SetFirstName)) string FirstName;
   
    // property set & get
    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }
    string GetLastName()
    {
        return _LastName;
    }
    __declspec(property(get = GetLastName , put = SetLastName)) string LastName;
   
    // property set & get
    void SetEmail(string Email)
    {
        _Email = Email;
    }
    string GetEmail()
    {
        return _Email;
    }
    __declspec(property(get = GetEmail , put = SetEmail)) string Email;
   
    // property set & get
    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }
    string GetPhone()
    {
        return _Phone;
    }
    __declspec(property(get = GetPhone , put = SetPhone)) string Phone;

};
