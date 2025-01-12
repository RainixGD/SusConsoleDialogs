struct DialogOption {
    std::string key;
    std::string description;

    DialogOption(std::string key, std::string description = "")
        : key(std::move(key)), description(std::move(description)) {}
};

class OptionDialog : public Dialog {
public:
    enum ListOrder {
        Normal,
        Alphabetical,
        Reverse,
        AlphabeticalAndReverse
    };
private:
    bool clearConsoleIfInvalidAnswer;
    bool selectUsingIndex;
    std::vector<DialogOption> options;

    void printList() const {
        size_t maxKeyLength = 0;
        for (const auto& option : options) {
            maxKeyLength = std::max(maxKeyLength, option.key.size());
        }

        for (size_t i = 0; i < options.size(); i++) {
            std::cout << std::left;

            if (selectUsingIndex) {
                std::cout << "(" << i << ") "
                          << std::setw(static_cast<int>(maxKeyLength + 2))
                          << options[i].key
                          << (!options[i].description.empty() ? " - " + options[i].description : "")
                          << std::endl;
            } else {
                std::cout << std::setw(static_cast<int>(maxKeyLength + 2))
                          << options[i].key
                          << (!options[i].description.empty() ? " - " + options[i].description : "")
                          << std::endl;
            }
        }
    }

    bool init(
        const std::string& questionMessage,
        std::vector<DialogOption> options,
        bool selectUsingIndex,
        bool clearConsoleIfInvalidAnswer,
        bool clearConsoleAtStart,
        ListOrder order
    ) {
        if (!Dialog::init(questionMessage, clearConsoleAtStart)) return false;
        this->clearConsoleIfInvalidAnswer = clearConsoleIfInvalidAnswer;
        this->selectUsingIndex = selectUsingIndex;

        this->options = options;


        if (order == Alphabetical || order == AlphabeticalAndReverse)
            std::sort(this->options.begin(), this->options.end(), [](const DialogOption& a, const DialogOption& b) {
                return a.key < b.key;
            });

        if (order == Reverse || order == AlphabeticalAndReverse)
            std::reverse(this->options.begin(), this->options.end());

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

    static int run(
        const std::string& questionMessage,
        std::vector<DialogOption> options,
        bool selectUsingIndex = false,
        bool clearConsoleIfInvalidAnswer = false,
        bool clearConsoleAtStart = false,
        ListOrder order = Normal
    ) {
        OptionDialog dialog;
        if (!dialog.init(questionMessage, options, selectUsingIndex, clearConsoleIfInvalidAnswer, clearConsoleAtStart, order)) throw std::runtime_error("OptionDialog: failed to initialize inline dialog");
        return dialog.run();
    }

    static std::unique_ptr<OptionDialog> create(
        const std::string& questionMessage,
        std::vector<DialogOption> options,
        bool selectUsingIndex = false,
        bool clearConsoleIfInvalidAnswer = false,
        bool clearConsoleAtStart = false,
        ListOrder order = Normal
    ) {
        auto dialog = std::make_unique<OptionDialog>();
        if (dialog && dialog->init(questionMessage, options, selectUsingIndex, clearConsoleIfInvalidAnswer, clearConsoleAtStart, order)) {
            return dialog;
        }
        return nullptr;
    }
};