# Observer Design Pattern

## UML Diagram

┌──────────────────────────────┐
│          Subject             │
├──────────────────────────────┤
│ - observers : List<Observer> │
├──────────────────────────────┤
│ + attach(o)                  │
│ + detach(o)                  │
│ + notify()                   │
└──────────────┬───────────────┘
               │
               │ HAS-A
               │
               ▼
      ┌───────────────────┐
      │     Observer      │
      │    <<interface>> │
      ├───────────────────┤
      │ + update()        │
      └─────────┬─────────┘
                │
          IMPLEMENTS
        ┌───────┴────────┐
        ▼                ▼
┌────────────────┐  ┌────────────────┐
│ ConcreteObs A  │  │ ConcreteObs B  │
├────────────────┤  ├────────────────┤
│ + update()     │  │ + update()     │
└────────────────┘  └────────────────┘


## Short Notes

• Subject = jis object/state ko observe karna hai.

• Observer = notification receive karne ka contract.

• ConcreteObserver = actual reaction/logic.

• Subject ke paas observers ki list hoti hai.
  → HAS-A relationship

• ConcreteObserver, Observer interface ko implement karta hai.
  → IS-A relationship

• Subject ka state change hota hai
  → notify()
  → har registered Observer ka update()

• Loose Coupling:
  Subject ko exact ConcreteObserver classes ka knowledge nahi hota.

• Dynamic Subscription:
  Observer attach() / detach() kar sakta hai.

• Common Use Cases:
  → YouTube notifications
  → Stock price updates
  → Weather updates
  → GUI event listeners
  → Pub/Sub type systems

## Core Flow

Subject State Changes
        ↓
    notify()
        ↓
 ┌──────┼──────┐
 ↓      ↓      ↓
Obs A  Obs B  Obs C
 ↓      ↓      ↓
update update update
```
