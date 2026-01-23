#include <iostream>
using namespace std;

/*
=========================================================
        HAS-A + POLYMORPHISM MASTER NOTES FILE
=========================================================

GOAL:
-----
We want to build a Car.
Car should work with DIFFERENT engines without changing Car code.

That is achieved using:
1. Interface (Engine)
2. HAS-A relationship (Car HAS-A Engine)
3. Polymorphism (runtime decision)

---------------------------------------------------------

KEY IDEA:
---------
Car should NOT care which engine it has.
It only cares that the engine can "start()".

So Car depends on ABSTRACTION, not on concrete class.

---------------------------------------------------------
*/


/*
=========================================================
STEP 1: CREATE INTERFACE (ABSTRACT CLASS)
=========================================================

Engine is NOT a real object.
It is a RULE BOOK.

It says:
"Any engine must implement start()"
*/

class Engine {
public:
    // Pure virtual function -> makes this an interface
    virtual void start() = 0;

    // Always good practice
    virtual ~Engine() {}
};


/*
=========================================================
STEP 2: CREATE DIFFERENT IMPLEMENTATIONS
=========================================================

These are REAL engines.
They FOLLOW the Engine rules.
*/


class PetrolEngine : public Engine {
public:
    void start() override {
        cout << "Petrol Engine: Ignition started...\n";
    }
};


class DieselEngine : public Engine {
public:
    void start() override {
        cout << "Diesel Engine: Heating plugs ON...\n";
    }
};


class ElectricEngine : public Engine {
public:
    void start() override {
        cout << "Electric Engine: Power flowing from battery...\n";
    }
};


/*
=========================================================
STEP 3: CREATE CAR (HAS-A RELATIONSHIP)
=========================================================

IMPORTANT LINE:
--------------
Engine* engine;

This means:
Car HAS-A Engine.

Not:
Car IS-A Engine.

Car does NOT create engine.
Car RECEIVES engine from outside.

This is called:
Dependency Injection.
*/

class Car {
private:
    Engine* engine;   // HAS-A relationship

public:
    /*
    Constructor:

    We pass engine from outside and store it.

    Flow:
    -----
    main() creates engine
    main() passes engine to Car
    Car stores it
    */
    Car(Engine* eng) {
        engine = eng;
    }

    void startCar() {
        cout << "Car checking engine...\n";

        // Polymorphism happens here
        engine->start();

        cout << "Car is running...\n\n";
    }
};


/*
=========================================================
STEP 4: MAIN FUNCTION (CLIENT CODE)
=========================================================
*/

int main() {

    /*
    We create DIFFERENT engines.

    NOTE:
    -----
    Object is real class.
    Pointer type is interface.
    */

    Engine* petrol = new PetrolEngine();
    Engine* diesel = new DieselEngine();
    Engine* electric = new ElectricEngine();


    /*
    We inject engines into Car.

    SAME Car class.
    DIFFERENT behavior.
    */

    Car car1(petrol);
    Car car2(diesel);
    Car car3(electric);


    /*
    Runtime Polymorphism:
    ---------------------
    Same function call.
    Different output.
    */

    car1.startCar();
    car2.startCar();
    car3.startCar();


    // cleanup
    delete petrol;
    delete diesel;
    delete electric;

    return 0;
}


/*
=========================================================
FINAL MEMORY NOTES
=========================================================

1. Interface defines WHAT to do.
2. Class defines HOW to do.
3. Car HAS-A Engine.
4. Engine is injected via constructor.
5. engine->start() decides at runtime.
6. Same Car, different behavior.

RULE TO REMEMBER:
-----------------
If something can change -> make it interface -> use HAS-A.

=========================================================
*/
