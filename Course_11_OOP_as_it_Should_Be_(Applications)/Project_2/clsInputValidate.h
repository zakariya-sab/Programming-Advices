#pragma once
#include <iostream>
#include <string>
using namespace std;
class clsInputValidate
{
public:
    static int ReadIntNumber(string message)
    {
        int Number;
        cout << "Please enter a number?" << endl;
        cin >> Number;
        while (cin.fail())
        {
            // user didn't input a number
            // cin.clear();
            // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // cout << message << endl;
            // cin >> Number;
        }
        return Number;
    }
    static double ReadDoubleNumber(string message)
    {
        double Number;
        cout << "Please enter a number?" << endl;
        cin >> Number;
        while (cin.fail())
        {
            // user didn't input a number
            // cin.clear();
            // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // cout << message << endl;
            // cin >> Number;
        }
        return Number;
    }
    static int ReadIntegerNumberBetween(int from, int to, string message)
    {
        int number = ReadIntNumber(message);
        while (!IsNumberBetween(number, from, to))
        {
            number = ReadIntNumber(message);
        }
        return number;
    }
    static double ReadDoubleNumberBetween(double from, double to, string message)
    {
        double number = ReadIntNumber(message);
        while (!IsNumberBetween(number, from, to))
        {
            number = ReadIntNumber(message);
        }
        return number;
    }
    static bool IsNumberBetween(int number, int from, int to)
    {
        return (number <= to) && (number >= from);
    }
    static bool IsNumberBetween(double number, double from, double to)
    {
        return (number <= to) && (number >= from);
    }
};
