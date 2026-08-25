# Strategy Design Pattern — Example
# Example: Payment System

Imagine an e-commerce application.

Customer can pay using:

    1. Credit Card
    2. UPI
    3. PayPal

------------------------------------------------------------
WITHOUT STRATEGY PATTERN
------------------------------------------------------------

class PaymentService {

    void pay(String type, double amount) {

        if(type == "CARD") {
            // Credit Card payment logic
        }
        else if(type == "UPI") {
            // UPI payment logic
        }
        else if(type == "PAYPAL") {
            // PayPal payment logic
        }
    }
};

Problem:

    Every new payment method requires modifying
    PaymentService.

    PaymentService becomes a huge if-else class.

------------------------------------------------------------
WITH STRATEGY PATTERN
------------------------------------------------------------

                ┌─────────────────────────────┐
                │      PaymentService         │
                ├─────────────────────────────┤
                │ - strategy: PaymentStrategy │
                ├─────────────────────────────┤
                │ + setStrategy()             │
                │ + makePayment()              │
                └──────────────┬──────────────┘
                               │
                               │ HAS-A
                               ▼
                ┌─────────────────────────────┐
                │     <<interface>>           │
                │     PaymentStrategy         │
                ├─────────────────────────────┤
                │ + pay(amount)               │
                └──────────────┬──────────────┘
                               △
                  ┌────────────┼────────────┐
                  │            │            │
              implements   implements   implements
                  │            │            │
        ┌─────────┴──────┐ ┌──┴─────────┐ ┌┴─────────────┐
        │ CreditCard     │ │ UPI        │ │ PayPal       │
        │ Strategy       │ │ Strategy   │ │ Strategy     │
        ├────────────────┤ ├────────────┤ ├──────────────┤
        │ + pay()        │ │ + pay()    │ │ + pay()      │
        └────────────────┘ └────────────┘ └──────────────┘


------------------------------------------------------------
C++ IMPLEMENTATION
------------------------------------------------------------

#include <iostream>
#include <memory>
using namespace std;


// ---------------------------------------------------------
// 1. Strategy Interface
// ---------------------------------------------------------

class PaymentStrategy {

public:

    virtual void pay(double amount) = 0;

    virtual ~PaymentStrategy() {}
};


// ---------------------------------------------------------
// 2. Concrete Strategy - Credit Card
// ---------------------------------------------------------

class CreditCardStrategy : public PaymentStrategy {

public:

    void pay(double amount) override {

        cout << "Paid Rs. " << amount
             << " using Credit Card\n";
    }
};


// ---------------------------------------------------------
// 3. Concrete Strategy - UPI
// ---------------------------------------------------------

class UPIStrategy : public PaymentStrategy {

public:

    void pay(double amount) override {

        cout << "Paid Rs. " << amount
             << " using UPI\n";
    }
};


// ---------------------------------------------------------
// 4. Concrete Strategy - PayPal
// ---------------------------------------------------------

class PayPalStrategy : public PaymentStrategy {

public:

    void pay(double amount) override {

        cout << "Paid Rs. " << amount
             << " using PayPal\n";
    }
};


// ---------------------------------------------------------
// 5. Context
// ---------------------------------------------------------

class PaymentService {

private:

    unique_ptr<PaymentStrategy> strategy;

public:

    void setStrategy(unique_ptr<PaymentStrategy> strategy) {

        this->strategy = move(strategy);
    }

    void makePayment(double amount) {

        strategy->pay(amount);
    }
};


// ---------------------------------------------------------
// 6. Client
// ---------------------------------------------------------

int main() {

    PaymentService paymentService;


    // Customer chooses Credit Card
    paymentService.setStrategy(
        make_unique<CreditCardStrategy>()
    );

    paymentService.makePayment(1000);


    // Later customer chooses UPI
    paymentService.setStrategy(
        make_unique<UPIStrategy>()
    );

    paymentService.makePayment(500);


    // Later customer chooses PayPal
    paymentService.setStrategy(
        make_unique<PayPalStrategy>()
    );

    paymentService.makePayment(2000);


    return 0;
}


------------------------------------------------------------
OUTPUT
------------------------------------------------------------

Paid Rs. 1000 using Credit Card
Paid Rs. 500 using UPI
Paid Rs. 2000 using PayPal


------------------------------------------------------------
HOW TO UNDERSTAND THIS AS AN INTERVIEWER
------------------------------------------------------------

PaymentService
       |
       | does NOT know
       | how payment works
       ↓
PaymentStrategy
       |
       | defines contract
       ↓
---------------------------------
|               |               |
CreditCard      UPI           PayPal
Strategy        Strategy      Strategy
---------------------------------

PaymentService only says:

    "Mujhe payment karni hai."

It does NOT say:

    "Payment UPI se kaise karni hai?"

That responsibility belongs to the concrete strategy.

------------------------------------------------------------
IMPORTANT RELATIONSHIPS
------------------------------------------------------------

PaymentService HAS-A PaymentStrategy

CreditCardStrategy IS-A PaymentStrategy

UPIStrategy IS-A PaymentStrategy

PayPalStrategy IS-A PaymentStrategy


------------------------------------------------------------
MOST IMPORTANT INTERVIEW POINT
------------------------------------------------------------

Strategy Pattern is useful when:

    1. We have multiple ways/algorithms
       to perform the same operation.

    2. These algorithms can change independently.

    3. We want to avoid large if-else / switch statements.

    4. We want to choose/change the algorithm
       at runtime.

Example:

    Payment
        → Credit Card
        → UPI
        → PayPal

    Sorting
        → QuickSort
        → MergeSort
        → HeapSort

    Navigation
        → Car
        → Bike
        → Walking

    Compression
        → ZIP
        → GZIP
        → 7-Zip


------------------------------------------------------------
ONE-LINE MEMORY TRICK
------------------------------------------------------------

Strategy Pattern =

    "Same job, different ways of doing it."

    Context
       ↓
    Strategy Interface
       ↓
    Different interchangeable algorithms


Instead of:

    "IF this algorithm → do this
     ELSE IF that algorithm → do that"

We do:

    "Give me whichever strategy you want,
     I'll execute it."