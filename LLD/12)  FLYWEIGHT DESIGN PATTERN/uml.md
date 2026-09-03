# ============================================================
#              FLYWEIGHT DESIGN PATTERN - UML
# ============================================================
#
# Example: Text Editor
#
# Imagine ek Text Editor hai jisme bahut saare characters hain.
#
# "A"  -> font = Arial, size = 14, color = black
# "B"  -> font = Arial, size = 14, color = black
# "C"  -> font = Arial, size = 14, color = black
#
# Agar har character ke liye alag-alag object banaya,
# toh bahut saare duplicate objects create honge.
#
# Flyweight ka idea:
#
#   SAME / REUSABLE information  -> ek hi object share karo
#   DIFFERENT information         -> bahar se pass karo
#
#
#
#                         ┌──────────────────────────┐
#                         │       Flyweight          │
#                         │──────────────────────────│
#                         │ + render(position)       │
#                         └────────────▲─────────────┘
#                                      │
#                              implements
#                                      │
#                         ┌────────────┴─────────────┐
#                         │       Character          │
#                         │──────────────────────────│
#                         │ - character : char      │
#                         │ - font : string         │
#                         │ - size : int            │
#                         │ - color : string        │
#                         │──────────────────────────│
#                         │ + render(position)       │
#                         └──────────────────────────┘
#                                      ▲
#                                      │
#                                      │ creates / returns
#                                      │
#                         ┌────────────┴─────────────┐
#                         │    FlyweightFactory      │
#                         │──────────────────────────│
#                         │ - pool : map<Key,        │
#                         │          Character>      │
#                         │──────────────────────────│
#                         │ + getCharacter(key)     │
#                         └────────────▲─────────────┘
#                                      │
#                                      │ uses
#                                      │
#                         ┌────────────┴─────────────┐
#                         │       TextEditor        │
#                         │──────────────────────────│
#                         │ - factory                │
#                         │──────────────────────────│
#                         │ + addCharacter(...)     │
#                         │ + render()              │
#                         └──────────────────────────┘
#
#
# ============================================================
#                    SABSE IMPORTANT IDEA
# ============================================================
#
# Character object ke andar:
#
#   character = 'A'
#   font      = "Arial"
#   size      = 14
#   color     = "Black"
#
# Ye information baar-baar same ho sakti hai.
#
# Agar document me 10,000 baar 'A' hai,
# toh hum 10,000 Character objects kyu banaye?
#
# Instead:
#
#             ┌─────────────────────┐
#             │ Character('A',      │
#             │ Arial, 14, Black)  │
#             └──────────┬──────────┘
#                        │
#             ┌──────────┼───────────┐
#             │          │           │
#             ▼          ▼           ▼
#           A at       A at        A at
#          pos 10     pos 50      pos 100
#
# SAME Character object
# DIFFERENT position
#
#
# ============================================================
#                  INTRINSIC vs EXTRINSIC STATE
# ============================================================
#
# Flyweight pattern ko samajhne ke liye ye sabse important hai.
#
#
# 1. INTRINSIC STATE
# ------------------
# Jo information same rahegi aur share ki ja sakti hai.
#
# Example:
#
#   character = 'A'
#   font      = "Arial"
#   size      = 14
#   color     = "Black"
#
# Ye Flyweight object ke andar rahegi.
#
#
# 2. EXTRINSIC STATE
# ------------------
# Jo information har usage ke according change hoti hai.
#
# Example:
#
#   position = 10
#   position = 50
#   position = 100
#
# Ye Flyweight object ke andar store NAHI karenge.
#
# Isko render() ke time bahar se pass karenge.
#
#
#                    ┌──────────────────┐
#                    │   Character      │
#                    │──────────────────│
#                    │ 'A'              │ ← Intrinsic
#                    │ Arial            │ ← Intrinsic
#                    │ 14               │ ← Intrinsic
#                    │ Black            │ ← Intrinsic
#                    └──────────────────┘
#
#                         ▲
#                         │
#                         │ shared
#                         │
#              ┌──────────┴───────────┐
#              │                      │
#              │                      │
#          position=10            position=50
#          position=100           position=200
#
#          ↑                         ↑
#          └──── Extrinsic State ────┘
#
#
# ============================================================
#                    FACTORY KA ROLE
# ============================================================
#
# FlyweightFactory ka main kaam:
#
#     "Agar same object already exist karta hai,
#      toh wahi object return karo."
#
#     "Agar exist nahi karta,
#      toh naya object banao aur pool me store karo."
#
#
# Example:
#
#     getCharacter('A', Arial, 14, Black)
#
#                    │
#                    ▼
#             ┌───────────────┐
#             │ Factory Pool   │
#             ├───────────────┤
#             │ A-Arial-14-B  │───► Character Object
#             │ B-Arial-14-B  │───► Character Object
#             │ C-Arial-14-B  │───► Character Object
#             └───────────────┘
#
#
# Pehli baar 'A':
#
#     Pool me nahi hai
#          ↓
#     New Character create
#          ↓
#     Pool me store
#          ↓
#     Object return
#
#
# Dusri baar same 'A':
#
#     Pool me already hai
#          ↓
#     New object MAT banao
#          ↓
#     Existing object return karo
#
#
# ============================================================
#                       DATA FLOW
# ============================================================
#
#
# TextEditor
#     │
#     │ "Mujhe A chahiye"
#     ▼
# FlyweightFactory
#     │
#     │ Check pool
#     ▼
# ┌────────────────────────────┐
# │       Pool / Cache         │
# │                            │
# │ A + Arial + 14 + Black     │
# │ B + Arial + 14 + Black     │
# └────────────────────────────┘
#     │
#     │ Existing?
#     │
#     ├──── YES ───────────────► Existing Character
#     │
#     └──── NO ────────────────► Create Character
#                                      │
#                                      ▼
#                                  Store in Pool
#
#
# Phir TextEditor:
#
#     Character.render(position)
#
# Yaha:
#
#     Character → intrinsic data
#     position  → extrinsic data
#
#
# ============================================================
#                    SIMPLE C++ CODE
# ============================================================
#
# #include <iostream>
# #include <unordered_map>
# #include <memory>
# using namespace std;
#
#
# // ==========================================================
# // FLYWEIGHT
# // ==========================================================
#
# class Flyweight {
# public:
#     virtual void render(int position) = 0;
#     virtual ~Flyweight() = default;
# };
#
#
# // ==========================================================
# // CONCRETE FLYWEIGHT
# // ==========================================================
#
# class Character : public Flyweight {
# private:
#
#     // These are INTRINSIC states.
#     // Same data can be shared by many usages.
#     char ch;
#     string font;
#     int size;
#     string color;
#
# public:
#
#     Character(char ch,
#               string font,
#               int size,
#               string color)
#         : ch(ch),
#           font(font),
#           size(size),
#           color(color) {}
#
#     void render(int position) override {
#
#         // position is EXTRINSIC state.
#         // It is supplied from outside.
#         cout << "Character: " << ch
#              << ", Font: " << font
#              << ", Size: " << size
#              << ", Color: " << color
#              << ", Position: " << position
#              << endl;
#     }
# };
#
#
# // ==========================================================
# // FLYWEIGHT FACTORY
# // ==========================================================
#
# class FlyweightFactory {
# private:
#
#     // Pool contains already-created Flyweight objects.
#     unordered_map<string, shared_ptr<Character>> pool;
#
# public:
#
#     shared_ptr<Character> getCharacter(
#         char ch,
#         string font,
#         int size,
#         string color) {
#
#         // Create a unique key for intrinsic data.
#         string key =
#             string(1, ch) + "_" +
#             font + "_" +
#             to_string(size) + "_" +
#             color;
#
#         // If object already exists,
#         // return the SAME object.
#         if (pool.count(key)) {
#             return pool[key];
#         }
#
#         // Otherwise create a new Flyweight.
#         auto character =
#             make_shared<Character>(
#                 ch, font, size, color
#             );
#
#         // Store it inside pool.
#         pool[key] = character;
#
#         return character;
#     }
# };
#
#
# // ==========================================================
# // CLIENT
# // ==========================================================
#
# class TextEditor {
# private:
#     FlyweightFactory factory;
#
# public:
#
#     void addCharacter(
#         char ch,
#         string font,
#         int size,
#         string color,
#         int position) {
#
#         // Ask factory for Flyweight.
#         auto character =
#             factory.getCharacter(
#                 ch, font, size, color
#             );
#
#         // Extrinsic state is passed here.
#         character->render(position);
#     }
# };
#
#
# // ==========================================================
# // MAIN
# // ==========================================================
#
# int main() {
#
#     TextEditor editor;
#
#     editor.addCharacter(
#         'A', "Arial", 14, "Black", 10
#     );
#
#     editor.addCharacter(
#         'A', "Arial", 14, "Black", 20
#     );
#
#     editor.addCharacter(
#         'A', "Arial", 14, "Black", 30
#     );
#
#     editor.addCharacter(
#         'B', "Arial", 14, "Black", 40
#     );
#
#     return 0;
# }
#
#
# ============================================================
#                    IS CODE ME KYA HUA?
# ============================================================
#
# First:
#
# editor.addCharacter('A', "Arial", 14, "Black", 10);
#
# Factory ke paas:
#
#     A + Arial + 14 + Black
#
# pehle se nahi hai.
#
# So:
#
#     CREATE Character A
#             ↓
#     STORE in pool
#             ↓
#     return object
#
#
# ------------------------------------------------------------
#
# Second:
#
# editor.addCharacter('A', "Arial", 14, "Black", 20);
#
# Factory ke paas same combination already hai.
#
# So:
#
#     pool me object mil gaya
#             ↓
#     NEW Character nahi banega
#             ↓
#     SAME Character object return hoga
#
# Sirf position change hai.
#
#
# ------------------------------------------------------------
#
# Third:
#
# editor.addCharacter('A', "Arial", 14, "Black", 30);
#
# Again SAME Flyweight.
#
#
# ------------------------------------------------------------
#
# Fourth:
#
# editor.addCharacter('B', "Arial", 14, "Black", 40);
#
# Character 'B' different hai.
#
# So:
#
#     New Character B create hoga.
#
#
# ============================================================
#                    ACTUAL MEMORY IDEA
# ============================================================
#
# WITHOUT FLYWEIGHT:
#
#     A object
#     A object
#     A object
#     A object
#     A object
#     A object
#     ...
#
#     10,000 A's
#     = 10,000 objects
#
#
# WITH FLYWEIGHT:
#
#              ┌────────────────────┐
#              │ Character A        │
#              │ Arial, 14, Black   │
#              └─────────┬──────────┘
#                        │
#          ┌─────────────┼──────────────┐
#          │             │              │
#          ▼             ▼              ▼
#       pos=10         pos=20         pos=30
#
#       1 Character object
#       3 different usages
#
#
# ============================================================
#                 FLYWEIGHT KA CORE FORMULA
# ============================================================
#
#
#             MANY OBJECTS
#                 │
#                 ▼
#       ┌─────────────────────┐
#       │ Identify common     │
#       │ / repeated state    │
#       └──────────┬──────────┘
#                  │
#                  ▼
#       ┌─────────────────────┐
#       │ Put common state     │
#       │ inside Flyweight     │
#       └──────────┬──────────┘
#                  │
#                  ▼
#       ┌─────────────────────┐
#       │ Reuse SAME object    │
#       └──────────┬──────────┘
#                  │
#                  ▼
#       ┌─────────────────────┐
#       │ Pass changing state  │
#       │ from outside         │
#       └─────────────────────┘
#
#
# ============================================================
#                  UML RELATIONSHIPS
# ============================================================
#
# 1. Character ──|> Flyweight
#
#    Character IS-A Flyweight.
#
#    Therefore:
#
#             Character
#                 │
#                 │ implements
#                 ▼
#             Flyweight
#
#
# 2. FlyweightFactory ──has──> Character objects
#
#    Factory ke paas Flyweight objects ka pool hai.
#
#             Factory
#                │
#                │ has
#                ▼
#              Pool
#                │
#                ▼
#            Character
#
#
# 3. TextEditor ──has──> FlyweightFactory
#
#    TextEditor factory ko use karta hai
#    Flyweight objects lene ke liye.
#
#             TextEditor
#                 │
#                 │ has
#                 ▼
#             Factory
#
#
# ============================================================
#                  WHY DO WE NEED FACTORY?
# ============================================================
#
# Ye question interview me bahut important hai.
#
# Hum directly:
#
#     new Character(...)
#
# kyu nahi kar dete?
#
# Because agar client directly objects create karega,
# toh reuse control karna difficult ho jayega.
#
# Factory ek central place ban jata hai jo decide karta hai:
#
#     "Object already hai?"
#          |
#       YES ──► reuse
#          |
#       NO ───► create + store
#
# Isliye Factory Flyweight pattern me
# object sharing ko control karti hai.
#
#
# ============================================================
#                 FLYWEIGHT KAB USE KARNA?
# ============================================================
#
# Jab:
#
# 1. Bahut saare similar objects create ho rahe ho.
#
# 2. Objects me kuch data common ho.
#
# 3. Common data ko safely share kiya ja sakta ho.
#
# 4. Memory consumption problem ban rahi ho.
#
#
# Real-world examples:
#
#     Text Editor
#     Browser
#     Game characters / trees / bullets
#     Map applications
#     Large document rendering
#
#
# ============================================================
#                    ONE-LINE INTERVIEW ANSWER
# ============================================================
#
# "Flyweight Design Pattern ka use large number of similar
# objects ko efficiently manage karne ke liye hota hai.
# Hum common/intrinsic state ko shared Flyweight object me
# rakhte hain aur changing/extrinsic state ko bahar se pass
# karte hain, jisse unnecessary duplicate objects create nahi
# hote aur memory save hoti hai."
#
#
# ============================================================
#                 SABSE IMPORTANT CHEEZ
# ============================================================
#
#               FLYWEIGHT
#                    │
#          ┌─────────┴─────────┐
#          │                   │
#          ▼                   ▼
#     INTRINSIC             EXTRINSIC
#     (shared)              (outside)
#          │                   │
#          ▼                   ▼
#     character              position
#     font                   location
#     size                   user-specific data
#     color                  changing data
#
#
#              CORE IDEA:
#
#        "SHARE WHAT IS SAME,
#         PASS WHAT IS DIFFERENT."
#
# ============================================================