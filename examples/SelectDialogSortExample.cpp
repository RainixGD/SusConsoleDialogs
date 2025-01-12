#include <SusConsoleDialogs/include.h>
#include <iostream>
#include <vector>

int main() {

    std::vector<DialogOption> mathOperations = {
        {"add", "Perform addition of two numbers."},
        {"subtract", "Perform subtraction of two numbers."},
        {"multiply", "Perform multiplication of two numbers."},
        {"divide", "Perform division of two numbers."},
        {"modulus", "Find the remainder of division between two numbers."},
        {"exponentiate", "Raise a number to the power of another number."},
        {"sqrt", "Calculate the square root of a number."},
        {"logarithm", "Find the logarithm of a number with a given base."},
        {"absolute", "Find the absolute value of a number."},
        {"factorial", "Calculate the factorial of a non-negative integer."},
        {"sin", "Calculate the sine of an angle (in radians)."},
        {"cos", "Calculate the cosine of an angle (in radians)."},
        {"tan", "Calculate the tangent of an angle (in radians)."},
        {"gcd", "Find the greatest common divisor of two numbers."},
        {"lcm", "Find the least common multiple of two numbers."}
    };

    auto operation = OptionDialog::run("Select math operation (alphabetical):", mathOperations, true, false, false, OptionDialog::Alphabetical);
    std::cout << operation << std::endl;

    auto operation2 = OptionDialog::run("Select math operation (reverse):", mathOperations, false, false, false, OptionDialog::Reverse);
    std::cout << operation2 << std::endl;

    while (true) {}

    return 0;
}