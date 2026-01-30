// Mayers thread safe sigleton with laze init
class Singleton {
private:
    Singleton() = default;
    ~Singleton() = default;
public:
    static Singleton& getInstance () {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

// thread safe egar init
class Singleton {
private:
    static Singleton instance;
    Singleton() = default;
    ~Singleton() = default;
public:
    static Singleton& getInstance() {
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

Singleton Singleton::instance{};


// optional thread safe pre-c++11 lazy init with locks (not safe)

#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx;

    Singleton() {}
    ~Singleton() {}

public:
    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }

    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
};

// definitions
Singleton* Singleton::instance = 0;
std::mutex Singleton::mtx;
