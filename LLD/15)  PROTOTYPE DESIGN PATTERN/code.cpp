#include <iostream>
#include <string>
using namespace std;

/*
=========================================================
PROTOTYPE PATTERN - GAME NPC CLONING
=========================================================

GOAL:
Alien NPC banana expensive hai.

Instead of:
new NPC() 100 times ❌

Use:
1 template + clone() multiple times ✅
*/


// =====================================================
// 1) PROTOTYPE INTERFACE
// =====================================================

/*
Clone contract define karta hai.

Any cloneable object must support:
clone()
*/
class Cloneable {
public:
    virtual Cloneable* clone() const = 0;
    virtual ~Cloneable() {}
};


// =====================================================
// 2) CONCRETE PROTOTYPE
// =====================================================

/*
NPC is actual prototype.

This object acts as:
- heavy template
- clone source
*/
class NPC : public Cloneable {
public:
    string name;
    int health;
    int attack;
    int defense;

    /*
    HEAVY CONSTRUCTOR
    -----------------
    Real world:
    - DB load
    - AI config
    - stats calculation
    - animation setup
    */
    NPC(const string& name,
        int health,
        int attack,
        int defense) {

        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;

        cout << "Setting up template NPC '"
             << name << "'\n";
    }

    /*
    COPY CONSTRUCTOR
    ----------------
    clone() isi ka use karega.

    Existing object ka exact state copy.
    */
    NPC(const NPC& other) {
        name = other.name;
        health = other.health;
        attack = other.attack;
        defense = other.defense;

        cout << "Cloning NPC '" << name << "'\n";
    }

    /*
    PROTOTYPE METHOD
    ----------------
    Existing object ka copy banata.
    */
    Cloneable* clone() const override {
        return new NPC(*this);
    }

    void describe() {
        cout << "NPC " << name
             << " [HP=" << health
             << " ATK=" << attack
             << " DEF=" << defense
             << "]\n";
    }

    /*
    Clone customize karne ke liye setters
    */
    void setName(const string& n) {
        name = n;
    }

    void setHealth(int h) {
        health = h;
    }

    void setAttack(int a) {
        attack = a;
    }

    void setDefense(int d) {
        defense = d;
    }
};


// =====================================================
// 3) CLIENT WORKFLOW
// =====================================================
int main() {

    /*
    STEP 1:
    One heavy template object
    */
    NPC* alien = new NPC("Alien", 30, 5, 2);

    /*
    STEP 2:
    Exact clone
    */
    NPC* alienCopied1 =
        dynamic_cast<NPC*>(alien->clone());

    alienCopied1->describe();

    /*
    STEP 3:
    Clone + tweak variant
    */
    NPC* alienCopied2 =
        dynamic_cast<NPC*>(alien->clone());

    alienCopied2->setName("Powerful Alien");
    alienCopied2->setHealth(50);

    alienCopied2->describe();

    return 0;
}


/*
=========================================================
RUNTIME FLOW
=========================================================

1) Template Alien created
2) clone() called
3) copy constructor runs
4) exact copy created
5) setters tweak variant
6) reused efficiently

This is Prototype 💯
=========================================================
*/