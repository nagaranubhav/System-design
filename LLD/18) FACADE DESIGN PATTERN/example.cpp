/*
====================================================================
                 FACADE DESIGN PATTERN
                 Example: FOOD ORDER SYSTEM
====================================================================


WHAT PROBLEM ARE WE SOLVING?
----------------------------

Maan le user ko online food order karna hai.

Food order place karne ke liye internally multiple systems
involved hain:

    1. Restaurant
    2. Payment
    3. Delivery
    4. Notification


Agar Client ko directly sabhi systems ko handle karna pade:

    restaurant.placeOrder();
    payment.makePayment();
    delivery.assignDelivery();
    notification.sendNotification();


Toh Client ko bahut saari internal complexity pata honi chahiye.


Facade Pattern ka idea:

    Client ko ye saari complexity mat dikhao.

    Ek simple class banao:

                FoodOrderFacade

    Client sirf Facade ko bole:

                placeOrder()

    Aur Facade internally saare systems ko manage kare.


MAIN IDEA:

                    CLIENT
                       |
                       | placeOrder()
                       ▼
             ┌───────────────────┐
             │ FoodOrderFacade   │
             └─────────┬─────────┘
                       |
             ┌─────────┼──────────┬──────────────┐
             ▼         ▼          ▼              ▼
        Restaurant  Payment    Delivery    Notification


====================================================================
                         IMPORTANT
====================================================================

Facade ka matlab:

    "Complex system ke upar ek simple layer/interface provide karna."

Client ko multiple subsystem classes ke saath directly
deal nahi karna padta.


====================================================================
                       HAS-A RELATIONSHIP
====================================================================

FoodOrderFacade ke andar:

    Restaurant restaurant;
    Payment payment;
    Delivery delivery;
    Notification notification;


Isliye:

    FoodOrderFacade HAS-A Restaurant
    FoodOrderFacade HAS-A Payment
    FoodOrderFacade HAS-A Delivery
    FoodOrderFacade HAS-A Notification


HAS-A kyun?

Kyuki Facade ke PAAS ye objects hain.

Simple language:

    Facade KE PAAS Restaurant object hai.
    Facade KE PAAS Payment object hai.
    Facade KE PAAS Delivery object hai.
    Facade KE PAAS Notification object hai.


Isliye HAS-A.


====================================================================
                        IS-A RELATIONSHIP
====================================================================

Is example mein koi IS-A relationship nahi hai.


Ye galat hoga:

    FoodOrderFacade IS-A Restaurant       ❌
    FoodOrderFacade IS-A Payment         ❌
    FoodOrderFacade IS-A Delivery        ❌
    FoodOrderFacade IS-A Notification    ❌


Kyun?

Kyunki FoodOrderFacade inmein se koi bhi nahi hai.

Facade sirf in objects ko USE/MANAGE karta hai.


IS-A generally inheritance ko represent karta hai.

Example:

    class Car : public Vehicle

Yahan:

    Car IS-A Vehicle


Lekin hamare example mein:

    FoodOrderFacade HAS-A Restaurant
    FoodOrderFacade HAS-A Payment
    FoodOrderFacade HAS-A Delivery
    FoodOrderFacade HAS-A Notification


====================================================================
                         CODE STARTS
====================================================================
*/

#include <iostream>
#include <string>

using namespace std;


// ==================================================================
// 1. RESTAURANT - SUBSYSTEM
// ==================================================================

/*
Restaurant ek SUBSYSTEM hai.

Iska kaam sirf restaurant mein food order place karna hai.

Facade ke bina Client ko directly Restaurant class ko
handle karna padta.
*/

class Restaurant {

public:

    void placeOrder(string food) {

        cout << "Restaurant: "
             << food
             << " order placed."
             << endl;
    }
};


// ==================================================================
// 2. PAYMENT - SUBSYSTEM
// ==================================================================

/*
Payment bhi ek SUBSYSTEM hai.

Iska kaam payment process karna hai.

Facade ke bina Client ko directly Payment class ko
handle karna padta.
*/

class Payment {

public:

    void makePayment(double amount) {

        cout << "Payment: Rs."
             << amount
             << " payment successful."
             << endl;
    }
};


// ==================================================================
// 3. DELIVERY - SUBSYSTEM
// ==================================================================

/*
Delivery ek SUBSYSTEM hai.

Iska kaam delivery partner assign karna hai.
*/

class Delivery {

public:

    void assignDelivery() {

        cout << "Delivery: "
             << "Delivery partner assigned."
             << endl;
    }
};


// ==================================================================
// 4. NOTIFICATION - SUBSYSTEM
// ==================================================================

/*
Notification bhi ek SUBSYSTEM hai.

Iska kaam user ko order confirmation bhejna hai.
*/

class Notification {

public:

    void sendNotification() {

        cout << "Notification: "
             << "Order confirmed!"
             << endl;
    }
};


// ==================================================================
// 5. FACADE CLASS
// ==================================================================

/*
====================================================================
                         FOOD ORDER FACADE
====================================================================

Ye hamari FACADE class hai.

Is class ka main kaam hai:

    Multiple subsystem classes ko internally manage karna.

Client ko directly:

    Restaurant
    Payment
    Delivery
    Notification

handle karne ki zarurat nahi padegi.


====================================================================
                         HAS-A RELATIONSHIP
====================================================================

Neeche dekho:

    Restaurant restaurant;
    Payment payment;
    Delivery delivery;
    Notification notification;


FoodOrderFacade ke paas in sabke objects hain.

Therefore:

    FoodOrderFacade HAS-A Restaurant
    FoodOrderFacade HAS-A Payment
    FoodOrderFacade HAS-A Delivery
    FoodOrderFacade HAS-A Notification


Diagram:

             FoodOrderFacade
                    |
          ┌─────────┼─────────┐
          |         |         |
        HAS-A     HAS-A     HAS-A
          |         |         |
          ▼         ▼         ▼
     Restaurant  Payment   Delivery

                    +
              HAS-A Notification


====================================================================
*/

class FoodOrderFacade {

private:

    // --------------------------------------------------------------
    // These are SUBSYSTEM objects.
    //
    // FoodOrderFacade HAS-A relationship rakhta hai inke saath.
    // --------------------------------------------------------------

    Restaurant restaurant;
    Payment payment;
    Delivery delivery;
    Notification notification;


public:

    // --------------------------------------------------------------
    // SIMPLE METHOD FOR CLIENT
    // --------------------------------------------------------------

    /*
    Client ko sirf ye ek method call karna hai:

            placeOrder()

    Client ko ye nahi pata ki andar kya-kya ho raha hai.


    Facade internally:

        1. Restaurant ko order karega
        2. Payment karega
        3. Delivery assign karega
        4. Notification bhejega
    */

    void placeOrder(string food, double amount) {

        // Step 1:
        // Restaurant mein food order place karo.

        restaurant.placeOrder(food);


        // Step 2:
        // Payment process karo.

        payment.makePayment(amount);


        // Step 3:
        // Delivery partner assign karo.

        delivery.assignDelivery();


        // Step 4:
        // User ko notification bhejo.

        notification.sendNotification();
    }
};


// ==================================================================
// 6. CLIENT
// ==================================================================

/*
====================================================================
                           CLIENT
====================================================================

Client wo hai jo system ko use kar raha hai.

Important point:

Client ko directly ye sab handle nahi karna:

    Restaurant
    Payment
    Delivery
    Notification


Client ko sirf Facade pata hai.

Client:

    FoodOrderFacade foodOrder;

Aur simply:

    foodOrder.placeOrder("Pizza", 499);


call karega.


====================================================================
                       CLIENT FLOW
====================================================================

                CLIENT
                   |
                   | placeOrder("Pizza", 499)
                   ▼
          FoodOrderFacade
                   |
          ┌────────┼────────┬──────────────┐
          ▼        ▼        ▼              ▼
      Restaurant Payment  Delivery    Notification
          |
          ▼
      Order placed
          |
          ▼
       Payment
          |
          ▼
      Delivery
          |
          ▼
     Notification


Client ko internal steps nahi pata.

Client sirf ek simple method call karta hai.


====================================================================
*/

int main() {

    // --------------------------------------------------------------
    // Client Facade ka object create karta hai.
    // --------------------------------------------------------------

    FoodOrderFacade foodOrder;


    /*
    --------------------------------------------------------------
    Client sirf placeOrder() call kar raha hai.

    Client ko internally ye nahi karna:

        Restaurant restaurant;
        Payment payment;
        Delivery delivery;
        Notification notification;

        restaurant.placeOrder(...);
        payment.makePayment(...);
        delivery.assignDelivery();
        notification.sendNotification();

    Ye saara kaam Facade internally karega.
    --------------------------------------------------------------
    */

    foodOrder.placeOrder("Pizza", 499);


    return 0;
}


/*
====================================================================
                         DRY RUN
====================================================================

Jab main() mein ye line execute hogi:

    foodOrder.placeOrder("Pizza", 499);


Step 1:
------

Control FoodOrderFacade ke:

    placeOrder("Pizza", 499)

method mein jayega.


Step 2:
------

Ye execute hoga:

    restaurant.placeOrder("Pizza");


Output:

    Restaurant: Pizza order placed.


Step 3:
------

Next:

    payment.makePayment(499);


Output:

    Payment: Rs.499 payment successful.


Step 4:
------

Next:

    delivery.assignDelivery();


Output:

    Delivery: Delivery partner assigned.


Step 5:
------

Finally:

    notification.sendNotification();


Output:

    Notification: Order confirmed!


====================================================================
                         FINAL OUTPUT
====================================================================

Restaurant: Pizza order placed.
Payment: Rs.499 payment successful.
Delivery: Delivery partner assigned.
Notification: Order confirmed!


====================================================================
                  WITHOUT FACADE vs WITH FACADE
====================================================================


WITHOUT FACADE
--------------

Client ko sabhi subsystem classes directly handle karni padti:

    Client
      |
      ├── Restaurant
      ├── Payment
      ├── Delivery
      └── Notification


Client ko pata hai ki order place karne ke liye
exactly kya-kya steps karne hain.


--------------------------------------------------------------------


WITH FACADE
-----------

Client:

    Client
      |
      | placeOrder()
      ▼
    FoodOrderFacade
      |
      ├── Restaurant
      ├── Payment
      ├── Delivery
      └── Notification


Ab Client ko sirf:

    placeOrder()

pata hai.

Internal complexity Facade ke andar hide ho gayi.


====================================================================
                       CORE IDEA
====================================================================

Facade Pattern ka main purpose:

    COMPLEX SYSTEM
          ↓
    SIMPLE INTERFACE
          ↓
       CLIENT


Yaad rakh:

    Client ko multiple classes directly handle nahi karni.

    Client → Facade → Multiple Subsystems


Aur relationship:

    Facade HAS-A Subsystems


Is example mein:

    FoodOrderFacade HAS-A Restaurant
    FoodOrderFacade HAS-A Payment
    FoodOrderFacade HAS-A Delivery
    FoodOrderFacade HAS-A Notification


IS-A relationship:

    NONE


ONE-LINE INTERVIEW DEFINITION:

    "Facade Pattern provides a simple interface to a complex
     subsystem by hiding its internal complexity from the client."


====================================================================
*/