template <typename T>
class InputDialog : public Dialog {
private:
    std::function<bool(T)> verificationFunction;

    bool init(const std::string& questionMessage, int outputOptions, std::function<bool(T)> verificationFunction = nullptr) {
        if (!Dialog::init(questionMessage, outputOptions)) return false;
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
        if (clearConsoleAtStart) clearConsole();
        print();

        T result;
        std::string input;

        while (true) {            
            std::cout << "> ";
            std::getline(std::cin, input);

            if (parseInput(input, result)) {
                if (verificationFunction && !verificationFunction(result))
                    runOnWrongAnswer();
                else
                    return result;
            }
            else {
                runOnWrongAnswer();
            }
        }
    }

    static T run(const std::string& questionMessage, int outputOptions = ClearConsoleAtStart, std::function<bool(T)> verificationFunction = nullptr) {
        InputDialog dialog;
        if (!dialog.init(questionMessage, outputOptions, verificationFunction))
            throw std::runtime_error("InputDialog: failed to initialize inline dialog");
        return dialog.run();
    }

    static InputDialog* create(const std::string& questionMessage, int outputOptions = ClearConsoleAtStart, std::function<bool(T)> verificationFunction = nullptr) {
        auto dialog = new InputDialog();
        if (dialog->init(questionMessage, outputOptions, verificationFunction)) {
            return dialog;
        }
        return nullptr;
    }
};