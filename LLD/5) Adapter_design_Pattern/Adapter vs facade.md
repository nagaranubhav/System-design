============================================================
        ADAPTER vs FACADE — COMPLETE NOTES
============================================================

YRR sabse pehle ekdum simple line yaad rakh:

    ADAPTER = TRANSLATOR

    FACADE = SIMPLE FRONT DOOR


============================================================
1. SABSE PEHLE ADAPTER KYA KARTA HAI?
============================================================

Maan lo Client ko kisi class se:

        pay()

call karna hai.

Lekin existing/old class mein:

        makePayment()

hai.

Dono ka kaam same hai:

        PAYMENT

Lekin dono ki language/interface different hai.

Problem:

        Client
           |
           | wants pay()
           v
        Target

        Old System
           |
           | provides makePayment()

Dono directly compatible nahi hain.


Isliye Adapter beech mein aata hai:

        Client
           |
           | pay()
           v
        Adapter
           |
           | makePayment()
           v
        Old System


Adapter basically bolta hai:

    "Client, tu apni language mein baat kar.
     Main usko old system ki language mein
     convert kar dunga."


Isliye:

        ADAPTER = TRANSLATOR


============================================================
2. TARGET KYA HAI?
============================================================

Target koi actual kaam karne wali class zaroori nahi hai.

Target basically batata hai:

    "CLIENT KO KIS FORMAT/INTERFACE MEIN
     KAAM KARWANA HAI?"

Example:

        Target
        ------
        pay()


Client ko bas:

        pay()

chahiye.

Client ko ye nahi pata ki actual payment:

        OldPaymentSystem

kar raha hai ya koi aur system.


Target = Client ki expectation.


============================================================
3. ADAPTER MEIN TARGET KYON HOTA HAI?
============================================================

Ye sabse important doubt tha.

Question:

    "Hum Client ko directly Adapter se baat
     kyu nahi karwa dete?"

Answer:

    Kar sakte ho!

Aisa code perfectly possible hai:

        PaymentAdapter adapter;

        adapter.pay(5000);


Kaam ho jayega.

Lekin problem ye hai ki Client ko pata chal gaya:

        "Mujhe PaymentAdapter hi chahiye."


Ab Client Adapter ke saath tightly connected ho gaya.


============================================================
4. TARGET KA ACTUAL BENEFIT
============================================================

Target ek COMMON LANGUAGE deta hai.

Client bolta hai:

    "Mujhe PaymentProcessor chahiye."

Client ye nahi bolta:

    "Mujhe PaymentAdapter chahiye."

Isliye:

        PaymentProcessor* processor;


Aur actual object ho sakta hai:

        PaymentAdapter


ya:

        NewPaymentSystem


ya:

        AnotherPaymentSystem


Client ko koi farak nahi.

Client bas:

        processor->pay(5000);


karega.


============================================================
5. IS-A RELATIONSHIP
============================================================

Adapter:

        class PaymentAdapter
            : public PaymentProcessor


iska matlab:

        PaymentAdapter IS-A PaymentProcessor


Kyun?

Kyuki Adapter Target ko implement/inherit karta hai.


Isliye Client:

        PaymentProcessor* processor;


mein Adapter ka object rakh sakta hai.


Example:

        PaymentProcessor* processor =
            new PaymentAdapter();


Yahan Client ko sirf PaymentProcessor pata hai.

Actual object:

        PaymentAdapter


hai.


============================================================
6. HAS-A RELATIONSHIP
============================================================

Adapter ke andar:

        OldPaymentSystem oldPaymentSystem;


iska matlab:

        PaymentAdapter HAS-A OldPaymentSystem


Kyun?

Kyuki Adapter ke paas OldPaymentSystem ka object hai.

Adapter khud old payment ka implementation
dobara nahi likh raha.

Wo existing class ko use kar raha hai.


Flow:

        Adapter
           |
           | HAS-A
           v
        OldPaymentSystem


Adapter ke andar:

        pay()
           |
           v
        makePayment()


Yaani Adapter Client ke function ko old system
ke function se connect kar raha hai.


============================================================
7. ADAPTER KA COMPLETE RELATIONSHIP
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


Yaad rakho:

    Adapter IS-A Target

    Adapter HAS-A Adaptee


Simple language:

    "Adapter Target jaisa behave karta hai
     aur uske paas Adaptee hota hai."


============================================================
8. AGAR TARGET NA HOTA TOH?
============================================================

Hum direct kar sakte the:

        Client
          |
          v
       Adapter
          |
          v
       Adaptee


Kaam ho jayega.

Lekin Client ko Adapter ka naam/type pata hoga.

Example:

        PaymentAdapter adapter;

        adapter.pay(5000);


Client bol raha hai:

    "Mujhe PaymentAdapter chahiye."


Target use karne par:

        PaymentProcessor* processor;

        processor->pay(5000);


Client bolta hai:

    "Mujhe koi bhi PaymentProcessor de do
     jo pay() kar sake."


Ye zyada flexible hai.


============================================================
9. KAL KO IMPLEMENTATION CHANGE HO JAYE TOH?
============================================================

Aaj:

        PaymentProcessor
               ^
               |
        PaymentAdapter
               |
               v
        OldPaymentSystem


Kal:

        PaymentProcessor
               ^
               |
        NewPaymentSystem


Client ka code same:

        processor->pay(5000);


Client ko implementation ke baare mein
kuch change nahi karna padega.


Yahi Target ka important benefit hai.


============================================================
10. AB FACADE KO SAMJHO
============================================================

Facade ka purpose Adapter se different hai.

Maan lo movie dekhni hai.

Movie start karne ke liye:

        DVD Player
        Sound System
        Projector
        Lights

sabko separately control karna pad raha hai.


Client ke liye ye complicated hai.


Facade bolta hai:

        "Tum bas mujhe startMovie() bolo.
         Baaki main sambhal lunga."


Diagram:

        Client
           |
           v
        Facade
           |
       +---+---+---+---+
       |   |   |   |   |
       v   v   v   v   v
      DVD Sound Projector Lights
          System


Client:

        facade.startMovie();


Bas.


============================================================
11. FACADE MEIN TARGET KYON NAHI?
============================================================

Kyuki Facade ka purpose hai:

    "Bahut saare complicated systems ke upar
     ek SIMPLE ENTRY POINT dena."


Client directly:

        Facade

se baat karta hai.


Flow:

        Client
           |
           v
        Facade
           |
           +----> System A
           |
           +----> System B
           |
           +----> System C


Facade ko abstract Target banane ki
special requirement nahi hai.


Simple words:

    Facade khud ek convenient front door hai.


============================================================
12. ADAPTER vs FACADE — REAL LIFE ANALOGY
============================================================


ADAPTER = TRAVEL PLUG ADAPTER
-----------------------------

Tumhare paas:

        US Charger

Wall socket:

        Indian Socket


Dono directly compatible nahi.


Adapter:

        US Charger
             |
             v
          Adapter
             |
             v
        Indian Socket


Adapter ka kaam:

    "Do incompatible cheezon ko compatible banana."


------------------------------------------------------------


FACADE = RESTAURANT MANAGER
---------------------------

Tum restaurant mein jaate ho.

Tum Manager ko bolte ho:

        "Pizza chahiye."


Manager internally:

        Chef
        Kitchen
        Billing
        Inventory
        Waiter

sab manage karta hai.


Tumhe ye sab directly handle nahi karna.


Manager = Facade


Matlab:

    "Complicated system ko simple interface
     ke peeche hide kar do."


============================================================
13. DONO KA MAIN DIFFERENCE
============================================================


ADAPTER:

    Existing class already hai.

    Functionality useful hai.

    Lekin interface match nahi kar raha.

    Adapter interface ko convert karta hai.


        Client
           |
           v
        Adapter
           |
           v
        Existing Class


        ADAPTER = COMPATIBILITY


------------------------------------------------------------


FACADE:

    Bahut saare systems/classes hain.

    Client ke liye sabko handle karna complicated hai.

    Facade ek simple entry point provide karta hai.


        Client
           |
           v
        Facade
         / | \
        /  |  \
       v   v   v
      A    B    C


        FACADE = SIMPLICITY


============================================================
14. KAISE PATA CHALEGA ADAPTER HAI?
============================================================

Problem dekhte waqt 3 questions poochho:


QUESTION 1:

    Kya existing/old/third-party class already hai?

        YES
         |
         v

QUESTION 2:

    Kya usme required functionality hai,
    lekin interface different hai?

        YES
         |
         v

QUESTION 3:

    Kya existing class ko change kiye bina
    use karna hai?

        YES
         |
         v

       ADAPTER


Shortcut:

        EXISTING CLASS
              +
        INTERFACE MISMATCH
              +
        REUSE KARNA HAI
              =
           ADAPTER


============================================================
15. KAISE PATA CHALEGA FACADE HAI?
============================================================

Problem dekhte waqt socho:

    "Kya Client ko bahut saari classes/systems
     ko directly call karna pad raha hai?"


Agar YES:

        System A
        System B
        System C
        System D

sabko Client directly handle kar raha hai,


toh ek simple class bana sakte ho:

        Facade


Aur Client:

        Client
          |
          v
        Facade


Bas.


Shortcut:

        MANY COMPLEX SYSTEMS
               +
        CLIENT CONFUSED/COMPLICATED
               +
        SIMPLE ENTRY POINT CHAHIYE
               =
             FACADE


============================================================
16. EKDUM FINAL COMPARISON
============================================================


                    ADAPTER
                    =======

Problem:

    "Ye existing class useful hai,
     but iska interface match nahi karta."

Solution:

    Adapter beech mein translator banega.


    Client → Target ← Adapter → Adaptee


Main goal:

    COMPATIBILITY


Important relationships:

    Adapter IS-A Target
    Adapter HAS-A Adaptee



------------------------------------------------------------


                    FACADE
                    ======

Problem:

    "Bahut saare systems hain
     aur Client ko sab handle karne pad rahe hain."


Solution:

    Facade ek simple front door dega.


    Client → Facade → Complex Systems


Main goal:

    SIMPLICITY


============================================================
17. SABSE IMPORTANT CONFUSION CLEAR
============================================================

Ye mat sochna:

    "Adapter mein Target hai,
     toh Target hi actual kaam karta hoga."


Nahi.


Target sirf batata hai:

        "Client ko ye interface chahiye."


Actual kaam:

        Adaptee

kar sakta hai.


Adapter dono ko connect karta hai.


        Target
          ^
          |
       Adapter
          |
          v
       Adaptee


Target = Client ki expectation

Adapter = Translator

Adaptee = Existing class


============================================================
18. ONE-LINE MEMORY TRICK
============================================================


ADAPTER:

    "Mere paas jo hai,
     usko tumhare expected format mein
     use karwa deta hoon."


FACADE:

    "Tumhe andar ki complexity nahi dekhni,
     bas mujhe ek simple call karo."


============================================================
19. INTERVIEW ANSWER
============================================================

Agar interviewer pooche:

    "Adapter Pattern kya hai?"


Simple answer:

    "Adapter Pattern tab use karte hain jab
     existing class ki functionality hume chahiye,
     lekin uska interface Client ke expected
     interface se match nahi karta.

     Adapter beech mein aakar dono ko compatible
     bana deta hai."


Aur agar pooche:

    "Facade se difference?"


Bolo:

    "Adapter ka main purpose compatibility hai,
     jabki Facade ka main purpose complexity
     ko hide karke simple interface dena hai."


============================================================
20. FINAL PICTURE — BAS ISKO YAAD RAKHO
============================================================


                ADAPTER

        Client
           |
           v
        Target
           ^
           |
          IS-A
           |
        Adapter
           |
          HAS-A
           |
           v
        Adaptee


    Adapter = Translator
    Target  = Client ki expectation
    Adaptee = Existing class


------------------------------------------------------------


                FACADE

        Client
           |
           v
        Facade
           |
       +---+---+
       |   |   |
       v   v   v
      A    B    C


    Facade = Simple Front Door
    A/B/C  = Complicated subsystems


============================================================
                 GOLDEN RULE
============================================================

Agar problem hai:

    "INTERFACE MATCH NAHI KAR RAHA"

        → ADAPTER


Agar problem hai:

    "SYSTEM BAHUT COMPLICATED HAI"

        → FACADE


Bas yrr:

    ADAPTER → COMPATIBILITY

    FACADE  → SIMPLICITY

Ye distinction dimaag mein clear ho gaya
toh dono patterns ko identify karna kaafi easy ho jayega.
============================================================
```
