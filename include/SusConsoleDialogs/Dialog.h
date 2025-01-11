class Dialog {
protected:
    std::string questionMessage;
    bool clearConsoleAtStart;

    virtual bool init(std::string questionMessage, bool clearConsoleAtStart) {
        this->questionMessage = questionMessage;
        this->clearConsoleAtStart = clearConsoleAtStart;
        return true;
    }

    Dialog() = default;
public:

    void run() {
        if (clearConsoleAtStart) clearConsole();
        std::cout << questionMessage << std::endl;
    }

    void clearConsole() {
        system("cls");
    }

    virtual ~Dialog() = default;
};