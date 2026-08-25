/*
================================================================================
                        OBSERVER DESIGN PATTERN (LLD)
================================================================================

📌 DEFINITION:
Observer Pattern is a Behavioral Design Pattern where:
- One object (Subject / Publisher) maintains a list of dependents (Observers)
- Whenever state changes → it automatically notifies all observers

👉 Real Life Analogy:
- YouTube Channel (Subject)
- Subscribers (Observers)
- When new video uploaded → all subscribers get notification

================================================================================
🎯 WHY DO WE NEED IT? (Interview Gold)
================================================================================

❌ Problem without Observer:
- Tight coupling: Subject directly calls each dependent
- Hard to scale (new subscriber → modify subject)
- Violates Open/Closed Principle

✅ Solution:
- Loose coupling between Subject & Observers
- Dynamic subscription/unsubscription
- Easy to extend system

================================================================================
🏗️ CORE COMPONENTS
================================================================================

1. Subject (Observable)
   - Maintains list of observers
   - Provides methods:
        - subscribe()
        - unsubscribe()
        - notify()

2. Observer Interface
   - Defines update() method

3. Concrete Subject
   - Stores state
   - Notifies observers when state changes

4. Concrete Observer
   - Implements update()
   - Reacts to changes

================================================================================
📊 UML DIAGRAM (VERY IMPORTANT FOR INTERVIEW)
================================================================================

        +-------------------+
        |     IChannel      |  <<interface>>
        |-------------------|
        | +subscribe()      |
        | +unsubscribe()    |
        | +notify()         |
        +-------------------+
                 ▲
                 |
        +-------------------+
        |      Channel      |
        |-------------------|
        | subscribers[]     |
        | latestVideo       |
        |-------------------|
        | +uploadVideo()    |
        | +notify()         |
        +-------------------+
                 |
                 | notifies
                 ▼
        +-------------------+
        |   ISubscriber     | <<interface>>
        |-------------------|
        | +update()         |
        +-------------------+
                 ▲
                 |
        +-------------------+
        |    Subscriber     |
        |-------------------|
        | name              |
        | channel           |
        |-------------------|
        | +update()         |
        +-------------------+

================================================================================
⚙️ FLOW (IMPORTANT)
================================================================================

1. Observer subscribes to Subject
2. Subject stores observer in list
3. State change happens (e.g., upload video)
4. Subject calls notify()
5. notify() → calls update() on all observers
6. Observers pull/push updated data

================================================================================
🔄 PUSH vs PULL MODEL (INTERVIEW FAV)
================================================================================

1. PUSH MODEL:
   - Subject sends data in update()
   - update(data)

2. PULL MODEL (used in your code):
   - Observer pulls data using getter
   - update() → getData()

================================================================================
💡 WHEN TO USE
================================================================================

✔ Event-driven systems
✔ Notification systems
✔ UI frameworks (button click listeners)
✔ Pub-Sub systems
✔ Stock price updates

================================================================================
🚫 COMMON MISTAKES
================================================================================

❌ Memory leaks (raw pointers)
❌ Duplicate subscriptions
❌ Not removing observers properly
❌ Tight coupling (observer knowing too much)

================================================================================
⚖️ PROS & CONS
================================================================================

✅ PROS:
- Loose coupling
- Open/Closed Principle
- Dynamic relationships
- Scalable

❌ CONS:
- Too many updates → performance issue
- Debugging becomes tricky
- Order of notification not guaranteed

================================================================================
🧠 INTERVIEW ANSWER TEMPLATE
================================================================================

"If I need to notify multiple objects about state change without tightly
coupling them, I use Observer Pattern. It defines a one-to-many relationship
where subject maintains a list of observers and notifies them automatically."

================================================================================
🚀 ADVANCED FOLLOW UPS
================================================================================

- Thread safety (mutex)
- Event filtering
- Async notifications (queue)
- Weak pointers (avoid memory leaks)

================================================================================
*/