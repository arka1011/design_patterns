#include <iostream>
#include <memory>

class File {
protected:
    virtual void open() = 0;
    virtual void parse() = 0;
    virtual void serialize() = 0;
    virtual void saveToDisk() {
        std::cout << "File saved to disk" << std::endl;
    }
public:
    virtual ~File() = default;
    void process() {
        open();
        parse();
        serialize();
        saveToDisk();
    }
};

class JSONFile : public File {
public:
    void open() override {
        std::cout << "Open JSON file" << std::endl;
    }
    void parse() override {
        std::cout << "Parse JSON file" << std::endl;
    }
    void serialize() override {
        std::cout << "Serialize JSON file" << std::endl;
    }
};

class XMLFile : public File {
public:
    void open() override {
        std::cout << "Open XML file" << std::endl;
    }
    void parse() override {
        std::cout << "Parse XML file" << std::endl;
    }
    void serialize() override {
        std::cout << "Serialize XML file" << std::endl;
    }
};

int main () {
    std::unique_ptr<File> json = std::make_unique<JSONFile>();
    json->process();

    std::unique_ptr<File> xml = std::make_unique<XMLFile>();
    xml->process();
};