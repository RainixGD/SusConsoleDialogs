class Dialog {
protected:
    std::string questionMessage;
    bool clearConsoleAtStart;

    virtual bool init(const std::string& questionMessage, bool clearConsoleAtStart) {
        this->questionMessage = questionMessage;
        this->clearConsoleAtStart = clearConsoleAtStart;
        return true;
    }

    Dialog() = default;

    void clearConsole() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

public:
    void run() {
        if (clearConsoleAtStart) clearConsole();
        std::cout << questionMessage << std::endl;
    }

    virtual ~Dialog() = default;
};
