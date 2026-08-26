# Factory Design Pattern

## 1. Basic Idea

Factory Design Pattern ka simple idea hai:

    "Object banane ka kaam Client khud nahi karega,
     balki ek Factory class karegi."

Example:
Humare paas 3 types ke Notification objects hain:

    - EmailNotification
    - SMSNotification
    - PushNotification

Client ko directly ye decide nahi karna:

    new EmailNotification()
    new SMSNotification()
    new PushNotification()

Instead, Client Factory ko bolega:

    "Mujhe EMAIL notification chahiye."

Factory internally decide karegi ki kaunsa object banana hai.


## 2. UML Diagram

                         ┌──────────────────────┐
                         │        Client        │
                         ├──────────────────────┤
                         │                      │
                         │ createNotification() │
                         └──────────┬───────────┘
                                    │
                                    │ asks Factory
                                    ▼
                         ┌──────────────────────┐
                         │ NotificationFactory  │
                         ├──────────────────────┤
                         │                      │
                         │ + createNotification │
                         │   (type)             │
                         └──────────┬───────────┘
                                    │
                         creates    │
                    ┌───────────────┼───────────────┐
                    │               │               │
                    ▼               ▼               ▼
          ┌────────────────┐ ┌───────────────┐ ┌────────────────┐
          │EmailNotification│ │SMSNotification│ │PushNotification│
          ├────────────────┤ ├───────────────┤ ├────────────────┤
          │ + send()       │ │ + send()      │ │ + send()       │
          └───────┬────────┘ └──────┬────────┘ └───────┬────────┘
                  │                 │                  │
                  │ implements      │ implements       │ implements
                  └─────────────────┼──────────────────┘
                                    │
                                    ▼
                         ┌──────────────────────┐
                         │     Notification     │
                         │     <<interface>>    │
                         ├──────────────────────┤
                         │ + send()             │
                         └──────────────────────┘


## 3. UML ko Simple Language Mein Samjho

### Notification

Ye ek common interface hai.

Iska matlab:

"Har notification ke paas send() hona chahiye."

Email, SMS aur Push teeno Notification ko implement karenge.


### EmailNotification / SMSNotification / PushNotification

Ye actual objects hain.

Inke paas apna-apna send() implementation hoga.

Example:

    EmailNotification → Email bhejega
    SMSNotification   → SMS bhejega
    PushNotification  → Push notification bhejega


### NotificationFactory

Ye sabse important part hai.

Factory ka kaam sirf ye decide karna hai:

    "Client ko kis type ka Notification object chahiye?"

Example:

    EMAIL → EmailNotification
    SMS   → SMSNotification
    PUSH  → PushNotification


### Client

Client ko actual class ka object directly create karne ki zarurat nahi hai.

Client simply Factory ko request karta hai:

    Client
       ↓
    Factory
       ↓
    Required Notification Object


## 4. Real-Life Analogy

Factory ko ek restaurant ke waiter/counter ki tarah socho.

Tum counter par jaake bolte ho:

    "Mujhe Pizza chahiye."

Tum khud kitchen mein jaake pizza nahi banate.

Counter/order system decide karta hai ki pizza kaise banega.

Same way:

    Client
       ↓
    Factory
       ↓
    Object


## 5. Main Point to Remember

Factory Pattern ka main purpose:

    OBJECT CREATION KO CENTRALIZE KARNA

Matlab:

    Client → "Mujhe object chahiye."

    Factory → "Theek hai, main required object bana deti hoon."

    Concrete Class → Actual object create hota hai.


## 6. One-Line Interview Definition

Factory Design Pattern is a creational design pattern
that moves object creation logic from the Client
to a separate Factory class.