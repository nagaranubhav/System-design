=========================================================
              BRIDGE DESIGN PATTERN
=========================================================

CATEGORY:
Structural Design Pattern

INTENT (Most Important Line):
"Decouple abstraction from its implementation so that both
can vary independently."

Simple Line:
"2 dimensions ko alag kar do taaki independently grow kar sakein."

---------------------------------------------------------
1) CORE INTUITION (VERY IMPORTANT)
---------------------------------------------------------

Imagine:

Cars:
- Sedan
- SUV

Engines:
- Petrol
- Diesel
- Electric

Agar inheritance use karte:
- PetrolSedan
- DieselSedan
- ElectricSedan
- PetrolSUV
- DieselSUV
- ElectricSUV

TOTAL CLASSES = N * M explosion 😱

Ye hi problem hai → CLASS EXPLOSION

Bridge bolta:
"Inheritance mat use karo, composition use karo."

Car "has-a" Engine

Now:
Cars grow independently
Engines grow independently

---------------------------------------------------------
2) PROBLEM IT SOLVES
---------------------------------------------------------

Without Bridge:
Multiple dimensions = exponential classes

Problems:
1. Class explosion
2. Tight coupling
3. Hard to extend
4. Code duplication
5. Violation of Open/Closed Principle

Bridge solves:
Decoupling + scalability

---------------------------------------------------------
3) WHEN TO USE
---------------------------------------------------------

Use Bridge when:
1. Multiple orthogonal dimensions ho
2. Runtime pe implementation change karna ho
3. Class explosion avoid karna ho
4. Implementation hide karna ho
5. Platform independent design chahiye

Golden Line:
"When abstraction and implementation both should evolve independently"

---------------------------------------------------------
4) UML DIAGRAM
---------------------------------------------------------

            ABSTRACTION LAYER (HLL)
                   +----------------+
                   |     Car        |
                   +----------------+
                   | - Engine*      |
                   | +drive()       |
                   +----------------+
                           ^
                           |
          ---------------------------------
          |                               |
   +--------------+              +--------------+
   |    Sedan     |              |     SUV      |
   +--------------+              +--------------+

                     ||
                     || BRIDGE (composition)
                     \/

         IMPLEMENTATION LAYER (LLL)
                   +----------------+
                   |    Engine      |
                   +----------------+
                   | +start()       |
                   +----------------+
                          ^
                          |
       ------------------------------------------
       |                  |                     |
+--------------+  +--------------+   +--------------+
| PetrolEngine |  | DieselEngine |   | ElectricEngine|
+--------------+  +--------------+   +--------------+

---------------------------------------------------------
5) PARTICIPANTS
---------------------------------------------------------

1. Abstraction (Car)
   - High-level interface
   - Contains reference of Implementor

2. Refined Abstraction (Sedan, SUV)
   - Extends abstraction
   - Uses implementation

3. Implementor (Engine)
   - Interface for implementation

4. Concrete Implementor
   - PetrolEngine, DieselEngine, ElectricEngine

---------------------------------------------------------
6) WHY WE NEED BRIDGE
---------------------------------------------------------

Key reasons:
1. Avoid class explosion
2. Decouple layers
3. Runtime flexibility
4. Independent extensibility
5. Clean architecture

---------------------------------------------------------
7) REAL LIFE EXAMPLES
---------------------------------------------------------

1. Remote + TV
   Remote types:
   - BasicRemote
   - SmartRemote

   TV brands:
   - SonyTV
   - SamsungTV

2. Payment System
   Payment:
   - CreditCard
   - UPI

   Gateway:
   - Razorpay
   - Stripe

3. Notification System
   Type:
   - Email
   - SMS

   Provider:
   - AWS SES
   - Twilio

4. GUI Framework
   Elements:
   - Button
   - Checkbox

   Platform:
   - Windows
   - Mac

---------------------------------------------------------
8) BRIDGE vs STRATEGY (VERY IMPORTANT 🔥)
---------------------------------------------------------

CONFUSION POINT!!

Both use composition... BUT INTENT DIFFERENT HAI.

---------------------------------------------------------
BRIDGE:
---------------------------------------------------------
Intent:
Separate abstraction & implementation.

Focus:
Structure of system

Use when:
2 independent dimensions exist

Example:
Car + Engine

Relationship:
Abstraction HAS-A Implementor

---------------------------------------------------------
STRATEGY:
---------------------------------------------------------
Intent:
Change behavior at runtime

Focus:
Algorithm variation

Use when:
Multiple algorithms for same task

Example:
Sorting strategy
Payment strategy

---------------------------------------------------------
KEY DIFFERENCE:
---------------------------------------------------------

Bridge:
"Structure split karna hai"

Strategy:
"Behavior change karna hai"

---------------------------------------------------------
Analogy:
---------------------------------------------------------

Bridge:
TV + Remote
2 separate dimensions

Strategy:
Sorting algorithm
same task, different ways

---------------------------------------------------------
9) HOW TO IDENTIFY IN INTERVIEW
---------------------------------------------------------

If interviewer says:
- "multiple dimensions"
- "avoid combinations"
- "platform independent"
- "decouple layers"

→ BRIDGE

If says:
- "different algorithms"
- "runtime behavior change"
- "switch logic"

→ STRATEGY

---------------------------------------------------------
10) ADVANTAGES
---------------------------------------------------------

1. Removes class explosion
2. Open/Closed principle
3. Flexible design
4. Runtime switching possible
5. Clean separation of concerns

---------------------------------------------------------
11) DISADVANTAGES
---------------------------------------------------------

1. Extra complexity
2. More classes
3. Indirection overhead

---------------------------------------------------------
12) INTERVIEW ANSWER TEMPLATE
---------------------------------------------------------

"Bridge pattern is used to decouple abstraction from its
implementation so both can vary independently. It helps
avoid class explosion when we have multiple orthogonal
dimensions by using composition instead of inheritance."

---------------------------------------------------------
13) GOLDEN TAKEAWAY
---------------------------------------------------------

"Bridge = Composition over Inheritance for multi-dimension problems"

=========================================================