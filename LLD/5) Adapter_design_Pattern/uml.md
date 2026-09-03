============================================================
             ADAPTER DESIGN PATTERN — UML DIAGRAM
============================================================

                 CLIENT
                    |
                    | uses
                    v
          +-------------------+
          |   Target          |
          |-------------------|
          | + request()       |
          +-------------------+
                    ^
                    | implements
                    |  "IS-A"
                    |
          +-------------------+
          |   Adapter         |
          |-------------------|
          | - adaptee         |------------------+
          | + request()       |                  |
          +-------------------+                  | "HAS-A"
                                                 |
                                                 v
                                      +-------------------+
                                      |     Adaptee       |
                                      |-------------------|
                                      | + specificRequest()|
                                      +-------------------+


============================================================
1. HAR BLOCK KYA KARTA HAI?
============================================================

CLIENT
------
Client wo banda hai jo kaam karwana chahta hai.

Example:
Client ko sirf ye pata hai:

    target.request();

Client ko ye nahi pata ki andar actual kaam kaise ho raha hai.


------------------------------------------------------------

TARGET
------
Target = Client ki expected language/interface.

    Target
       |
       +-- request()

Client sirf Target ko samajhta hai.

Matlab:

Client bolta hai:
    "Mujhe request() chahiye."

Lekin problem ye hai ki jo purani class hamare paas hai,
wo request() provide nahi karti.


------------------------------------------------------------

ADAPTEE
-------
Adaptee = Existing / old / third-party class.

Iske paas already functionality hai:

    specificRequest()

Lekin iska function Client ke expected format mein nahi hai.

Example:

Client ko chahiye:
    request()

Old class ke paas hai:
    specificRequest()

Functionality same ho sakti hai,
lekin interface/language alag hai.


------------------------------------------------------------

ADAPTER
-------
Adapter beech ka translator hai.

Client:
    request()

        |
        v

Adapter:
    request()
        |
        v
    adaptee.specificRequest()

        |
        v

Adaptee:
    specificRequest()


Adapter ka main kaam:

    "Client jo language samajhta hai,
     usko Adaptee ki language mein convert karna."


============================================================
2. ADAPTER KE PAAS "HAS-A" KYON HAI?
============================================================

Diagram:

Adapter ---------------------> Adaptee
          HAS-A

Adapter ke andar:

    Adaptee* adaptee;

ya

    Adaptee adaptee;


Matlab:

    Adapter HAS-A Adaptee

Simple language mein:

Adapter ke paas Adaptee ka object hai.

Adapter khud actual kaam nahi karta.

Wo Adaptee se kaam karwata hai.

Example:

    Adapter
       |
       +---- has ----> OldPrinter

Jab Adapter ko request() milti hai:

    Adapter.request()

toh wo internally:

    OldPrinter.printOldWay()

call kar deta hai.


IMPORTANT:

HAS-A ka matlab:

    "iske paas doosre class ka object/reference hai."


============================================================
3. ADAPTER AUR TARGET MEIN "IS-A" KYON?
============================================================

Diagram:

        Target
          ^
          |
       IS-A
          |
       Adapter


Adapter Target ko implement karta hai.

Matlab:

    Adapter IS-A Target


Agar:

    Target
    {
        request()
    }

hai,

toh Adapter:

    Adapter : public Target

kar sakta hai.

Isliye Adapter ko Client Target ki tarah treat kar sakta hai.

Client ko farak nahi padta ki actual object Adapter hai.

Client bas bolta hai:

    Target* target;

    target->request();


============================================================
4. DONO RELATIONSHIP EK SAATH KYON?
============================================================

Ye Adapter Pattern ka sabse important point hai.

Adapter:

    IS-A Target
    HAS-A Adaptee


Visual:

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


Kyun?

Adapter ko CLIENT ke liye Target banna hai.

Isliye:

    Adapter IS-A Target


Aur Adapter ko OLD CLASS ka kaam use karna hai.

Isliye:

    Adapter HAS-A Adaptee


Yahi actual Adapter Pattern ka core hai.


============================================================
5. REAL-LIFE EXAMPLE
============================================================

Socho tumhare ghar mein:

    Indian Socket
    = Target

Aur tumhare paas:

    US Charger
    = Adaptee

Indian socket bol raha hai:

    "Mujhe Indian plug chahiye."

Lekin charger ke paas US plug hai.

Toh hum kya karenge?

             Indian Socket
                    ^
                    |
                 Adapter
                    |
                    v
               US Charger


Adapter beech mein translate karega:

    Indian Socket format
            ↓
         Adapter
            ↓
    US Charger format


Adapter khud electricity generate nahi kar raha.

Bas connection compatible bana raha hai.


============================================================
6. KAISE PATA CHALEGA KI ADAPTER LAGANA HAI?
============================================================

Ye interview mein bahut important hai.

Khud se ye 3 questions poochho:


QUESTION 1:
------------
"Kya mere paas already ek existing class hai
jiska functionality mujhe use karna hai?"

YES
 |
 v
Aage dekho.


QUESTION 2:
------------
"Kya existing class ka interface
mere client ke expected interface se different hai?"

YES
 |
 v
Adapter ka strong signal.


QUESTION 3:
------------
"Kya main existing class ko modify nahi karna chahta?"

YES
 |
 v

              ADAPTER PATTERN


Short formula yaad rakho:

    EXISTING CLASS
          +
    WRONG / DIFFERENT INTERFACE
          +
    CLIENT KO EXPECTED INTERFACE CHAHIYE
          =
       ADAPTER


============================================================
7. SIMPLE EXAMPLE
============================================================

Client ko chahiye:

    Target
       |
       +-- request()


Lekin old class ke paas:

    Adaptee
       |
       +-- specificRequest()


Problem:

    Client ---> request()

    Adaptee --> specificRequest()

Dono directly compatible nahi hain.


Solution:

    Client
      |
      v
    Target
      ^
      |
    Adapter
      |
      v
    Adaptee


Adapter:

    request()
       |
       +----> specificRequest()


Ab Client ko kuch change nahi karna pada.


============================================================
8. CODE MEIN RELATIONSHIP KAISE DIKHEGA?
============================================================

Target:

    class Target {
    public:
        virtual void request() = 0;
    };


Adaptee:

    class Adaptee {
    public:
        void specificRequest();
    };


Adapter:

    class Adapter : public Target {
    private:
        Adaptee adaptee;

    public:
        void request() override {
            adaptee.specificRequest();
        }
    };


Yahan:

    Adapter : public Target

means:

    Adapter IS-A Target


Aur:

    Adaptee adaptee;

means:

    Adapter HAS-A Adaptee


============================================================
9. UML ARROWS KO YAAD KAISE RAKHNA HAI?
============================================================

IS-A / Inheritance:

    Child --------|> Parent

Example:

    Adapter --------|> Target


HAS-A / Composition or Association:

    Whole ---------> Part

Example:

    Adapter ---------> Adaptee


Mental trick:

    IS-A:
    "Kya Adapter ek Target hai?"
             YES
             ↓
         inheritance


    HAS-A:
    "Kya Adapter ke paas Adaptee hai?"
             YES
             ↓
       object/reference


============================================================
10. ADAPTER KAHAN USE HOTA HAI?
============================================================

Adapter tab useful hota hai jab:

1. Legacy code ko new system mein use karna ho.

2. Third-party library ka interface tumhare system
   ke interface se different ho.

3. Do existing classes compatible nahi hain.

4. Purani class ko modify nahi kar sakte.

5. Multiple systems ko ek common interface ke through
   use karna ho.


Example:

    Your Application
          |
       Target
          ^
          |
       Adapter
          |
          v
    Third Party API


Tumhari application ko third-party API ki
internal implementation se koi lena-dena nahi.

Adapter compatibility ka kaam karega.


============================================================
11. SABSE IMPORTANT INTERVIEW LINE
============================================================

Adapter Pattern ka use tab karte hain jab:

    "Existing class ki functionality hume chahiye,
     lekin uska interface hamare client ke expected
     interface se match nahi karta."

Adapter beech mein aakar:

    Client Interface
          ↓
       Adapter
          ↓
    Existing Class


kar deta hai.


============================================================
12. ONE-LINE MEMORY TRICK
============================================================

ADAPTER = TRANSLATOR

    Client ki language
          ↓
       Adapter
          ↓
    Old class ki language


Aur Adapter ke relationships:

    Adapter IS-A Target
    Adapter HAS-A Adaptee


Bas ye 2 lines yaad rakh:

    IS-A  → "Main kis type ka hoon?"
    HAS-A → "Mere paas kya object hai?"

Adapter:

    "Main Target hoon,
     aur mere paas Adaptee hai."

============================================================