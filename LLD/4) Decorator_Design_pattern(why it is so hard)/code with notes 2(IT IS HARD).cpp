# ============================================================
# DECORATOR DESIGN PATTERN
# UML DIAGRAM + COMPLETE EXPLANATION
# ============================================================

/*
================================================================
1. DECORATOR DESIGN PATTERN KYA HAI?
================================================================

Decorator Pattern ka main purpose hai:

    "Existing object ko modify kiye bina usme dynamically
     extra functionality add karna."

Simple language me:

Maan lo humare paas ek Coffee hai.

    Coffee
       |
       +---- Basic Coffee
              Price = ₹50

Ab customer bolta hai:

    + Milk      -> ₹60
    + Sugar     -> ₹65
    + Whipped   -> ₹80

Problem:

Agar hum har combination ke liye alag class banayenge:

    MilkCoffee
    SugarCoffee
    MilkSugarCoffee
    MilkSugarWhippedCoffee
    ...

toh classes ki number bahut zyada badh jayegi.

Decorator Pattern bolta hai:

    Basic Coffee
        ↓
    Milk Decorator
        ↓
    Sugar Decorator
        ↓
    Whipped Cream Decorator

Har decorator existing coffee ko "wrap" karega aur
usme apni responsibility add karega.

================================================================
2. UML DIAGRAM
================================================================

                         <<interface>>
                       ┌─────────────────┐
                       │    Beverage     │
                       ├─────────────────┤
                       │ + getDescription()
                       │ + getCost()      │
                       └────────┬─────────┘
                                ▲
                                │ implements
                  ┌─────────────┴─────────────┐
                  │                           │
                  │                           │
        ┌─────────┴──────────┐      ┌────────┴──────────────┐
        │    Espresso        │      │  BeverageDecorator    │
        ├────────────────────┤      ├───────────────────────┤
        │ - cost             │      │ # beverage            │
        ├────────────────────┤      ├───────────────────────┤
        │ + getDescription() │      │ + getDescription()    │
        │ + getCost()        │      │ + getCost()           │
        └────────────────────┘      └───────────┬───────────┘
                                                ▲
                                                │ extends
                           ┌────────────────────┼────────────────────┐
                           │                    │                    │
                 ┌─────────┴─────────┐ ┌───────┴─────────┐ ┌───────┴────────────┐
                 │   MilkDecorator   │ │ SugarDecorator  │ │ WhippedCreamDecorator│
                 ├───────────────────┤ ├─────────────────┤ ├─────────────────────┤
                 │ + getDescription()│ │ + getDescription()│ │ + getDescription() │
                 │ + getCost()       │ │ + getCost()      │ │ + getCost()        │
                 └───────────────────┘ └─────────────────┘ └─────────────────────┘


IMPORTANT RELATIONSHIP:

Beverage
   ↑
   │
BeverageDecorator
   │
   ├── MilkDecorator
   ├── SugarDecorator
   └── WhippedCreamDecorator


BeverageDecorator ke andar:

        BeverageDecorator
        ┌─────────────────────┐
        │ Beverage* beverage  │
        └──────────┬──────────┘
                   │
                   │ HAS-A
                   ▼
              Beverage


Yahi Decorator Pattern ka sabse important part hai:

    Decorator IS-A Beverage
    AND
    Decorator HAS-A Beverage


================================================================
3. HAR CLASS KYON BANAYI?
================================================================


---------------------------------------------------------------
A. Beverage Interface
---------------------------------------------------------------

class Beverage

Ye common contract hai.

Hum bol rahe hain:

"Har beverage ko apna description aur cost batana hi padega."

Methods:

    getDescription()
    getCost()


WHY?

Agar Beverage interface nahi banate toh:

MilkDecorator ko pata nahi chalega ki
uske andar ka object Coffee hai ya Tea ya ColdDrink.

Decorator ko generic banana hai.

Example:

    Beverage* beverage;

Ab ye kisi bhi Beverage ko hold kar sakta hai.

    Espresso
    Tea
    Cappuccino
    etc.


AGAR Beverage interface nahi banate:

Har decorator ko specific class ke saath tightly couple karna padega.

Example:

    MilkDecorator -> Espresso ke liye
    SugarDecorator -> Espresso ke liye

Phir Tea ko decorate karna mushkil ho jayega.

Isliye common interface zaroori hai.


---------------------------------------------------------------
B. Espresso
---------------------------------------------------------------

Espresso actual/basic object hai.

Ye original functionality provide karta hai.

Example:

    Espresso
    cost = ₹50
    description = "Espresso"


Isko Concrete Component bhi bolte hain.


IMPORTANT:

Decorator khud se beverage nahi banata.

Decorator existing Beverage ko modify/extend karta hai.


---------------------------------------------------------------
C. BeverageDecorator
---------------------------------------------------------------

Ye Decorator ka BASE CLASS hai.

Iske andar:

    Beverage* beverage;

Kyun?

Taaki decorator kisi bhi Beverage ko wrap kar sake.

Example:

    MilkDecorator(Espresso)

    SugarDecorator(MilkDecorator(Espresso))


Yahan:

MilkDecorator ke andar Espresso hai.

SugarDecorator ke andar MilkDecorator hai.


Ye possible hai kyunki:

MilkDecorator IS-A Beverage

Aur:

MilkDecorator HAS-A Beverage


Isliye:

    Beverage*
        |
        +--> Espresso
        +--> MilkDecorator
        +--> SugarDecorator


Sab ek hi type ki tarah behave kar sakte hain.


---------------------------------------------------------------
D. MilkDecorator
---------------------------------------------------------------

Iska kaam:

Existing beverage me Milk add karna.

Example:

    Espresso = ₹50

    MilkDecorator(Espresso)
        = ₹50 + ₹10
        = ₹60


Ye existing Espresso class ko modify nahi karta.

Bas usko wrap karta hai.


---------------------------------------------------------------
E. SugarDecorator
---------------------------------------------------------------

Existing beverage me Sugar add karta hai.

Example:

    MilkDecorator(Espresso)
        = ₹60

    SugarDecorator(MilkDecorator(Espresso))
        = ₹60 + ₹5
        = ₹65


---------------------------------------------------------------
F. WhippedCreamDecorator
---------------------------------------------------------------

Existing beverage me Whipped Cream add karta hai.

Example:

    SugarDecorator(MilkDecorator(Espresso))
        = ₹65

    WhippedCreamDecorator(...)
        = ₹65 + ₹15
        = ₹80


================================================================
4. DECORATOR PATTERN KA ACTUAL FLOW
================================================================

Suppose customer order karta hai:

    Espresso
    + Milk
    + Sugar
    + Whipped Cream


Hum object banayenge:

    Beverage* beverage = new Espresso();

                ↓

    beverage = new MilkDecorator(beverage);

                ↓

    beverage = new SugarDecorator(beverage);

                ↓

    beverage = new WhippedCreamDecorator(beverage);


Final structure:

        WhippedCreamDecorator
                 |
                 ▼
          SugarDecorator
                 |
                 ▼
           MilkDecorator
                 |
                 ▼
              Espresso


Ye ek WRAPPER CHAIN hai.


================================================================
5. getCost() KAISE FLOW KARTA HAI?
================================================================

Final object:

    WhippedCreamDecorator
            |
            ▼
      SugarDecorator
            |
            ▼
       MilkDecorator
            |
            ▼
         Espresso


Call:

    beverage->getCost();


Sabse pehle:

WhippedCreamDecorator::getCost()

    return beverage->getCost() + 15;


Lekin iska beverage hai:

    SugarDecorator


Toh SugarDecorator::getCost()

    return beverage->getCost() + 5;


Iska beverage:

    MilkDecorator


MilkDecorator:

    return beverage->getCost() + 10;


Iska beverage:

    Espresso


Espresso:

    return 50;


Ab return back:

    Espresso
       50

    Milk
       50 + 10 = 60

    Sugar
       60 + 5 = 65

    Whipped Cream
       65 + 15 = 80


FINAL COST:

    ₹80


================================================================
6. getDescription() KA FLOW
================================================================

Espresso:

    "Espresso"


MilkDecorator:

    "Espresso + Milk"


SugarDecorator:

    "Espresso + Milk + Sugar"


WhippedCreamDecorator:

    "Espresso + Milk + Sugar + Whipped Cream"


Final output:

    Espresso + Milk + Sugar + Whipped Cream
    Cost: ₹80


================================================================
7. AGAR DECORATOR PATTERN USE NAHI KARTE TOH?
================================================================

Suppose hum normal inheritance use karte.

Hume classes banani pad sakti hain:

    Espresso
    EspressoWithMilk
    EspressoWithSugar
    EspressoWithMilkAndSugar
    EspressoWithMilkAndSugarAndWhippedCream
    EspressoWithMilkAndWhippedCream
    EspressoWithSugarAndWhippedCream
    ...


Aur agar beverages bhi multiple hain:

    Espresso
    Tea
    Cappuccino
    ColdCoffee

Aur toppings:

    Milk
    Sugar
    Cream
    Chocolate


Combinations exponentially grow karenge.

Example:

    4 beverages × 2^4 toppings

Bahut saari classes ban sakti hain.


MAIN PROBLEM:

    CLASS EXPLOSION


Decorator Pattern is problem ko solve karta hai.


================================================================
8. DECORATOR USE KARNE KA BENEFIT
================================================================

Without Decorator:

    EspressoWithMilk
    EspressoWithSugar
    EspressoWithMilkAndSugar
    ...

With Decorator:

    Espresso
       ↓
    MilkDecorator
       ↓
    SugarDecorator
       ↓
    CreamDecorator


Ab runtime par combination decide kar sakte hain.


Customer:

    "Mujhe Espresso + Milk chahiye."

Code:

    new MilkDecorator(new Espresso());


Customer:

    "Mujhe Espresso + Sugar chahiye."

Code:

    new SugarDecorator(new Espresso());


Customer:

    "Mujhe Espresso + Milk + Sugar chahiye."

Code:

    new SugarDecorator(
        new MilkDecorator(
            new Espresso()
        )
    );


No new combination-specific class required.


================================================================
9. OPEN/CLOSED PRINCIPLE
================================================================

Decorator Pattern OCP ko support karta hai:

    Open for Extension
    Closed for Modification


Suppose kal hume Chocolate add karna hai.

Existing classes:

    Espresso
    MilkDecorator
    SugarDecorator

ko modify karne ki zaroorat nahi.


Bas:

    ChocolateDecorator

bana do.


Existing code safe rahega.

Ye SOLID perspective se bhi important benefit hai.


================================================================
10. IMPORTANT INTERVIEW POINT
================================================================

Interviewer agar pooche:

"Decorator aur inheritance me kya difference hai?"


Answer:

Inheritance:

    Functionality compile-time/class level par extend hoti hai.

Decorator:

    Functionality runtime par dynamically compose ki ja sakti hai.


Inheritance:

    Class combinations badh sakte hain.


Decorator:

    Multiple decorators ko chain karke
    behavior dynamically combine kar sakte hain.


Example:

    new MilkDecorator(
        new SugarDecorator(
            new Espresso()
        )
    );


================================================================
11. COMPLETE C++ CODE
================================================================

#include <iostream>
#include <string>

using namespace std;


// ============================================================
// 1. COMPONENT
// ============================================================
//
// Beverage ek common interface hai.
//
// Har beverage ko:
//     1. description deni hogi
//     2. cost deni hogi
//
// Decorator isi interface par depend karega.
// ============================================================

class Beverage {

public:

    virtual string getDescription() = 0;

    virtual double getCost() = 0;

    virtual ~Beverage() = default;
};


// ============================================================
// 2. CONCRETE COMPONENT
// ============================================================
//
// Espresso actual/basic beverage hai.
//
// Ye original functionality provide karta hai.
//
// Ye kisi decorator ke bina bhi independently kaam kar sakta hai.
// ============================================================

class Espresso : public Beverage {

public:

    string getDescription() override {

        return "Espresso";
    }

    double getCost() override {

        return 50.0;
    }
};


// ============================================================
// 3. DECORATOR BASE CLASS
// ============================================================
//
// BeverageDecorator bhi Beverage hai.
//
// Isliye:
//     BeverageDecorator IS-A Beverage
//
// Saath hi iske andar ek Beverage hai:
//
//     BeverageDecorator HAS-A Beverage
//
// Ye HAS-A relationship hi wrapping enable karti hai.
// ============================================================

class BeverageDecorator : public Beverage {

protected:

    Beverage* beverage;

public:

    BeverageDecorator(Beverage* beverage) {

        this->beverage = beverage;
    }
};


// ============================================================
// 4. MILK DECORATOR
// ============================================================
//
// Existing beverage me Milk add karta hai.
//
// Example:
//
//     Espresso
//     +
//     Milk
//
// Cost:
//     Espresso = 50
//     Milk    = 10
//     Total   = 60
// ============================================================

class MilkDecorator : public BeverageDecorator {

public:

    MilkDecorator(Beverage* beverage)
        : BeverageDecorator(beverage) {
    }


    string getDescription() override {

        return beverage->getDescription() + " + Milk";
    }


    double getCost() override {

        return beverage->getCost() + 10.0;
    }
};


// ============================================================
// 5. SUGAR DECORATOR
// ============================================================
//
// Existing beverage me Sugar add karta hai.
// ============================================================

class SugarDecorator : public BeverageDecorator {

public:

    SugarDecorator(Beverage* beverage)
        : BeverageDecorator(beverage) {
    }


    string getDescription() override {

        return beverage->getDescription() + " + Sugar";
    }


    double getCost() override {

        return beverage->getCost() + 5.0;
    }
};


// ============================================================
// 6. WHIPPED CREAM DECORATOR
// ============================================================
//
// Existing beverage me Whipped Cream add karta hai.
// ============================================================

class WhippedCreamDecorator : public BeverageDecorator {

public:

    WhippedCreamDecorator(Beverage* beverage)
        : BeverageDecorator(beverage) {
    }


    string getDescription() override {

        return beverage->getDescription() + " + Whipped Cream";
    }


    double getCost() override {

        return beverage->getCost() + 15.0;
    }
};


// ============================================================
// 7. MAIN
// ============================================================

int main() {


    // --------------------------------------------------------
    // STEP 1:
    // Basic Espresso create kiya.
    //
    // Current object:
    //
    //     Espresso
    //
    // Cost = 50
    // --------------------------------------------------------

    Beverage* beverage = new Espresso();


    cout << beverage->getDescription() << endl;
    cout << "Cost: " << beverage->getCost() << endl;

    cout << "--------------------------" << endl;


    // --------------------------------------------------------
    // STEP 2:
    // Espresso ko Milk se decorate kiya.
    //
    // Structure:
    //
    //     MilkDecorator
    //           |
    //           ▼
    //        Espresso
    //
    // Cost:
    //
    //     50 + 10 = 60
    // --------------------------------------------------------

    beverage = new MilkDecorator(beverage);


    cout << beverage->getDescription() << endl;
    cout << "Cost: " << beverage->getCost() << endl;

    cout << "--------------------------" << endl;


    // --------------------------------------------------------
    // STEP 3:
    // Ab Milk wali coffee ko Sugar se decorate kiya.
    //
    // Structure:
    //
    //     SugarDecorator
    //           |
    //           ▼
    //     MilkDecorator
    //           |
    //           ▼
    //        Espresso
    //
    // Cost:
    //
    //     50 + 10 + 5 = 65
    // --------------------------------------------------------

    beverage = new SugarDecorator(beverage);


    cout << beverage->getDescription() << endl;
    cout << "Cost: " << beverage->getCost() << endl;

    cout << "--------------------------" << endl;


    // --------------------------------------------------------
    // STEP 4:
    // Ab Sugar wali coffee ko Whipped Cream se decorate kiya.
    //
    // Final structure:
    //
    //     WhippedCreamDecorator
    //             |
    //             ▼
    //       SugarDecorator
    //             |
    //             ▼
    //        MilkDecorator
    //             |
    //             ▼
    //          Espresso
    //
    // Cost:
    //
    //     50 + 10 + 5 + 15
    //     = 80
    // --------------------------------------------------------

    beverage = new WhippedCreamDecorator(beverage);


    cout << beverage->getDescription() << endl;
    cout << "Cost: " << beverage->getCost() << endl;


    return 0;
}


/*
================================================================
12. EXPECTED OUTPUT
================================================================

Espresso
Cost: 50

--------------------------

Espresso + Milk
Cost: 60

--------------------------

Espresso + Milk + Sugar
Cost: 65

--------------------------

Espresso + Milk + Sugar + Whipped Cream
Cost: 80


================================================================
13. FINAL OBJECT STRUCTURE
================================================================

Final line ke baad:

    beverage = new WhippedCreamDecorator(beverage);


Memory/object structure approximately:

    beverage
       |
       ▼
┌───────────────────────────────┐
│ WhippedCreamDecorator         │
│ cost addition = 15            │
│                               │
│ beverage ──────────────────┐  │
└─────────────────────────────│──┘
                              ▼
                    ┌──────────────────────┐
                    │ SugarDecorator       │
                    │ cost addition = 5    │
                    │                      │
                    │ beverage ─────────┐  │
                    └───────────────────│──┘
                                        ▼
                              ┌──────────────────┐
                              │ MilkDecorator    │
                              │ cost addition=10 │
                              │                  │
                              │ beverage ─────┐  │
                              └───────────────│──┘
                                             ▼
                                    ┌────────────────┐
                                    │ Espresso       │
                                    │ cost = 50      │
                                    └────────────────┘


================================================================
14. ONE-LINE MEMORY TRICK
================================================================

Decorator Pattern:

    "Object ko wrap karo,
     same interface maintain karo,
     aur wrapper ke through extra behavior add karo."


Formula:

    Component
        ↑
        |
    Decorator
        |
        +---- Concrete Decorator
        |
        +---- HAS-A Component


Most important interview line:

    "Decorator allows us to dynamically add responsibilities
     to an object without modifying its original class."


================================================================
15. INTERVIEW ME FLOW KAISE EXPLAIN KARNA HAI?
================================================================

Agar interviewer bole:

"Explain Decorator Pattern."


Tum bolo:

    "Decorator Pattern is a structural design pattern used
     to dynamically add responsibilities to an object without
     modifying its original class."

Then example:

    "For example, in a coffee ordering system, instead of
     creating separate classes for every combination of
     coffee and toppings, we can wrap a coffee object with
     MilkDecorator, SugarDecorator, CreamDecorator etc."

Then architecture:

    Beverage
        ↑
        |
    BeverageDecorator
        ↑
        |
    Concrete Decorators


Then key relationship:

    Decorator IS-A Beverage
    Decorator HAS-A Beverage


Then runtime composition:

    Espresso
       ↓
    MilkDecorator
       ↓
    SugarDecorator
       ↓
    WhippedCreamDecorator


And finally benefit:

    "This avoids class explosion and follows the
     Open/Closed Principle."


================================================================
16. SABSE IMPORTANT CONCEPT
================================================================

Decorator Pattern ko sirf diagram ki tarah yaad mat karo.

Isko ye flow samjho:

    ORIGINAL OBJECT
          ↓
       WRAP IT
          ↓
    ADD RESPONSIBILITY
          ↓
       WRAP AGAIN
          ↓
    ADD ANOTHER RESPONSIBILITY
          ↓
       FINAL OBJECT


Example:

    Espresso
       ↓
    + Milk
       ↓
    + Sugar
       ↓
    + Whipped Cream


Isi ko Decorator Pattern kehte hain.


================================================================
17. REAL WORLD EXAMPLES
================================================================

Decorator Pattern ka use conceptually yahan mil sakta hai:

    Coffee + toppings

    Pizza + toppings

    Notification
        + Email
        + SMS
        + Push

    File Stream
        + Compression
        + Encryption
        + Buffering

    Web Request
        + Authentication
        + Logging
        + Caching


Core idea har jagah same hai:

    Existing functionality
            +
    Additional functionality
            +
    Without modifying original object


================================================================
18. DECORATOR VS INHERITANCE — QUICK REVISION
================================================================

Inheritance:

    Parent
      ↓
    Child

    Behavior class hierarchy me fixed hota hai.


Decorator:

    Object
      ↓
    Decorator
      ↓
    Another Decorator
      ↓
    Another Decorator

    Behavior runtime par compose hota hai.


Therefore:

    Inheritance = "What class are you?"

    Decorator = "What extra responsibilities are
                  currently wrapped around you?"


================================================================
END
================================================================
*/