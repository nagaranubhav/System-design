#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////
// 1. COMPONENT (Interface)
// Base abstraction for Coffee
////////////////////////////////////////////////////////////
class Coffee {
public:
    virtual string getDescription() = 0;
    virtual int cost() = 0;
};

////////////////////////////////////////////////////////////
// 2. CONCRETE COMPONENT
// Actual basic coffee
////////////////////////////////////////////////////////////
class SimpleCoffee : public Coffee {
public:
    string getDescription() {
        return "Simple Coffee";
    }

    int cost() {
        return 5;
    }
};

////////////////////////////////////////////////////////////
// 3. DECORATOR BASE CLASS
// Wraps a Coffee object
////////////////////////////////////////////////////////////
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee;

public:
    CoffeeDecorator(Coffee* c) {
        coffee = c;
    }

    string getDescription() {
        return coffee->getDescription();
    }

    int cost() {
        return coffee->cost();
    }
};

////////////////////////////////////////////////////////////
// 4. CONCRETE DECORATOR - Milk
////////////////////////////////////////////////////////////
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* c) : CoffeeDecorator(c) {}

    string getDescription() {
        return coffee->getDescription() + " + Milk";
    }

    int cost() {
        return coffee->cost() + 2;
    }
};

////////////////////////////////////////////////////////////
// 5. CONCRETE DECORATOR - Chocolate
////////////////////////////////////////////////////////////
class ChocolateDecorator : public CoffeeDecorator {
public:
    ChocolateDecorator(Coffee* c) : CoffeeDecorator(c) {}

    string getDescription() {
        return coffee->getDescription() + " + Chocolate";
    }

    int cost() {
        return coffee->cost() + 3;
    }
};

////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////
int main() {

    Coffee* coffee = new SimpleCoffee();

    coffee = new MilkDecorator(coffee);

    coffee = new ChocolateDecorator(coffee);

    cout << coffee->getDescription() << endl;
    cout << coffee->cost() << endl;
}