class MessageDialog : public Dialog {
private:
    bool init(const std::string& message, bool clearConsoleAtStart) {
        return Dialog::init(message, clearConsoleAtStart);
    }

public:
    void run() {
        Dialog::run();
        std::cout << "(Press enter to continue)" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void run(const std::string& message, bool clearConsoleAtStart = true) {
        MessageDialog dialog;
        if (!dialog.init(message, clearConsoleAtStart)) {
            throw std::runtime_error("MessageDialog: failed to initialize inline dialog");
        }
        dialog.run();
    }

    static std::unique_ptr<MessageDialog> create(const std::string& message, bool clearConsoleAtStart = true) {
        auto dialog = std::make_unique<MessageDialog>();
        if (dialog->init(message, clearConsoleAtStart)) {
            return dialog;
        }
        return nullptr;
    }
};