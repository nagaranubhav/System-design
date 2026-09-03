# ================================================================
#        FLYWEIGHT DESIGN PATTERN — FOREST EXAMPLE
#                     COMPLETE UML + EXPLANATION
# ================================================================
#
# Ab hum exactly wahi Forest / Tree example ka UML banayenge
# jo humne pichhle example me use kiya tha.
#
# Pehle overall picture samajh:
#
#
#                         ┌─────────────────────────┐
#                         │     TreeFlyweight       │
#                         │       <<interface>>     │
#                         │─────────────────────────│
#                         │ + render(x, y)          │
#                         └────────────▲────────────┘
#                                      │
#                                      │ implements
#                                      │
#                         ┌────────────┴────────────┐
#                         │        TreeType         │
#                         │      <<Flyweight>>      │
#                         │─────────────────────────│
#                         │ - name                  │
#                         │ - texture               │
#                         │ - color                 │
#                         │─────────────────────────│
#                         │ + render(x, y)          │
#                         └────────────▲────────────┘
#                                      │
#                                      │ shared
#                        ┌─────────────┼─────────────┐
#                        │             │             │
#                        │             │             │
#                        ▼             ▼             ▼
#                 ┌────────────┐ ┌────────────┐ ┌────────────┐
#                 │   Tree     │ │   Tree     │ │   Tree     │
#                 │────────────│ │────────────│ │────────────│
#                 │ - x        │ │ - x        │ │ - x        │
#                 │ - y        │ │ - y        │ │ - y        │
#                 │ - type ────┼─┼──►         │ │ - type ────┼──►
#                 │────────────│ │────────────│ │────────────│
#                 │ + render() │ │ + render() │ │ + render() │
#                 └────────────┘ └────────────┘ └────────────┘
#
#
#                         ┌─────────────────────────┐
#                         │      TreeFactory        │
#                         │       <<Factory>>       │
#                         │─────────────────────────│
#                         │ - treeTypes             │
#                         │   Map<Key, TreeType>    │
#                         │─────────────────────────│
#                         │ + getTreeType(...)      │
#                         └────────────▲────────────┘
#                                      │
#                                      │ manages / caches
#                                      │
#                                      ▼
#                               TreeType objects
#
#
#                         ┌─────────────────────────┐
#                         │         Forest          │
#                         │        <<Client>>        │
#                         │─────────────────────────│
#                         │ - trees                 │
#                         │ - factory               │
#                         │─────────────────────────│
#                         │ + plantTree(...)        │
#                         │ + renderForest()        │
#                         └─────────────────────────┘
#
#
# ================================================================
#              AB HAR CLASS KO EK-EK KARKE SAMJHO
# ================================================================
#
#
# ================================================================
# 1. TreeFlyweight
# ================================================================
#
#
#                 TreeFlyweight
#                 <<interface>>
#                       │
#                       │
#                       ▼
#                 render(x, y)
#
#
# Ye actual tree nahi hai.
#
# Ye ek contract hai.
#
# Iska matlab:
#
#     "Jo bhi Flyweight object hoga,
#      usko render() karna aana chahiye."
#
#
# Code:
#
# class TreeFlyweight {
# public:
#
#     virtual void render(int x, int y) = 0;
#
#     virtual ~TreeFlyweight() = default;
# };
#
#
# ------------------------------------------------
# render(x, y) me x aur y kyu hain?
# ------------------------------------------------
#
# Kyunki x aur y EXTRINSIC STATE hain.
#
# Example:
#
#     Oak Tree #1 → (100, 200)
#     Oak Tree #2 → (500, 700)
#     Oak Tree #3 → (900, 100)
#
# TreeType same hai,
# lekin position different hai.
#
# Isliye position ko Flyweight ke andar store nahi
# karenge.
#
#
# ================================================================
# 2. TreeType
# ================================================================
#
#
#                         TreeType
#                      <<Flyweight>>
#                         / | \
#                        /  |  \
#                       /   |   \
#                    name texture color
#
#
# Ye actual Flyweight hai.
#
# Iske andar wo data hoga jo multiple trees ke liye
# same ho sakta hai.
#
#
# class TreeType : public TreeFlyweight {
#
# private:
#
#     string name;
#     string texture;
#     string color;
#
# public:
#
#     TreeType(string name,
#              string texture,
#              string color)
#         : name(name),
#           texture(texture),
#           color(color) {
#     }
#
#     void render(int x, int y) override {
#
#         cout << "Rendering "
#              << name
#              << " at ("
#              << x << ", "
#              << y << ")"
#              << endl;
#     }
# };
#
#
# Yaha:
#
#     name
#     texture
#     color
#
# INTRINSIC STATE hain.
#
#
# ================================================================
# 3. Tree
# ================================================================
#
#
#                    Tree
#                 ┌─────────┐
#                 │ x       │
#                 │ y       │
#                 │ type ───┼──────► TreeType
#                 └─────────┘
#
#
# Tree individual tree ko represent karta hai.
#
# Example:
#
#     Tree #1
#         x = 100
#         y = 200
#
#     Tree #2
#         x = 500
#         y = 700
#
# Dono ke paas different position hai.
#
# Lekin dono same TreeType ko point kar sakte hain.
#
#
# class Tree {
#
# private:
#
#     int x;
#     int y;
#
#     shared_ptr<TreeType> type;
#
# public:
#
#     Tree(int x,
#          int y,
#          shared_ptr<TreeType> type)
#         : x(x),
#           y(y),
#           type(type) {
#     }
#
#     void render() {
#
#         type->render(x, y);
#     }
# };
#
#
# Yaha ek important relationship hai:
#
#
#       Tree
#        │
#        │ HAS-A
#        ▼
#     TreeType
#
#
# Tree IS-A TreeType nahi hai.
#
# Tree ke paas TreeType hai.
#
# Isliye:
#
#                 HAS-A
#                   │
#                   ▼
#             Tree ───────► TreeType
#
#
# ================================================================
# 4. TreeFactory
# ================================================================
#
#
#                     TreeFactory
#                   <<Factory>>
#                         │
#                         │ manages
#                         ▼
#                       Pool
#                         │
#             ┌───────────┼───────────┐
#             ▼           ▼           ▼
#          OakType     PineType    MangoType
#
#
# Factory ka sabse important kaam:
#
#     "Same TreeType already exist karta hai?"
#
#            │
#       ┌────┴────┐
#       │         │
#      YES        NO
#       │         │
#       ▼         ▼
#     RETURN    CREATE
#     EXISTING     │
#                  ▼
#                STORE
#                  │
#                  ▼
#                RETURN
#
#
# Code:
#
# class TreeFactory {
#
# private:
#
#     unordered_map<
#         string,
#         shared_ptr<TreeType>
#     > treeTypes;
#
#
# public:
#
#     shared_ptr<TreeType> getTreeType(
#         string name,
#         string texture,
#         string color) {
#
#
#         string key =
#             name + "_" +
#             texture + "_" +
#             color;
#
#
#         if (treeTypes.find(key)
#             != treeTypes.end()) {
#
#             return treeTypes[key];
#         }
#
#
#         auto treeType =
#             make_shared<TreeType>(
#                 name,
#                 texture,
#                 color
#             );
#
#
#         treeTypes[key] = treeType;
#
#
#         return treeType;
#     }
# };
#
#
# ================================================================
#             FACTORY KA POOL ACTUALLY KYA HAI?
# ================================================================
#
# Maan le humne 3 types use kiye:
#
#
#              treeTypes
#       ┌─────────────────────────────┐
#       │                             │
#       │ "Oak_oak.png_Green"         │────► TreeType #1
#       │                             │
#       │ "Pine_pine.png_DarkGreen"   │────► TreeType #2
#       │                             │
#       │ "Mango_mango.png_Green"     │────► TreeType #3
#       │                             │
#       └─────────────────────────────┘
#
#
# Ye basically CACHE / POOL hai.
#
# Agar Oak already bana hua hai:
#
#     factory.getTreeType("Oak", ...)
#
# toh factory:
#
#     "Naya Oak mat banao.
#      Jo already hai wahi de do."
#
#
# ================================================================
# 5. Forest
# ================================================================
#
#
#                    Forest
#                 <<Client>>
#                  /       \
#                 /         \
#                ▼           ▼
#             trees        factory
#
#
# Forest actual client hai.
#
# Ye trees plant karta hai.
#
#
# class Forest {
#
# private:
#
#     vector<Tree> trees;
#
#     TreeFactory factory;
#
# public:
#
#     void plantTree(
#         int x,
#         int y,
#         string name,
#         string texture,
#         string color) {
#
#
#         auto treeType =
#             factory.getTreeType(
#                 name,
#                 texture,
#                 color
#             );
#
#
#         trees.emplace_back(
#             x,
#             y,
#             treeType
#         );
#     }
#
#
#     void renderForest() {
#
#         for (auto& tree : trees) {
#             tree.render();
#         }
#     }
# };
#
#
# Forest ko ye decide karne ki zarurat nahi hai ki
# TreeType already exist karta hai ya nahi.
#
# Ye responsibility Factory ki hai.
#
#
# ================================================================
#              AB COMPLETE RELATIONSHIP UML
# ================================================================
#
#
#                         <<interface>>
#                      ┌──────────────────┐
#                      │  TreeFlyweight   │
#                      ├──────────────────┤
#                      │ + render(x,y)    │
#                      └────────▲─────────┘
#                               │
#                               │ realization
#                               │
#                      ┌────────┴─────────┐
#                      │    TreeType      │
#                      │  <<Flyweight>>   │
#                      ├──────────────────┤
#                      │ - name           │
#                      │ - texture        │
#                      │ - color          │
#                      ├──────────────────┤
#                      │ + render(x,y)    │
#                      └────────▲─────────┘
#                               │
#                               │ shared reference
#                  ┌────────────┼────────────┐
#                  │            │            │
#                  │            │            │
#                  ▼            ▼            ▼
#             ┌─────────┐  ┌─────────┐  ┌─────────┐
#             │  Tree   │  │  Tree   │  │  Tree   │
#             ├─────────┤  ├─────────┤  ├─────────┤
#             │ x       │  │ x       │  │ x       │
#             │ y       │  │ y       │  │ y       │
#             │ type ───┼─►│ type ───┼─►│ type ───┼─►
#             └─────────┘  └─────────┘  └─────────┘
#
#
#                  ▲
#                  │
#                  │ manages
#                  │
#          ┌───────┴──────────┐
#          │   TreeFactory    │
#          │    <<Factory>>   │
#          ├──────────────────┤
#          │ - treeTypes      │
#          ├──────────────────┤
#          │ + getTreeType()  │
#          └────────▲─────────┘
#                   │
#                   │ used by
#                   │
#          ┌────────┴─────────┐
#          │      Forest      │
#          │     <<Client>>   │
#          ├──────────────────┤
#          │ - trees          │
#          │ - factory        │
#          ├──────────────────┤
#          │ + plantTree()    │
#          │ + renderForest() │
#          └──────────────────┘
#
#
# ================================================================
#                  UML ARROWS KO SAMJHO
# ================================================================
#
#
# 1. TreeType ────────▷ TreeFlyweight
#
#        IS-A relationship
#
# Kyunki:
#
#     class TreeType : public TreeFlyweight
#
# TreeType TreeFlyweight ka implementation hai.
#
#
# ------------------------------------------------
#
# 2. Tree ────────────► TreeType
#
#        HAS-A relationship
#
# Kyunki:
#
#     shared_ptr<TreeType> type;
#
# Tree ke paas TreeType ka reference hai.
#
#
# ------------------------------------------------
#
# 3. Forest ──────────► TreeFactory
#
#        HAS-A relationship
#
# Kyunki:
#
#     TreeFactory factory;
#
#
# ------------------------------------------------
#
# 4. TreeFactory ─────► TreeType
#
#        MANAGES / CACHES
#
# Factory TreeType objects ko pool me store karti hai.
#
#
# ================================================================
#              INTRINSIC VS EXTRINSIC UML
# ================================================================
#
#
#              TreeType
#           <<Flyweight>>
#                 │
#       ┌─────────┼─────────┐
#       │         │         │
#       ▼         ▼         ▼
#      name    texture     color
#
#       ↑
#       │
#       │ INTRINSIC STATE
#       │
#       │ "SAME / SHAREABLE"
#
#
#
#              Tree
#               │
#          ┌────┴────┐
#          ▼         ▼
#          x         y
#
#          ↑
#          │
#          │ EXTRINSIC STATE
#          │
#          │ "UNIQUE / CHANGING"
#
#
# So:
#
#     TreeType = common information
#
#     Tree     = individual information
#
#
# ================================================================
#                 ACTUAL OBJECT DIAGRAM
# ================================================================
#
# UML CLASS DIAGRAM batata hai:
#
#     classes ka structure kya hai.
#
# OBJECT DIAGRAM batata hai:
#
#     runtime par actual objects kaise connected hain.
#
#
# Example:
#
#
#       ┌────────────────────────────┐
#       │ TreeType #1                │
#       │────────────────────────────│
#       │ name = "Oak"               │
#       │ texture = "oak.png"        │
#       │ color = "Green"            │
#       └──────────────▲─────────────┘
#                      │
#              ┌───────┼────────┐
#              │       │        │
#              │       │        │
#              │       │        │
#        ┌─────┴──┐ ┌──┴─────┐ ┌┴────────┐
#        │ Tree#1 │ │ Tree#2 │ │ Tree#3  │
#        │────────│ │────────│ │─────────│
#        │x=100   │ │x=500   │ │x=900    │
#        │y=200   │ │y=700   │ │y=100    │
#        └────────┘ └────────┘ └─────────┘
#
#
# Three Tree objects.
#
# One TreeType object.
#
# THAT is the actual memory optimization.
#
#
# ================================================================
#                   COMPLETE FLOW
# ================================================================
#
#
# User:
#
#     "Oak tree plant karo at (100,200)"
#
#                │
#                ▼
#             Forest
#                │
#                │ getTreeType()
#                ▼
#          TreeFactory
#                │
#                │ check pool
#                ▼
#       "Oak_oak.png_Green"
#                │
#          ┌─────┴─────┐
#          │           │
#        found       not found
#          │           │
#          ▼           ▼
#       return       create
#       existing       │
#                      ▼
#                   store
#                      │
#                      ▼
#                  TreeType
#                      │
#                      ▼
#                    Tree
#                 x=100,y=200
#
#
# ================================================================
#             SECOND OAK TREE KA FLOW
# ================================================================
#
#
# User:
#
#     "Oak tree plant karo at (500,700)"
#
#                │
#                ▼
#             Forest
#                │
#                ▼
#          TreeFactory
#                │
#                ▼
#       "Oak_oak.png_Green"
#                │
#                ▼
#          ALREADY EXISTS
#                │
#                ▼
#       SAME TreeType object
#                │
#                ▼
#         New Tree object
#         x=500,y=700
#
#
# Notice:
#
#     TreeType NEW nahi bana.
#
#     Sirf Tree instance bana.
#
#
# ================================================================
#                 WHY NOT PUT x AND y IN TreeType?
# ================================================================
#
# Bahut important interview question.
#
# Agar hum ye kar dete:
#
# class TreeType {
#
#     string name;
#     string texture;
#     string color;
#
#     int x;
#     int y;
# };
#
#
# Toh problem:
#
# Oak #1:
#
#     x = 100
#     y = 200
#
#
# Oak #2:
#
#     x = 500
#     y = 700
#
#
# Agar dono SAME TreeType object share kar rahe hain,
# toh x aur y kya rakhenge?
#
#
#     x = 100 ?
#
#     ya
#
#     x = 500 ?
#
#
# Dono ek hi object hain.
#
# Isliye impossible.
#
#
# Therefore:
#
#     COMMON DATA
#         ↓
#     TreeType
#
#     UNIQUE DATA
#         ↓
#     Tree
#
#
# ================================================================
#                  WHY FACTORY IS IMPORTANT
# ================================================================
#
# Suppose Factory nahi hoti.
#
# Client:
#
#     auto oak1 =
#         make_shared<TreeType>(
#             "Oak",
#             "oak.png",
#             "Green"
#         );
#
#
#     auto oak2 =
#         make_shared<TreeType>(
#             "Oak",
#             "oak.png",
#             "Green"
#         );
#
#
# Client ne accidentally 2 same objects bana diye.
#
#
#             oak1
#               ↓
#          TreeType Oak
#
#             oak2
#               ↓
#          TreeType Oak
#
#
# Duplicate!
#
#
# Factory ye responsibility apne paas rakhti hai:
#
#     "Object creation mere control me hoga."
#
# Therefore:
#
#     Client
#       │
#       ▼
#     Factory
#       │
#       ├── already exists → reuse
#       │
#       └── doesn't exist → create
#
#
# ================================================================
#                  FULL C++ IMPLEMENTATION
# ================================================================
#
#
# #include <iostream>
# #include <string>
# #include <vector>
# #include <unordered_map>
# #include <memory>
#
# using namespace std;
#
#
# // ============================================================
# // FLYWEIGHT INTERFACE
# // ============================================================
#
# class TreeFlyweight {
#
# public:
#
#     // x and y are EXTRINSIC.
#     // They are supplied from outside.
#     virtual void render(int x, int y) = 0;
#
#     virtual ~TreeFlyweight() = default;
# };
#
#
# // ============================================================
# // CONCRETE FLYWEIGHT
# // ============================================================
#
# class TreeType : public TreeFlyweight {
#
# private:
#
#     // INTRINSIC STATE
#     // These values can be shared.
#     string name;
#     string texture;
#     string color;
#
#
# public:
#
#     TreeType(string name,
#              string texture,
#              string color)
#         : name(name),
#           texture(texture),
#           color(color) {
#     }
#
#
#     void render(int x, int y) override {
#
#         cout << "Tree: " << name
#              << " | Position: ("
#              << x << ", "
#              << y << ")"
#              << " | Texture: "
#              << texture
#              << " | Color: "
#              << color
#              << endl;
#     }
# };
#
#
# // ============================================================
# // FLYWEIGHT FACTORY
# // ============================================================
#
# class TreeFactory {
#
# private:
#
#     // Pool / Cache of Flyweight objects.
#     unordered_map<
#         string,
#         shared_ptr<TreeType>
#     > treeTypes;
#
#
# public:
#
#     shared_ptr<TreeType> getTreeType(
#         string name,
#         string texture,
#         string color) {
#
#
#         // Build a unique key using intrinsic data.
#         string key =
#             name + "_" +
#             texture + "_" +
#             color;
#
#
#         // If object already exists,
#         // return the existing object.
#         if (treeTypes.find(key)
#             != treeTypes.end()) {
#
#             return treeTypes[key];
#         }
#
#
#         // Otherwise create a new Flyweight.
#         auto treeType =
#             make_shared<TreeType>(
#                 name,
#                 texture,
#                 color
#             );
#
#
#         // Save it for future reuse.
#         treeTypes[key] = treeType;
#
#
#         return treeType;
#     }
# };
#
#
# // ============================================================
# // TREE
# // ============================================================
#
# class Tree {
#
# private:
#
#     // EXTRINSIC STATE
#     int x;
#     int y;
#
#     // Shared Flyweight
#     shared_ptr<TreeType> type;
#
#
# public:
#
#     Tree(int x,
#          int y,
#          shared_ptr<TreeType> type)
#         : x(x),
#           y(y),
#           type(type) {
#     }
#
#
#     void render() {
#
#         // Pass unique state to shared object.
#         type->render(x, y);
#     }
# };
#
#
# // ============================================================
# // CLIENT
# // ============================================================
#
# class Forest {
#
# private:
#
#     vector<Tree> trees;
#
#     TreeFactory factory;
#
#
# public:
#
#     void plantTree(
#         int x,
#         int y,
#         string name,
#         string texture,
#         string color) {
#
#
#         // Factory decides whether to create
#         // or reuse the Flyweight.
#         auto treeType =
#             factory.getTreeType(
#                 name,
#                 texture,
#                 color
#             );
#
#
#         // Create lightweight Tree instance.
#         trees.emplace_back(
#             x,
#             y,
#             treeType
#         );
#     }
#
#
#     void renderForest() {
#
#         for (auto& tree : trees) {
#
#             tree.render();
#         }
#     }
# };
#
#
# // ============================================================
# // MAIN
# // ============================================================
#
# int main() {
#
#     Forest forest;
#
#
#     forest.plantTree(
#         100,
#         200,
#         "Oak",
#         "oak.png",
#         "Green"
#     );
#
#
#     forest.plantTree(
#         500,
#         700,
#         "Oak",
#         "oak.png",
#         "Green"
#     );
#
#
#     forest.plantTree(
#         900,
#         100,
#         "Oak",
#         "oak.png",
#         "Green"
#     );
#
#
#     forest.plantTree(
#         300,
#         400,
#         "Pine",
#         "pine.png",
#         "DarkGreen"
#     );
#
#
#     forest.plantTree(
#         800,
#         600,
#         "Pine",
#         "pine.png",
#         "DarkGreen"
#     );
#
#
#     forest.renderForest();
#
#
#     return 0;
# }
#
#
# ================================================================
#                   FINAL MENTAL MODEL
# ================================================================
#
#
#                 "FOREST"
#                    │
#                    │ wants trees
#                    ▼
#              "TreeFactory"
#                    │
#                    │ gives shared type
#                    ▼
#                "TreeType"
#             <<FLYWEIGHT>>
#                    │
#             ┌──────┼──────┐
#             │      │      │
#             ▼      ▼      ▼
#           Tree   Tree   Tree
#            │      │      │
#          (x,y)  (x,y)  (x,y)
#
#
# TreeType:
#
#     "Main same information mere paas rakho."
#
#
# Tree:
#
#     "Meri position mere paas rahegi."
#
#
# Factory:
#
#     "Same TreeType ko dobara create nahi hone dungi."
#
#
# Forest:
#
#     "Mujhe bas tree plant karna hai;
#      object reuse ka tension mujhe nahi chahiye."
#
#
# ================================================================
#                    INTERVIEW GOLD
# ================================================================
#
# Agar interviewer puche:
#
# "Why Flyweight?"
#
# Answer:
#
#     "Because we have a large number of similar objects
#      and want to avoid storing the same heavy data again
#      and again."
#
#
# "What is intrinsic state?"
#
#     "State that is common and can safely be shared,
#      like tree type, texture and color."
#
#
# "What is extrinsic state?"
#
#     "State that varies per object or per usage,
#      like the tree's x and y position."
#
#
# "Why Factory?"
#
#     "The factory maintains a pool of Flyweights and
#      ensures that an existing Flyweight is reused instead
#      of creating a duplicate."
#
#
# "Where is the actual memory saving?"
#
#     "Heavy common data such as texture/model information
#      is stored only once inside TreeType. Individual Tree
#      objects only store their changing state and a reference
#      to the shared Flyweight."
#
#
# ================================================================
#                  FLYWEIGHT KA GOLDEN RULE
# ================================================================
#
#
#                    SAME
#                      │
#                      ▼
#                   SHARE
#                      │
#                      ▼
#                 Flyweight
#
#
#                  DIFFERENT
#                      │
#                      ▼
#                    PASS
#                      │
#                      ▼
#                Extrinsic State
#
#
#
#             🔥 REMEMBER THIS 🔥
#
#       INTRINSIC  =  SHARE
#       EXTRINSIC  =  PASS
#       FACTORY    =  REUSE
#       RESULT     =  MEMORY SAVE
#
# ================================================================