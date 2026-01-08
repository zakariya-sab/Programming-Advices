#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen

{
private:
    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange : ";
        float NewAmount = 0;

        NewAmount = clsInputValidate::ReadFloatNumber();
        return NewAmount;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nConvert From:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";
    }

    float static _Exchange(clsCurrency Src_Currency, clsCurrency Des_Currency, float amount)
    {
        float resulte = 0;
        if (Des_Currency.CurrencyCode() == "USD")
        {
            resulte = amount / Src_Currency.Rate();
        }
        else if (Src_Currency.CurrencyCode() == "USD")
        {
            resulte = amount * Des_Currency.Rate();
        }
        else
        {
            clsCurrency BaisCurrency = clsCurrency::FindByCode("USD");
            resulte = _Exchange(Src_Currency, BaisCurrency, amount);
            resulte = _Exchange(BaisCurrency, Des_Currency, resulte);
        }
        return resulte;
    }

public:
    static void _ShowCurrencyCalculatorScreen()
    {

        _DrawScreenHeader("    Calculat Currency Exchange  Screen");
        // srours:
        string Src_CurrencyCode = "";

        cout << "\nPlease Enter Currency 1 Code: ";
        Src_CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(Src_CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            Src_CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Src_Currency = clsCurrency::FindByCode(Src_CurrencyCode);
        // distantion:
        string Des_CurrencyCode = "";

        cout << "\nPlease Enter Currency 2 Code: ";
        Des_CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(Des_CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            Des_CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Des_Currency = clsCurrency::FindByCode(Des_CurrencyCode);

        //
        float Amount = _ReadAmount();
       // cout << "\nConvert From:";
        _PrintCurrency(Src_Currency);
        //print result :
        cout << "\n" << Amount <<"  "<< clsString::UpperAllString(Src_CurrencyCode) << " = "<< _Exchange(Src_Currency, Des_Currency, Amount) << " "<<clsString::UpperAllString(Des_CurrencyCode);
    }
};
