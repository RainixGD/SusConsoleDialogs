class MessageDialog : public Dialog {
private:

    bool init(const std::string& questionMessage, int outputOptions) {
        if (!Dialog::init(questionMessage, outputOptions)) return false;
        return true;
    }

public:
    virtual void print() override {
        std::cout << questionMessage << std::endl;
        std::cout << "(Press enter to continue)" << std::endl;
    }

    void run() {
        if (clearConsoleAtStart) clearConsole();
        print();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void run(const std::string& message, int outputOptions = ClearConsoleAtStart) {
        MessageDialog dialog;
        if (!dialog.init(message, outputOptions)) {
            throw std::runtime_error("MessageDialog: failed to initialize inline dialog");
        }
        dialog.run();
    }

    static MessageDialog* create(const std::string& message, int outputOptions = ClearConsoleAtStart) {
        auto dialog = new MessageDialog();
        if (dialog->init(message, outputOptions)) {
            return dialog;
        }
        return nullptr;
    }
};