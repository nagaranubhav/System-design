=========================================================
                 STATE DESIGN PATTERN
=========================================================

CATEGORY:
Behavioral Design Pattern

INTENT (MOST IMPORTANT):
"Allow an object to alter its behavior when its internal
state changes. The object appears to change its class."

Simple one-line:
"State change hone par object ka behavior automatically change ho."

Golden line:
Same method call, different behavior based on current state.

---------------------------------------------------------
1) CORE INTUITION
---------------------------------------------------------

Real life soch:

Vending Machine:
States:
- NO_COIN
- HAS_COIN
- DISPENSING
- SOLD_OUT

Same operation:
selectItem()

Behavior changes:
- NO_COIN → "insert coin first"
- HAS_COIN → "check balance"
- SOLD_OUT → "machine empty"

Method same
Behavior state ke hisaab se different

This is State Pattern 🔥

---------------------------------------------------------
2) PROBLEM IT SOLVES
---------------------------------------------------------

Without state pattern:
Context class me huge if-else / switch hota

if(state == NO_COIN) ...
else if(state == HAS_COIN) ...
else if(state == SOLD_OUT) ...

Problems:
1. Massive conditional logic
2. Hard to extend
3. Hard to test
4. OCP violation
5. State transitions scattered

State pattern:
Har state apna behavior khud handle kare

---------------------------------------------------------
3) WHEN TO USE
---------------------------------------------------------

Use when:
1. Object ka behavior state pe depend karta ho
2. State transitions complex ho
3. Too many if-else chains ho
4. Lifecycle driven system ho
5. Workflow transitions ho

Golden trigger:
"Same action but different behavior in different states"

---------------------------------------------------------
4) UML DIAGRAM
---------------------------------------------------------

                    +----------------------+
                    |   VendingState       |
                    +----------------------+
                    | +insertCoin()        |
                    | +selectItem()        |
                    | +dispense()          |
                    | +returnCoin()        |
                    +----------------------+
                              ^
                              |
      -------------------------------------------------------
      |                |               |                    |
      |                |               |                    |
+-------------+  +-------------+  +-------------+  +-------------+
| NoCoinState |  | HasCoinState|  |DispenseState|  |SoldOutState |
+-------------+  +-------------+  +-------------+  +-------------+

                              ^
                              |
                    +----------------------+
                    |   VendingMachine     |
                    +----------------------+
                    | - currentState       |
                    | - itemCount          |
                    | - insertedCoins      |
                    +----------------------+
                    | +insertCoin()        |
                    | +selectItem()        |
                    +----------------------+

---------------------------------------------------------
5) PARTICIPANTS
---------------------------------------------------------

1) State Interface
Common behavior contract

2) Concrete States
Actual state-specific logic
- NoCoinState
- HasCoinState
- DispenseState
- SoldOutState

3) Context
Current state maintain karta hai
delegation karta hai

---------------------------------------------------------
6) WHY WE NEED IT
---------------------------------------------------------

Need because:
- behavior dynamic hai
- transitions multiple hain
- workflow complex hai
- lifecycle rules strict hain

Most important:
"State-specific behavior ko modular banana"

---------------------------------------------------------
7) REAL LIFE EXAMPLES
---------------------------------------------------------

1. Vending Machine
2. ATM machine
3. Order lifecycle
   - CREATED
   - PAID
   - SHIPPED
   - DELIVERED
4. Traffic light
5. Media player
6. TCP connection lifecycle
7. Game character states
8. Elevator states

---------------------------------------------------------
8) STATE vs STRATEGY (VERY IMPORTANT 🔥)
---------------------------------------------------------

Dono composition use karte
BUT INTENT ALAG HAI

---------------------------------------------------------
STATE:
---------------------------------------------------------
Intent:
Behavior changes due to INTERNAL state transitions

Focus:
Object lifecycle / workflow

Example:
Vending machine states

Transition:
Automatic / rule-driven

---------------------------------------------------------
STRATEGY:
---------------------------------------------------------
Intent:
Choose algorithm externally

Focus:
Behavior variation

Example:
Payment method
Sort strategy

Transition:
Client driven

---------------------------------------------------------
KEY DIFFERENCE:
---------------------------------------------------------

State:
"object changes itself"

Strategy:
"client changes behavior"

---------------------------------------------------------
9) HOW TO IDENTIFY IN INTERVIEW
---------------------------------------------------------

If interviewer says:
- lifecycle
- workflow
- state transitions
- status-based behavior
- remove if else

→ Think STATE PATTERN

---------------------------------------------------------
10) ADVANTAGES
---------------------------------------------------------

1. Removes giant if-else
2. Easy extensibility
3. Better testing
4. Clear transitions
5. OCP compliant
6. Modular state logic
7. Cleaner workflows

---------------------------------------------------------
11) DISADVANTAGES
---------------------------------------------------------

1. More classes
2. Transition debugging tricky
3. Overkill for simple systems

---------------------------------------------------------
12) INTERVIEW ANSWER TEMPLATE
---------------------------------------------------------

"State pattern is used when object behavior changes based
on its internal lifecycle state. Instead of using large
conditional logic, each state is represented as a separate
class encapsulating state-specific behavior and transitions."

---------------------------------------------------------
13) GOLDEN TAKEAWAY
---------------------------------------------------------

State = Replace lifecycle if-else with polymorphic states

=========================================================