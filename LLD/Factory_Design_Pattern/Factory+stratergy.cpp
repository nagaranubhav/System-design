/*
Factory + Strategy Together (Payment System)

👉 Goal:

Factory decide kare: UPI, Card, Wallet kaunsa object mile

Strategy decide kare: Payment ka behavior kaise chale

Matlab:

Factory = creation
Strategy = behavior
*/

#include <iostream>
using namespace std;

// =====================================================
//      FACTORY + STRATEGY PATTERN - PAYMENT SYSTEM
// =====================================================

// --------------------
// STRATEGY INTERFACE
// --------------------
// Ye Strategy pattern ka interface hai.
// Har payment method me pay() hoga.
// Strategy ka kaam hota hai behavior define karna.

class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

// --------------------
// CONCRETE STRATEGIES
// --------------------
// Ye alag-alag behaviors hain.

class UPI : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "Paying " << amount << " using UPI\n";
    }
};

class Card : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "Paying " << amount << " using Card\n";
    }
};

class Wallet : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "Paying " << amount << " using Wallet\n";
    }
};

// --------------------
// FACTORY FOR STRATEGY
// --------------------
// Factory ka kaam yaha Strategy object banana hai.
// Client ko new UPI(), new Card() likhne nahi dete.

class PaymentStrategyFactory {
public:
    static PaymentStrategy* getStrategy(const string& type) {

        // Factory decides WHAT object to create.

        if (type == "upi") {
            return new UPI();
        }
        else if (type == "card") {
            return new Card();
        }
        else if (type == "wallet") {
            return new Wallet();
        }

        return nullptr;
    }
};

// --------------------
// CONTEXT (STRATEGY USER)
// --------------------
// Ye Strategy pattern ka Context hai.
// Iske andar behavior change hota hai at runtime.

class Checkout {
private:
    PaymentStrategy* strategy;   // pointer to strategy

public:
    Checkout() : strategy(nullptr) {}

    // Strategy set karna (behavior change)
    void setStrategy(PaymentStrategy* s) {
        strategy = s;
    }

    // Same function, different behavior
    void pay(int amount) {

        if (strategy == nullptr) {
            cout << "No payment strategy selected\n";
            return;
        }

        // Polymorphism:
        // runtime pe decide hota hai kaunsa pay() chalega
        strategy->pay(amount);
    }
};

// --------------------
// CLIENT
// --------------------

int main() {

    Checkout checkout;

    // Client bolta: mujhe UPI use karna hai
    // Factory creates Strategy object
    PaymentStrategy* s1 = PaymentStrategyFactory::getStrategy("upi");

    // Strategy set
    checkout.setStrategy(s1);

    // Same checkout, different behavior
    checkout.pay(500);

    // Client bolta: ab Card se pay karna hai
    PaymentStrategy* s2 = PaymentStrategyFactory::getStrategy("card");
    checkout.setStrategy(s2);
    checkout.pay(1000);

    return 0;
}

// --------------------
// REVISION POINTS FROM THIS EXAMPLE
// --------------------
// Factory creates Strategy objects.
// Strategy defines HOW behavior works.
// Factory = WHAT object.
// Strategy = HOW logic runs.
// Checkout object same rehta hai,
// bas strategy swap hoti hai.
// Polymorphism runtime pe kaam karta hai.
// Pointer (*) because new returns address.
// =====================================================
