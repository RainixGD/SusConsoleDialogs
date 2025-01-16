#include <SusConsoleDialogs/include.h>
#include <iostream>
#include <vector>

int main() {

    YesNoDialog::run("YesNoDialog basic");
    YesNoDialog::run("YesNoDialog basic");
    YesNoDialog::run("YesNoDialog without outputOptions", Dialog::None);
    YesNoDialog::run("YesNoDialog clear console if invalid answer", Dialog::ClearConsoleIfInvalidAnswer);
    YesNoDialog::run("YesNoDialog repeat question if invalid answer", Dialog::RepeatQuestionIfInvalidAnswer);
    YesNoDialog::run("YesNoDialog clean console at start and repeat question if invalid answer", Dialog::ClearConsoleAtStart | Dialog::RepeatQuestionIfInvalidAnswer);

    while (true) {}

    return 0;
}