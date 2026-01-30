#include <iostream>
#include <memory>

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void makePayment(double) const = 0;
};

class CCPayment : public PaymentStrategy {
public:
    void makePayment(double amount) const override {
        std::cout << "Payment of rupees " << amount << " made with CC" << std::endl;
    }
};

class NetBankingPayment : public PaymentStrategy {
public:
    void makePayment(double amount) const override {
        std::cout << "Payment of rupees " << amount << " made with NetBanking" << std::endl;
    }
};

class UPIPayment : public PaymentStrategy {
public:
    void makePayment(double amount) const override {
        std::cout << "Payment of rupees " << amount << " made with UPI" << std::endl;
    }
};

class OnlineStore {
private:
    std::unique_ptr<PaymentStrategy> payMode;
public:
    void setPaymentMode(std::unique_ptr<PaymentStrategy> mode) {
        payMode = std::move(mode);
    }
    void checkout(double amount) const {
        if (!payMode) {
            std::cout << "No payment mode selected" << std::endl;
        } else {
            payMode->makePayment(amount);
        }
    }
};

int main() {
    OnlineStore store;

    store.setPaymentMode(std::make_unique<CCPayment>());
    store.checkout(500.00);

    store.setPaymentMode(std::make_unique<NetBankingPayment>());
    store.checkout(500.00);

    store.setPaymentMode(std::make_unique<UPIPayment>());
    store.checkout(500.00);
}