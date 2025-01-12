#include <SusConsoleDialogs/include.h>
#include <iostream>
#include <vector>

int main() {
    
    std::vector<DialogOption> operationOptions = {
        {"+"}, {"-"}, {"*"}, {"/"}, {"^"}, {"exit", "if you want to exit the app"}
    };

    MessageDialog::run("Hey! Welcome in my calculator! It's a good example program to demonstrate the dialogs library");

    auto readFloatArgDialog = InputDialog<float>::create("Enter argument:", false, true);
    auto readIntArgDialog = InputDialog<int>::create("Enter argument:", false, true);

    while (true) {
        auto operation = OptionDialog::run("Select the operation you want to use:", operationOptions, true, false, true, OptionDialog::Normal);
        
        if (operation == operationOptions.size() - 1) break;

        auto useFloatNumbers = YesNoDialog::run("Do you want to use float numbers?", false, true);

        if (useFloatNumbers) {
            float arg1 = readFloatArgDialog->run();
            float arg2 = readFloatArgDialog->run();
            float result = 0;

            switch (operation) {
            case 0: result = arg1 + arg2; break;
            case 1: result = arg1 - arg2; break;
            case 2: result = arg1 * arg2; break;
            case 3:
                if (arg2 != 0) {
                    result = arg1 / arg2;
                }
                else {
                    MessageDialog::run("Error: Division by zero is not allowed.");
                    continue;
                }
                break;
            case 4: result = std::pow(arg1, arg2); break;
            default:
                MessageDialog::run("Unknown operation.");
                continue;
            }

            MessageDialog::run("The result is: " + std::to_string(result));
        }
        else {
            int arg1 = readIntArgDialog->run();
            int arg2 = readIntArgDialog->run();
            int result = 0;

            switch (operation) {
            case 0: result = arg1 + arg2; break;
            case 1: result = arg1 - arg2; break;
            case 2: result = arg1 * arg2; break;
            case 3:
                if (arg2 != 0) {
                    result = arg1 / arg2;
                }
                else {
                    MessageDialog::run("Error: Division by zero is not allowed.");
                    continue;
                }
                break;
            case 4: result = static_cast<int>(std::pow(arg1, arg2)); break;
            default:
                MessageDialog::run("Unknown operation.");
                continue;
            }

            MessageDialog::run("The result is: " + std::to_string(result));
        }
    }

    MessageDialog::run("Thank you for using the calculator. Goodbye!");

    return 0;
}