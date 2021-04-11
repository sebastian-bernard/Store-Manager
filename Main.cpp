#include <iostream>
#include "ConsoleUI.h"
#include "TestManager.h"

int main()
{
    runAllTests();
 
    ConsoleUI consoleUI;

    consoleUI.help();

    consoleUI.start();

    return 0;
}