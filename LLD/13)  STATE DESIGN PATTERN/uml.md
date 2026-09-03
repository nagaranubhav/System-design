# ================================================================
#           STATE DESIGN PATTERN — STANDARD UML
#           Example: Online Order
# ================================================================


                           <<interface>>
                       +-------------------+
                       |       State       |
                       +-------------------+
                       | + cancel()        |
                       | + confirm()       |
                       | + ship()          |
                       | + deliver()       |
                       | + track()         |
                       +---------^---------+
                                 |
                    - - - - - - -|- - - - - - -
                   /              |              \
                  /               |               \
                 /                |                \
                /                 |                 \
   +-------------------+ +-------------------+ +-------------------+
   |    PlacedState    | |  ConfirmedState   | |   ShippedState    |
   +-------------------+ +-------------------+ +-------------------+
   | + cancel()        | | + cancel()        | | + cancel()        |
   | + confirm()       | | + confirm()       | | + confirm()       |
   | + ship()          | | + ship()          | | + ship()          |
   | + deliver()       | | + deliver()       | | + deliver()       |
   | + track()         | | + track()         | | + track()         |
   +-------------------+ +-------------------+ +-------------------+
                  \               |               /
                   \              |              /
                    \             |             /
                     \            |            /
                      \           |           /
                       \          |          /
                        \         |         /
                         \        |        /
                          \       |       /
                           \      |      /
                            \     |     /
                             \    |    /
                              \   |   /
                               \  |  /
                                \ | /
                         +-------------------+
                         |  DeliveredState   |
                         +-------------------+
                         | + cancel()        |
                         | + confirm()       |
                         | + ship()          |
                         | + deliver()       |
                         | + track()         |
                         +-------------------+


                              ▲
                              |
                              | has-a
                              |
                    +---------+---------+
                    |       Order       |
                    |     <<Context>>   |
                    +-------------------+
                    | - state : State   |
                    +-------------------+
                    | + cancel()        |
                    | + confirm()       |
                    | + ship()          |
                    | + deliver()       |
                    | + track()         |
                    | + setState(State) |
                    +-------------------+


# ================================================================
# IMPORTANT UML RELATIONSHIPS
# ================================================================


1. ORDER → STATE
----------------

                    Order
                      |
                      |  has-a
                      v
                    State

Order ke andar:

        state : State

hai.

Matlab Order apni CURRENT STATE ko hold karta hai.

Example:

        Order
          |
          +----> PlacedState


Baad mein:

        Order
          |
          +----> ConfirmedState


Phir:

        Order
          |
          +----> ShippedState


Isliye Order aur State ke beech:

        HAS-A / Association

relationship hai.


# ================================================================
# 2. CONCRETE STATE → STATE
# ================================================================


        PlacedState
              - - - - - - - - -▷
                                State


        ConfirmedState
              - - - - - - - - -▷
                                State


        ShippedState
              - - - - - - - - -▷
                                State


        DeliveredState
              - - - - - - - - -▷
                                State


Ye IMPORTANT hai.

Concrete states:

        PlacedState
        ConfirmedState
        ShippedState
        DeliveredState

sab State interface ko IMPLEMENT karti hain.

Therefore:

        PlacedState IS-A State
        ConfirmedState IS-A State
        ShippedState IS-A State
        DeliveredState IS-A State


Standard UML mein interface implementation ko:

        dashed line + hollow triangle

se represent karte hain.

Triangle interface ki taraf point karta hai.

        ConcreteState  - - - -▷  State


# ================================================================
# 3. ORDER KA ROLE — CONTEXT
# ================================================================


                    +-------------------+
                    |       Order       |
                    |     <<Context>>   |
                    +-------------------+

Order ko Context isliye bolte hain kyunki:

    Order actual object hai jiska behavior change ho raha hai.


Example:

    Same Order object hai.

    Lekin uski state:

        Placed
           ↓
        Confirmed
           ↓
        Shipped
           ↓
        Delivered


change hoti rehti hai.

Aur state change hone ke saath Order ke operations ka behavior
bhi change ho jata hai.


# ================================================================
# 4. STATE INTERFACE KA ROLE
# ================================================================


                    <<interface>>
                  +-------------+
                  |    State    |
                  +-------------+
                  | cancel()    |
                  | confirm()   |
                  | ship()      |
                  | deliver()   |
                  | track()     |
                  +-------------+


State interface common operations define karta hai.

Har concrete state apne according in operations ka behavior
provide karegi.


Example:

    PlacedState:

        cancel()  → Order cancel ho sakta hai
        confirm() → Confirm ho sakta hai
        ship()    → Abhi nahi
        deliver() → Abhi nahi


    ShippedState:

        cancel()  → Allowed nahi
        confirm() → Already confirmed
        ship()    → Already shipped
        deliver() → Delivery complete


Yaani SAME operation:

        cancel()

different states mein different behavior de sakta hai.


# ================================================================
# 5. STATE TRANSITION
# ================================================================


          confirm()
    +--------------------+
    |                    |
    v                    |
+-----------+       +-------------+
|  Placed   | ----> |  Confirmed  |
+-----------+       +-------------+
                          |
                          | ship()
                          v
                    +-----------+
                    |  Shipped  |
                    +-----------+
                          |
                          | deliver()
                          v
                    +------------+
                    | Delivered  |
                    +------------+


Ye arrows UML ki class relationship nahi hain.

Ye STATE TRANSITIONS ko show kar rahe hain.

Matlab:

    PlacedState
        |
        | confirm()
        v
    ConfirmedState


    ConfirmedState
        |
        | ship()
        v
    ShippedState


    ShippedState
        |
        | deliver()
        v
    DeliveredState


# ================================================================
# 6. ACTUAL UML KO EK SAATH PADHO
# ================================================================


                         <<interface>>
                       +---------------+
                       |     State     |
                       +---------------+
                       | + cancel()    |
                       | + confirm()   |
                       | + ship()      |
                       | + deliver()   |
                       | + track()     |
                       +-------^-------+
                               |
                    - - - - - -|- - - - - -
                   /            |            \
                  /             |             \
                 /              |              \
                v               v               v

        +-----------+    +-------------+    +-----------+
        |  Placed   |    |  Confirmed  |    |  Shipped  |
        |   State   |    |    State    |    |   State   |
        +-----------+    +-------------+    +-----------+
        | +cancel() |    | +cancel()   |    | +cancel() |
        | +confirm()|    | +confirm()  |    | +confirm()|
        | +ship()   |    | +ship()     |    | +ship()   |
        | +deliver()|    | +deliver()  |    | +deliver()|
        | +track()  |    | +track()    |    | +track()  |
        +-----------+    +-------------+    +-----------+


                    +----------------------+
                    |        Order         |
                    |      <<Context>>     |
                    +----------------------+
                    | - state : State      |
                    +----------------------+
                    | + cancel()           |
                    | + confirm()          |
                    | + ship()             |
                    | + deliver()          |
                    | + track()            |
                    | + setState(State)    |
                    +----------+-----------+
                               |
                               |
                               | association
                               | has-a
                               |
                               v
                         +-----------+
                         |   State   |
                         +-----------+


# ================================================================
# INTERVIEW MEIN IS UML KO KAISE EXPLAIN KARNA HAI?
# ================================================================


"Here Order is the Context.

Order maintains a reference to the State interface, so Order
has-a State relationship.

State defines the common operations whose behavior can vary
depending on the current state.

PlacedState, ConfirmedState, ShippedState and DeliveredState
implement the State interface, so they have an IS-A relationship
with State.

At runtime, Order delegates its operations to its current State
object. When the state changes, the behavior of the same Order
object changes accordingly.

This allows us to replace large if-else or switch statements
with polymorphism."


# ================================================================
# SABSE IMPORTANT CHEEZ YAAD RAKH
# ================================================================


            STATE PATTERN UML


              Context
                |
                | HAS-A
                v
               State
             interface
                ^
                |
          IMPLEMENTS
                |
        +-------+-------+
        |       |       |
      StateA  StateB  StateC


Meaning:


    Context
       ↓
    "Mere paas current State hai."


    State
       ↓
    "Har state ko ye operations implement karne honge."


    Concrete States
       ↓
    "Main apni state ke according operation ka behavior dungi."


    State Change
       ↓
    Behavior Change


# ================================================================
# ONE-LINE MEMORY TRICK
# ================================================================


        Context HAS-A State

        ConcreteState IS-A State

        State changes
              ↓
        Behavior changes