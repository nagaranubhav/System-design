# Chain of Responsibility
# Concrete Example: Leave Approval System

============================================================
1. UML CLASS DIAGRAM
============================================================


                         ┌──────────────────────────────────┐
                         │         LeaveHandler             │
                         │          <<abstract>>             │
                         ├──────────────────────────────────┤
                         │ # next: shared_ptr<LeaveHandler>│
                         ├──────────────────────────────────┤
                         │ + setNext(handler)               │
                         │ + handleRequest(request)          │
                         └────────────────┬─────────────────┘
                                          │
                         ┌────────────────┼────────────────┐
                         │                │                │
                         │                │                │
                     inherits         inherits         inherits
                         │                │                │
                         ▼                ▼                ▼
              ┌─────────────────┐ ┌─────────────────┐ ┌─────────────────┐
              │     Manager     │ │    Director     │ │       VP        │
              ├─────────────────┤ ├─────────────────┤ ├─────────────────┤
              │ + handleRequest │ │ + handleRequest │ │ + handleRequest │
              └────────┬────────┘ └────────┬────────┘ └────────┬────────┘
                       │                   │                   │
                       │                   │                   │
                       │ setNext()        │ setNext()         │
                       │                   │                   │
                       ▼                   ▼                   ▼
                  ┌─────────┐         ┌─────────┐          ┌─────────┐
                  │Director │────────►│   VP    │─────────►│  null   │
                  └─────────┘         └─────────┘          └─────────┘


                         ▲
                         │
                         │ sends
                         │
              ┌──────────────────────┐
              │       Client         │
              │       main()         │
              └──────────┬───────────┘
                         │
                         │ handleRequest()
                         ▼
              ┌──────────────────────┐
              │      Manager         │
              └──────────────────────┘



============================================================
2. REQUEST CLASS
============================================================


              ┌──────────────────────────────┐
              │       LeaveRequest          │
              ├──────────────────────────────┤
              │ - employeeName : string     │
              │ - days : int                │
              ├──────────────────────────────┤
              │ + LeaveRequest(name, days)  │
              └──────────────┬───────────────┘
                             │
                             │ passed to
                             ▼
                    ┌─────────────────┐
                    │  LeaveHandler   │
                    └─────────────────┘



============================================================
3. COMPLETE RELATIONSHIP
============================================================


                    <<abstract>>
                 ┌─────────────────┐
                 │  LeaveHandler   │
                 ├─────────────────┤
                 │ next            │◄────────────────────┐
                 ├─────────────────┤                     │
                 │ setNext()       │                     │
                 │ handleRequest() │                     │
                 └────────┬────────┘                     │
                          │                              │
             implements   │                              │
          ┌───────────────┼────────────────┐             │
          │               │                │             │
          ▼               ▼                ▼             │
     ┌──────────┐    ┌──────────┐    ┌──────────┐       │
     │ Manager  │    │ Director │    │    VP    │       │
     └────┬─────┘    └────┬─────┘    └────┬─────┘       │
          │               │               │             │
          │ next          │ next          │             │
          ▼               ▼               ▼             │
     ┌──────────┐    ┌──────────┐       null            │
     │ Director │───►│    VP    │───────────────────────┘
     └──────────┘    └──────────┘


          ┌──────────────────┐
          │  LeaveRequest    │
          ├──────────────────┤
          │ employeeName     │
          │ days             │
          └────────┬─────────┘
                   │
                   │ request
                   ▼
             ┌───────────┐
             │  Manager  │
             └───────────┘



============================================================
4. UML KO STEP-BY-STEP KAISE READ KARE?
============================================================


STEP 1:
--------

Sabse pehle hamare paas ek common abstraction hai:

                LeaveHandler

Ye decide karta hai ki har handler ke paas kya common
functionality hogi.

Isme:

    next

aur

    handleRequest()

hai.


------------------------------------------------------------

STEP 2:
--------

Manager, Director aur VP:

    LeaveHandler

ko inherit karte hain.

Isliye teeno ke paas:

    handleRequest()

available hai.


                    LeaveHandler
                         ▲
                         │
              ┌──────────┼──────────┐
              │          │          │
              │          │          │
           Manager    Director      VP


------------------------------------------------------------

STEP 3:
--------

LeaveHandler ke andar:

    next

hai.

Ye bahut important hai.

next ka matlab:

    "Agar main request handle nahi kar paaya,
     toh request kis handler ko deni hai?"

Example:

    Manager.next = Director

    Director.next = VP

    VP.next = null


Isliye actual chain ban jaati hai:


    Manager
       │
       ▼
    Director
       │
       ▼
      VP
       │
       ▼
     null


------------------------------------------------------------

STEP 4:
--------

Client ko sirf Manager ka pata hai.

Client:

    manager->handleRequest(request);


Client ko ye pata hona zaroori nahi hai ki:

    Manager -> Director -> VP

chain ke andar kya hai.

Ye Chain of Responsibility ka main benefit hai.


============================================================
5. ACTUAL REQUEST FLOW
============================================================


Suppose:

    Employee = Anubhav
    Leave    = 10 days


Client:

    manager->handleRequest(request);


              Client
                 │
                 │ 10 days
                 ▼
             ┌─────────┐
             │ Manager │
             └────┬────┘
                  │
                  │ 10 > 3
                  │ Cannot handle
                  ▼
             ┌──────────┐
             │ Director │
             └────┬─────┘
                  │
                  │ 10 > 7
                  │ Cannot handle
                  ▼
             ┌─────────┐
             │   VP    │
             └────┬────┘
                  │
                  │ 10 <= 15
                  │ Can handle
                  ▼
               APPROVED


IMPORTANT:

Manager ne request reject nahi ki.

Manager ne bola:

    "Main handle nahi kar sakta,
     next handler ko de do."

Same Director ke saath hua.

VP ne handle kar liya,
isliye chain wahi stop ho gayi.


============================================================
6. DIFFERENT REQUESTS KA FLOW
============================================================


CASE 1: 2 DAYS
---------------

    Client
      │
      ▼
    Manager
      │
      │ 2 <= 3
      ▼
    APPROVED

Chain:

    Manager


------------------------------------------------------------

CASE 2: 5 DAYS
---------------

    Client
      │
      ▼
    Manager
      │
      │ 5 > 3
      ▼
    Director
      │
      │ 5 <= 7
      ▼
    APPROVED

Chain used:

    Manager → Director


------------------------------------------------------------

CASE 3: 10 DAYS
----------------

    Client
      │
      ▼
    Manager
      │
      │ cannot handle
      ▼
    Director
      │
      │ cannot handle
      ▼
    VP
      │
      │ can handle
      ▼
    APPROVED

Chain used:

    Manager → Director → VP


------------------------------------------------------------

CASE 4: 20 DAYS
----------------

    Client
      │
      ▼
    Manager
      │
      ▼
    Director
      │
      ▼
    VP
      │
      │ cannot handle
      ▼
    REJECTED

Chain completely traverse ho gayi.


============================================================
7. UML MEIN SABSE IMPORTANT PART
============================================================


Ye:

    # next : shared_ptr<LeaveHandler>


Aur ye:

    + setNext(handler)


actually Chain of Responsibility ko create karte hain.


Hum:

    manager->setNext(director);

    director->setNext(vp);


karte hain.


Result:


    Manager
       │
       │ next
       ▼
    Director
       │
       │ next
       ▼
       VP
       │
       │ next
       ▼
      null


Isi ko hum:

    CHAIN

bol rahe hain.


============================================================
8. INTERVIEW MEIN UML EXPLAIN KARNE KA BEST TARIKA
============================================================


Agar interviewer bole:

"Explain your Chain of Responsibility design."


Tu bol sakta hai:


"First, I define a common Handler abstraction that contains
the request handling operation and a reference to the next
handler.

Each concrete handler decides whether it can handle the
request.

If it can handle the request, it processes it.

Otherwise, it forwards the request to the next handler.

In my example, Manager, Director and VP form the chain.
The client only interacts with the first handler, Manager,
and does not need to know which handler will ultimately
process the request."


Then diagram draw kar:


              LeaveHandler
                   ▲
           ┌───────┼───────┐
           │       │       │
        Manager Director   VP

        Manager → Director → VP


Aur bol:


"The important part is the `next` reference because that
creates the chain."


============================================================
9. ONE-LINE UML MEMORY TRICK
============================================================


             Handler
                ▲
       ┌────────┼────────┐
       │        │        │
       A        B        C

       A → B → C → null


Har Handler:

    Can I handle?
          │
      ┌───┴───┐
     YES      NO
      │        │
      ▼        ▼
   HANDLE     NEXT


Bas yahi Chain of Responsibility ka poora UML concept hai.


============================================================