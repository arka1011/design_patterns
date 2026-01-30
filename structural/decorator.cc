#include <iostream>
#include <string>
#include <memory>

class Coffee {
public:
    Coffee() = default;
    virtual ~Coffee() = default;
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
};

class SimpleCoffee : public Coffee {
public:
    std::string getName() const override {
        return "Coffee";
    }
    double getPrice() const override {
        return 2.0;
    }
};

class CoffeeDecorator : public Coffee {
protected:
    std::unique_ptr<Coffee> coffee;
public:
    virtual ~CoffeeDecorator() = default;
    explicit CoffeeDecorator(std::unique_ptr<Coffee> c) 
                            : coffee(std::move(c)) {}
};

class Milk final : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;

    std::string getName() const override {
        return coffee->getName() + " with Milk";
    }
    double getPrice() const override {
        return coffee->getPrice() + 0.5;
    }
};

class Cream final : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;

    std::string getName() const override {
        return coffee->getName() + " with Cream";
    }
    double getPrice() const override {
        return coffee->getPrice() + 0.25;
    }
};

int main () {
    std::unique_ptr<Coffee> coffee =
                std::make_unique<Cream> (
                    std::make_unique<Milk>(
                        std::make_unique<SimpleCoffee>()
                    )
                );
    std::cout << coffee->getName() << std::endl;
    std::cout << coffee->getPrice() << std::endl;
}