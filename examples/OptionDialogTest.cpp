#include <SusConsoleDialogs/include.h>
#include <iostream>

int main() {
    std::vector<DialogOption> fruitOptions = {
        {"apple", "A very healthy fruit rich in vitamins."},
        {"banana", "A popular fruit, great for energy."},
        {"watermelon", "A refreshing fruit, perfect for summer."}
    };

    OptionDialog::run("Option input, basic", fruitOptions);
    OptionDialog::run("Option input, basic", fruitOptions);
    OptionDialog::run("Option input, select using index", fruitOptions, OptionDialog::SelectUsingIndex);
    OptionDialog::run("Option input, sort alphabetical, clear console at start, repeat question if invalid answer", fruitOptions, OptionDialog::SortAlphabetical, Dialog::ClearConsoleAtStart | Dialog::RepeatQuestionIfInvalidAnswer);
    OptionDialog::run("Option input, sorted alphabetical, reversed order, select using index, clear console if invalid answer", fruitOptions,
        OptionDialog::SortAlphabetical | OptionDialog::ReversedOrder | OptionDialog::SelectUsingIndex, Dialog::ClearConsoleIfInvalidAnswer);

    while (true) {}

    return 0;
}