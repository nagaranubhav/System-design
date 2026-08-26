#include <iostream>
using namespace std;

/*
===============================================================
DECORATOR DESIGN PATTERN (FULL CODE + DEEP EXPLANATION NOTES)
===============================================================

Goal:
-----
Hum ek Coffee system banana chahte hain jaha customer runtime par
coffee me toppings add kar sake.

Example:
Simple Coffee -> 5
Coffee + Milk -> 7
Coffee + Milk + Chocolate -> 10

Problem Without Decorator:
--------------------------
Agar inheritance use kare:

class MilkCoffee
class ChocolateCoffee
class MilkChocolateCoffee
class MilkChocolateCreamCoffee

Classes explode ho jayengi (2^n combinations).

Solution:
---------
Decorator Pattern.

Idea:
-----
Object ko wrap karo aur behaviour add karo.

Structure Example:

ChocolateDecorator
        ↓
MilkDecorator
        ↓
SimpleCoffee
*/


/*
===============================================================
1. COMPONENT (INTERFACE)
===============================================================

Sabse pehle ek common interface define karte hain.

Ye batata hai ki har Coffee object me ye functions honge:

1. getDescription()
2. cost()

Important:
-----------
=0 ka matlab hai pure virtual function.

Iska matlab:
- ye class abstract hai
- iska object nahi banega
- jo bhi subclass banegi usko ye methods implement karne padenge
*/

class Coffee {
public:

    // runtime polymorphism ke liye virtual
    virtual string getDescription() = 0;

    virtual int cost() = 0;

};


/*
===============================================================
2. CONCRETE COMPONENT
===============================================================

Ye actual base object hai.

Matlab ye simple coffee hai jisme koi toppings nahi hai.
*/

class SimpleCoffee : public Coffee {

public:

    // base description
    string getDescription() {
        return "Simple Coffee";
    }

    // base cost
    int cost() {
        return 5;
    }
};


/*
===============================================================
3. DECORATOR BASE CLASS
===============================================================

Ye decorator pattern ka core part hai.

IMPORTANT IDEA:
---------------
Decorator bhi Coffee hi hona chahiye.

Isliye:

CoffeeDecorator IS-A Coffee

Aur decorator ke paas ek aur Coffee object hota hai.

Diagram:

CoffeeDecorator
       ↓
    Coffee
*/

class CoffeeDecorator : public Coffee {

protected:

    // ye pointer wrapped object ko store karega
    Coffee* coffee;

public:

    /*
    Constructor

    Jab bhi decorator banega usko ek Coffee object diya jayega
    jise wo wrap karega.

    Example:

    MilkDecorator(simpleCoffee)
    */

    CoffeeDecorator(Coffee* c) {
        coffee = c;
    }

    /*
    DEFAULT FORWARDING IMPLEMENTATION

    Ye line bahut important hai.

    Ye function call ko wrapped object ko forward karta hai.

    Matlab decorator khud kuch nahi kar raha,
    bas next object ko call kar raha hai.

    Isko bolte hain delegation.
    */

    string getDescription() {
        return coffee->getDescription();
    }

    int cost() {
        return coffee->cost();
    }

};


/*
===============================================================
4. MILK DECORATOR
===============================================================

Ye CoffeeDecorator ko inherit karta hai.

Iska kaam hai:
- behaviour add karna
- wrapped object ko call karna
*/

class MilkDecorator : public CoffeeDecorator {

public:

    /*
    Constructor

    : CoffeeDecorator(c)

    Matlab parent constructor call karo aur coffee pointer
    initialize karo.

    Ye line actually parent ko batati hai ki kaunsa object wrap
    karna hai.
    */

    MilkDecorator(Coffee* c) : CoffeeDecorator(c) {}

    /*
    Description me Milk add karna
    */

    string getDescription() {

        /*
        Important:

        coffee->getDescription()

        ye next object ko call karega.

        Agar chain hai:

        Chocolate
            ↓
        Milk
            ↓
        SimpleCoffee

        To yaha call Milk se SimpleCoffee ko jayega.
        */

        return coffee->getDescription() + " + Milk";
    }

    /*
    Cost me Milk ka price add
    */

    int cost() {

        /*
        Flow:

        coffee->cost()

        next object ka cost return karega.

        Fir usme milk ka price add hoga.
        */

        return coffee->cost() + 2;
    }

};


/*
===============================================================
5. CHOCOLATE DECORATOR
===============================================================

Same concept as MilkDecorator.
*/

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


/*
===============================================================
MAIN FUNCTION
===============================================================
*/

int main() {

    /*
    STEP 1
    --------

    Base object create.

    Memory:

    SimpleCoffee
    cost = 5
    */

    Coffee* coffee = new SimpleCoffee();


    /*
    STEP 2
    --------

    MilkDecorator wrap karta hai SimpleCoffee ko.

    Structure:

    MilkDecorator
        ↓
    SimpleCoffee
    */

    coffee = new MilkDecorator(coffee);


    /*
    STEP 3
    --------

    ChocolateDecorator wrap karta hai MilkDecorator ko.

    Final structure:

    ChocolateDecorator
            ↓
       MilkDecorator
            ↓
       SimpleCoffee
    */

    coffee = new ChocolateDecorator(coffee);


    /*
    STEP 4
    --------

    Description print
    */

    cout << coffee->getDescription() << endl;


    /*
    STEP 5
    --------

    Cost print
    */

    cout << coffee->cost() << endl;

}



/*
===============================================================
IMPORTANT DOUBT NOTES (YOUR QUESTION)
===============================================================

Question:
---------
CoffeeDecorator me implementation kyu di hai?

Hum direct concrete decorators me call kar rahe hain na?


Answer:
-------

CoffeeDecorator ka kaam hai DEFAULT FORWARDING.

Matlab:

agar koi decorator behaviour add nahi karta
toh call next object ko forward ho jaye.

Example:

ChocolateDecorator
        ↓
MilkDecorator
        ↓
SimpleCoffee

Call flow:

coffee->cost()

Step1
ChocolateDecorator::cost()

return coffee->cost() + 3

coffee = MilkDecorator


Step2
MilkDecorator::cost()

return coffee->cost() + 2

coffee = SimpleCoffee


Step3
SimpleCoffee::cost()

return 5


Return chain:

5
5 + 2 = 7
7 + 3 = 10



===============================================================
KEY IDEA OF DECORATOR PATTERN
===============================================================

Decorator pattern = Wrapper Pattern

Har decorator:

1. wrapped object ko store karta hai
2. call ko next object ko forward karta hai
3. extra behaviour add karta hai



===============================================================
VISUAL STRUCTURE
===============================================================

ChocolateDecorator
        |
        v
   MilkDecorator
        |
        v
   SimpleCoffee


Function call flow:

coffee->cost()

ChocolateDecorator
        ↓
MilkDecorator
        ↓
SimpleCoffee


Return flow:

5
7
10



===============================================================
REAL LIFE ANALOGY
===============================================================

Burger

Base burger = 100

Add cheese
Add mayo
Add paneer

Structure:

Paneer
  ↓
Mayo
  ↓
Cheese
  ↓
Burger


Price calculation:

Burger
+ cheese
+ mayo
+ paneer


===============================================================
CORE PRINCIPLE FOLLOWED
===============================================================

Open Closed Principle

Open for extension
Closed for modification


===============================================================
SHORT MEMORY TRICK
===============================================================

Decorator Pattern:

Wrapper + Same Interface + Behaviour Add
*/