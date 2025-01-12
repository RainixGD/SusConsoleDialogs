#include <SusConsoleDialogs/include.h>
#include <iostream>

int main() {
    auto numberInputDialog = InputDialog<int>::create("Please enter an integer:");

    int userInputNumber = numberInputDialog->run();
    std::cout << "You entered the integer: " << userInputNumber << std::endl;

    int reusedInputNumber = numberInputDialog->run();
    std::cout << "You entered the integer again: " << reusedInputNumber << std::endl;

    auto stringInput = InputDialog<std::string>::run("Please enter a string:");
    std::cout << "You entered the string: " << stringInput << std::endl;

    while (true) {}

    return 0;
}