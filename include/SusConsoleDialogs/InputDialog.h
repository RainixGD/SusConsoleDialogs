template <typename T>
class InputDialog : public Dialog {
private:
    bool clearConsoleIfInvalidAnswer;
    std::function<bool(T)> verificationFunction;

    bool init(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer, bool clearConsoleAtStart, std::function<bool(T)> verificationFunction = nullptr) {
        if (!Dialog::init(questionMessage, clearConsoleAtStart)) return false;
        this->clearConsoleIfInvalidAnswer = clearConsoleIfInvalidAnswer;
        this->verificationFunction = verificationFunction;
        return true;
    }

    template <typename U>
    bool parseInput(const std::string& input, U& output) {
        if constexpr (std::is_arithmetic<U>::value) {
            std::istringstream iss(input);
            return (iss >> output) && iss.eof();
        }
        else if constexpr (std::is_same<U, std::string>::value) {
            output = input;
            return true;
        }
        else {
            return false;
        }
    }

public:
    T run() {
        Dialog::run();
        T result;
        std::string input;

        while (true) {
            if (clearConsoleIfInvalidAnswer) {
                Dialog::clearConsole();
                Dialog::run();
            }
            std::cout << "> ";
            std::getline(std::cin, input);

            if (parseInput(input, result)) {
                if (verificationFunction && !verificationFunction(result))
                    std::cout << "Invalid input. The answer is not suitable for the function." << std::endl;
                else
                    return result;
            }
            else {
                std::cout << "Invalid input. Please try again." << std::endl;
            }
        }
    }

    static T run(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer = false, bool clearConsoleAtStart = true, std::function<bool(T)> verificationFunction = nullptr) {
        InputDialog dialog;
        if (!dialog.init(questionMessage, clearConsoleIfInvalidAnswer, clearConsoleAtStart, verificationFunction))
            throw std::runtime_error("InputDialog: failed to initialize inline dialog");
        return dialog.run();
    }

    static std::unique_ptr<InputDialog> create(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer = false, bool clearConsoleAtStart = true, std::function<bool(T)> verificationFunction = nullptr) {
        auto dialog = std::make_unique<InputDialog>();
        if (dialog->init(questionMessage, clearConsoleIfInvalidAnswer, clearConsoleAtStart, verificationFunction)) {
            return dialog;
        }
        return nullptr;
    }
};