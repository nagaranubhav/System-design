#include <iostream>
#include <string>
using namespace std;

/*
=========================================================
STATE PATTERN - VENDING MACHINE
=========================================================

GOAL:
Vending machine ka behavior current state ke hisaab se change ho.

States:
1) NO_COIN
2) HAS_COIN
3) DISPENSING
4) SOLD_OUT

Instead of giant if-else,
har state apni class me logic rakhega.
*/


// Forward declaration
class VendingMachine;


// =====================================================
// 1) ABSTRACT STATE INTERFACE
// =====================================================

/*
Har state ko same operations support karni hain.

Important:
Each function next state return karti hai.

This makes transitions explicit 🔥
*/
class VendingState {
public:
    virtual VendingState* insertCoin(VendingMachine* machine, int coin) = 0;
    virtual VendingState* selectItem(VendingMachine* machine) = 0;
    virtual VendingState* dispense(VendingMachine* machine) = 0;
    virtual VendingState* returnCoin(VendingMachine* machine) = 0;
    virtual VendingState* refill(VendingMachine* machine, int quantity) = 0;

    virtual string getStateName() = 0;
};


// =====================================================
// 2) CONTEXT CLASS
// =====================================================

/*
VendingMachine is CONTEXT.

Responsibilities:
1) current state maintain karna
2) state objects store karna
3) transitions delegate karna
4) shared machine data store karna
*/
class VendingMachine {
private:
    VendingState* currentState;

    /*
    Shared machine data
    */
    int itemCount;
    int itemPrice;
    int insertedCoins;

    /*
    Reusable state objects
    */
    VendingState* noCoinState;
    VendingState* hasCoinState;
    VendingState* dispenseState;
    VendingState* soldOutState;

public:
    VendingMachine(int itemCount, int itemPrice);

    /*
    Delegation:
    current state decides behavior + next state
    */
    void insertCoin(int coin) {
        currentState = currentState->insertCoin(this, coin);
    }

    void selectItem() {
        currentState = currentState->selectItem(this);
    }

    void dispense() {
        currentState = currentState->dispense(this);
    }

    void returnCoin() {
        currentState = currentState->returnCoin(this);
    }

    void refill(int quantity) {
        currentState = currentState->refill(this, quantity);
    }
};


/*
=========================================================
3) CONCRETE STATES
=========================================================
*/


// -----------------------------------------------------
// NO COIN STATE
// -----------------------------------------------------
/*
Machine idle hai.
Coin insert ka wait.
*/
class NoCoinState : public VendingState {
public:
    VendingState* insertCoin(VendingMachine* machine, int coin) override {
        /*
        Coin insert hote hi next state:
        HAS_COIN
        */
        machine->setInsertedCoin(coin);
        return machine->getHasCoinState();
    }

    /*
    Coin ke bina item select invalid
    */
    VendingState* selectItem(VendingMachine* machine) override {
        cout << "Insert coin first\n";
        return machine->getNoCoinState();
    }
};


// -----------------------------------------------------
// HAS COIN STATE
// -----------------------------------------------------
/*
Ab machine ke paas sufficient ya insufficient balance ho sakta.
*/
class HasCoinState : public VendingState {
public:
    VendingState* selectItem(VendingMachine* machine) override {

        /*
        Price check
        */
        if (machine->getInsertedCoin() >= machine->getPrice()) {

            /*
            Next:
            DISPENSING
            */
            machine->setInsertedCoin(0);
            return machine->getDispenseState();
        }

        /*
        Stay in same state
        */
        return machine->getHasCoinState();
    }
};


// -----------------------------------------------------
// DISPENSING STATE
// -----------------------------------------------------
/*
Item nikal raha hai
*/
class DispenseState : public VendingState {
public:
    VendingState* dispense(VendingMachine* machine) override {

        /*
        Actual stock reduce
        */
        machine->decrementItemCount();

        /*
        Next state depends on inventory
        */
        if (machine->getItemCount() > 0) {
            return machine->getNoCoinState();
        }

        return machine->getSoldOutState();
    }
};


// -----------------------------------------------------
// SOLD OUT STATE
// -----------------------------------------------------
/*
No inventory left
*/
class SoldOutState : public VendingState {
public:
    VendingState* refill(VendingMachine* machine, int quantity) override {

        /*
        Refill transitions back to NO_COIN
        */
        machine->incrementItemCount(quantity);
        return machine->getNoCoinState();
    }
};


/*
=========================================================
4) STATE FLOW
=========================================================

NO_COIN
   |
insertCoin
   v
HAS_COIN
   |
selectItem
   v
DISPENSING
   |
dispense
   v
NO_COIN / SOLD_OUT

=========================================================
*/


// =====================================================
// 5) MAIN FLOW
// =====================================================
int main() {

    /*
    Initial:
    2 items
    Rs 20 each
    */
    VendingMachine machine(2, 20);

    /*
    Scenario walkthrough:
    */
    machine.insertCoin(10);   // NO_COIN -> HAS_COIN
    machine.insertCoin(10);   // stay HAS_COIN
    machine.selectItem();     // HAS_COIN -> DISPENSING
    machine.dispense();       // DISPENSING -> NO_COIN

    return 0;
}


/*
=========================================================
BIGGEST LEARNING
=========================================================

Behavior same method pe depend nahi kar raha,
CURRENT STATE pe depend kar raha.

That is STATE PATTERN 💯
=========================================================
*/