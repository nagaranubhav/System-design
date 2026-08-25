# Chain of Responsibility Design Pattern

## 1. UML Diagram

                         ┌──────────────────────────────┐
                         │          Handler             │
                         │          <<interface>>       │
                         ├──────────────────────────────┤
                         │ + setNext(Handler)           │
                         │ + handle(Request)            │
                         └───────────────┬──────────────┘
                                         │
                                         │ implements
                 ┌───────────────────────┼────────────────────────┐
                 │                       │                        │
                 ▼                       ▼                        ▼
       ┌─────────────────┐     ┌─────────────────┐      ┌─────────────────┐
       │    HandlerA     │     │    HandlerB     │      │    HandlerC     │
       ├─────────────────┤     ├─────────────────┤      ├─────────────────┤
       │ - next: Handler │     │ - next: Handler │      │ - next: Handler │
       ├─────────────────┤     ├─────────────────┤      ├─────────────────┤
       │ + handle()      │     │ + handle()      │      │ + handle()      │
       └────────┬────────┘     └────────┬────────┘      └────────┬────────┘
                │                       │                        │
                │ next                  │ next                   │
                └──────────────────────►└───────────────────────►│
                                                                 │
                                                                 ▼
                                                               null


                         Request Flow

        Client
          │
          ▼
     ┌──────────┐
     │ HandlerA │
     └────┬─────┘
          │
          │ Can't Handle
          ▼
     ┌──────────┐
     │ HandlerB │
     └────┬─────┘
          │
          │ Can't Handle
          ▼
     ┌──────────┐
     │ HandlerC │
     └────┬─────┘
          │
          │ Can't Handle
          ▼
        END


============================================================
2. Problem
============================================================

Normally agar multiple objects request ko handle kar sakte hain,
toh hum code mein directly conditions likhne lagte hain:

    if (manager) {
        ...
    }
    else if (director) {
        ...
    }
    else if (admin) {
        ...
    }

Problem:

- Client ko pata hota hai ki request kis object ko deni hai.
- Bahut saare if-else / switch statements ban jaate hain.
- New handler add karne par existing code modify karna padta hai.
- Sender aur receiver ke beech tight coupling ho jaati hai.
- Request processing ka flow difficult to maintain ho jaata hai.


============================================================
3. Solution
============================================================

Chain of Responsibility pattern request ko handlers ki ek chain
mein pass karta hai.

Har handler ke paas:

    1. Request ko handle karne ka chance hota hai.
    2. Agar handle kar sakta hai -> request process karega.
    3. Agar handle nahi kar sakta -> next handler ko forward karega.

Example:

    Handler A
       |
       | cannot handle
       v
    Handler B
       |
       | cannot handle
       v
    Handler C
       |
       | handles
       v
      Done


============================================================
4. Pattern mein kya use hua?
============================================================

Main abstraction:

    Handler

Handler ke andar:

    Handler* next;

Ye "next" reference chain create karta hai.

Example:

    HandlerA -> HandlerB -> HandlerC -> null


Client ko sirf first handler ke baare mein pata hota hai:

    handlerA->handle(request);

Uske baad request chain ke andar automatically travel karti hai.


============================================================
5. Core Idea
============================================================

"Give multiple objects a chance to handle a request by passing
the request along a chain of handlers."


Simple words:

    Request
       ↓
    Kya main handle kar sakta hoon?
       ↓
      YES ──────> Handle
       │
       NO
       ↓
    Next Handler
       ↓
    Kya main handle kar sakta hoon?
       ↓
      YES ──────> Handle
       │
       NO
       ↓
    Next Handler


============================================================
6. Kab use karna hai?
============================================================

Chain of Responsibility tab use karo jab:

1. Multiple objects request ko handle kar sakte hain.

2. Tum nahi chahte ki sender ko pata ho ki actual handler kaun hai.

3. Request ko sequentially different handlers ke through pass
   karna hai.

4. Handler order important hai.

5. Runtime par chain change karni ho.

6. Future mein naye handlers easily add karne hain.


============================================================
7. Real-Life Examples
============================================================

Example 1: Leave Approval

Employee
   ↓
Manager
   ↓
Director
   ↓
VP

Manager chhoti leave approve karega.

Agar leave manager ki limit se bahar hai,
toh Director ko forward karega.

Agar Director bhi approve nahi kar sakta,
toh VP ko forward karega.


Example 2: Customer Support

Level 1 Support
   ↓
Level 2 Support
   ↓
Senior Engineer
   ↓
Manager

Har level request ko solve karne ki try karega.


Example 3: Logging

INFO
 ↓
DEBUG
 ↓
WARNING
 ↓
ERROR

Different handlers different log levels process kar sakte hain.


Example 4: Authentication / Authorization

Request
   ↓
Authentication Handler
   ↓
Role Handler
   ↓
Permission Handler
   ↓
Final Handler


============================================================
8. Interview mein kaunsa hint milega?
============================================================

Agar question mein ye words aaye:

    "pass the request"
    "forward the request"
    "next handler"
    "one of several handlers"
    "don't know who will handle"
    "hierarchy of handlers"
    "if one cannot handle, pass to next"
    "request travels through multiple objects"

Toh Chain of Responsibility ke baare mein sochna.


============================================================
9. Strategy vs Chain of Responsibility
============================================================

Ye confusion interview mein bahut common hai.

Strategy:

    Client chooses ONE strategy.

        Client
          |
          └──> Strategy

Example:

    CreditCard
    UPI
    PayPal

Ek time par generally ek strategy choose hoti hai.


Chain of Responsibility:

    Request handlers ki CHAIN mein travel karti hai.

        Client
          |
          ▼
       Handler A
          |
          ▼
       Handler B
          |
          ▼
       Handler C

Handler A handle karega toh chain stop.

Nahi toh B.

B nahi karega toh C.


============================================================
10. Important Design Point
============================================================

Chain ko client se hide karna important hai.

Client:

    handler->handle(request);

Client ko ye nahi pata:

    A ke baad B hai
    B ke baad C hai
    C final handler hai

Ye chain ka internal responsibility hai.


============================================================
11. Benefits
============================================================

+ Sender aur receiver decoupled hote hain.
+ New handler easily add kar sakte ho.
+ Existing handlers ko modify karne ki zarurat kam hoti hai.
+ Runtime par chain configure/change kar sakte ho.
+ Request processing flexible ho jaati hai.


============================================================
12. Drawbacks
============================================================

- Request potentially poori chain traverse kar sakti hai.
- Agar kisi handler ne request handle nahi ki toh request unhandled
  reh sakti hai.
- Large chain debugging difficult ho sakti hai.
- Handler order galat hua toh behaviour change ho sakta hai.


============================================================
13. One-Line Memory Trick
============================================================

"Main nahi kar sakta -> next ko de do."


Ye line yaad rakh:

    HANDLE KAR SAKTA HOON?
           |
       YES | NO
        ↓   ↓
      HANDLE NEXT


============================================================