#include <iostream>
using namespace std;

// =====================================================
//            FACTORY PATTERN - VEHICLE EXAMPLE
// =====================================================

// --------------------
// STEP 1: Interface
// --------------------
// Ye common contract hai.
// Jo bhi Vehicle banega usme drive() hona hi chahiye.
// Client sirf Vehicle ko jaanta hai, concrete class ko nahi.
class Vehicle {
public:
    virtual void drive() = 0;   // common behavior
    virtual ~Vehicle() {}       // safe deletion
};

// --------------------
// STEP 2: Concrete Classes
// --------------------
// Ye real implementations hain.
// Sab Vehicle hain, par chalne ka tareeka alag-alag hai.

class Bike : public Vehicle {
public:
    void drive() override {
        cout << "Driving Bike\n";
    }
};

class Car : public Vehicle {
public:
    void drive() override {
        cout << "Driving Car\n";
    }
};

class Truck : public Vehicle {
public:
    void drive() override {
        cout << "Driving Truck\n";
    }
};

// --------------------
// STEP 3: Factory
// --------------------
// Factory ka kaam sirf object banana hai.
// Client yaha kabhi new Bike(), new Car() nahi likhega.
// Factory decide karegi kaunsa object banana hai.

class VehicleFactory {
public:
    static Vehicle* getVehicle(const string& type) {

        // new keyword heap me object banata hai
        // aur uska ADDRESS return karta hai.
        // Isliye return type Vehicle* hota hai.

        if (type == "bike") {
            return new Bike();      // address of Bike
        } 
        else if (type == "car") {
            return new Car();       // address of Car
        } 
        else if (type == "truck") {
            return new Truck();     // address of Truck
        }

        return nullptr;
    }
};

// --------------------
// STEP 4: Client
// --------------------
// Client ko sirf Factory aur Interface pata hai.
// Client ko concrete class ka idea nahi.

int main() {

    // Client bolta: mujhe bike chahiye
    Vehicle* v1 = VehicleFactory::getVehicle("bike");

    // Polymorphism:
    // v1 ka type Vehicle* hai
    // par point kar raha hai Bike ko
    // runtime pe Bike::drive() chalega
    v1->drive();

    // Client bolta: mujhe truck chahiye
    Vehicle* v2 = VehicleFactory::getVehicle("truck");
    v2->drive();

    return 0;
}

// --------------------
// REVISION POINTS FROM THIS EXAMPLE
// --------------------
// Factory decides WHAT to create.
// Client never uses new.
// new returns ADDRESS -> so pointer (*) is used.
// Base pointer -> Derived object (polymorphism).
// Object slicing avoid hoti hai.
// Loose coupling milti hai.
// =====================================================
