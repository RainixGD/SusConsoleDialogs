struct DialogOption {
    std::string_view key;
    std::string_view description;

    DialogOption(std::string_view key, std::string_view description = "")
        : key(key), description(description) {}
};

class OptionDialog : public Dialog {
private:
    bool clearConsoleIfInvalidAnswer;
    bool selectUsingIndex;
    std::vector<DialogOption> options;

    void printList() const {
        for (size_t i = 0; i < options.size(); i++) {
            if (selectUsingIndex)
                std::cout << "(" << i << ") " << options[i].key << (options[i].description.size() > 0 ? std::string("\t- ") + std::string(options[i].description) : "") << std::endl;
            else
                std::cout << options[i].key << (options[i].description.size() > 0 ? std::string("\t- ") + std::string(options[i].description) : "") << std::endl;
        }
    }

    bool init(const std::string& questionMessage, std::vector<DialogOption> options, bool selectUsingIndex, bool clearConsoleIfInvalidAnswer, bool clearConsoleAtStart) {
        if (!Dialog::init(questionMessage, clearConsoleAtStart)) return false;
        this->clearConsoleIfInvalidAnswer = clearConsoleIfInvalidAnswer;
        this->options = options;
        this->selectUsingIndex = selectUsingIndex;
        return true;
    }

    std::optional<int> parseInt(const std::string& input) const {
        try {
            size_t pos;
            int value = std::stoi(input, &pos);
            if (pos == input.size()) {
                return value;
            }
        }
        catch (...) {}
        return std::nullopt;
    }

    std::optional<size_t> findByKey(const std::string& input) const {
        auto it = std::find_if(options.begin(), options.end(), [&](const DialogOption& opt) {
            return opt.key == input;
            });
        if (it != options.end()) {
            return std::distance(options.begin(), it);
        }
        return std::nullopt;
    }

public:
    int run() {
        Dialog::run();
        printList();

        std::string input;

        while (true) {
            if (clearConsoleIfInvalidAnswer) {
                Dialog::clearConsole();
                Dialog::run();
                printList();
            }
            std::cout << "> ";
            std::getline(std::cin, input);

            if (selectUsingIndex) {
                auto index = parseInt(input);
                if (index.has_value() && index >= 0 && index < options.size()) {
                    return index.value();
                }
                std::cout << "Invalid index. Please enter a number between 0 and " << options.size() - 1 << "." << std::endl;
            }
            else {
                auto index = findByKey(input);
                if (index.has_value()) {
                    return index.value();
                }
                std::cout << "Invalid option. Please enter a valid key." << std::endl;
            }
        }
    }

    static int run(const std::string& questionMessage, std::vector<DialogOption> options, bool selectUsingIndex = false, bool clearConsoleIfInvalidAnswer = false, bool clearConsoleAtStart = false) {
        OptionDialog dialog;
        if (!dialog.init(questionMessage, options, selectUsingIndex, clearConsoleIfInvalidAnswer, clearConsoleAtStart)) throw std::runtime_error("OptionDialog: failed to initialize inline dialog");
        return dialog.run();
    }

    static OptionDialog* create(const std::string& questionMessage, std::vector<DialogOption> options, bool selectUsingIndex = false, bool clearConsoleIfInvalidAnswer = false, bool clearConsoleAtStart = false) {
        auto dialog = new OptionDialog();
        if (dialog && dialog->init(questionMessage, options, selectUsingIndex, clearConsoleIfInvalidAnswer, clearConsoleAtStart)) {
            return dialog;
        }
        delete dialog;
        return nullptr;
    }
};