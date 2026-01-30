#include <iostream>

class IPrinter {
public:
    IPrinter() = default;
    virtual ~IPrinter() = default;
    virtual void print(const std::string& str) const = 0;
};

class OldPrinter {
public:
    void print(const char* str) const {
        if (str) {
            std::cout << "[OldPrinter]: " << str << std::endl;
        }
    }
};

class ModernPrinter : public IPrinter {
public:
    void print(const std::string& str) const override {
        std::cout << "[ModernPrinter]: " << str << std::endl;
    }
};

class OldPrinterAdapter final : public IPrinter {
private:
    std::unique_ptr<OldPrinter> oldPrinter;
public:
    explicit OldPrinterAdapter(std::unique_ptr<OldPrinter> printerIn) 
                                : oldPrinter(std::move(printerIn)) {}
    void print(const std::string& str) const override {
        oldPrinter->print(str.c_str());
    }
};

int main() {
    std::unique_ptr<IPrinter> p1 = std::make_unique<ModernPrinter>();
    p1->print("logs");

    std::unique_ptr<IPrinter> p2 = std::make_unique<OldPrinterAdapter>(std::make_unique<OldPrinter>());
    p2->print("logs");
}
