class YesNoDialog : public Dialog {
private:
    bool init(const std::string& questionMessage, int outputOptions) {
        if (!Dialog::init(questionMessage, outputOptions)) return false;
        return true;
    }

public:
    virtual void print() override {
        std::cout << questionMessage << std::endl;
        std::cout << "(Y/N)" << std::endl;
    }

    bool run() {
        if (clearConsoleAtStart) clearConsole();
        print();
        std::string input;

        while (true) {
            std::cout << "> ";
            std::getline(std::cin, input);

            if (input == "Y" || input == "y")
                return true;
            else if (input == "N" || input == "n")
                return false;
            else {
                runOnWrongAnswer();
            }
        }
    }

    static bool run(const std::string& questionMessage, int outputOptions = ClearConsoleAtStart) {
        YesNoDialog dialog;
        if (!dialog.init(questionMessage, outputOptions))
            throw std::runtime_error("InputDialog: failed to initialize inline dialog");
        return dialog.run();
    }

    static YesNoDialog* create(const std::string& questionMessage, int outputOptions = ClearConsoleAtStart) {
        auto dialog = new YesNoDialog();
        if (dialog->init(questionMessage, outputOptions)) {
            return dialog;
        }
        return nullptr;
    }
};