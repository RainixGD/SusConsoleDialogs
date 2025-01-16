#include <SusConsoleDialogs/include.h>
#include <iostream>

int main() {
    InputDialog<int>::run("Int input, basic");
    InputDialog<int>::run("Int input, basic");
    InputDialog<int>::run("Int input, empty output options", Dialog::None);
    InputDialog<int>::run("Int input, clear console at start", Dialog::ClearConsoleAtStart);
    InputDialog<int>::run("Int input, repeat question if invalid answer", Dialog::RepeatQuestionIfInvalidAnswer);
    InputDialog<int>::run("Int input, clear console if invalid answer", Dialog::ClearConsoleIfInvalidAnswer);
    InputDialog<int>::run("Int input, repeat question and clear console if invalid answer", Dialog::RepeatQuestionIfInvalidAnswer | Dialog::ClearConsoleIfInvalidAnswer);
    InputDialog<int>::run("Int input, clear console at start and clear console if invalid answer", Dialog::ClearConsoleAtStart | Dialog::ClearConsoleIfInvalidAnswer);
    InputDialog<int>::run("Int input, all", Dialog::ClearConsoleAtStart | Dialog::ClearConsoleIfInvalidAnswer | Dialog::RepeatQuestionIfInvalidAnswer);

    while (true) {}

    return 0;
}