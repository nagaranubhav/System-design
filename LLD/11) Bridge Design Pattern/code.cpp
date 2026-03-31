#include <iostream>
#include <string>

using namespace std;

/*
=========================================================
BRIDGE PATTERN IMPLEMENTATION
=========================================================

We have 2 dimensions:
1) Cars (Sedan, SUV)        → ABSTRACTION (HLL)
2) Engines (Petrol, Diesel) → IMPLEMENTATION (LLL)

Instead of:
PetrolSedan, DieselSUV, etc (class explosion ❌)

We use:
Car HAS-A Engine ✅
*/


// =====================================================
// IMPLEMENTATION HIERARCHY (LOW LEVEL LAYER)
// =====================================================

/*
Engine is IMPLEMENTOR interface.

Ye define karta hai:
"engine ka behavior kya hoga"

Car ko farak nahi padta:
engine petrol hai ya electric

Car sirf bolta:
engine.start()
*/
class Engine {
public:
    virtual void start() = 0;
    virtual ~Engine() {}
};


/*
Concrete Implementations

Each engine apna specific behavior define karta hai.

Ye completely independent hai Car se.
*/
class PetrolEngine : public Engine {
public:
    void start() override {
        cout << "Petrol engine starting with ignition!" << endl;
    }
};

class DieselEngine : public Engine {
public:
    void start() override {
        cout << "Diesel engine roaring to life!" << endl;
    }
};

class ElectricEngine : public Engine {
public:
    void start() override {
        cout << "Electric engine powering up silently!" << endl;
    }
};


// =====================================================
// ABSTRACTION HIERARCHY (HIGH LEVEL LAYER)
// =====================================================

/*
Car is ABSTRACTION.

Important:
Car HAS-A Engine

This is the BRIDGE 💡

Car abstraction ko implementation se jodta hai.
*/
class Car {
protected:
    Engine* engine;

public:
    /*
    Constructor injection:
    Runtime pe engine inject kar sakte hain.

    This is dependency injection 🔥
    */
    Car(Engine* e) {
        engine = e;
    }

    /*
    High level behavior:
drive()

Actual implementation:
engine.start()

So abstraction delegates work to implementation.
    */
    virtual void drive() = 0;
};


/*
Refined Abstraction

Sedan car ka behavior define karta hai.

Notice:
Sedan ko engine type ka kuch pata nahi.
*/
class Sedan : public Car {
public:
    Sedan(Engine* e) : Car(e) {}

    void drive() override {
        engine->start();  // delegate to implementation
        cout << "Driving a Sedan on the highway." << endl;
    }
};


/*
Another refined abstraction

SUV ka behavior alag hai,
but engine reuse ho raha hai.
*/
class SUV : public Car {
public:
    SUV(Engine* e) : Car(e) {}

    void drive() override {
        engine->start();  // same interface, different engine possible
        cout << "Driving an SUV off-road." << endl;
    }
};


// =====================================================
// CLIENT CODE
// =====================================================

/*
Client combines both dimensions dynamically.

This is POWER of Bridge:
Any car + any engine combination possible at runtime.
*/
int main() {

    // -----------------------------------------------
    // ENGINE CREATION (IMPLEMENTATION OBJECTS)
    // -----------------------------------------------
    Engine* petrolEng = new PetrolEngine();
    Engine* dieselEng = new DieselEngine();
    Engine* electricEng = new ElectricEngine();

    // -----------------------------------------------
    // CAR CREATION (ABSTRACTION OBJECTS)
    // -----------------------------------------------

    /*
    Mixing combinations dynamically:

    Sedan + Petrol
    SUV + Electric
    SUV + Diesel

    No new classes needed 🔥
    */
    Car* mySedan = new Sedan(petrolEng);
    Car* mySUV = new SUV(electricEng);
    Car* yourSUV = new SUV(dieselEng);

    // -----------------------------------------------
    // EXECUTION
    // -----------------------------------------------

    /*
    Flow:
    drive() -> engine->start()

    Abstraction calls implementation
    */
    mySedan->drive();
    // Output:
    // Petrol engine starting...
    // Driving a Sedan...

    mySUV->drive();
    // Electric + SUV

    yourSUV->drive();
    // Diesel + SUV


    // -----------------------------------------------
    // CLEANUP (IMPORTANT)
    // -----------------------------------------------
    /*
    Memory leak avoid karne ke liye delete karna chahiye.

    (commented currently)
    */
    // delete mySedan;
    // delete mySUV;
    // delete yourSUV;

    return 0;
}


/*
=========================================================
FINAL UNDERSTANDING
=========================================================

2 Dimensions:
- Car type
- Engine type

Bridge Pattern:
Car HAS-A Engine

Instead of inheritance explosion,
we use composition.

Result:
Flexible, scalable, clean architecture.

=========================================================
*/