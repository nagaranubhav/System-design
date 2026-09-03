============================================================
        FLYWEIGHT DESIGN PATTERN — TAGDA REAL-WORLD EXAMPLE
============================================================

Example: ONLINE MAP APPLICATION 🌍

Soch tu Google Maps jaisi application bana raha hai.

Map ke andar thousands / millions of objects ho sakte hain:

    🌳 Tree
    🌳 Tree
    🌳 Tree
    🏠 House
    🏠 House
    🚗 Car
    🚗 Car
    🚗 Car
    ...

Agar har tree ke liye completely naya object banaya:

    Tree object 1
    Tree object 2
    Tree object 3
    ...
    Tree object 1,00,000

Toh memory bahut consume hogi.

Lekin dhyaan de:

1000 trees ka TYPE same ho sakta hai.

For example:

    Tree Type = Oak
    Texture   = oak.png
    Color     = Green
    Size      = Large

Ye information har Oak tree ke liye same hai.

Lekin:

    x = 100, y = 200
    x = 500, y = 800
    x = 900, y = 100

Ye har tree ki location alag hai.

TOH IDEA:

    SAME DATA
        ↓
    ek hi object share karo

    DIFFERENT DATA
        ↓
    bahar se pass karo


============================================================
                    PROBLEM
============================================================

Normal approach:

class Tree {

    string type;
    string texture;
    string color;

    int x;
    int y;

public:

    Tree(string type,
         string texture,
         string color,
         int x,
         int y) {

        this->type = type;
        this->texture = texture;
        this->color = color;
        this->x = x;
        this->y = y;
    }
};


Ab maan le:

    1,00,000 trees hain.

Har tree ke paas:

    type
    texture
    color
    x
    y

sab kuch individually stored hai.

Problem:

    SAME type
    SAME texture
    SAME color

baar-baar store ho raha hai.

Humein ye duplication avoid karna hai.


============================================================
                FLYWEIGHT SOLUTION
============================================================

Hum Tree ko 2 parts me divide karenge:

             TREE
               |
        ┌──────┴──────┐
        │             │
        ▼             ▼
   Intrinsic       Extrinsic
     State            State
        │             │
        ▼             ▼
     Shared         Unique
        │             │
        ▼             ▼
      type            x
      texture         y
      color


INTRINSIC STATE:

    Jo multiple objects ke liye same hai.

EXTRINSIC STATE:

    Jo har object ke liye different hai.


============================================================
              STEP 1 — FLYWEIGHT INTERFACE
============================================================

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;


class TreeFlyweight {

public:

    virtual void render(int x, int y) = 0;

    virtual ~TreeFlyweight() = default;
};


Yaha TreeFlyweight ek interface hai.

Iska matlab:

    "Jo bhi actual tree flyweight banega,
     usko render() provide karna padega."


IMPORTANT:

    render(int x, int y)

Yaha x aur y kya hain?

    EXTRINSIC STATE

Kyun?

Kyunki tree ki location har baar different hogi.


============================================================
             STEP 2 — CONCRETE FLYWEIGHT
============================================================

class TreeType : public TreeFlyweight {

private:

    // ============================================
    // INTRINSIC STATE
    // ============================================

    string name;
    string texture;
    string color;


public:

    TreeType(string name,
             string texture,
             string color)
        : name(name),
          texture(texture),
          color(color) {

    }


    void render(int x, int y) override {

        cout << "Rendering "
             << name
             << " tree at ("
             << x << ", "
             << y << ")"
             << endl;

        cout << "Texture : "
             << texture
             << endl;

        cout << "Color   : "
             << color
             << endl;

        cout << "----------------------"
             << endl;
    }
};


AB DHYAAN DE.

TreeType object ke andar:

    name
    texture
    color

hain.

Lekin:

    x
    y

NAHI hain.

Kyun?

Because x and y har tree ke liye different hain.


============================================================
             EK IMPORTANT CONCEPT
============================================================

Suppose:

    Oak tree #1
        position = (100, 200)

    Oak tree #2
        position = (500, 700)

    Oak tree #3
        position = (900, 100)


Kya teeno ke liye ye information different hai?

    position → YES

Kya teeno ka ye data same ho sakta hai?

    name     → Oak
    texture  → oak.png
    color    → Green

YES!


Therefore:

             ONE OBJECT

       TreeType("Oak",
                "oak.png",
                "Green")


aur usi object ko:

       (100,200)
       (500,700)
       (900,100)

par render kar denge.


============================================================
        STEP 3 — FLYWEIGHT FACTORY
============================================================

Ab ek problem hai.

Kaun decide karega ki:

    "Oak ka object already bana hua hai
     ya nahi?"

Iske liye:

    FlyweightFactory


class TreeFactory {

private:

    // ============================================
    // OBJECT POOL
    // ============================================

    unordered_map<string,
                   shared_ptr<TreeType>> treeTypes;


public:

    shared_ptr<TreeType> getTreeType(
        string name,
        string texture,
        string color) {


        // ----------------------------------------
        // UNIQUE KEY
        // ----------------------------------------

        string key =
            name + "_" +
            texture + "_" +
            color;


        // ----------------------------------------
        // CHECK:
        // Kya same TreeType already exist karta hai?
        // ----------------------------------------

        if (treeTypes.find(key) != treeTypes.end()) {

            return treeTypes[key];
        }


        // ----------------------------------------
        // Object nahi mila.
        // New object create karo.
        // ----------------------------------------

        auto treeType =
            make_shared<TreeType>(
                name,
                texture,
                color
            );


        // ----------------------------------------
        // Future reuse ke liye store kar do.
        // ----------------------------------------

        treeTypes[key] = treeType;


        return treeType;
    }
};


============================================================
             AB FACTORY KO TOD KE SAMJH
============================================================

Ye line:

unordered_map<string, shared_ptr<TreeType>> treeTypes;


Isko simple language me samajh:

    map ke andar:

        KEY
          ↓
        TREE OBJECT

Example:

    "Oak_oak.png_Green"
             ↓
        TreeType object


    "Pine_pine.png_DarkGreen"
             ↓
        TreeType object


Factory ke paas basically ek POOL hai.

Pool ka matlab:

    "Already created objects ka collection."


============================================================
             shared_ptr KYA KAR RAHA HAI?
============================================================

Ye thoda advanced syntax hai:

    shared_ptr<TreeType>


Simple language:

    shared_ptr ek smart pointer hai.

Ye object ki memory ko automatically manage karta hai.

Suppose:

    TreeType object

ko multiple jagah se use kiya ja raha hai.

shared_ptr track karta hai:

    "Kitne references is object ko use kar rahe hain?"

Jab koi use nahi karta:

    object automatically destroy ho sakta hai.


Flyweight me ye useful hai because:

    SAME object
       ↑
       |
    multiple clients
       |
       ↓
    share kar sakte hain.


============================================================
             make_shared KYA HAI?
============================================================

Ye:

    make_shared<TreeType>(
        name,
        texture,
        color
    );


roughly ye kaam kar raha hai:

    new TreeType(name, texture, color)

but smart pointer ke saath.

Matlab:

    make_shared<TreeType>(...)

    ↓

    TreeType object create karo
            +
    shared_ptr bana do


Modern C++ me ye generally better/safe approach hai.


============================================================
           find(key) != end() KA MATLAB
============================================================

Ye line:

    if (treeTypes.find(key) != treeTypes.end())


beginner ke liye confusing hoti hai.

Simple meaning:

    "Kya map me ye key exist karti hai?"


find(key):

    key mil gayi
        ↓
    iterator return karega


key nahi mili
        ↓
    end() return karega


So:

    find(key) != end()

means:

    "Key mil gayi."


Therefore:

    if (treeTypes.find(key) != treeTypes.end())

means:

    "Agar same TreeType pehle se available hai,
     toh naya object mat banao."


============================================================
             STEP 4 — TREE OBJECT
============================================================

Ab hum ek Tree class banayenge.

Ye actual individual tree ko represent karegi.


class Tree {

private:

    int x;
    int y;

    shared_ptr<TreeType> type;


public:

    Tree(int x,
         int y,
         shared_ptr<TreeType> type)
        : x(x),
          y(y),
          type(type) {

    }


    void render() {

        type->render(x, y);
    }
};


Ab ye bahut important hai.


Tree ke paas:

    x
    y
    TreeType


hai.


TreeType ke paas:

    name
    texture
    color


hai.


So:

             Tree
        ┌───────────────┐
        │ x             │
        │ y             │
        │               │
        │ TreeType ─────┼──────► SHARED
        └───────────────┘


Tree ka:

    x, y

unique hai.


TreeType ka:

    name
    texture
    color

shared hai.


============================================================
             STEP 5 — FOREST / CLIENT
============================================================

Ab actual client:

class Forest {

private:

    vector<Tree> trees;

    TreeFactory factory;


public:

    void plantTree(
        int x,
        int y,
        string name,
        string texture,
        string color) {


        // ----------------------------------------
        // Factory se Flyweight lo
        // ----------------------------------------

        auto treeType =
            factory.getTreeType(
                name,
                texture,
                color
            );


        // ----------------------------------------
        // Individual Tree create karo
        // ----------------------------------------

        trees.emplace_back(
            x,
            y,
            treeType
        );
    }


    void renderForest() {

        for (auto& tree : trees) {

            tree.render();
        }
    }
};


============================================================
              emplace_back KYA HAI?
============================================================

Ye:

    trees.emplace_back(
        x,
        y,
        treeType
    );


vector ke end me directly Tree object construct
kar deta hai.

Conceptually:

    Tree tree(x, y, treeType);

    trees.push_back(tree);


jaisa samajh sakta hai.

emplace_back directly vector ke andar object
construct karne ki koshish karta hai.


============================================================
                    MAIN
============================================================

int main() {

    Forest forest;


    // ============================================
    // OAK TREES
    // ============================================

    forest.plantTree(
        100,
        200,
        "Oak",
        "oak.png",
        "Green"
    );


    forest.plantTree(
        500,
        700,
        "Oak",
        "oak.png",
        "Green"
    );


    forest.plantTree(
        900,
        100,
        "Oak",
        "oak.png",
        "Green"
    );


    // ============================================
    // PINE TREES
    // ============================================

    forest.plantTree(
        300,
        400,
        "Pine",
        "pine.png",
        "DarkGreen"
    );


    forest.plantTree(
        800,
        600,
        "Pine",
        "pine.png",
        "DarkGreen"
    );


    forest.renderForest();


    return 0;
}


============================================================
                 AB ACTUAL DRY RUN
============================================================

Let's dry run.


------------------------------------------------------------
CALL 1
------------------------------------------------------------

forest.plantTree(
    100,
    200,
    "Oak",
    "oak.png",
    "Green"
);


Step 1:

    Forest ke paas factory hai.


Step 2:

    factory.getTreeType(
        "Oak",
        "oak.png",
        "Green"
    );


key banegi:

    "Oak_oak.png_Green"


Pool:

    EMPTY


Check:

    Kya "Oak_oak.png_Green" hai?

    NO.


So new object:

    TreeType(
        "Oak",
        "oak.png",
        "Green"
    );


Pool:

    "Oak_oak.png_Green"
              ↓
        TreeType #1


Ab Tree:

    x = 100
    y = 200
    type = TreeType #1


------------------------------------------------------------
CALL 2
------------------------------------------------------------

forest.plantTree(
    500,
    700,
    "Oak",
    "oak.png",
    "Green"
);


Again key:

    "Oak_oak.png_Green"


Pool:

    "Oak_oak.png_Green"
              ↓
        TreeType #1


Object ALREADY exists.


Therefore:

    NO NEW TreeType.


Factory return karegi:

    TreeType #1


New Tree:

    x = 500
    y = 700
    type = TreeType #1


Ab:

    Tree #1 ───────┐
                   │
                   ▼
             TreeType #1
                   ▲
                   │
    Tree #2 ───────┘


SAME TreeType object.


------------------------------------------------------------
CALL 3
------------------------------------------------------------

forest.plantTree(
    900,
    100,
    "Oak",
    "oak.png",
    "Green"
);


Again:

    key = "Oak_oak.png_Green"


Pool me already present.


Again:

    TreeType #1


So now:


             Tree #1
             (100,200)
                 │
                 │
                 ▼
          ┌─────────────┐
          │ TreeType #1 │
          │ Oak         │
          │ oak.png     │
          │ Green       │
          └─────────────┘
                 ▲
                 │
                 │
             Tree #2
             (500,700)

                 ▲
                 │
             Tree #3
             (900,100)


3 Trees.

BUT:

    only 1 TreeType object.


THIS IS FLYWEIGHT.


============================================================
                THEN PINE AYA
============================================================

forest.plantTree(
    300,
    400,
    "Pine",
    "pine.png",
    "DarkGreen"
);


Key:

    "Pine_pine.png_DarkGreen"


Pool:

    Oak_oak.png_Green
              ↓
          TreeType #1


    Pine_pine.png_DarkGreen

              NOT FOUND


So:

    create TreeType #2


Pool becomes:


    "Oak_oak.png_Green"
             ↓
        TreeType #1


    "Pine_pine.png_DarkGreen"
             ↓
        TreeType #2


------------------------------------------------------------
NEXT PINE
------------------------------------------------------------

forest.plantTree(
    800,
    600,
    "Pine",
    "pine.png",
    "DarkGreen"
);


Same key:

    "Pine_pine.png_DarkGreen"


Already present.


So:

    SAME TreeType #2


No duplicate object.


============================================================
                  FINAL MEMORY
============================================================


                    FOREST
                       │
             ┌─────────┴─────────┐
             │                   │
             ▼                   ▼
          Tree #1              Tree #2
         (100,200)             (500,700)
             │                   │
             └────────┐   ┌──────┘
                      ▼   ▼
                 TreeType #1
                 ┌────────────┐
                 │ Oak        │
                 │ oak.png    │
                 │ Green      │
                 └────────────┘


          Tree #3
         (900,100)
             │
             ▼
        TreeType #1


          Tree #4
         (300,400)
             │
             ▼
        TreeType #2
        ┌────────────┐
        │ Pine       │
        │ pine.png   │
        │ DarkGreen  │
        └────────────┘


          Tree #5
         (800,600)
             │
             ▼
        TreeType #2


So:

    5 individual Tree objects

BUT

    only 2 TreeType objects.


============================================================
          WHY IS THIS CALLED FLYWEIGHT?
============================================================

"Flyweight" ka basic idea hai:

    lightweight object ko bahut jagah reuse karna.


Humne:

    TreeType

ko reusable bana diya.


1000 Oak trees:

    ❌ 1000 TreeType objects


instead:

    ✅ 1 TreeType object

aur:

    1000 Trees
       ↓
    same TreeType


============================================================
              UML OF THIS EXAMPLE
============================================================


┌───────────────────────────────┐
│        TreeFlyweight           │
│───────────────────────────────│
│ + render(x, y)                │
└───────────────▲───────────────┘
                │
                │ implements
                │
┌───────────────┴───────────────┐
│          TreeType              │
│───────────────────────────────│
│ - name                         │
│ - texture                      │
│ - color                        │
│───────────────────────────────│
│ + render(x, y)                 │
└────────────────▲──────────────┘
                 │
                 │ shared by
                 │
          ┌──────┴───────┐
          │              │
          ▼              ▼
      ┌────────┐     ┌────────┐
      │  Tree  │     │  Tree  │
      │────────│     │────────│
      │ x      │     │ x      │
      │ y      │     │ y      │
      │ type ──┼─────┼──►    │
      └────────┘     └────────┘
             \          /
              \        /
               ▼      ▼
              TreeType


                 ▲
                 │
                 │ creates / reuses
                 │
┌────────────────┴────────────────┐
│          TreeFactory             │
│─────────────────────────────────│
│ - treeTypes                     │
│─────────────────────────────────│
│ + getTreeType(...)              │
└────────────────▲────────────────┘
                 │
                 │ used by
                 │
┌────────────────┴────────────────┐
│             Forest               │
│─────────────────────────────────│
│ - trees                         │
│ - factory                       │
│─────────────────────────────────│
│ + plantTree(...)                │
│ + renderForest()                │
└─────────────────────────────────┘


============================================================
             RELATIONSHIPS CLEARLY
============================================================

TreeType

    IS-A

TreeFlyweight

because:

    class TreeType : public TreeFlyweight


--------------------------------------------

Tree

    HAS-A

TreeType

because Tree ke paas:

    shared_ptr<TreeType> type;


--------------------------------------------

Forest

    HAS-A

TreeFactory

because:

    TreeFactory factory;


--------------------------------------------

TreeFactory

    HAS-A / manages

TreeType objects

because:

    unordered_map<
        string,
        shared_ptr<TreeType>
    > treeTypes;


============================================================
          FLYWEIGHT MEIN SABSE IMPORTANT CONFUSION
============================================================

Question:

    "Agar Tree object hi bana rahe hain,
     toh memory save kaha hui?"


Answer:

YES, Tree objects toh banenge.


But Tree object lightweight hai:


Tree:

    x
    y
    pointer/reference to TreeType


Heavy information:

    name
    texture
    color
    potentially image/mesh/model data

ye TreeType me hai.


Aur TreeType SHARE ho raha hai.


So:

    Tree
       ↓
    small


    TreeType
       ↓
    heavy
    but shared


============================================================
              REAL GAME EXAMPLE
============================================================

Imagine game me:

    1,00,000 trees.


WITHOUT FLYWEIGHT:


    Tree #1
       ├── Oak
       ├── oak.png
       ├── Green
       └── huge texture/model


    Tree #2
       ├── Oak
       ├── oak.png
       ├── Green
       └── huge texture/model


    Tree #3
       ├── Oak
       ├── oak.png
       ├── Green
       └── huge texture/model


Ye huge data repeat ho raha hai.


WITH FLYWEIGHT:


                   TreeType
              ┌───────────────┐
              │ Oak            │
              │ oak.png        │
              │ Green          │
              │ Heavy model    │
              └───────▲───────┘
                      │
          ┌───────────┼────────────┐
          │           │            │
          ▼           ▼            ▼
       Tree #1      Tree #2      Tree #3
       x,y          x,y          x,y


Heavy data:

    ONLY ONCE.


============================================================
                 INTERVIEW ME KAISE BOLNA
============================================================

Interviewer:

    "Explain Flyweight Pattern."


Tu bol:


"Flyweight pattern ka use tab karte hain jab application
me bahut large number of similar objects create ho rahe
hote hain aur unke andar kuch common data repeat ho raha
hota hai.

Hum common data ko intrinsic state ke form me ek shared
Flyweight object me rakhte hain.

Jo data object-specific hota hai, jaise tree ki position,
usse extrinsic state ke form me bahar se pass karte hain.

Ek FlyweightFactory maintain karte hain jo object pool
manage karti hai. Agar required Flyweight already exist
karta hai toh factory same object return karti hai,
otherwise naya object create karke pool me store karti hai.

Isse duplicate heavy objects avoid hote hain aur memory
consumption reduce hota hai."


============================================================
                 ONE-LINE MEMORY TRICK
============================================================


              FLYWEIGHT


        "JO SAME HAI USKO SHARE KARO
         JO DIFFERENT HAI USKO PASS KARO."


             INTRINSIC
                 ↓
               SHARE


             EXTRINSIC
                 ↓
               PASS


Example:

    TREE TYPE
       ↓
    Oak + texture + color
       ↓
    SHARE


    TREE INSTANCE
       ↓
    x + y
       ↓
    DIFFERENT


============================================================
              COMPLETE ARCHITECTURE
============================================================


                 CLIENT
                (Forest)
                    │
                    │ asks for
                    ▼
            ┌───────────────┐
            │ TreeFactory   │
            └───────┬───────┘
                    │
              checks Pool
                    │
          ┌─────────┴─────────┐
          │                   │
       EXISTS               NOT EXISTS
          │                   │
          ▼                   ▼
       RETURN              CREATE
       SAME OBJECT         OBJECT
          │                   │
          │                   ▼
          │                STORE
          │                   │
          └─────────┬─────────┘
                    │
                    ▼
                TreeType
              (Flyweight)
                    │
                    │ shared
          ┌─────────┼─────────┐
          │         │         │
          ▼         ▼         ▼
        Tree      Tree      Tree
          │         │         │
          │         │         │
          ▼         ▼         ▼
       (x,y)      (x,y)     (x,y)

     Extrinsic State
          ↓
     passed to render()


============================================================
                 FINAL TAKEAWAY
============================================================

Flyweight ka main purpose:

    MEMORY OPTIMIZATION


Problem:

    Many similar objects
          +
    Repeated common data
          ↓
    Wasted memory


Solution:

    Common data
          ↓
    Flyweight
          ↓
    Shared


    Unique data
          ↓
    Client / individual object
          ↓
    Passed from outside


And Factory ka kaam:

    "Same Flyweight already hai?
         ↓
       YES → reuse
         ↓
       NO → create + store"


Bas ye 3 cheezein dimaag me rakh:


    1. INTRINSIC STATE
       = shared data


    2. EXTRINSIC STATE
       = changing / unique data


    3. FACTORY
       = existing Flyweight ko reuse karwati hai


                 🔥 CORE IDEA 🔥

        MANY OBJECTS
             ↓
       COMMON DATA
             ↓
       ONE SHARED OBJECT
             ↓
       MEMORY SAVE