class YesNoDialog : public Dialog {
private:
    bool clearConsoleIfInvalidAnswer;

    bool init(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer, bool clearConsoleAtStart) {
        if (!Dialog::init(questionMessage, clearConsoleAtStart)) return false;
        this->clearConsoleIfInvalidAnswer = clearConsoleIfInvalidAnswer;
        return true;
    }

public:
    bool run() {
        Dialog::run();
        std::cout << "(Y/N)" << std::endl;
        std::string input;

        while (true) {
            if (clearConsoleIfInvalidAnswer) {
                Dialog::clearConsole();
                Dialog::run();
                std::cout << "(Y/N)" << std::endl;
            }
            std::cout << "> ";
            std::getline(std::cin, input);

            if (input == "Y" || input == "y")
                return true;
            else if (input == "N" || input == "n")
                return false;
            else
                std::cout << "Invalid input. Please try again." << std::endl;
        }
    }

    static bool run(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer = false, bool clearConsoleAtStart = true) {
        YesNoDialog dialog;
        if (!dialog.init(questionMessage, clearConsoleIfInvalidAnswer, clearConsoleAtStart))
            throw std::runtime_error("InputDialog: failed to initialize inline dialog");
        return dialog.run();
    }

    static std::unique_ptr<YesNoDialog> create(const std::string& questionMessage, bool clearConsoleIfInvalidAnswer = false, bool clearConsoleAtStart = true) {
        auto dialog = std::make_unique<YesNoDialog>();
        if (dialog->init(questionMessage, clearConsoleIfInvalidAnswer, clearConsoleAtStart)) {
            return dialog;
        }
        return nullptr;
    }
};