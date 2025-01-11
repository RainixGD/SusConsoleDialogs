#include <SusConsoleDialogs/include.h>
#include <iostream>
#include <vector>

int main() {

    std::vector<DialogOption> fruitOptions = {
        {"apple", "A very healthy fruit rich in vitamins."},
        {"banana", "A popular fruit, great for energy."},
        {"watermelon", "A refreshing fruit, perfect for summer."}
    };

    auto selectFruitDialog = OptionDialog::create(
        "Please select a fruit:",
        fruitOptions
    );

    int selectedFruitIndex = selectFruitDialog->run();

    std::cout << "You selected the fruit at index: " << selectedFruitIndex << std::endl;

    delete selectFruitDialog;

    while (true) {}

    return 0;
}