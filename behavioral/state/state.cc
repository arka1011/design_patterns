#include <iostream>
#include <memory>

class State;

class Geek {
private:
    std::unique_ptr<State> state;
public:
    explicit Geek(std::unique_ptr<State> st) : state(std::move(st)) {}
    void setState(std::unique_ptr<State> st) {
        state = std::move(st);
    }
    void eat();
    void sleep();
    void code();
};

class State {
public:
    virtual ~State() = default;
    virtual void eat(Geek&) const = 0;
    virtual void sleep(Geek&) const = 0;
    virtual void code(Geek&) const = 0;
};

void Geek::eat() { state->eat(*this); }
void Geek::sleep() { state->sleep(*this); }
void Geek::code() { state->code(*this); }

class Eating;
class Sleeping;
class Coding;

class Eating : public State {
public:
    void eat(Geek& geek) const override {
        std::cout << "already eating" << std::endl;
    }
    void sleep(Geek& geek) const override {
        std::cout << "going to sleep after eating" << std::endl;
        geek.setState(std::make_unique<Sleeping>());
    }
    void code(Geek& geek) const override {
        std::cout << "can't code while eating" << std::endl;
    }
};

class Sleeping : public State {
public:
    void eat(Geek& geek) const override {
        std::cout << "going to eat after sleeping" << std::endl;
        geek.setState(std::make_unique<Eating>());
    }
    void sleep(Geek& geek) const override {
        std::cout << "already sleeping" << std::endl;
    }
    void code(Geek& geek) const override {
        std::cout << "can't code while sleeping" << std::endl;
    }
};

class Coding : public State {
public:
    void eat(Geek& geek) const override {
        std::cout << "can't eat while coding" << std::endl;
    }
    void sleep(Geek& geek) const override {
        std::cout << "going to sleep after coding" << std::endl;
        geek.setState(std::make_unique<Sleeping>());
    }
    void code(Geek& geek) const override {
        std::cout << "already coding" << std::endl;
    }
};

int main () {
    Geek geek(std::make_unique<Coding>());
    geek.eat();
    geek.code();
    geek.eat();
    geek.sleep();
    geek.code();
    geek.sleep();
}