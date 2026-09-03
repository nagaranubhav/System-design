============================================================
          ADAPTER DESIGN PATTERN — REAL WORLD EXAMPLE
             OLD PAYMENT SYSTEM + NEW PAYMENT SYSTEM
============================================================

YRR ek realistic example lete hain:

Maan le hamari application mein ek NEW payment system hai.

Hamari application chahti hai ki har payment gateway ke paas:

        pay(amount)

function ho.

Lekin hume ek OLD payment library milti hai jisme:

        makePayment(amount)

function hai.

Functionality dono ki same hai:

        "Payment karna"

Lekin function ka naam/interface different hai.

Hum OLD library ka code change nahi karna chahte.

Toh hum Adapter use karenge.


============================================================
1. PROBLEM KO PEHLE SAMJHO
============================================================

Hamari application bolti hai:

        "Mujhe pay() chahiye."

Lekin OldPaymentSystem bolta hai:

        "Mere paas makePayment() hai."

Matlab:

        CLIENT
           |
           | wants pay()
           v
        Target
           ^
           |
        Adapter
           |
           | calls makePayment()
           v
    OldPaymentSystem


Adapter yahan TRANSLATOR ka kaam karega.


============================================================
2. COMPLETE CODE
============================================================

#include <iostream>
using namespace std;


// ==========================================================
// 1. TARGET
// ==========================================================
//
// Ye hamari application ka expected interface hai.
//
// Application chahti hai ki payment karne ke liye
// har payment system mein pay() function ho.
//

class PaymentProcessor {

public:

    virtual void pay(double amount) = 0;

    virtual ~PaymentProcessor() = default;
};


// ==========================================================
// 2. ADAPTEE
// ==========================================================
//
// Ye existing/old payment system hai.
//
// Iska code already bana hua hai.
// Hum isko change nahi karna chahte.
//
// Problem:
// Isme pay() nahi hai.
//
// Isme function ka naam hai:
//
//     makePayment()
//
//

class OldPaymentSystem {

public:

    void makePayment(double amount) {

        cout << "Old Payment System: "
             << "Paid Rs. " << amount << endl;
    }
};


// ==========================================================
// 3. ADAPTER
// ==========================================================
//
// Adapter Target ko implement karega.
//
// Isliye:
//
//     Adapter IS-A PaymentProcessor
//
// Aur Adapter ke paas OldPaymentSystem ka object hoga.
//
// Isliye:
//
//     Adapter HAS-A OldPaymentSystem
//
// Adapter ka kaam:
//
//     pay()
//        |
//        v
//     makePayment()
//
//

class PaymentAdapter : public PaymentProcessor {

private:

    OldPaymentSystem oldPaymentSystem;


public:

    void pay(double amount) override {

        // Client ne pay() call kiya.
        //
        // Lekin OldPaymentSystem ke paas pay() nahi hai.
        //
        // Isliye Adapter us call ko convert karega:

        oldPaymentSystem.makePayment(amount);
    }
};


// ==========================================================
// 4. CLIENT
// ==========================================================
//
// Client ko sirf PaymentProcessor ke baare mein pata hai.
//
// Client ko ye nahi pata ki andar:
//     New payment system hai
//     Old payment system hai
//     Adapter hai
//
// Client bas:
//
//     pay()
//
// call karta hai.
//

class Checkout {

public:

    void makePayment(PaymentProcessor* processor,
                     double amount) {

        processor->pay(amount);
    }
};


// ==========================================================
// 5. MAIN
// ==========================================================

int main() {

    Checkout checkout;

    PaymentProcessor* processor =
        new PaymentAdapter();

    checkout.makePayment(processor, 5000);

    delete processor;

    return 0;
}


============================================================
3. AB CODE KO STEP-BY-STEP SAMJHO
============================================================


STEP 1:
-------

Ye hamara TARGET hai:

        class PaymentProcessor

        virtual void pay(double amount) = 0;


Matlab hamari application ka rule hai:

        "Mujhe payment karni hai,
         aur payment karne ke liye pay() available hona chahiye."


Toh Client sirf PaymentProcessor ko jaanta hai.


------------------------------------------------------------

STEP 2:
-------

Ab hamare paas ek OLD SYSTEM hai:

        class OldPaymentSystem

Iske paas:

        makePayment()

hai.


Problem:

PaymentProcessor:

        pay()


OldPaymentSystem:

        makePayment()


Dono ka kaam same hai:

        PAYMENT

Lekin interface different hai.


------------------------------------------------------------

STEP 3:
-------

Ab hum directly Client se OldPaymentSystem ko use nahi kar
sakte.

Client:

        processor->pay(5000);


Lekin:

        OldPaymentSystem

ke paas:

        pay()

hai hi nahi.


Isliye mismatch hai.


------------------------------------------------------------

STEP 4:
-------

Hum Adapter banate hain:

        class PaymentAdapter : public PaymentProcessor


Ye line bahut important hai.


        PaymentAdapter IS-A PaymentProcessor


Kyun?

Kyuki PaymentAdapter ne PaymentProcessor ko inherit kiya hai.


Isliye:

        PaymentProcessor* processor;

mein hum:

        PaymentAdapter

ka object rakh sakte hain.


------------------------------------------------------------

STEP 5:
-------

Ab Adapter ke andar:

        OldPaymentSystem oldPaymentSystem;


Ye kya hai?

        Adapter HAS-A OldPaymentSystem


Matlab Adapter ke paas old payment system ka object hai.


Adapter khud payment ka actual old implementation nahi likh raha.

Wo old system ko use kar raha hai.


------------------------------------------------------------

STEP 6:
-------

Ab sabse important function:

        void pay(double amount) override {

            oldPaymentSystem.makePayment(amount);
        }


Client bolta hai:

        pay(5000)


Adapter receive karta hai:

        pay(5000)


Aur Adapter internally bolta hai:

        oldPaymentSystem.makePayment(5000)


Matlab:

        Client
           |
           | pay(5000)
           v
      PaymentAdapter
           |
           | makePayment(5000)
           v
    OldPaymentSystem


YAHI ADAPTER PATTERN HAI.


============================================================
4. MAIN FUNCTION KA DRY RUN
============================================================

Code:

    Checkout checkout;

    PaymentProcessor* processor =
        new PaymentAdapter();


Yahan:

        processor

ka type hai:

        PaymentProcessor*


Lekin actual object hai:

        PaymentAdapter


Ye possible hai kyunki:

        PaymentAdapter IS-A PaymentProcessor


------------------------------------------------------------

Ab:

    checkout.makePayment(processor, 5000);


Client ke paas:

        PaymentProcessor*

hai.


Checkout ke andar:

    processor->pay(5000);


call hota hai.


Lekin actual object PaymentAdapter hai.

Isliye runtime par:

        PaymentAdapter::pay()

call hoga.


Adapter ke andar:

    oldPaymentSystem.makePayment(5000);


call hoga.


Aur output:

    Old Payment System: Paid Rs. 5000


============================================================
5. PURA FLOW EK BAAR VISUALIZE KARO
============================================================


        +----------------------+
        |       Checkout       |
        |       CLIENT         |
        +----------------------+
                   |
                   | pay(5000)
                   v
        +----------------------+
        |   PaymentProcessor   |
        |       TARGET         |
        |----------------------|
        | + pay(amount)        |
        +----------------------+
                   ^
                   |
                 IS-A
                   |
        +----------------------+
        |   PaymentAdapter     |
        |       ADAPTER        |
        |----------------------|
        | - oldPaymentSystem   |------+
        | + pay(amount)        |      |
        +----------------------+      |
                                      |
                                    HAS-A
                                      |
                                      v
                             +----------------------+
                             | OldPaymentSystem    |
                             |      ADAPTEE         |
                             |----------------------|
                             | + makePayment()      |
                             +----------------------+


============================================================
6. AB "IS-A" AUR "HAS-A" PERFECTLY SAMAJHO
============================================================


                    TARGET
                      ^
                      |
                    IS-A
                      |
                   ADAPTER
                      |
                    HAS-A
                      |
                      v
                   ADAPTEE


ADAPTER IS-A TARGET
-------------------

Code:

    class PaymentAdapter : public PaymentProcessor


Matlab:

    PaymentAdapter ek PaymentProcessor hai.


Isliye Client usko PaymentProcessor samajh sakta hai.


------------------------------------------------------------

ADAPTER HAS-A ADAPTEE
---------------------

Code:

    OldPaymentSystem oldPaymentSystem;


Matlab:

    PaymentAdapter ke paas OldPaymentSystem hai.


Adapter us old object ko use karke
actual kaam karwa raha hai.


============================================================
7. AGAR ADAPTER NA HOTA TOH?
============================================================

Client:

    checkout.makePayment(
        oldPaymentSystem,
        5000
    );


Problem:

Checkout ko PaymentProcessor chahiye.

OldPaymentSystem PaymentProcessor nahi hai.


Aur agar hum Client ke code ko change karne lag gaye:

    oldPaymentSystem.makePayment(5000);


toh hamara Client directly old implementation
ke saath tightly coupled ho jayega.


Kal ko old payment system replace karna hua,
toh Client ka code bhi change karna padega.


Adapter ye problem solve karta hai.


============================================================
8. ADAPTER USE KARNE KE BAAD
============================================================

Client ko sirf ye pata hai:

        PaymentProcessor

                |

              pay()


Client ko andar ki implementation ki tension nahi.


Aaj:

        PaymentAdapter
              |
              v
        OldPaymentSystem


Kal:

        PaymentAdapter
              |
              v
        SomeOtherOldPaymentSystem


Client same rahega.


        checkout.makePayment(processor, 5000);


Client ko kuch change nahi karna.


============================================================
9. REAL-LIFE MEIN KAHAN USE HOGA?
============================================================


EXAMPLE 1 — PAYMENT
-------------------

Application expects:

        pay()


Third-party library provides:

        makePayment()


Adapter:

        pay()
          ↓
        makePayment()


------------------------------------------------------------

EXAMPLE 2 — OLD DATABASE
------------------------

New application expects:

        saveUser()


Old database library provides:

        insertRecord()


Adapter:

        saveUser()
            ↓
        insertRecord()


------------------------------------------------------------

EXAMPLE 3 — THIRD-PARTY API
----------------------------

Application expects:

        sendMessage()


Third-party API provides:

        sendSMSMessage()


Adapter:

        sendMessage()
             ↓
        sendSMSMessage()


------------------------------------------------------------

EXAMPLE 4 — LEGACY CODE
-----------------------

New code expects:

        getUser()


Legacy system provides:

        fetchUserData()


Adapter:

        getUser()
           ↓
        fetchUserData()


============================================================
10. INTERVIEW MEIN KAISE IDENTIFY KARNA HAI?
============================================================


Problem statement padho aur ye socho:


        "Kya mere paas already koi existing
         class/library hai?"

                |
               YES
                |
                v

        "Kya uska interface mere system
         ke interface se different hai?"

                |
               YES
                |
                v

        "Kya mujhe us existing functionality
         ko reuse karna hai?"

                |
               YES
                |
                v

              ADAPTER


Shortcut:

    EXISTING CODE
         +
    INTERFACE MISMATCH
         +
    REUSE KARNA HAI
         =
       ADAPTER


============================================================
11. SABSE IMPORTANT CONCEPT
============================================================


Adapter functionality ko change nahi karta.

Adapter mainly:

        INTERFACE

ko compatible banata hai.


Example:

Old system already jaanta hai:

        "Payment kaise karni hai."


Hume usko dobara implement nahi karna.


Bas problem ye hai:

        Client → pay()

        Old System → makePayment()


Adapter bolta hai:

        "Tum mujhe pay() do,
         main andar makePayment() call karwa dunga."


Yaani:

        Adapter = Translator


============================================================
12. EK LINE MEIN PURA PATTERN
============================================================


        CLIENT
           |
           | expected interface
           v
        TARGET
           ^
           |
           | IS-A
           |
        ADAPTER
           |
           | HAS-A
           v
        ADAPTEE
           |
           | existing functionality
           v
        ACTUAL WORK


Aur interview mein bolo:

    "Adapter Pattern is used when an existing class
     has the required functionality but its interface
     is incompatible with the interface expected by
     the client. The Adapter converts the client's
     expected interface into the interface understood
     by the existing class."


============================================================
13. FINAL MEMORY TRICK
============================================================


ADAPTER = "DOOSRE KI SERVICE KO APNI LANGUAGE MEIN USE KARNA"


        Client ki language
              |
              | pay()
              v
           Adapter
              |
              | makePayment()
              v
        Old System


Aur relationships:

        Adapter IS-A Target

        Adapter HAS-A Adaptee


Bas yrr Adapter Pattern ke liye ye 3 cheezein pakad lo:

    1. Existing class already hai.
    2. Interface match nahi kar raha.
    3. Adapter beech mein translator ban jaata hai.


Ye samajh aa gaya toh Adapter Pattern ka core
concept pakad liya.
============================================================