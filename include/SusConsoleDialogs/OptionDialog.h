struct DialogOption {
    std::string key;
    std::string description;

    DialogOption(std::string key, std::string description = "")
        : key(std::move(key)), description(std::move(description)) {}
};

class OptionDialog : public Dialog {
public:
    enum Settings {
        Nothing = 0,
        SelectUsingIndex = 1 << 2,
        SortAlphabetical = 1 << 3,
        ReversedOrder = 1 << 4
    };
private:
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
        int settings,
        int outputOptions
    ) {
        if (!Dialog::init(questionMessage, outputOptions)) return false;
        this->selectUsingIndex = settings & SelectUsingIndex;
        this->options = options;

        if (settings & SortAlphabetical)
            std::sort(this->options.begin(), this->options.end(), [](const DialogOption& a, const DialogOption& b) {
                return a.key < b.key;
            });

        if (settings & ReversedOrder)
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
    virtual void print() override {
        std::cout << questionMessage << std::endl;
        printList();
    }

    int run() {
        if (clearConsoleAtStart) clearConsole();
        print();

        std::string input;

        while (true) {
            std::cout << "> ";
            std::getline(std::cin, input);

            if (selectUsingIndex) {
                auto index = parseInt(input);
                if (index.has_value() && index >= 0 && index < options.size()) {
                    return index.value();
                }
                runOnWrongAnswer();
            }
            else {
                auto index = findByKey(input);
                if (index.has_value()) {
                    return index.value();
                }
                runOnWrongAnswer();
            }
        }
    }

    static int run(
        const std::string& questionMessage,
        std::vector<DialogOption> options,
        int settings = Nothing,
        int outputOptions = ClearConsoleAtStart
    ) {
        OptionDialog dialog;
        if (!dialog.init(questionMessage, options, settings, outputOptions)) throw std::runtime_error("OptionDialog: failed to initialize inline dialog");
        return dialog.run();
    }

    static OptionDialog* create(
        const std::string& questionMessage,
        std::vector<DialogOption> options,
        int settings = Nothing,
        int outputOptions = ClearConsoleAtStart
    ) {
        auto dialog = new OptionDialog();
        if (dialog && dialog->init(questionMessage, options, settings, outputOptions)) {
            return dialog;
        }
        return nullptr;
    }
};