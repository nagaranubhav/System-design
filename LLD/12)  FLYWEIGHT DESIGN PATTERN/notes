=========================================================
               FLYWEIGHT DESIGN PATTERN
=========================================================

CATEGORY:
Structural Design Pattern

INTENT (MOST IMPORTANT):
"Large number of similar objects ke common shared state ko
reuse karke memory optimize karna."

Simple one-line:
"Jo data same hai usko share karo, jo unique hai usko alag rakho."

Golden line:
INTRINSIC share hota hai
EXTRINSIC alag hota hai

---------------------------------------------------------
1) CORE INTUITION
---------------------------------------------------------

Soch game me 10 lakh asteroids hain.

Har asteroid me:
- color
- texture
- material
- size
- weight
- position
- velocity

Agar har asteroid ke paas sab kuch separately hoga:
MEMORY BLAST 💥

Example:
1,000,000 asteroids
Each = 100 bytes
Total = 100 MB+

But actual reality:
Sirf 3 asteroid TYPES hain:
- Red Rocky Iron
- Blue Metallic Stone
- Gray Icy Ice

Toh:
Common data share karo
Unique data alag rakho

Ye hi Flyweight.

---------------------------------------------------------
2) MAIN IDEA
---------------------------------------------------------

Object state ko 2 parts me tod do:

1) INTRINSIC STATE (SHARED)
Same for many objects
Example:
- color
- texture
- material
- size

Stored inside Flyweight object

2) EXTRINSIC STATE (UNIQUE)
Per object unique
Example:
- x position
- y position
- velocity

Stored outside in context

---------------------------------------------------------
3) WHY WE NEED IT
---------------------------------------------------------

Use when:
- bahut large number of similar objects
- object creation costly hai
- memory bottleneck hai
- repeated immutable data hai

Most important:
"Object duplication avoid karni ho"

---------------------------------------------------------
4) UML DIAGRAM
---------------------------------------------------------

                 +----------------------+
                 |   FlyweightFactory   |
                 +----------------------+
                 | +getFlyweight()      |
                 +----------------------+
                           |
                           v
                 +----------------------+
                 |  AsteroidFlyweight   |
                 +----------------------+
                 | intrinsic state      |
                 | - size               |
                 | - color              |
                 | - texture            |
                 +----------------------+
                 | +render(extrinsic)   |
                 +----------------------+
                           ^
                           |
                           |
                 +----------------------+
                 |  AsteroidContext     |
                 +----------------------+
                 | extrinsic state      |
                 | - posX               |
                 | - posY               |
                 | - velocity           |
                 +----------------------+

---------------------------------------------------------
5) PARTICIPANTS
---------------------------------------------------------

1) Flyweight
Shared object
Stores intrinsic state

2) Concrete Flyweight
Actual implementation
AsteroidFlyweight

3) Flyweight Factory
Ensures reuse
Cache maintain karta hai

4) Context
Extrinsic state rakhta hai
Runtime pe flyweight ko pass karta hai

---------------------------------------------------------
6) WHEN TO USE
---------------------------------------------------------

Perfect use cases:
1. Game engines
2. Bullet systems
3. Particle systems
4. Text editors (characters formatting)
5. Chess boards
6. Map markers
7. Tree rendering in forests
8. Icons in UI systems
9. Cache-heavy backend services

Golden interview trigger:
"Lakhs/millions of similar objects"

---------------------------------------------------------
7) REAL LIFE EXAMPLES
---------------------------------------------------------

1) Text Editor
Every character object alag nahi banta
font style shared hota hai

2) PUBG / GTA
Trees, bullets, stones, grass textures

3) Google Maps
Same restaurant icon reused

4) OS Icon Rendering
Same folder icon shared

5) Browser Tabs favicon cache

---------------------------------------------------------
8) BIGGEST BENEFIT
---------------------------------------------------------

MEMORY SAVING 🚀

Example:
Without Flyweight:
10 lakh * 100 bytes = 100 MB

With Flyweight:
10 lakh * 24 bytes + 3 shared objects

Huge saving.

---------------------------------------------------------
9) HOW TO IDENTIFY IN INTERVIEW
---------------------------------------------------------

If interviewer says:
- too many similar objects
- memory optimization
- rendering millions of items
- repeated immutable data
- cache common objects

→ Think FLYWEIGHT

---------------------------------------------------------
10) FLYWEIGHT vs STRATEGY (VERY IMPORTANT)
---------------------------------------------------------

BOTH use composition
BUT INTENT ALAG HAI

---------------------------------------------------------
FLYWEIGHT:
---------------------------------------------------------
Intent:
Memory optimize by sharing common state

Focus:
Object data sharing

Problem:
Repeated objects

Example:
Asteroids, bullets, characters

---------------------------------------------------------
STRATEGY:
---------------------------------------------------------
Intent:
Runtime behavior/algorithm change

Focus:
Behavior switching

Problem:
Multiple algorithms

Example:
Payment strategy
Sort strategy

---------------------------------------------------------
KEY DIFFERENCE:
---------------------------------------------------------

Flyweight:
"Same data share karna"

Strategy:
"Same task ke different algorithms"

---------------------------------------------------------
11) ADVANTAGES
---------------------------------------------------------

1. Huge memory optimization
2. Faster object creation
3. Better cache locality
4. Scalable for millions objects
5. Reuse common immutable state

---------------------------------------------------------
12) DISADVANTAGES
---------------------------------------------------------

1. More complex design
2. Extrinsic state manage karna padta
3. Debugging harder
4. Thread-safe factory needed sometimes

---------------------------------------------------------
13) INTERVIEW ANSWER TEMPLATE
---------------------------------------------------------

"Flyweight pattern is used when we need to create a large
number of similar objects and want to reduce memory usage
by sharing intrinsic immutable state while keeping unique
extrinsic state outside."

---------------------------------------------------------
14) GOLDEN TAKEAWAY
---------------------------------------------------------

Flyweight = Memory optimization through shared immutable state

Intrinsic → shared
Extrinsic → unique

=========================================================