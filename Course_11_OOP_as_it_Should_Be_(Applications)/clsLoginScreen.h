#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{

private:
    static bool _Login()
    {
        bool LoginFaild = false;
        short number_of_trials = 3;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                --number_of_trials;
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "\nYou have " << number_of_trials << "Trails to login.\n\n";
                if (number_of_trials == 0)
                {
                    number_of_trials = 3;
                    cout << "\nYou are locked after " << number_of_trials << " Faild Trails.\n\n";
                    return false;
                }
            }

            cout << "Enter Username? ";
            // Username = clsInputValidate::ReadString();
            cin >> Username;

            cout << "Enter Password? ";
            // cin >> Password;
            Password = clsInputValidate::ReadString();

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }
};
