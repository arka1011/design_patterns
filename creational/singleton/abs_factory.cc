// there are two types of cars, SUV and Sedan
// cars can be built with two specs, EU and US specs

#include <memory>

enum class SPEC { EU=0, US };
enum class ENGINE { V10=0, V8 };
enum class TRANSMISSION { MANNUAL=0, AUTOMATIC };

class Car {
protected:
    SPEC spec;
    ENGINE engine;
    TRANSMISSION transmission;
    Car(SPEC specIn, ENGINE engineIn, TRANSMISSION transmissionIn) 
        : spec(specIn), engine(engineIn), transmission(transmissionIn) {};
public:
    Car() = delete;
    virtual ~Car() = default;
    SPEC getSpec() const { return spec; }
    ENGINE getEngine() const { return engine; }
    TRANSMISSION getTransmission() const { return transmission; }
};

class SUV : public Car { 
public:
    SUV() = delete;
    SUV(SPEC specIn, ENGINE engineIn, TRANSMISSION transmissionIn) 
        : Car(specIn,engineIn,transmissionIn) {};
    ~SUV() = default;
};

class Sedan : public Car {
public:
    Sedan() = delete;
    Sedan(SPEC specIn, ENGINE engineIn, TRANSMISSION transmissionIn) 
        : Car(specIn,engineIn,transmissionIn) {};
    ~Sedan() = default;
};

class CarFactory {
public:
    CarFactory() = default;
    virtual ~CarFactory() = default;
    virtual std::unique_ptr<Car> getSUV() const = 0;
    virtual std::unique_ptr<Car> getSedan() const = 0;
};

class GermanCarFactory : public CarFactory{
public:
    GermanCarFactory() = default;
    ~GermanCarFactory() = default;
    std::unique_ptr<Car> getSUV() const override {
        return std::make_unique<SUV>(SPEC::EU, ENGINE::V10, TRANSMISSION::MANNUAL);
    }
    std::unique_ptr<Car> getSedan() const override {
        return std::make_unique<Sedan>(SPEC::EU, ENGINE::V10, TRANSMISSION::MANNUAL);
    }
};

class TexasCarFactory : public CarFactory{
public:
    TexasCarFactory() = default;
    ~TexasCarFactory() = default;
    std::unique_ptr<Car> getSUV() const override {
        return std::make_unique<SUV>(SPEC::US, ENGINE::V10, TRANSMISSION::MANNUAL);
    }
    std::unique_ptr<Car> getSedan() const override {
        return std::make_unique<Sedan>(SPEC::US, ENGINE::V10, TRANSMISSION::MANNUAL);
    }
};

// for demo only
enum class TYPE { SUV=0, Sedan };

int main () {
    SPEC spec = SPEC::EU;
    TYPE type = TYPE::Sedan;
    std::unique_ptr<CarFactory> factory;
    std::unique_ptr<Car> car;
    if (spec == SPEC::EU) {
        factory = std::make_unique<GermanCarFactory>();
        if (type == TYPE::Sedan) {
            car = factory->getSedan();
        } else {
            car = factory->getSUV();
        }
    } else {
        factory = std::make_unique<TexasCarFactory>();
        if (type == TYPE::Sedan) {
            car = factory->getSedan();
        } else {
            car = factory->getSUV();
        }
    }
}