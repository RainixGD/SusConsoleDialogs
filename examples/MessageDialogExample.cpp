#include <SusConsoleDialogs/include.h>
#include <iostream>

int main() {
    auto messageDialog = MessageDialog::create("Here can be very important information user needs", true);
    messageDialog->run();

    MessageDialog::run("Another very important information here", true);

    while (true) {}

    return 0;
}