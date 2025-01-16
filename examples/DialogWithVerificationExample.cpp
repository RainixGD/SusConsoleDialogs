#include <SusConsoleDialogs/include.h>
#include <iostream>

int main() {
    auto evenNumber = InputDialog<int>::run("Enter an even number:", InputDialog<int>::ClearConsoleAtStart, [](int result) {
        return result % 2 == 0;
    });

    std::cout << evenNumber << std::endl;

    while (true) {}

    return 0;
}