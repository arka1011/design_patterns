#include <iostream>

class Car {
public:
    Car() = default;
    virtual ~Car() = default;
    virtual void build() = 0;
};

class SUV : public Car {
public:
    SUV() {}
    ~SUV() {}
    void build() override {
        std::cout << "SUV built" << std::endl;
    }
};

class Sedan : public Car {
public:
    Sedan() {}
    ~Sedan() {}
    void build() override {
        std::cout << "Sedan built" << std::endl;
    }
};

class CarFactory {
public:
    std::unique_ptr<Car> buildCar(std::string type) {
        if (type == "SUV") {
            return std::make_unique<SUV>();
        } else if (type == "Sedan") {
            return std::make_unique<Sedan>();
        }
        return nullptr;
    }
};

int main() {
    std::string type = "Sedan";
    CarFactory factory;
    std::unique_ptr<Car> car;
    car = factory.buildCar(type);
}