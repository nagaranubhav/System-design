/*
====================================================================
              STATE DESIGN PATTERN — ORDER EXAMPLE
====================================================================

YRR PEHLE EK BAAR UML DEKH LE, PHIR NICHE EXACT SAME DESIGN KA
CODE LIKH RAHE HAIN.

IMPORTANT:
UML ko sirf code ke saath mapping samajhne ke liye rakha hai.
Main explanation code ke andar hi kar raha hoon.


====================================================================
                         UML DIAGRAM
====================================================================


                         <<interface>>
                    +----------------------+
                    |        State         |
                    +----------------------+
                    | + cancel(Order*)     |
                    | + confirm(Order*)    |
                    | + ship(Order*)       |
                    | + deliver(Order*)    |
                    | + track(Order*)      |
                    +----------^-----------+
                               |
              - - - - - - - - -| - - - - - - - - -
              |                 |                 |
              |                 |                 |
      +---------------+ +---------------+ +---------------+
      | PlacedState   | |ConfirmedState | | ShippedState |
      +---------------+ +---------------+ +---------------+
      | + cancel()    | | + cancel()    | | + cancel()    |
      | + confirm()   | | + confirm()   | | + ship()      |
      | + ship()      | | + ship()      | | + deliver()   |
      | + deliver()   | | + deliver()   | | + track()     |
      | + track()     | | + track()     | +---------------+
      +---------------+ +---------------+
              |
              |
              |                         +----------------+
              +------------------------>|DeliveredState |
                                        +----------------+
                                        | + cancel()     |
                                        | + confirm()    |
                                        | + ship()       |
                                        | + deliver()    |
                                        | + track()      |
                                        +----------------+


                    +---------------------------+
                    |          Order            |
                    |        <<Context>>        |
                    +---------------------------+
                    | - currentState : State*   |
                    | - orderId : int           |
                    +---------------------------+
                    | + cancel()                |
                    | + confirm()               |
                    | + ship()                  |
                    | + deliver()               |
                    | + track()                 |
                    | + setState(State*)        |
                    +-------------+-------------+
                                  |
                                  | HAS-A
                                  v
                                State


STATE FLOW:

    PLACED
       |
       | confirm()
       v
    CONFIRMED
       |
       | ship()
       v
    SHIPPED
       |
       | deliver()
       v
    DELIVERED


====================================================================
1. INCLUDE FILES
====================================================================
*/

#include <iostream>

using namespace std;


/*
====================================================================
2. FORWARD DECLARATION
====================================================================

Yahan ek bahut important C++ problem hai.

State class ke methods ko Order ka pointer chahiye:

    Order*

Lekin abhi Order class bani hi nahi hai.

Toh compiler ko pehle bata dete hain:

    "Bhai Order naam ki ek class exist karegi."

Isko FORWARD DECLARATION bolte hain.
*/

class Order;


/*
====================================================================
3. STATE INTERFACE
====================================================================

Ye hamara UML wala:

                    <<interface>>
                       State

hai.

Iska kaam actual behavior likhna nahi hai.

Ye sirf contract define karega:

    Har state ko:
        cancel()
        confirm()
        ship()
        deliver()
        track()

handle karna aana chahiye.
*/

class State {

public:

    /*
        virtual

        Iska matlab hai runtime par actual object ki implementation
        call hogi.

        Example:

            State* state = new PlacedState();

        Agar:

            state->confirm(order);

        call kiya,

        toh PlacedState ka confirm() chalega.

        Isi ko runtime polymorphism kehte hain.
    */

    virtual void cancel(Order* order) = 0;

    virtual void confirm(Order* order) = 0;

    virtual void ship(Order* order) = 0;

    virtual void deliver(Order* order) = 0;

    virtual void track(Order* order) = 0;


    /*
        = 0

        Iska matlab ye PURE VIRTUAL FUNCTION hai.

        State khud nahi batayegi ki:

            cancel() kaise hoga?
            ship() kaise hoga?

        Har concrete state apna behavior define karegi.

        Is wajah se State ek ABSTRACT CLASS ban jaati hai.
    */


    /*
        Virtual destructor bahut important hai.

        Kyunki hum derived objects ko base pointer se handle
        kar rahe hain:

            State* state;

        Isliye destructor virtual hona safe design hai.
    */

    virtual ~State() = default;
};


/*
====================================================================
4. CONCRETE STATE CLASSES
====================================================================

Ab UML mein State ke neeche jo classes hain:

    PlacedState
    ConfirmedState
    ShippedState
    DeliveredState

wo banayenge.

IMPORTANT:

In classes mein hum sirf functions DECLARE karenge.

Actual implementation baad mein karenge.

Aisa isliye kyunki in functions ke andar:

    Order

ke methods call karne hain.

Aur Order ki complete definition hum next mein denge.
*/


class PlacedState : public State {

public:

    void cancel(Order* order) override;

    void confirm(Order* order) override;

    void ship(Order* order) override;

    void deliver(Order* order) override;

    void track(Order* order) override;
};


/*
    : public State

    Matlab:

        PlacedState IS-A State

    UML mein ye:

        PlacedState - - -▷ State

    wali implementation relationship represent karta hai.


    override

    Compiler ko batata hai:

        "Main parent State class ke virtual function ko
         override kar raha hoon."

    Agar signature galat hui toh compiler error dega.
*/


class ConfirmedState : public State {

public:

    void cancel(Order* order) override;

    void confirm(Order* order) override;

    void ship(Order* order) override;

    void deliver(Order* order) override;

    void track(Order* order) override;
};


class ShippedState : public State {

public:

    void cancel(Order* order) override;

    void confirm(Order* order) override;

    void ship(Order* order) override;

    void deliver(Order* order) override;

    void track(Order* order) override;
};


class DeliveredState : public State {

public:

    void cancel(Order* order) override;

    void confirm(Order* order) override;

    void ship(Order* order) override;

    void deliver(Order* order) override;

    void track(Order* order) override;
};


/*
====================================================================
5. CONTEXT CLASS — ORDER
====================================================================

Ab UML ka:

                    Order
                  <<Context>>

banate hain.

State Pattern mein Context wo main object hota hai jiska behavior
state ke according change hota hai.

Yahan:

                    Order

hamara Context hai.
*/


class Order {

private:

    /*
        Ye sabse important variable hai:

            State* currentState;

        Order ke paas CURRENT STATE ka pointer hai.

        Example:

            currentState
                  |
                  v
            PlacedState


        Baad mein:

            currentState
                  |
                  v
            ConfirmedState


        Phir:

            currentState
                  |
                  v
            ShippedState


        Isliye:

            Order HAS-A State
    */

    State* currentState;


    /*
        Ye sirf example ke liye order ki identification hai.

        State Pattern ke liye mandatory nahi hai.
    */

    int orderId;


public:

    /*
        Constructor:

            Order(int id)

        order create karte waqt id receive karega.
    */

    Order(int id);


    /*
    ================================================================
    PUBLIC OPERATIONS
    ================================================================

    Ye wo operations hain jo user/client Order par call karega.

        order.confirm();
        order.ship();
        order.deliver();
        order.cancel();
        order.track();

    Notice:

        Order khud decide nahi karega ki kya karna hai.

        Ye current state ko operation DELEGATE karega.
    */


    void cancel();

    void confirm();

    void ship();

    void deliver();

    void track();


    /*
    ================================================================
    setState()
    ================================================================

    Current state ko change karne ke liye.

        Placed
            ↓
        Confirmed

        Confirmed
            ↓
        Shipped

        Shipped
            ↓
        Delivered
    */

    void setState(State* newState);


    /*
    ================================================================
    getOrderId()
    ================================================================

    State classes ko order ki information chahiye toh ye getter
    use kar sakti hain.
    */

    int getOrderId() const;


    /*
        Destructor ka kaam:

            currentState

        ko delete karna.

        Hum raw pointers use kar rahe hain, isliye memory manually
        manage karni padegi.
    */

    ~Order();
};


/*
====================================================================
6. ORDER CONSTRUCTOR
====================================================================

Ab Order ki actual constructor definition.

Important cheez:

    currentState = new PlacedState();

Matlab order create hote hi uski initial state:

    PLACED

hai.
*/


Order::Order(int id)
    : currentState(new PlacedState()),
      orderId(id)
{
    /*
        Ye initializer list hai.

            : currentState(...)
              orderId(...)

        Iska matlab object ke members ko constructor body se
        pehle initialize karna.

        So:

            currentState
                  |
                  v
            PlacedState

        Initial state = PLACED.
    */

    cout << "Order #" << orderId
         << " created.\n";

    cout << "Initial state: PLACED\n\n";
}


/*
====================================================================
7. setState()
====================================================================

Ye method state change karega.

Example:

    currentState = PlacedState

    Agar:

        setState(new ConfirmedState());

    hua,

    toh:

        currentState = ConfirmedState
*/


void Order::setState(State* newState)
{
    /*
        Pehle purani state ko delete karna padega.

        Example:

            currentState
                 |
                 v
            PlacedState

        Agar new state:

            ConfirmedState

        hai toh old PlacedState ki memory release karenge.
    */

    delete currentState;


    /*
        Ab currentState new state ko point karega.
    */

    currentState = newState;
}


/*
====================================================================
8. ORDER — cancel()
====================================================================

User/client call karega:

    order.cancel();

Order khud cancellation ka logic nahi jaanta.

Wo simply current state se bolta hai:

    "Bhai tum cancel handle karo."
*/


void Order::cancel()
{
    currentState->cancel(this);
}


/*
    Is line ko bahut carefully samajh:

        currentState->cancel(this);


    currentState:

        State*

    type ka hai.

    Lekin actual object ho sakta hai:

        PlacedState
        ConfirmedState
        ShippedState
        DeliveredState


    Runtime par actual object decide karega ki kaunsa cancel()
    execute hoga.


    this:

        current Order object ka pointer hai.


    Agar:

        Order order(101);

    aur:

        order.cancel();

    call hua,

    toh internally:

        currentState->cancel(this);

    mein:

        this = &order

    hoga.


    State ko Order ka pointer isliye de rahe hain taaki State:

        order->setState(...)

    kar sake.
*/


/*
====================================================================
9. ORDER — confirm()
====================================================================
*/

void Order::confirm()
{
    currentState->confirm(this);
}


/*
    Again:

        Order
          |
          | delegate
          v
        currentState
          |
          v
        confirm()


    Order ko ye nahi pata:

        "Main Placed hoon ya Shipped?"

    Current state khud decide karegi.
*/


/*
====================================================================
10. ORDER — ship()
====================================================================
*/

void Order::ship()
{
    currentState->ship(this);
}


/*
====================================================================
11. ORDER — deliver()
====================================================================
*/

void Order::deliver()
{
    currentState->deliver(this);
}


/*
====================================================================
12. ORDER — track()
====================================================================
*/

void Order::track()
{
    currentState->track(this);
}


/*
====================================================================
13. getOrderId()
====================================================================
*/

int Order::getOrderId() const
{
    return orderId;
}


/*
    const

    Yahan:

        int getOrderId() const

    ka matlab:

        Ye function Order object ke data ko modify nahi karega.

    Sirf data read karega.
*/


/*
====================================================================
14. ORDER DESTRUCTOR
====================================================================
*/

Order::~Order()
{
    delete currentState;
}


/*
    Kyunki constructor mein:

        new PlacedState()

    kiya tha,

    toh destructor mein:

        delete currentState;

    karna zaroori hai.


    Ye raw pointer memory management ka part hai.


====================================================================
15. AB ACTUAL STATE BEHAVIOR
====================================================================

Ab har state apna actual behavior implement karegi.

Yahi State Pattern ka main part hai.

Order sirf operation delegate karta hai.

Actual decision:

        "Is state mein kya hona chahiye?"

Concrete State class karegi.


====================================================================
16. PLACED STATE
====================================================================
*/


void PlacedState::cancel(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " cancelled.\n";
}


/*
    PLACED state mein cancel allowed hai.

    Example:

        Order created
              |
              v
           PLACED

        User:
            cancel()

        Result:
            Order cancelled.


    Notice:

        State ko Order object mil raha hai:

            Order* order

        Isliye:

            order->getOrderId()

        call kar sakte hain.
*/


void PlacedState::confirm(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " confirmed.\n";


    /*
        Ab state transition:

            PLACED
               |
               | confirm()
               v
            CONFIRMED


        Isliye new state create karke Context ko de rahe hain.
    */

    order->setState(
        new ConfirmedState()
    );
}


/*
    Ye line:

        order->setState(new ConfirmedState());

    kaafi important hai.

    Breakdown:

        new ConfirmedState()

            ↓

        Heap par ConfirmedState object create karo.

            ↓

        uska address return hoga.

            ↓

        setState(...)

            ↓

        Order ka currentState update ho jayega.


    Before:

        currentState
             |
             v
        PlacedState


    After:

        currentState
             |
             v
        ConfirmedState
*/


void PlacedState::ship(Order* order)
{
    cout << "Cannot ship Order #"
         << order->getOrderId()
         << ".\n";

    cout << "Order must be confirmed first.\n";
}


/*
    Important:

    Yahan state change nahi hui.

    Kyunki PLACED order ko directly ship karna allowed nahi hai.

        PLACED
           |
           | ship()
           X

    So currentState same rahegi.
*/


void PlacedState::deliver(Order* order)
{
    cout << "Cannot deliver Order #"
         << order->getOrderId()
         << ".\n";

    cout << "Order must be shipped first.\n";
}


/*
    Same logic:

        PLACED -> DELIVERED

    directly allowed nahi.
*/


void PlacedState::track(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " is waiting for confirmation.\n";
}


/*
====================================================================
17. CONFIRMED STATE
====================================================================

Ab order:

        CONFIRMED

state mein hai.

Allowed flow:

        CONFIRMED
             |
             | ship()
             v
          SHIPPED
*/


void ConfirmedState::cancel(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " cancelled.\n";
}


/*
    Confirmed order ko abhi cancel kiya ja sakta hai.
*/


void ConfirmedState::confirm(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " is already confirmed.\n";
}


/*
    Already confirmed.

    Isliye state change nahi hogi.
*/


void ConfirmedState::ship(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " shipped.\n";


    /*
        State transition:

            CONFIRMED
                 |
                 | ship()
                 v
              SHIPPED
    */

    order->setState(
        new ShippedState()
    );
}


void ConfirmedState::deliver(Order* order)
{
    cout << "Cannot deliver Order #"
         << order->getOrderId()
         << ".\n";

    cout << "Order must be shipped first.\n";
}


void ConfirmedState::track(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " is being prepared for shipping.\n";
}


/*
====================================================================
18. SHIPPED STATE
====================================================================

Ab order:

        SHIPPED

state mein hai.

Expected behavior:

        cancel()  -> NOT allowed
        confirm() -> already confirmed
        ship()    -> already shipped
        deliver() -> allowed
        track()   -> order on the way
*/


void ShippedState::cancel(Order* order)
{
    cout << "Cannot cancel Order #"
         << order->getOrderId()
         << ".\n";

    cout << "Order has already been shipped.\n";
}


void ShippedState::confirm(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " is already confirmed.\n";
}


void ShippedState::ship(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " is already shipped.\n";
}


void ShippedState::deliver(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " delivered successfully.\n";


    /*
        State transition:

            SHIPPED
                |
                | deliver()
                v
            DELIVERED
    */

    order->setState(
        new DeliveredState()
    );
}


void ShippedState::track(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " is on the way.\n";
}


/*
====================================================================
19. DELIVERED STATE
====================================================================

Final state.

    DELIVERED

Normally ab order ko:

    cancel()
    confirm()
    ship()
    deliver()

nahi karna chahiye.

Sirf track kar sakte hain.
*/


void DeliveredState::cancel(Order* order)
{
    cout << "Cannot cancel Order #"
         << order->getOrderId()
         << ".\n";

    cout << "Order has already been delivered.\n";
}


void DeliveredState::confirm(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " is already delivered.\n";
}


void DeliveredState::ship(Order* order)
{
    cout << "Cannot ship Order #"
         << order->getOrderId()
         << ".\n";

    cout << "Order has already been delivered.\n";
}


void DeliveredState::deliver(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " is already delivered.\n";
}


void DeliveredState::track(Order* order)
{
    cout << "Order #"
         << order->getOrderId()
         << " was delivered successfully.\n";
}


/*
====================================================================
20. MAIN — AB POORA FLOW DEKH
====================================================================
*/


int main()
{
    /*
        Order create hua.

        Constructor:

            Order(int id)

        call hoga.

        Initial state:

            PlacedState
    */

    Order order(101);


    /*
    ================================================================
    STATE 1: PLACED
    ================================================================
    */

    order.track();

    /*
        Flow:

            order.track()
                  |
                  v
            currentState->track(this)
                  |
                  v
            PlacedState::track()


        Output:

            Order #101 is waiting for confirmation.
    */


    /*
    ================================================================
    STATE TRANSITION:

            PLACED -> CONFIRMED
    ================================================================
    */

    order.confirm();


    /*
        Step-by-step:

            order.confirm()
                  |
                  v
            Order::confirm()
                  |
                  v
            currentState->confirm(this)
                  |
                  v
            PlacedState::confirm(order)
                  |
                  v
            order->setState(
                new ConfirmedState()
            )


        Ab currentState:

            ConfirmedState


        Yaani:

            BEFORE:

                order
                  |
                  v
              PlacedState


            AFTER:

                order
                  |
                  v
             ConfirmedState
    */


    /*
    ================================================================
    STATE 2: CONFIRMED
    ================================================================
    */

    order.track();

    /*
        Ab same:

            order.track()

        call hua.

        Lekin currentState ab:

            ConfirmedState

        hai.

        Therefore:

            ConfirmedState::track()

        call hoga.

        Notice:

            SAME order.track()

        lekin behavior change ho gaya.


        YEHI STATE PATTERN KA CORE HAI.
    */


    /*
    ================================================================
    STATE TRANSITION:

            CONFIRMED -> SHIPPED
    ================================================================
    */

    order.ship();


    /*
        Flow:

            order.ship()
                 |
                 v
            Order::ship()
                 |
                 v
            currentState->ship(this)
                 |
                 v
            ConfirmedState::ship(order)
                 |
                 v
            order->setState(
                new ShippedState()
            )


        Ab:

            currentState = ShippedState
    */


    /*
    ================================================================
    STATE 3: SHIPPED
    ================================================================
    */

    order.track();

    /*
        Current state:

            ShippedState

        Therefore:

            ShippedState::track()

        Output:

            Order #101 is on the way.
    */


    /*
        Ab cancellation try karte hain.
    */

    order.cancel();


    /*
        Flow:

            order.cancel()
                 |
                 v
            currentState->cancel(this)
                 |
                 v
            ShippedState::cancel()


        Output:

            Cannot cancel Order #101.
            Order has already been shipped.


        Notice:

            Same cancel() method.

            PLACED state mein:

                cancel() -> SUCCESS

            SHIPPED state mein:

                cancel() -> NOT ALLOWED


        Behavior current state ke according change hua.
    */


    /*
    ================================================================
    STATE TRANSITION:

            SHIPPED -> DELIVERED
    ================================================================
    */

    order.deliver();


    /*
        Flow:

            order.deliver()
                  |
                  v
            currentState->deliver(this)
                  |
                  v
            ShippedState::deliver()
                  |
                  v
            setState(
                new DeliveredState()
            )
    */


    /*
    ================================================================
    STATE 4: DELIVERED
    ================================================================
    */

    order.track();

    /*
        Current state:

            DeliveredState

        Therefore:

            DeliveredState::track()

        execute hoga.
    */


    /*
        Delivered order ko cancel karne ki try:
    */

    order.cancel();


    /*
        Current state:

            DeliveredState

        So:

            DeliveredState::cancel()

        call hoga.

        Output:

            Cannot cancel Order #101.
            Order has already been delivered.
    */


    return 0;
}


/*
====================================================================
21. AB POORE CODE KA FLOW EK BAAR VISUALIZE KAR
====================================================================


        main()
          |
          v
    Order order(101)
          |
          v
    +-------------+
    | PLACED      |
    +-------------+
          |
          | order.confirm()
          v
    +-------------+
    | CONFIRMED   |
    +-------------+
          |
          | order.ship()
          v
    +-------------+
    | SHIPPED     |
    +-------------+
          |
          | order.deliver()
          v
    +-------------+
    | DELIVERED   |
    +-------------+


IMPORTANT:

Ye states khud alag-alag Order objects nahi hain.

Sirf STATE OBJECT change ho raha hai.


Same Order:

        Order #101

hai.

Sirf:

        currentState

change ho raha hai.


====================================================================
22. EK ACTUAL DRY RUN — MEMORY LEVEL PAR
====================================================================


STEP 1:

    Order order(101);


    Memory conceptually:

        order
          |
          | currentState
          v
      +-----------+
      | PlacedState|
      +-----------+


STEP 2:

    order.confirm();


    Current state:

        PlacedState


    Call:

        currentState->confirm(this);


    Actual function:

        PlacedState::confirm()


    Inside:

        order->setState(
            new ConfirmedState()
        );


    setState():

        delete currentState;

    Old:

        PlacedState

    delete ho gaya.


    Then:

        currentState = new ConfirmedState();


    Now:

        order
          |
          | currentState
          v
      +--------------+
      | ConfirmedState|
      +--------------+


STEP 3:

    order.ship();


    Current state:

        ConfirmedState


    Therefore:

        ConfirmedState::ship()


    It does:

        setState(
            new ShippedState()
        );


    Now:

        order
          |
          v
      +-------------+
      | ShippedState|
      +-------------+


STEP 4:

    order.deliver();


    Current:

        ShippedState


    Therefore:

        ShippedState::deliver()


    State changes:

        ShippedState
             |
             v
        DeliveredState


    Final:

        order
          |
          v
      +---------------+
      | DeliveredState|
      +---------------+


====================================================================
23. AB SABSE IMPORTANT LINE
====================================================================


    currentState->cancel(this);


Ye line basically State Pattern ka heart hai.


Socho:

    currentState = PlacedState


Then:

    currentState->cancel(this);


becomes conceptually:

    PlacedState::cancel(this);


Agar:

    currentState = ShippedState


Then same line:

    currentState->cancel(this);


becomes:

    ShippedState::cancel(this);


Agar:

    currentState = DeliveredState


Then:

    DeliveredState::cancel(this);


Same:

        cancel()

Different behavior.

WHY?

Because of:

        POLYMORPHISM.


====================================================================
24. ORDER CLASS MEIN LOGIC KYON NAHI HAI?
====================================================================


Agar State Pattern nahi hota toh Order kuch aisa hota:


    void Order::cancel()
    {
        if (state == PLACED)
        {
            // cancel
        }
        else if (state == CONFIRMED)
        {
            // cancel
        }
        else if (state == SHIPPED)
        {
            // don't cancel
        }
        else if (state == DELIVERED)
        {
            // don't cancel
        }
    }


Aur:

    confirm()

mein bhi same checks.


    ship()

mein bhi same checks.


    deliver()

mein bhi same checks.


Result:

        Order class
             |
             +-- state checking
             +-- cancellation logic
             +-- confirmation logic
             +-- shipping logic
             +-- delivery logic
             +-- tracking logic


Order bahut bada ho jayega.


STATE PATTERN:


        Order
          |
          | delegate
          v
      currentState
          |
          +--> PlacedState
          +--> ConfirmedState
          +--> ShippedState
          +--> DeliveredState


Har state apna behavior sambhalti hai.


====================================================================
25. "this" KO EKDUM CLEAR KAR
====================================================================


Code:

    currentState->confirm(this);


Yahan:

        this

ka matlab hai:

        "Current Order object ka address."


Agar:

    Order order(101);


Then:

    order.confirm();


ke andar:

    this

roughly:

    &order

hoga.


State ko ye pointer kyun diya?


Because State ko Context ke saath kaam karna hai.


Example:

    PlacedState::confirm(Order* order)


Ab State ke paas Order ka pointer hai.

Therefore:

    order->setState(...);


possible hai.


So:

        State
          |
          | receives
          v
        Order*


Aur phir State Context ko bol sakti hai:

        "Bhai apni state change kar le."


====================================================================
26. "->" OPERATOR
====================================================================


Code:

    order->setState(...);


Yahan:

    order

ek pointer hai:

    Order* order


Pointer ke through object ka member access karne ke liye:

    ->

use hota hai.


Example:

    Order* ptr;


    ptr->setState(...);


Conceptually:

    (*ptr).setState(...);


Dono ka meaning same hai.


Normal object:

    order.setState(...);


Pointer:

    order->setState(...);


====================================================================
27. "new" KYA KAR RAHA HAI?
====================================================================


Code:

    new ConfirmedState()


Matlab:

    Heap memory mein ConfirmedState ka object banao.

Aur us object ka address return karo.


Example:

    State* state = new ConfirmedState();


Yahan:

    state

parent/interface pointer hai.


Lekin actual object:

    ConfirmedState

hai.


Therefore:

    state->ship(...)

runtime polymorphism ke through:

    ConfirmedState::ship()

call kar sakta hai.


====================================================================
28. "delete" KYA KAR RAHA HAI?
====================================================================


Code:

    delete currentState;


Iska matlab:

    currentState jis object ko point kar raha hai,
    uski heap memory release kar do.


Example:

    currentState
         |
         v
    PlacedState


Then:

    delete currentState;


PlacedState object destroy ho jayega.


Phir:

    currentState = new ConfirmedState();


====================================================================
29. CONSTRUCTOR INITIALIZER LIST
====================================================================


Code:

    Order::Order(int id)
        : currentState(new PlacedState()),
          orderId(id)
    {
    }


Ye:

        initializer list

hai.


Iska matlab:

    currentState ko directly initialize karo:

        new PlacedState()


    aur:

        orderId ko id se initialize karo.


Ye constructor ke body ke andar:

    currentState = new PlacedState();
    orderId = id;


likhne se conceptually alag initialization mechanism hai.


C++ mein initializer list preferred hoti hai,
especially jab const/reference/member objects involved hon.


====================================================================
30. "public State" KYON?
====================================================================


    class ConfirmedState : public State


Matlab:

    ConfirmedState

State ki public interface ko inherit karegi.


Conceptually:

    ConfirmedState IS-A State


Therefore:

    State* ptr = new ConfirmedState();


valid hai.


Isi wajah se:

    currentState

ka type:

    State*

ho sakta hai,

chahe actual object:

    ConfirmedState

ho.


====================================================================
31. STATE PATTERN KI 4 MAIN CHEEZEIN
====================================================================


    1. CONTEXT

            Order


    2. STATE INTERFACE

            State


    3. CONCRETE STATES

            PlacedState
            ConfirmedState
            ShippedState
            DeliveredState


    4. CURRENT STATE

            State* currentState


Flow:


        Order
          |
          | HAS-A
          v
        State
          ^
          |
          | implements
          |
        Concrete States


====================================================================
32. IS-A VS HAS-A — JO TU UML MEIN PUCHTA REHTA HAI
====================================================================


    Order HAS-A State

        because:

            State* currentState;


    Matlab Order ke paas State ka reference/pointer hai.


    ---------------------------------------------------------------


    PlacedState IS-A State

    ConfirmedState IS-A State

    ShippedState IS-A State

    DeliveredState IS-A State


    because all of them:

        inherit/implement State.


    ---------------------------------------------------------------


    So:

        Order
          |
          | HAS-A
          v
        State


    And:

        PlacedState
              |
              | IS-A
              v
            State


====================================================================
33. SABSE IMPORTANT INTERVIEW POINT
====================================================================


Interviewer:

    "Why did you use State Pattern here?"


Answer:


    "Because the behavior of an Order depends on its current state.

     Instead of putting state-based if-else or switch conditions
     inside Order, I encapsulated each state's behavior into a
     separate class.

     Order acts as the Context and maintains a reference to the
     State interface.

     It delegates operations like confirm(), ship(), deliver()
     and cancel() to the current state.

     Each concrete state can also trigger the next state
     transition.

     This gives us polymorphic behavior and keeps state-specific
     logic separated."


====================================================================
34. FINAL MENTAL MODEL
====================================================================


                 USER
                   |
                   v
              order.ship()
                   |
                   v
            +-------------+
            |    Order    |
            |  Context    |
            +------+------+
                   |
                   | delegate
                   v
            +-------------+
            | currentState|
            +------+------+
                   |
                   v
            +-------------+
            |   State*    |
            +------+------+
                   |
          +--------+--------+
          |        |        |
          v        v        v
       Placed   Confirmed  Shipped
                            |
                            | deliver()
                            v
                         Delivered


CORE IDEA:


        Order khud behavior decide nahi karta.

        Order bolta hai:

            "Current State,
             tum decide karo."


        State bolti hai:

            "Main abhi jis state mein hoon,
             uske according behavior ye hoga."


        Aur agar transition chahiye:

            State
              |
              v
        order->setState(...)
              |
              v
        New State


====================================================================
35. EK LINE MEIN POORA CODE
====================================================================


        Order = Context

        State = common interface

        ConcreteState = state-specific behavior

        currentState = current condition

        currentState->operation(this)
                =
        "Current state, tum operation handle karo."


        State change:
                ↓
        Behavior change


        IF-ELSE BASED STATE LOGIC
                ↓
        POLYMORPHISM


====================================================================
36. ACTUAL ORDER LIFECYCLE
====================================================================


             confirm()
        +----------------+
        |                |
        v                |
    +--------+      +-----------+
    | PLACED | ---> | CONFIRMED |
    +--------+      +-----------+
                         |
                         | ship()
                         v
                    +---------+
                    | SHIPPED |
                    +---------+
                         |
                         | deliver()
                         v
                   +-----------+
                   | DELIVERED |
                   +-----------+


Aur SAME Order object poore lifecycle mein exist karta hai:

        Order #101


Sirf:

        currentState

change hota rehta hai.


YAHI STATE DESIGN PATTERN KA ACTUAL CORE HAI.
====================================================================
*/ 