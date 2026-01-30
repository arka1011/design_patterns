#include <iostream>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    virtual int getId() const = 0;
    virtual void update() = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void registerObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void deRegisterObserver(const Observer* obs) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void notify() {
        for (auto* obs : observers) {
            obs->update();
        }
    }

    void update() {
        std::cout << "Updating Subject\n";
        notify();
    }
};

class ConcreteObserver : public Observer {
private:
    int id;

public:
    explicit ConcreteObserver(int idIn) : id(idIn) {}

    int getId() const override {
        return id;
    }

    void update() override {
        std::cout << "Observer " << id << " updated\n";
    }
};

int main() {
    ConcreteObserver ob1(1);
    ConcreteObserver ob2(2);
    ConcreteObserver ob3(3);
    ConcreteObserver ob4(4);

    Subject sub;

    sub.registerObserver(&ob1);
    sub.registerObserver(&ob2);
    sub.registerObserver(&ob3);
    sub.registerObserver(&ob4);

    sub.update();

    sub.deRegisterObserver(&ob2);
    sub.deRegisterObserver(&ob4);

    sub.update();
}
