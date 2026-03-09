#include <iostream>
using namespace std;

/*
==========================================================
 STRATEGY DESIGN PATTERN - ENGINE EXAMPLE (C++)
==========================================================

 PROBLEM:
 Car ko kaunsa engine use karna hai (Petrol/Diesel/Electric)
 ye runtime par decide hota hai.

 BAD APPROACH:
 if(engineType == "petrol") ...
 else if(engineType == "diesel") ...
 else if(engineType == "electric") ...

 ISSUE:
 - Too many if-else
 - Hard to extend
 - Violates Open/Closed Principle

 SOLUTION:
 Use Strategy Pattern.

 IDEA:
 - Engine -> Strategy Interface
 - PetrolEngine, DieselEngine, ElectricEngine -> Concrete Strategies
 - Car -> Context (uses strategy)
==========================================================
*/


/*
==========================================================
 STEP 1: STRATEGY INTERFACE
----------------------------------------------------------
This defines the common behavior for all engines.
Car will talk only to this interface.
==========================================================
*/
class Engine {
public:
    virtual void start() = 0;     // Each engine must implement this
    virtual ~Engine() {}          // Virtual destructor for safety
};


/*
==========================================================
 STEP 2: CONCRETE STRATEGIES
----------------------------------------------------------
These are actual implementations of Engine.
Each one provides its own behavior.
==========================================================
*/

class PetrolEngine : public Engine {
public:
    void start() override {
        cout << "[PetrolEngine] Starting petrol engine..." << endl;
    }
};

class DieselEngine : public Engine {
public:
    void start() override {
        cout << "[DieselEngine] Starting diesel engine..." << endl;
    }
};

class ElectricEngine : public Engine {
public:
    void start() override {
        cout << "[ElectricEngine] Starting electric engine..." << endl;
    }
};


/*
==========================================================
 STEP 3: CONTEXT CLASS
----------------------------------------------------------
Car does NOT know which engine it has.
It only knows it has an Engine pointer.
Behavior is delegated to strategy.
==========================================================
*/
class Car {
private:
    Engine* engine;   // Strategy pointer

public:
    // Constructor injection
    Car(Engine* e) {
        engine = e;
    }

    // Runtime switching of strategy
    void setEngine(Engine* e) {
        engine = e;
    }

    void drive() {
        if (!engine) {
            cout << "No engine set!" << endl;
            return;
        }

        engine->start();                 // Delegation to strategy
        cout << "Car is driving...\n" << endl;
    }
};


/*
==========================================================
 STEP 4: CLIENT CODE
----------------------------------------------------------
Here we create strategies using new and switch them
at runtime.
==========================================================
*/
int main() {

    // Creating strategies dynamically
    Engine* petrol   = new PetrolEngine();
    Engine* diesel   = new DieselEngine();
    Engine* electric = new ElectricEngine();

    // Car uses Petrol engine first
    Car car(petrol);
    car.drive();

    // Switch to Diesel at runtime
    car.setEngine(diesel);
    car.drive();

    // Switch to Electric at runtime
    car.setEngine(electric);
    car.drive();

    // Clean up (important in interviews)
    delete petrol;
    delete diesel;
    delete electric;

    return 0;
}
