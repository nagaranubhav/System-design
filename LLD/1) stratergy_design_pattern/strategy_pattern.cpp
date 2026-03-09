
/*
=====================================================
 STRATEGY DESIGN PATTERN - COMPLETE C++ GUIDE
 Author: Anubhav nagar (Interview + GitHub Ready Notes)
=====================================================

👉 Goal:
Remove large if-else blocks and allow behavior to change at runtime.

👉 Example Used:
Payment System (UPI, Card, Wallet)

-----------------------------------------------------
 KEY IDEA:
 "Encapsulate algorithms and make them interchangeable"
-----------------------------------------------------
*/

#include <iostream>
using namespace std;

/*
=====================================================
 STEP 1: STRATEGY INTERFACE
-----------------------------------------------------
This is a common interface.
All payment types must follow this rule.
Context will talk only to this interface.
=====================================================
*/
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;  // pure virtual function
    virtual ~PaymentStrategy() {}       // virtual destructor
};

/*
=====================================================
 STEP 2: CONCRETE STRATEGIES
-----------------------------------------------------
These are actual implementations.
Each one defines its own behavior.
=====================================================
*/

class UPIPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "[UPI] Paid Rs." << amount << endl;
    }
};

class CardPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "[CARD] Paid Rs." << amount << endl;
    }
};

class WalletPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "[WALLET] Paid Rs." << amount << endl;
    }
};

/*
=====================================================
 STEP 3: CONTEXT CLASS
-----------------------------------------------------
This class does not know WHICH payment.
It only knows HOW to call strategy.
=====================================================
*/

class PaymentContext {
private:
    PaymentStrategy* strategy;

public:
    PaymentContext() {
        strategy = nullptr;
    }

    // Set strategy at runtime
    void setStrategy(PaymentStrategy* newStrategy) {
        strategy = newStrategy;
    }

    // Execute selected strategy
    void payAmount(int amount) {
        if (!strategy) {
            cout << "No Payment Strategy Selected!" << endl;
            return;
        }
        strategy->pay(amount);
    }
};

/*
=====================================================
 STEP 4: CLIENT CODE (MAIN)
-----------------------------------------------------
Here user selects behavior dynamically.
=====================================================
*/

int main() {

    PaymentContext context;

    UPIPayment upi;
    CardPayment card;
    WalletPayment wallet;

    // Runtime decision
    context.setStrategy(&upi);
    context.payAmount(500);

    context.setStrategy(&card);
    context.payAmount(1000);

    context.setStrategy(&wallet);
    context.payAmount(300);

    return 0;
}
