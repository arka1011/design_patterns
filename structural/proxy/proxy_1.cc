#include <iostream>
#include <string>
#include <memory>

class Iimage {
public:
    virtual ~Iimage() = default;
    virtual void load() const = 0;
}; 

class ActualImage : public Iimage {
private:
    std::string name;
public:
    explicit ActualImage(const std::string& n) : name(n) {}
    void load() const override {
        std::cout << "Actual image loaded" << std::endl;
    }
};

class ProxyImage : public Iimage {
private:
    std::string name;
    mutable std::unique_ptr<ActualImage> aImg;
public:
    explicit ProxyImage(std::string n) : name(std::move(n)), aImg(nullptr) {}
    void load() const override {
        if (!aImg) {
            std::cout << "Loading from Secondary storage" << std::endl;
            // for demo purpose just creating the obj
            aImg = std::make_unique<ActualImage>(name);
        }
        aImg->load();
    }
};

int main () {
    std::unique_ptr<ProxyImage> img = std::make_unique<ProxyImage>("myImage.img");
    img->load();
    img->load();
}