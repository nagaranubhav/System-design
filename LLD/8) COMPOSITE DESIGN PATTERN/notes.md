/*
================================================================================
                        COMPOSITE DESIGN PATTERN (LLD)
================================================================================

📌 DEFINITION:
Composite is a Structural Design Pattern that lets you treat:
    - Individual objects (Leaf)
    - Group of objects (Composite)

👉 uniformly (same interface)

================================================================================
🧠 INTUITION (VERY IMPORTANT)
================================================================================

👉 Problem:
Sometimes we have tree-like structures:

Example:
- File System (Folder + Files)
- Organization (Manager + Employees)
- UI (Button + Panel + Window)

👉 We want:
- Same operations on both individual objects AND groups

❌ Without Composite:
- Separate handling for file & folder
- Code becomes messy (if-else everywhere)

✅ With Composite:
- Treat everything as "FileSystemItem"
- Call same functions → polymorphism handles behavior

================================================================================
🎯 REAL LIFE ANALOGY (INTERVIEW GOLD)
================================================================================

📁 File System:
- File → Leaf node
- Folder → Composite node

👉 Both support:
- ls()
- getSize()
- open()

But:
- File → direct size
- Folder → sum of children

================================================================================
🏗️ CORE COMPONENTS
================================================================================

1. Component (Base Interface)
   - Common interface for both leaf & composite
   - Example: FileSystemItem

2. Leaf
   - Represents individual object
   - No children
   - Example: File

3. Composite
   - Contains children (list of components)
   - Delegates work to children
   - Example: Folder

================================================================================
📊 UML DIAGRAM (VERY IMPORTANT)
================================================================================

        +------------------------+
        |   FileSystemItem       |  <<interface>>
        |------------------------|
        | +ls()                  |
        | +openAll()             |
        | +getSize()             |
        | +cd()                  |
        +------------------------+
                 ▲
        ┌────────┴────────┐
        │                 │
+---------------+   +------------------+
|     File      |   |      Folder      |
|---------------|   |------------------|
| name          |   | name             |
| size          |   | children[]       |
|---------------|   |------------------|
| +getSize()    |   | +add()           |
| +ls()         |   | +getSize()       |
| +openAll()    |   | +openAll()       |
+---------------+   +------------------+

================================================================================
⚙️ FLOW
================================================================================

Client interacts with Component (FileSystemItem)

Case 1:
    item = File → direct behavior

Case 2:
    item = Folder → delegates to children recursively

================================================================================
💡 WHEN TO USE
================================================================================

✔ Tree structures
✔ Hierarchical data
✔ Recursive operations
✔ When uniform treatment is needed

Examples:
- File system
- DOM (HTML tree)
- Organization hierarchy
- Menu systems

================================================================================
⚖️ PROS & CONS
================================================================================

✅ PROS:
- Uniform interface
- Cleaner code (no type checking)
- Easy to extend
- Recursive structure handled naturally

❌ CONS:
- Over-generalization
- Hard to restrict invalid operations
  (e.g., File shouldn't support add())

================================================================================
⚠️ DESIGN DECISION (INTERVIEW TRAP)
================================================================================

👉 Should Leaf implement all methods?

Option 1:
- Yes (like your code)
- Simpler interface

Option 2:
- No → throw exception
- More strict design

================================================================================
🧠 INTERVIEW ANSWER TEMPLATE
================================================================================

"I use Composite Pattern when I have a tree structure and I want to treat
individual objects and compositions uniformly. It helps eliminate conditional
logic and enables recursive operations."

================================================================================
🚀 ADVANCED FOLLOW UPS
================================================================================

- Smart pointers (avoid memory leaks)
- Iterator pattern with composite
- Lazy evaluation
- Caching subtree sizes

================================================================================
*/