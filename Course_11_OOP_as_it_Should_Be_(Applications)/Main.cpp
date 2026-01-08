// system is a function that alwo to you code execute a OS commands , the process is :
//  Your C++ program → Calls OS → OS executes the command → Returns to your program
//  like : system("cls");
// also it depande on your machine
#include "clsLoginScreen.h"
int main()

{
    // clsMainScreen::ShowMainMenue();

    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
    system("pause>0");
    return 0;
}