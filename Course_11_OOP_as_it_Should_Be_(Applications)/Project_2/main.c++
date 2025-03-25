#include <iostream>
#include "clsInputValidate.h"

int main()
{
    int a = clsInputValidate::ReadIntNumber("ereur,again! ");
    double b = clsInputValidate::ReadDoubleNumber("ereur,again! ");
    cout <<"\nIs number 1 between 5 & 82 :"<<clsInputValidate::IsNumberBetween(a,5,82);
    cout <<"\nIs number 2 between 5 & 9 :"<<clsInputValidate::IsNumberBetween(b,8.2,12.0);
    return 0;
}
