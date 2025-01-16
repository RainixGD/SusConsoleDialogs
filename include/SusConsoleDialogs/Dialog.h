class Dialog {
public:
    enum OutputOptions {
        None = 0,
        ClearConsoleAtStart = 1 << 0,
        ClearConsoleIfInvalidAnswer = 1 << 1,
        RepeatQuestionIfInvalidAnswer = 1 << 2
    };
protected:
    std::string questionMessage;
    bool clearConsoleAtStart;
    bool clearConsoleIfInvalidAnswer;
    bool repeatQuestionIfInvalidAnswer;

    bool init(const std::string& questionMessage, int dialogOptions) {
        this->questionMessage = questionMessage;
        this->clearConsoleAtStart = dialogOptions & ClearConsoleAtStart;
        this->clearConsoleIfInvalidAnswer = dialogOptions & ClearConsoleIfInvalidAnswer;
        this->repeatQuestionIfInvalidAnswer = dialogOptions & RepeatQuestionIfInvalidAnswer;
        return true;
    }

    virtual void print() {
        std::cout << questionMessage << std::endl;
    }

    virtual void printIfWrongAnswer() {
        std::cout << "Invalid answer" << std::endl;
    }

    void runOnWrongAnswer() {
        if (clearConsoleIfInvalidAnswer) {
            clearConsole();
            print();
        }
        else {
            printIfWrongAnswer();
            if (repeatQuestionIfInvalidAnswer) {
                print();
            }
        }
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

    virtual ~Dialog() = default;
};
