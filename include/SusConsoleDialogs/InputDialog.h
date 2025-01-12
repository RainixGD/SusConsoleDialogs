template <typename T>
class InputDialog : public Dialog {
private:
    bool clearConsoleIfInvalidAnswer;

    bool init(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer, bool clearConsoleAtStart) {
        if (!Dialog::init(questionMessage, clearConsoleAtStart)) return false;
        this->clearConsoleIfInvalidAnswer = clearConsoleIfInvalidAnswer;
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
                return result;
            }
            else {
                std::cout << "Invalid input. Please try again." << std::endl;
            }
        }
    }

    static T run(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer = false, bool clearConsoleAtStart = false) {
        InputDialog dialog;
        if (!dialog.init(questionMessage, clearConsoleIfInvalidAnswer, clearConsoleAtStart))
            throw std::runtime_error("InputDialog: failed to initialize inline dialog");
        return dialog.run();
    }

    static std::unique_ptr<InputDialog> create(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer = false, bool clearConsoleAtStart = false) {
        auto dialog = std::make_unique<InputDialog>();
        if (dialog->init(questionMessage, clearConsoleIfInvalidAnswer, clearConsoleAtStart)) {
            return dialog;
        }
        return nullptr;
    }
};