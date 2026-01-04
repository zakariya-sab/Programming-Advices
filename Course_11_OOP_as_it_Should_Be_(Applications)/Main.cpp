// system is a function that alwo to you code execute a OS commands , the process is :
//  Your C++ program → Calls OS → OS executes the command → Returns to your program
//  like : system("cls");
// also it depande on your machine
#include "clsLoginScreen.h"
void testD_affichage()
{
    cout << "-------------------------------------------------------" << endl;
    cout << "the curent  user name   : " << CurrentUser.GetUserName() << endl;
    cout << "the curent  first name  : " << CurrentUser.GetFirstName() << endl;
    cout << "the curent  last name   : " << CurrentUser.GetLastName() << endl;
    cout << "the curent  Password    : " << CurrentUser.GetPassword() << endl;
    cout << "the curent  Permissions : " << CurrentUser.GetPermissions() << endl;
    cout << "-------------------------------------------------------" << endl;
}
int main()

{
    // clsMainScreen::ShowMainMenue();

    while ((4-2)%2==0/*don't use true hhh*/)
    {
        clsLoginScreen::ShowLoginScreen();
    }
    // testD_affichage();
    system("pause>0");
    return 0;
}