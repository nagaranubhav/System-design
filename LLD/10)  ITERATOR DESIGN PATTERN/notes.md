========================================
        ITERATOR DESIGN PATTERN
========================================

CATEGORY:
Behavioral Design Pattern

INTENT:
Provides a way to access elements of a collection sequentially
WITHOUT exposing its internal representation.

Simple line:
"Traversal logic ko collection se alag kar dena."

--------------------------------------------------
1) REAL WORLD INTUITION
--------------------------------------------------

Soch Netflix playlist, LinkedList, Tree, Browser history,
file system folders — sabke traversal ka tarika alag hota hai.

Client ko ye nahi pata hona chahiye ki:
- data vector me hai
- linked list me hai
- tree me hai
- graph me hai
- database cursor me hai

Client ko sirf ye chahiye:
- next item do
- batao aur items bache hain ya nahi

Exactly ye kaam Iterator karta hai.

Real life analogy:
TV remote.

Tumhe TV ke internal circuit ka traversal nahi pata.
Bas:
- next channel
- previous channel
- current channel

Same iterator.

--------------------------------------------------
2) PROBLEM IT SOLVES
--------------------------------------------------

Without iterator:
Client ko har DS ka traversal alag likhna padega.

Example:
- linked list -> while(node)
- tree -> recursion/stack
- vector -> index based
- graph -> bfs/dfs

Problems:
1. Traversal logic duplicate hota
2. Client tightly coupled ho jata
3. Internal structure expose hota
4. New traversal add karna mushkil
5. Common traversal interface nahi hota

Iterator solves all.

--------------------------------------------------
3) CORE IDEA
--------------------------------------------------

Collection:
"mere elements store hain"

Iterator:
"un elements ko kaise traverse karna hai"

Ye SRP (Single Responsibility Principle) follow karta hai.

Collection stores data.
Iterator traverses data.

--------------------------------------------------
4) WHY WE NEED IT
--------------------------------------------------

Interview golden answer:

We use Iterator when:
- collection traversal hide karna ho
- same traversal API deni ho
- multiple collection types ko same client code se process karna ho
- multiple traversal strategies support karni ho
- encapsulation preserve karna ho

Main reasons:
1. Uniform traversal
2. Encapsulation
3. Extensible traversal logic
4. Cleaner client code
5. Supports polymorphism

--------------------------------------------------
5) UML CLASS DIAGRAM
--------------------------------------------------

                    +------------------+
                    |    Iterator<T>   |
                    +------------------+
                    | +hasNext()       |
                    | +next()          |
                    +------------------+
                             ^
                             |
         --------------------------------------------
         |                    |                     |
         |                    |                     |
+----------------+  +----------------------+  +------------------+
|LinkedListItr   |  |BinaryTreeInorderItr  |  |PlaylistIterator |
+----------------+  +----------------------+  +------------------+

                    +------------------+
                    |   Iterable<T>    |
                    +------------------+
                    | +getIterator()   |
                    +------------------+
                             ^
                             |
        ---------------------------------------------
        |                    |                      |
        |                    |                      |
+----------------+   +----------------+   +----------------+
| LinkedList     |   | BinaryTree     |   | Playlist      |
+----------------+   +----------------+   +----------------+

FLOW:
Client -> asks collection for iterator
Collection -> returns suitable iterator
Iterator -> handles traversal state

--------------------------------------------------
6) PARTICIPANTS
--------------------------------------------------

1. Iterator
Defines traversal contract.
Example:
- hasNext()
- next()

2. Concrete Iterator
Actual traversal implementation.
Examples:
- LinkedListIterator
- TreeIterator
- PlaylistIterator

3. Iterable / Aggregate
Creates iterator object.

4. Concrete Collection
Actual data structure.

--------------------------------------------------
7) WHEN TO USE
--------------------------------------------------

Use when:
- collection structure complex ho
- traversal logic multiple ho
- internal structure hide karna ho
- for-each like functionality chahiye
- lazy traversal chahiye
- database cursor traversal
- file system traversal
- nested object traversal

Excellent use cases:
- Binary Tree traversal
- Graph BFS iterator
- Menu traversal
- Playlist songs
- Social media feed pagination
- Chat history scrolling
- DB result set

--------------------------------------------------
8) WHEN NOT TO USE
--------------------------------------------------

Avoid when:
- traversal trivial hai
- sirf ek hi fixed DS hai
- no abstraction needed
- overengineering ho raha hai

--------------------------------------------------
9) ADVANTAGES
--------------------------------------------------

1. Uniform traversal API
2. Hides internal DS
3. Supports multiple traversal styles
4. Open/Closed principle
5. Cleaner client code
6. Reusable traversal logic
7. Parallel iterators possible

--------------------------------------------------
10) DISADVANTAGES
--------------------------------------------------

1. More classes
2. Slight memory overhead
3. Extra abstraction
4. Iterator invalidation issues possible

--------------------------------------------------
11) REAL LIFE EXAMPLES
--------------------------------------------------

1. Java
- Iterator
- ListIterator
- Iterable
- enhanced for loop

2. C++
- begin()
- end()
- STL iterators

3. Python
- __iter__()
- __next__()

4. DB cursor
Rows one by one

5. Spotify playlist
Next song

6. File explorer
Next file/folder

--------------------------------------------------
12) MULTIPLE ITERATION STRATEGIES
--------------------------------------------------

Amazing interview point:

Same Binary Tree can have:
- inorder iterator
- preorder iterator
- postorder iterator
- level order iterator

This is huge advantage.

--------------------------------------------------
13) INTERVIEW ANSWER TEMPLATE
--------------------------------------------------

"Iterator pattern is a behavioral pattern used to traverse
different collections using a common interface without
exposing internal implementation.

It separates traversal logic from the collection itself,
improving encapsulation and making client code independent
of collection structure."

--------------------------------------------------
14) FAANG FOLLOW-UP QUESTIONS
--------------------------------------------------

Q1. How to support reverse iterator?
Q2. How to make thread-safe iterator?
Q3. How Java fail-fast iterator works?
Q4. How STL random access iterator works?
Q5. Difference from Visitor?
Q6. External vs internal iterator?
Q7. Lazy iterator?
Q8. Generator vs iterator?

--------------------------------------------------
15) BIGGEST INTERVIEW GOLD POINT
--------------------------------------------------

FOR-EACH LOOP INTERNALLY ITERATOR HI HOTA HAI.

Java:
for(int x : list)

Behind scenes:
Iterator it = list.iterator();

This line interviewer ko impress karegi.
========================================