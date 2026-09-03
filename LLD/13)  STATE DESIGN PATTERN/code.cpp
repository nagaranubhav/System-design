# ================================================================
#             STATE DESIGN PATTERN — VENDING MACHINE
#             COMPLETE CODE EXPLANATION IN HINGLISH
# ================================================================


# ================================================================
# 0. SABSE PEHLE — YE CODE KAR KYA RAHA HAI?
# ================================================================

/*
    Yrr is pure code ko samajhne se pehle ek simple cheez
    dimaag mein bitha le:

    Vending Machine ek hi object hai.

    Lekin machine ki CURRENT CONDITION/state badalti rehti hai.

        NO COIN
           |
           | coin insert
           v
        HAS COIN
           |
           | item select
           v
        DISPENSING
           |
           | item dispense
           v
        NO COIN
           |
           | agar stock 0 ho gaya
           v
        SOLD OUT


    Ab problem ye hai ki:

        insertCoin()
        selectItem()
        dispense()
        returnCoin()
        refill()

    in methods ka behavior har state mein different hoga.

    Example:

    ---------------------------------------------------------------

    NO COIN mein:

        insertCoin()  -> allowed
        selectItem()  -> "coin daalo"
        dispense()    -> allowed nahi
        returnCoin()  -> kuch nahi

    ---------------------------------------------------------------

    HAS COIN mein:

        insertCoin()  -> balance badhao
        selectItem()  -> price check karo
        dispense()    -> abhi direct nahi

    ---------------------------------------------------------------

    DISPENSING mein:

        dispense() -> item do aur stock kam karo

    ---------------------------------------------------------------

    SOLD OUT mein:

        refill() -> stock wapas lao

    ---------------------------------------------------------------

    Agar hum ye sab ek hi VendingMachine class ke andar karte,
    toh bahut saare:

        if(state == NO_COIN)
        else if(state == HAS_COIN)
        else if(state == DISPENSING)
        else if(state == SOLD_OUT)

    lagte.

    STATE PATTERN ka idea:

        "Har state ka behavior uski alag class mein daal do."

    Therefore:

        NoCoinState
        HasCoinState
        DispenseState
        SoldOutState

    apna-apna behavior sambhalengi.


# ================================================================
# 1. INCLUDE FILES
# ================================================================

#include <iostream>
#include <string>

using namespace std;


/*
    #include <iostream>

    Ye input/output ke liye hai.

    Hum is code mein:

        cout

    use kar rahe hain.

    Isliye iostream chahiye.


    ---------------------------------------------------------------

    #include <string>

    Hum:

        string getStateName()

    jaisa return type use kar rahe hain.

    Isliye string header include kiya hai.


    ---------------------------------------------------------------

    using namespace std;

    Isse hume har jagah:

        std::cout
        std::string

    nahi likhna padega.

    Hum directly:

        cout
        string

    likh sakte hain.


# ================================================================
# 2. FORWARD DECLARATION
# ================================================================

class VendingMachine;


/*
    Ye bahut important syntax hai.

    Abhi humne VendingMachine ki complete class nahi banayi.

    Lekin upar State interface ke methods mein hum:

        VendingMachine*

    use karna chahte hain.

    Compiler ko pehle se batana padta hai:

        "Bhai VendingMachine naam ki ek class exist karegi."

    Isliye:

        class VendingMachine;

    likha.

    Isko FORWARD DECLARATION bolte hain.


    Simple language:

        "Abhi poori class nahi bata raha,
         bas naam bata raha hoon ki aisi class hai."


# ================================================================
# 3. ABSTRACT STATE INTERFACE
# ================================================================

class VendingState {

public:

    virtual VendingState* insertCoin(
        VendingMachine* machine,
        int coin
    ) = 0;


    virtual VendingState* selectItem(
        VendingMachine* machine
    ) = 0;


    virtual VendingState* dispense(
        VendingMachine* machine
    ) = 0;


    virtual VendingState* returnCoin(
        VendingMachine* machine
    ) = 0;


    virtual VendingState* refill(
        VendingMachine* machine,
        int quantity
    ) = 0;


    virtual string getStateName() = 0;
};


/*
# ================================================================
# AB EK-EK SYNTAX TODTE HAIN
# ================================================================


    class VendingState

    Matlab hum ek class bana rahe hain jiska naam:

        VendingState

    hai.


    Ye actual state nahi hai.

    Ye ek COMMON INTERFACE/CONTRACT hai.


    Iska matlab:

        Jo bhi actual state class banegi,
        usko VendingState ke operations implement karne honge.


# ================================================================
# virtual
# ================================================================

    Example:

        virtual VendingState* insertCoin(...) = 0;


    "virtual" ka matlab yahan:

        Runtime par actual object ki implementation
        decide karegi.


    Example:

        VendingState* state = new NoCoinState();

        state->insertCoin(...);


    Compiler/runtime actual object:

        NoCoinState

    ki implementation call karega.


    Ye POLYMORPHISM ka important part hai.


# ================================================================
# VendingState*
# ================================================================

    Ye return type hai.

        VendingState*

    means:

        VendingState ka pointer.


    Lekin interesting part ye hai ki function:

        NEXT STATE

    return kar raha hai.


    Example:

        NoCoinState::insertCoin()

    ke baad:

        HasCoinState

    aana chahiye.

    Isliye function next state ka pointer return karta hai.


    Matlab:

        current state
              |
              | operation
              v
        next state


# ================================================================
# VendingMachine* machine
# ================================================================

    Ye machine ka pointer hai.

    State ko machine ki information chahiye.


    Example:

        HasCoinState ko check karna hai:

            insertedCoins >= itemPrice ?

    Ye information kahan hai?

        VendingMachine

    ke andar.


    Isliye State method ko machine ka pointer diya:

        VendingMachine* machine


    Taaki state machine ke data/functions access kar sake.


# ================================================================
# int coin
# ================================================================

    insertCoin() mein:

        int coin

    batata hai user ne kitne rupees insert kiye.


    Example:

        insertCoin(10);

    toh:

        coin = 10


# ================================================================
# = 0
# ================================================================

    Example:

        virtual VendingState* insertCoin(...) = 0;


    Ye PURE VIRTUAL FUNCTION hai.

    Iska matlab:

        VendingState khud iska implementation provide nahi kar rahi.

        Concrete state classes ko implementation deni padegi.


    Is wajah se:

        VendingState

    ABSTRACT CLASS ban jaati hai.


    Hum normally:

        VendingState state;

    nahi bana sakte.


# ================================================================
# getStateName()
# ================================================================

    Ye current state ka naam return karne ke liye hai.

    Example:

        "NO COIN"
        "HAS COIN"
        "DISPENSING"
        "SOLD OUT"


    Tumhare current code mein concrete states ne iska
    implementation nahi diya hai.

    Isliye technically current code as-written incomplete hai
    aur compile nahi karega.

    Agar ise complete karna ho toh har concrete state mein:

        string getStateName() override {
            return "NO COIN";
        }

    etc. dena padega.

    Lekin State Pattern samajhne ke main concept par iska
    koi effect nahi hai.


# ================================================================
# 4. CONTEXT — VENDING MACHINE
# ================================================================

class VendingMachine {

private:

    VendingState* currentState;

    int itemCount;
    int itemPrice;
    int insertedCoins;


    VendingState* noCoinState;
    VendingState* hasCoinState;
    VendingState* dispenseState;
    VendingState* soldOutState;


public:

    VendingMachine(int itemCount, int itemPrice);


    void insertCoin(int coin) {

        currentState =
            currentState->insertCoin(this, coin);
    }


    void selectItem() {

        currentState =
            currentState->selectItem(this);
    }


    void dispense() {

        currentState =
            currentState->dispense(this);
    }


    void returnCoin() {

        currentState =
            currentState->returnCoin(this);
    }


    void refill(int quantity) {

        currentState =
            currentState->refill(this, quantity);
    }
};


/*
# ================================================================
# VENDING MACHINE KA ROLE
# ================================================================

    VendingMachine = CONTEXT


    State Pattern mein:

        Context

    wo main object hota hai jiska behavior state ke according
    change hota hai.


    Yahan:

        VendingMachine

    ka behavior state ke according change ho raha hai.


# ================================================================
# currentState
# ================================================================

    VendingState* currentState;


    Ye sabse important variable hai.


    Iska matlab:

        Machine ke paas ek current state ka pointer hai.


    Example:

        currentState
              |
              v
        NoCoinState


    Phir coin insert kiya:

        currentState
              |
              v
        HasCoinState


    Phir item select:

        currentState
              |
              v
        DispenseState


    Yaani machine ka:

        currentState

    continuously change ho sakta hai.


# ================================================================
# ITEM DATA
# ================================================================

    int itemCount;

        Machine mein kitne items available hain.


    Example:

        itemCount = 2


    ---------------------------------------------------------------

    int itemPrice;

        Ek item ki price.


    Example:

        itemPrice = 20


    ---------------------------------------------------------------

    int insertedCoins;

        User ne kitne coins/rupees insert kiye hain.


    Example:

        insertedCoins = 10


    Ye teen cheezein:

        itemCount
        itemPrice
        insertedCoins

    machine ka SHARED DATA hain.


# ================================================================
# STATE OBJECT POINTERS
# ================================================================

    VendingState* noCoinState;
    VendingState* hasCoinState;
    VendingState* dispenseState;
    VendingState* soldOutState;


    Ye reusable state objects ke pointers hain.


    Machine in states ko store karke rakhti hai.


    Example:

        noCoinState
             |
             v
        NoCoinState object


        hasCoinState
             |
             v
        HasCoinState object


        dispenseState
             |
             v
        DispenseState object


        soldOutState
             |
             v
        SoldOutState object


    Iska fayda:

        Har transition par baar-baar new state object create
        karne ki zarurat nahi.


# ================================================================
# CONSTRUCTOR
# ================================================================

    VendingMachine(int itemCount, int itemPrice);


    Ye constructor ka declaration hai.

    Actual definition code mein missing hai.

    Is constructor mein normally hume:

        itemCount
        itemPrice
        insertedCoins
        state objects
        currentState

    initialize karne honge.


    Example logically:

        insertedCoins = 0;

        noCoinState = new NoCoinState();
        hasCoinState = new HasCoinState();
        dispenseState = new DispenseState();
        soldOutState = new SoldOutState();

        currentState = noCoinState;


    Matlab machine start hogi:

        currentState = NO COIN


# ================================================================
# AB SABSE IMPORTANT METHODS
# ================================================================


    void insertCoin(int coin) {

        currentState =
            currentState->insertCoin(this, coin);
    }


    Isko slowly samajh.


    User call karta hai:

        machine.insertCoin(10);


    VendingMachine ke andar:

        currentState->insertCoin(this, 10);


    Agar current state:

        NoCoinState

    hai toh call jayega:

        NoCoinState::insertCoin(...)


    Agar current state:

        HasCoinState

    hota toh call jayega:

        HasCoinState::insertCoin(...)


    Yaani VendingMachine ko khud nahi pata ki current state mein
    kya karna hai.

    Wo current State ko poochti hai.


# ================================================================
# THIS = KYA HAI?
# ================================================================

        currentState->insertCoin(this, coin);


    Yahan:

        this

    current VendingMachine object ka pointer hai.


    Agar:

        VendingMachine machine;

    hai aur:

        machine.insertCoin(10);


    toh member function ke andar:

        this

    basically:

        &machine

    ko represent karta hai.


    Isliye:

        this

    = current VendingMachine object ka address.


    State ko machine ka pointer isliye diya gaya taaki state
    machine ke data ko modify/check kar sake.


# ================================================================
# CURRENT STATE UPDATE
# ================================================================

        currentState =
            currentState->insertCoin(this, coin);


    Ye line State Pattern ki jaan hai.


    Isme do kaam ho rahe hain:

        1. Current state ka insertCoin() call karo.

        2. Jo next state return hui, usko currentState bana do.


    Example:

        currentState = NoCoinState


    Call:

        currentState->insertCoin(...)


    NoCoinState returns:

        HasCoinState


    Therefore:

        currentState = HasCoinState


    Bas!

    Isi tarah state transition hoti hai.


# ================================================================
# 5. NO COIN STATE
# ================================================================

class NoCoinState : public VendingState {

public:

    VendingState* insertCoin(
        VendingMachine* machine,
        int coin
    ) override {

        machine->setInsertedCoin(coin);

        return machine->getHasCoinState();
    }


    VendingState* selectItem(
        VendingMachine* machine
    ) override {

        cout << "Insert coin first\n";

        return machine->getNoCoinState();
    }
};


/*
# ================================================================
# : public VendingState
# ================================================================

    Iska matlab:

        NoCoinState

    VendingState ko inherit kar rahi hai.


    Conceptually:

        NoCoinState IS-A VendingState


    Ye UML mein:

        implementation / inheritance

    relationship banata hai.


# ================================================================
# override
# ================================================================

        override

    compiler ko batata hai:

        "Main parent class ke virtual function ko override kar raha
         hoon."


    Agar signature galat ho gaya toh compiler error dega.


    Ye useful safety check hai.


# ================================================================
# NO COIN STATE KA LOGIC
# ================================================================

    Machine abhi:

        NO COIN

    state mein hai.


    Is state mein sabse important operation:

        insertCoin()


    User:

        machine.insertCoin(10);


    Flow:

        VendingMachine
              |
              | delegate
              v
        NoCoinState::insertCoin()
              |
              | set coin
              v
        HasCoinState


# ================================================================
# machine->setInsertedCoin(coin)
# ================================================================

    Yahan:

        machine

    ek pointer hai.

    Arrow:

        ->

    pointer ke through object ka member access karne ke liye use
    hota hai.


    Example:

        machine->setInsertedCoin(10);


    Roughly:

        (*machine).setInsertedCoin(10);


    Dono conceptually same access hain.


    Is line ka matlab:

        "Machine mein inserted coin ko update kar do."


# ================================================================
# return machine->getHasCoinState();
# ================================================================

    Ye next state return kar raha hai.


    Current:

        NO COIN


    Coin insert hua:

        HAS COIN


    Therefore:

        return HAS COIN state


    Ye explicit state transition hai.


# ================================================================
# SELECT ITEM WITHOUT COIN
# ================================================================

    User:

        machine.selectItem();


    Current state:

        NoCoinState


    Therefore:

        NoCoinState::selectItem()


    Output:

        Insert coin first


    Aur:

        return machine->getNoCoinState();


    Matlab state same rahegi.


        NO COIN
           |
           | selectItem()
           |
           v
        NO COIN


    Isko SELF TRANSITION keh sakte ho.


# ================================================================
# 6. HAS COIN STATE
# ================================================================

class HasCoinState : public VendingState {

public:

    VendingState* selectItem(
        VendingMachine* machine
    ) override {

        if (
            machine->getInsertedCoin()
            >= machine->getPrice()
        ) {

            machine->setInsertedCoin(0);

            return machine->getDispenseState();
        }

        return machine->getHasCoinState();
    }
};


/*
# ================================================================
# HAS COIN KA IDEA
# ================================================================

    Ab user ne coin insert kar diya.

    Machine:

        HAS COIN


    Ab user item select karega.

    Lekin pehle check karna padega:

        Kya inserted money >= item price?


    Example:

        insertedCoins = 20
        itemPrice = 20

        20 >= 20

        TRUE


    Therefore:

        DISPENSING


# ================================================================
# if condition
# ================================================================

        if (
            machine->getInsertedCoin()
            >= machine->getPrice()
        )


    Isko simple language mein:

        "Jo paisa user ne dala hai,
         kya wo item ki price se zyada ya equal hai?"


    Example 1:

        inserted = 10
        price = 20

        10 >= 20
        FALSE


    Therefore:

        return HasCoinState


    Machine wahi rahegi:

        HAS COIN


    Example 2:

        inserted = 20
        price = 20

        20 >= 20
        TRUE


    Therefore:

        DISPENSING


# ================================================================
# setInsertedCoin(0)
# ================================================================

        machine->setInsertedCoin(0);


    Yahan inserted money ko reset kiya ja raha hai.


    Why?


    Kyunki selection successful ho gayi.

    Code ka simplified model assume kar raha hai ki required
    amount accept ho gaya aur ab machine dispensing mode mein
    ja rahi hai.


    Note:

    Real vending machine mein agar:

        insertedCoins = 30
        price = 20

    ho, toh ideally Rs 10 change return karna padega.

    Tumhara current code us complexity ko model nahi kar raha.


# ================================================================
# NEXT STATE
# ================================================================

        return machine->getDispenseState();


    Transition:

        HAS COIN
            |
            | selectItem()
            v
        DISPENSING


# ================================================================
# INSUFFICIENT MONEY
# ================================================================

        return machine->getHasCoinState();


    Agar:

        insertedCoins < itemPrice

    toh machine:

        HAS COIN

    mein hi rahegi.


    Example:

        inserted = 10
        price = 20


        HAS COIN
            |
            | selectItem()
            v
        HAS COIN


    User aur coin insert kar sakta hai.


# ================================================================
# 7. DISPENSING STATE
# ================================================================

class DispenseState : public VendingState {

public:

    VendingState* dispense(
        VendingMachine* machine
    ) override {

        machine->decrementItemCount();

        if (
            machine->getItemCount() > 0
        ) {

            return machine->getNoCoinState();
        }

        return machine->getSoldOutState();
    }
};


/*
# ================================================================
# DISPENSING KA KAAM
# ================================================================

    Ab machine:

        DISPENSING

    state mein hai.


    User ne:

        selectItem()

    kar diya tha.

    Ab actual item nikalna hai.

    Isliye:

        dispense()

    operation yahan handle hota hai.


# ================================================================
# decrementItemCount()
# ================================================================

        machine->decrementItemCount();


    Matlab stock ek item kam karo.


    Example:

        itemCount = 2


    dispense hua:

        itemCount = 1


# ================================================================
# STOCK CHECK
# ================================================================

        if (machine->getItemCount() > 0)


    Item dispense hone ke baad check:

        Kya abhi bhi items bache hain?


    Agar:

        itemCount = 1

    then:

        > 0

    TRUE.


    Next state:

        NO COIN


    Why?

    Kyunki current customer ka item dispense ho gaya.

    Ab machine next customer ka wait karegi.


# ================================================================
# STOCK ZERO
# ================================================================

    Agar:

        itemCount = 0


    Then:

        return machine->getSoldOutState();


    Transition:

        DISPENSING
             |
             | dispense()
             v
        SOLD OUT


# ================================================================
# 8. SOLD OUT STATE
# ================================================================

class SoldOutState : public VendingState {

public:

    VendingState* refill(
        VendingMachine* machine,
        int quantity
    ) override {

        machine->incrementItemCount(quantity);

        return machine->getNoCoinState();
    }
};


/*
# ================================================================
# SOLD OUT KA MATLAB
# ================================================================

    Machine ke andar:

        itemCount = 0


    Isliye:

        SOLD OUT


    Ab normal customer operations kaam nahi karne chahiye.


    Main useful operation:

        refill()


# ================================================================
# refill()
# ================================================================

    Example:

        machine.refill(5);


    Then:

        machine->incrementItemCount(5);


    Agar pehle:

        itemCount = 0


    toh:

        itemCount = 5


    Ab machine ke paas items hain.


    Therefore:

        return NoCoinState


    Transition:

        SOLD OUT
            |
            | refill()
            v
        NO COIN


# ================================================================
# 9. STATE FLOW
# ================================================================


                    insertCoin()
             +----------------------+
             |                      |
             v                      |
       +------------+               |
       | NO COIN    |               |
       +------------+               |
             |                      |
             | insertCoin()         |
             v                      |
       +------------+               |
       | HAS COIN   |<--------------+
       +------------+
             |
             | selectItem()
             |
             | money >= price
             v
       +------------+
       | DISPENSING |
       +------------+
             |
             | dispense()
             |
             +------------------+
             |                  |
        stock > 0          stock == 0
             |                  |
             v                  v
       +------------+      +------------+
       | NO COIN    |      | SOLD OUT   |
       +------------+      +------------+
                                |
                                | refill()
                                v
                          +------------+
                          | NO COIN    |
                          +------------+


    Ye basically state machine hai.


# ================================================================
# 10. MAIN KO LINE-BY-LINE DRY RUN
# ================================================================

int main() {

    VendingMachine machine(2, 20);

    machine.insertCoin(10);

    machine.insertCoin(10);

    machine.selectItem();

    machine.dispense();

    return 0;
}


/*
# ================================================================
# STEP 1
# ================================================================

    VendingMachine machine(2, 20);


    Machine create hui.


    Conceptually:

        itemCount = 2
        itemPrice = 20
        insertedCoins = 0
        currentState = NO COIN


    Visual:

        machine
           |
           v
       NO COIN

        stock = 2
        price = 20
        inserted = 0


# ================================================================
# STEP 2
# ================================================================

    machine.insertCoin(10);


    VendingMachine::insertCoin(10)


    Internally:

        currentState->insertCoin(this, 10);


    Current state:

        NO COIN


    Therefore:

        NoCoinState::insertCoin(machine, 10)


    It does:

        setInsertedCoin(10)


    Now:

        insertedCoins = 10


    Then:

        return HasCoinState


    VendingMachine receives returned state:

        currentState = HasCoinState


    FINAL:

        machine
           |
           v
       HAS COIN

        stock = 2
        price = 20
        inserted = 10


# ================================================================
# STEP 3
# ================================================================

    machine.insertCoin(10);


    Current state:

        HAS COIN


    So runtime polymorphism calls:

        HasCoinState::insertCoin()


    BUT!!!

    Tumhare current HasCoinState class mein insertCoin()
    override nahi kiya gaya.

    Ye ek IMPORTANT issue hai.

    Parent VendingState mein insertCoin() pure virtual hai:

        virtual ... insertCoin(...) = 0;


    Therefore HasCoinState ko bhi ise implement karna padega.

    Warna HasCoinState bhi abstract rahegi aur code compile nahi
    karega.

    Conceptually tumhara intention clearly ye hai:

        HAS COIN
           |
           | insert another coin
           v
        HAS COIN

    aur:

        insertedCoins += coin


    Lekin current pasted code mein ye implementation missing hai.


# ================================================================
# STEP 4
# ================================================================

    machine.selectItem();


    Assume:

        insertedCoins = 20
        currentState = HAS COIN


    VendingMachine:

        currentState->selectItem(this)


    Runtime polymorphism:

        HasCoinState::selectItem()


    Check:

        20 >= 20

        TRUE


    Then:

        insertedCoins = 0


    And:

        return DispenseState


    Therefore:

        currentState = DISPENSING


    Current machine:

        machine
           |
           v
       DISPENSING

        stock = 2
        inserted = 0


# ================================================================
# STEP 5
# ================================================================

    machine.dispense();


    Current state:

        DISPENSING


    Therefore:

        DispenseState::dispense()


    First:

        decrementItemCount()


    Stock:

        2 -> 1


    Check:

        1 > 0

        TRUE


    Therefore:

        return NoCoinState


    Machine becomes:

        NO COIN


    Final:

        stock = 1
        inserted = 0
        currentState = NO COIN


# ================================================================
# 11. SABSE IMPORTANT CONCEPT — DELEGATION
# ================================================================

/*
    Ye pattern ka heart hai.

    VendingMachine khud operation ka actual logic nahi kar rahi.


    Example:

        machine.selectItem();


    VendingMachine simply says:

        "Current state, tum decide karo."


    Internally:

        currentState->selectItem(this);


    So:

        VendingMachine
              |
              | delegates
              v
        Current State
              |
              v
        actual behavior


    Isko DELEGATION bolte hain.


# ================================================================
# 12. POLYMORPHISM YAHAN KAHAAN USE HO RAHA HAI?
# ================================================================

/*
    currentState ka type:

        VendingState*

    hai.


    Lekin actual object:

        NoCoinState
        HasCoinState
        DispenseState
        SoldOutState

    mein se koi ho sakta hai.


    Example:

        VendingState* currentState = noCoinState;


    Call:

        currentState->selectItem(machine);


    Actual object decide karega:

        NoCoinState::selectItem()


    Agar:

        currentState = hasCoinState;


    Then same:

        currentState->selectItem(machine);


    call karega:

        HasCoinState::selectItem()


    SAME pointer type.

    SAME method call.

    DIFFERENT behavior.

    This is POLYMORPHISM.


# ================================================================
# 13. STATE PATTERN NE IF-ELSE KAISE HATAYA?
# ================================================================


    WITHOUT STATE PATTERN:

        void selectItem() {

            if (state == NO_COIN) {

                cout << "Insert coin";

            }
            else if (state == HAS_COIN) {

                if (money >= price) {
                    ...
                }

            }
            else if (state == DISPENSING) {

                ...

            }
            else if (state == SOLD_OUT) {

                ...

            }
        }


    Problem:

        VendingMachine class ko har state ka knowledge hai.


    ---------------------------------------------------------------

    WITH STATE PATTERN:


        machine.selectItem()
                |
                v
        currentState->selectItem()
                |
        +-------+-------+-------+
        |       |       |       |
        v       v       v       v
      NoCoin  HasCoin Dispense SoldOut


    Har state apna behavior jaanti hai.


# ================================================================
# 14. "STATE" AUR "DATA" KO ALAG SAMJHO
# ================================================================

/*
    Ye bahut important distinction hai.


    VendingMachine ke paas:

        itemCount
        itemPrice
        insertedCoins

    = DATA


    Aur:

        NoCoinState
        HasCoinState
        DispenseState
        SoldOutState

    = BEHAVIOR based on current condition


    Example:

        itemCount = 2

    Ye machine ka data hai.


    Whereas:

        "coin ke bina selectItem nahi kar sakte"

    Ye NO COIN state ka behavior hai.


    State Pattern mainly:

        behavior

    ko organize karta hai.


# ================================================================
# 15. STATE TRANSITION KA CONTROL
# ================================================================

/*
    Is implementation mein ek interesting design choice hai.


    State methods:

        VendingState* insertCoin(...)
        VendingState* selectItem(...)
        VendingState* dispense(...)
        ...


    next state return karti hain.


    Example:

        return machine->getHasCoinState();


    Matlab state khud bol rahi hai:

        "Operation ke baad machine ko HAS COIN mein jaana chahiye."


    Aur Context:

        currentState = returnedState;


    kar deta hai.


    Isliye transition explicit hai.


# ================================================================
# 16. YE POINTERS KYON?
# ================================================================

    VendingState* currentState;


    Pointer isliye use hua kyunki:

        currentState

    ko different concrete objects point karne hain.


    Aaj:

        currentState -> NoCoinState


    Kal:

        currentState -> HasCoinState


    Phir:

        currentState -> DispenseState


    Ek parent/interface pointer different child objects ko
    point kar sakta hai.


    Ye hi polymorphism ke liye useful hai.


# ================================================================
# 17. EK IMPORTANT C++ PROBLEM — MEMORY MANAGEMENT
# ================================================================

/*
    Tumhare code mein:

        VendingState* currentState;

        VendingState* noCoinState;
        VendingState* hasCoinState;
        VendingState* dispenseState;
        VendingState* soldOutState;


    raw pointers hain.


    Agar actual code mein:

        new NoCoinState()
        new HasCoinState()

    use karoge, toh destructor mein:

        delete

    karna padega.


    Aur VendingState mein ideally:

        virtual ~VendingState() = default;

    hona chahiye.


    Modern C++ mein better approach:

        unique_ptr

    use karna hai.


    Lekin State Pattern samajhne ke liye raw pointer version
    conceptually simple hai.


# ================================================================
# 18. EK AUR IMPORTANT ISSUE — CURRENT CODE INCOMPLETE HAI
# ================================================================

/*
    Yrr tumne jo code paste kiya hai usmein kuch functions/classes
    intentionally simplified hain, lekin as-is code compile nahi
    karega.

    MAIN PROBLEMS:


    1. VendingMachine constructor sirf declared hai:

        VendingMachine(int itemCount, int itemPrice);

    Iski definition missing hai.


    2. Ye methods use kiye gaye hain:

        setInsertedCoin()
        getInsertedCoin()
        getPrice()
        getHasCoinState()
        getNoCoinState()
        getDispenseState()
        getSoldOutState()
        decrementItemCount()
        getItemCount()
        incrementItemCount()

    Lekin VendingMachine class mein unki definitions/declarations
    nahi hain.


    3. VendingState ke PURE VIRTUAL methods:

        insertCoin()
        selectItem()
        dispense()
        returnCoin()
        refill()
        getStateName()

    hain.

    Lekin har concrete State ne sab implement nahi kiye.


    Example:

        HasCoinState

    ne sirf:

        selectItem()

    implement kiya hai.

    Lekin:

        insertCoin()
        dispense()
        returnCoin()
        refill()
        getStateName()

    bhi implement karne padenge.


    Same issue NoCoinState, DispenseState, SoldOutState mein bhi hai.


    4. HasCoinState mein insertCoin() missing hai.

    Tumhare main mein:

        machine.insertCoin(10);
        machine.insertCoin(10);

    hai.

    Pehli call:

        NO COIN -> HAS COIN

    second call:

        HAS COIN -> ?

    Iske liye HasCoinState::insertCoin() chahiye.

    Likely:

        insertedCoins += coin;

        return machine->getHasCoinState();


    hona chahiye.


# ================================================================
# 19. EK REALISTIC CORRECT FLOW
# ================================================================

/*
    Agar hum intended logic ko complete karein:

        START
          |
          v
       NO COIN
          |
          | insertCoin(10)
          v
       HAS COIN
          |
          | insertCoin(10)
          v
       HAS COIN

        insertedCoins = 20


          |
          | selectItem()
          |
          | 20 >= 20
          v
       DISPENSING
          |
          | dispense()
          |
          | stock 2 -> 1
          v
       NO COIN


    Ye tumhare main ka actual intended behavior hai.


# ================================================================
# 20. WHY NOT JUST USE ENUM?
# ================================================================

/*
    Koi interviewer pooch sakta hai:

        "State ko enum bana dete, classes kyun banayi?"


    Enum approach:

        enum State {
            NO_COIN,
            HAS_COIN,
            DISPENSING,
            SOLD_OUT
        };


    Phir:

        if(state == NO_COIN)
        ...
        else if(state == HAS_COIN)
        ...


    Small system mein enum perfectly fine ho sakta hai.


    Lekin jab:

        states bahut ho
        +
        har state ka behavior complex ho
        +
        operations bahut ho

    toh if-else/switch bahut bada ho sakta hai.


    State Pattern:

        State-specific logic
              ↓
        separate classes


    Isse code cleaner aur extensible hota hai.


# ================================================================
# 21. STATE PATTERN KA ACTUAL BENEFIT
# ================================================================

/*
    State Pattern ka goal sirf:

        "classes zyada banana"

    nahi hai.


    Actual goal:

        STATE-BASED CONDITIONAL LOGIC KO
        POLYMORPHISM MEIN CONVERT KARNA.


    BEFORE:


        VendingMachine
              |
              +-- if NO_COIN
              |
              +-- if HAS_COIN
              |
              +-- if DISPENSING
              |
              +-- if SOLD_OUT


    AFTER:


        VendingMachine
              |
              v
        VendingState*
              |
       +------+------+------+------+
       |      |      |      |
       v      v      v      v
     NoCoin HasCoin Dispense SoldOut


    Ab har state apna behavior jaanti hai.


# ================================================================
# 22. STATE PATTERN UML KO CODE SE MAP KARO
# ================================================================


    UML:

                    <<interface>>
                  +---------------+
                  | VendingState  |
                  +---------------+
                          ^
                          |
             +------------+------------+
             |            |            |
             |            |            |
        NoCoinState   HasCoinState  DispenseState
                                       |
                                       |
                                  SoldOutState


    CODE:

        class VendingState
        {
            virtual ... = 0;
        };


        class NoCoinState
            : public VendingState
        {
        };


        class HasCoinState
            : public VendingState
        {
        };


        class DispenseState
            : public VendingState
        {
        };


        class SoldOutState
            : public VendingState
        {
        };


    Context:

        +--------------------+
        |  VendingMachine    |
        +--------------------+
        | currentState       |
        +--------------------+


    Code:

        VendingState* currentState;


    Therefore:

        VendingMachine HAS-A VendingState


# ================================================================
# 23. FINAL MENTAL MODEL
# ================================================================

/*
    Yrr is pure code ko ek vending machine employee ki tarah soch.


    VendingMachine bolti hai:

        "Mere paas current state hai."

        "Jo bhi customer operation karega,
         main wo operation current state ko de dungi."


    NO COIN bolti hai:

        "Mere paas coin nahi hai.
         Coin aayega toh HAS COIN mein jao."


    HAS COIN bolti hai:

        "Money enough hai?
         Haan -> DISPENSING
         Nahi -> mere state mein raho."


    DISPENSING bolti hai:

        "Item nikaalo.
         Stock bacha hai -> NO COIN
         Stock khatam -> SOLD OUT"


    SOLD OUT bolti hai:

        "Refill karo.
         Refill ke baad -> NO COIN"


# ================================================================
# 24. SAB KUCH EK FLOW MEIN
# ================================================================


                        VENDING MACHINE
                              |
                              v
                         currentState
                              |
                              v
                         +----------+
                         | NO COIN  |
                         +----------+
                              |
                        insertCoin()
                              |
                              v
                         +----------+
                         | HAS COIN |
                         +----------+
                              |
                         selectItem()
                              |
                    +---------+---------+
                    |                   |
              money < price       money >= price
                    |                   |
                    v                   v
               HAS COIN            DISPENSING
                                       |
                                    dispense()
                                       |
                            +----------+----------+
                            |                     |
                       stock > 0              stock == 0
                            |                     |
                            v                     v
                        NO COIN               SOLD OUT
                                                  |
                                               refill()
                                                  |
                                                  v
                                               NO COIN


# ================================================================
# 25. INTERVIEW KE LIYE CORE ANSWER
# ================================================================

/*
    Agar interviewer bole:

        "Explain your State Pattern implementation."


    Tum bol sakte ho:


    "VendingMachine is the Context and VendingState is the common
     State interface.

     The machine maintains a reference to its current state.

     Concrete states such as NoCoinState, HasCoinState,
     DispenseState and SoldOutState implement state-specific
     behavior.

     Instead of putting state checks inside VendingMachine,
     the machine delegates each operation to the current state.

     Each state can return the next state, so state transitions
     are explicit.

     This replaces large if-else or switch based state logic
     with polymorphism."


# ================================================================
# 26. SABSE IMPORTANT 6 LINES
# ================================================================

/*
    Agar poore code mein se sirf 6 cheezein yaad rakhni hain:


    1.

        VendingMachine = Context


    2.

        VendingState = State interface


    3.

        NoCoinState / HasCoinState /
        DispenseState / SoldOutState

        = Concrete States


    4.

        VendingMachine HAS-A VendingState


    5.

        ConcreteState IS-A VendingState


    6.

        currentState->operation()

        means:

        "Current state, tum decide karo ki ye operation
         kaise behave karega."


    Aur:

        returned State

             ↓

        currentState = returnedState;


    means:

        "Operation ke baad machine ki state change ho gayi."


# ================================================================
# FINAL ONE-LINE INTUITION
# ================================================================

/*
        SAME VENDING MACHINE
                +
        DIFFERENT CURRENT STATE
                =
        DIFFERENT BEHAVIOR


    Aur State Pattern:

        "Har state ka behavior uski apni class mein daal kar,
         Context ko current state ke through behavior delegate
         karwata hai."


    Bas yahi poora State Design Pattern ka core hai.
*/