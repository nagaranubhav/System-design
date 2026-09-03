/***************************************************************************************************
===================================== ADAPTER DESIGN PATTERN =====================================

INTERVIEW NOTES (THEORY PART)

----------------------------------------------------------------------------------------------------
1. PROBLEM ADAPTER PATTERN SOLVES
----------------------------------------------------------------------------------------------------

Real-world situation:

Client expects → Format A
Existing System → Format B

Both cannot talk directly because their interfaces are incompatible.

Example:
Client expects JSON
Legacy system gives XML

Instead of changing legacy code or client code,
we create an intermediate translator.

That translator = ADAPTER

----------------------------------------------------------------------------------------------------
2. SIMPLE ANALOGY (INTERVIEW GOLD)

Laptop charger analogy

Laptop plug      : 3-pin
Wall socket      : 2-pin

Adapter converts:
3-pin → 2-pin

Laptop (client) does not change
Wall socket (existing system) does not change

Adapter sits between them.

----------------------------------------------------------------------------------------------------
3. DEFINITION (INTERVIEW READY)

Adapter Pattern is a Structural Design Pattern that allows objects with incompatible
interfaces to work together by converting the interface of one class into another
interface the client expects.

----------------------------------------------------------------------------------------------------
4. WHEN TO USE ADAPTER PATTERN

Use Adapter when:

1️⃣ You want to use an existing class but its interface does not match your needs.

2️⃣ You want to reuse legacy code.

3️⃣ You cannot modify the existing system.

4️⃣ You want integration between two third-party systems.

Example scenarios:

Payment Gateway integration
Legacy APIs
Data format conversion
Library compatibility

----------------------------------------------------------------------------------------------------
5. STRUCTURE OF ADAPTER PATTERN

Important components:

1️⃣ Target Interface
2️⃣ Adaptee
3️⃣ Adapter
4️⃣ Client

Diagram:

Client
  |
  v
Target Interface (Expected Interface)
  ^
  |
Adapter (Translator)
  |
  v
Adaptee (Existing System)

----------------------------------------------------------------------------------------------------
6. COMPONENTS EXPLAINED

TARGET
------

Interface the client expects.

Example:
IReports -> getJsonData()

CLIENT
------

Code that depends only on Target interface.

Important:
Client must NOT know about adaptee.

ADAPTEE
-------

Existing class with incompatible interface.

Example:
XmlDataProvider -> getXmlData()

ADAPTER
-------

Bridges Target and Adaptee.

Adapter:
1. receives request from client
2. calls adaptee
3. converts result
4. returns expected format

----------------------------------------------------------------------------------------------------
7. TYPES OF ADAPTER PATTERN

1️⃣ OBJECT ADAPTER (MOST COMMON)

Uses composition.

Adapter HAS-A Adaptee.

Example:
XmlDataProviderAdapter
contains
XmlDataProvider*

Advantage:
Flexible

----------------------------------------------------------------------------------------------------

2️⃣ CLASS ADAPTER

Uses inheritance.

Adapter extends Adaptee and implements Target.

Not common in C++.

----------------------------------------------------------------------------------------------------
8. REAL WORLD EXAMPLES

Java InputStreamReader

InputStreamReader
adapts
InputStream → Reader

Payment gateways

Stripe API → internal payment interface

Legacy system integration

XML service → JSON microservice

----------------------------------------------------------------------------------------------------
9. ADVANTAGES

1️⃣ Reuse existing code
2️⃣ Loose coupling
3️⃣ Integrates legacy systems
4️⃣ No modification needed in client or adaptee

----------------------------------------------------------------------------------------------------
10. DISADVANTAGES

1️⃣ Extra abstraction layer
2️⃣ Too many adapters can make system complex

----------------------------------------------------------------------------------------------------
11. INTERVIEW QUESTIONS

Q1: Difference between Adapter and Decorator?

Adapter
changes interface

Decorator
adds behavior

------------------------------------

Q2: Difference between Adapter and Facade?

Adapter
converts interface

Facade
simplifies interface

------------------------------------

Q3: Adapter uses which principle?

Composition over inheritance

----------------------------------------------------------------------------------------------------
12. FAANG INTERVIEW ANSWER STRUCTURE

If asked:

"Explain Adapter Pattern"

Answer structure:

1️⃣ Define the problem (incompatible interfaces)
2️⃣ Explain idea (translation layer)
3️⃣ Show structure (Target, Adapter, Adaptee, Client)
4️⃣ Give real-world example
5️⃣ Mention advantages

This shows senior level understanding.

***************************************************************************************************/