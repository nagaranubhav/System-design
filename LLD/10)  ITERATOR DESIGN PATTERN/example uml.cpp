/*
====================================================================
             ITERATOR DESIGN PATTERN — COMPLETE UML
                 University Management System
====================================================================


                         <<interface>>
                         Iterable<T>
                    +----------------------+
                    | + createIterator()   |
                    |   : Iterator<T>      |
                    +----------^-----------+
                               |
                  implements   |
                               |
              +----------------+----------------+
              |                                 |
              |                                 |
   +----------+-----------+          +----------+------------+
   |    CourseCatalog     |          |   StudentDirectory    |
   +----------------------+          +-----------------------+
   | - courses            |          | - students            |
   |   vector<Course>     |          |   map<int, Student>   |
   +----------------------+          +-----------------------+
   | + addCourse()        |          | + addStudent()        |
   | + createIterator()   |          | + createIterator()    |
   +----------+-----------+          +-----------+------------+
              |                                  |
              | creates                          | creates
              |                                  |
              v                                  v
   +----------+-----------+          +------------+-----------+
   |   CourseIterator     |          |    StudentIterator    |
   +----------------------+          +------------------------+
   | - catalog            |          | - directory            |
   | - index              |          | - current               |
   +----------------------+          +------------------------+
   | + hasNext()          |          | + hasNext()             |
   | + next()             |          | + next()                |
   +----------+-----------+          +------------+------------+
              |                                   |
              | implements                        | implements
              |                                   |
              v                                   v
                    <<interface>>
                       Iterator<T>
                +----------------------+
                | + hasNext(): bool    |
                | + next(): T          |
                +----------------------+


====================================================================
                           DATA CLASSES
====================================================================


       +---------------------+        +----------------------+
       |       Course        |        |       Student        |
       +---------------------+        +----------------------+
       | - id                |        | - id                 |
       | - name              |        | - name               |
       +---------------------+        +----------------------+


       CourseCatalog                     StudentDirectory
            |                                  |
            | stores                           | stores
            v                                  v
     +---------------+                 +--------------------+
     | vector<Course>|                 | map<int, Student>  |
     +---------------+                 +--------------------+


====================================================================
                         COMPLETE DATA FLOW
====================================================================


                  ┌─────────────────────────────┐
                  │           CLIENT            │
                  └──────────────┬──────────────┘
                                 │
                                 │ 1. createIterator()
                                 │
                    ┌────────────┴────────────┐
                    │                         │
                    ▼                         ▼
          ┌──────────────────┐      ┌────────────────────┐
          │  CourseCatalog   │      │ StudentDirectory   │
          └────────┬─────────┘      └─────────┬──────────┘
                   │                          │
                   │ 2. creates              │ 2. creates
                   ▼                          ▼
          ┌──────────────────┐      ┌────────────────────┐
          │ CourseIterator   │      │ StudentIterator    │
          └────────┬─────────┘      └─────────┬──────────┘
                   │                          │
                   │ 3. accesses             │ 3. accesses
                   ▼                          ▼
          ┌──────────────────┐      ┌────────────────────┐
          │ vector<Course>   │      │ map<int, Student>  │
          └────────┬─────────┘      └─────────┬──────────┘
                   │                          │
                   │ 4. gets Course           │ 4. gets Student
                   ▼                          ▼
             ┌──────────┐                ┌──────────┐
             │  Course  │                │ Student  │
             └────┬─────┘                └────┬─────┘
                  │                           │
                  │ 5. next()                 │ 5. next()
                  └──────────┐   ┌────────────┘
                             ▼   ▼
                         ┌──────────┐
                         │  CLIENT  │
                         └──────────┘


====================================================================
                  AB DATA EXACTLY KAISE FLOW HOTA HAI?
====================================================================


---------------------------------------------------------------
                    PART 1 — COURSES
---------------------------------------------------------------


Client ke paas:

    CourseCatalog catalog;


Catalog ke andar actual data:

    vector<Course>

    +--------------------------------------+
    |                                      |
    |  Course(1, "Data Structures")        |
    |  Course(2, "Operating Systems")      |
    |  Course(3, "System Design")          |
    |  Course(4, "Database Systems")       |
    |                                      |
    +--------------------------------------+


Client bolta hai:

        catalog.createIterator()
                 |
                 v
        CourseCatalog
                 |
                 | creates
                 v
        CourseIterator
                 |
                 | stores reference to
                 v
        CourseCatalog


Ab CourseIterator ke paas:

        catalog  ────────────────┐
                                  │
        index = 0                 │
                                  │
                                  v
                         CourseCatalog
                              |
                              v
                        vector<Course>


---------------------------------------------------------------
                 COURSE ITERATOR KA FLOW
---------------------------------------------------------------


Initially:

    index = 0

    vector:

    +----+----------------------+
    | 0  | Data Structures      |
    +----+----------------------+
    | 1  | Operating Systems    |
    +----+----------------------+
    | 2  | System Design        |
    +----+----------------------+
    | 3  | Database Systems     |
    +----+----------------------+

         ^
         |
       index


Client:

        iterator->hasNext()

              |
              v

        index < size

        0 < 4

              |
              v

            TRUE


Then:

        iterator->next()

              |
              v

        courses[index]

              |
              v

        Course(1, "Data Structures")

              |
              v

           CLIENT


Aur phir:

        index++

        index = 1


Ab next call:

        next()

              |
              v

        courses[1]

              |
              v

        "Operating Systems"

              |
              v

           CLIENT


Ye process continue hota hai.


====================================================================
                 PART 2 — STUDENTS
====================================================================


StudentDirectory ke andar:

        map<int, Student>


    +--------------------------------+
    | 101 -> Rahul                   |
    | 102 -> Aman                    |
    | 103 -> Priya                   |
    | 104 -> Neha                    |
    +--------------------------------+


Client:

        directory.createIterator()
                    |
                    v
            StudentDirectory
                    |
                    | creates
                    v
            StudentIterator


StudentIterator ke andar:

        directory reference

        current = students.begin()


Yaani current first student:

        101 -> Rahul


====================================================================
                 STUDENT ITERATOR FLOW
====================================================================


Initially:

        current
           |
           v

    +-----------------------------+
    | 101 -> Rahul                |  <--- current
    +-----------------------------+
    | 102 -> Aman                 |
    +-----------------------------+
    | 103 -> Priya                |
    +-----------------------------+
    | 104 -> Neha                 |
    +-----------------------------+


Client:

        studentIterator->hasNext()

                    |
                    v

            current != end

                    |
                    v

                  TRUE


Then:

        studentIterator->next()

                    |
                    v

            current->second

                    |
                    v

                 Rahul

                    |
                    v

                 CLIENT


Then:

        ++current


Ab:

        current
           |
           v

    +-----------------------------+
    | 101 -> Rahul                |
    +-----------------------------+
    | 102 -> Aman                 |  <--- current
    +-----------------------------+
    | 103 -> Priya                |
    +-----------------------------+
    | 104 -> Neha                 |
    +-----------------------------+


Next:

        next()
          |
          v
        Aman


Then:

        ++current


And so on.


====================================================================
                    IMPORTANT RELATIONSHIPS
====================================================================


1. CourseCatalog --> Iterable<Course>

   "CourseCatalog IS-A Iterable"

   Kyunki CourseCatalog:

        createIterator()

   provide karta hai.


---------------------------------------------------------------


2. StudentDirectory --> Iterable<Student>

   "StudentDirectory IS-A Iterable"


---------------------------------------------------------------


3. CourseIterator --> Iterator<Course>

   "CourseIterator IS-A Iterator"


---------------------------------------------------------------


4. StudentIterator --> Iterator<Student>

   "StudentIterator IS-A Iterator"


---------------------------------------------------------------


5. CourseIterator --> CourseCatalog

   "CourseIterator HAS-A CourseCatalog"

   Iterator ko pata hona chahiye ki kis collection ko traverse
   karna hai.


---------------------------------------------------------------


6. StudentIterator --> StudentDirectory

   "StudentIterator HAS-A StudentDirectory"


---------------------------------------------------------------


7. CourseCatalog --> Course

   CourseCatalog ke paas multiple Course objects hain.

        vector<Course>


---------------------------------------------------------------


8. StudentDirectory --> Student

   StudentDirectory ke paas multiple Student objects hain.

        map<int, Student>


====================================================================
                   SABSE IMPORTANT CONCEPT
====================================================================


                    CLIENT
                       |
                       |
             +---------+---------+
             |                   |
             v                   v
       CourseIterator      StudentIterator
             |                   |
             |                   |
             v                   v
        CourseCatalog      StudentDirectory
             |                   |
             v                   v
        vector<Course>      map<int,Student>


Notice:

CourseIterator ko pata hai:

        vector kaise traverse karna hai.


StudentIterator ko pata hai:

        map kaise traverse karna hai.


BUT...


Client ko dono ke andar ki implementation
BILKUL NAHI PATA.


Client ke liye dono:

        Iterator<T>

hain.


Isliye Client:

        hasNext()
        next()

use karta hai.


====================================================================
                     WHY 2 ITERATORS?
====================================================================


Question:

"Ek hi Iterator kyun nahi bana dete?"


Answer:

Kyuki dono collections ka traversal logic different hai.


CourseCatalog:

        vector
           |
           v
        index based traversal


StudentDirectory:

        map
           |
           v
        map iterator based traversal


Isliye:

        CourseIterator
              ↓
        vector-specific traversal


        StudentIterator
              ↓
        map-specific traversal


Lekin dono ek common interface follow karte hain:

        Iterator<T>


====================================================================
                    REAL FLOW IN MAIN()
====================================================================


Step 1:

    CourseCatalog catalog;


                         |
                         v

                 CourseCatalog
                         |
                         v
                  vector<Course>


Step 2:

    catalog.addCourse(...)


                         |
                         v

                  vector<Course>
                         |
                         v
                  Course objects


Step 3:

    Iterator<Course>* it =
        catalog.createIterator();


                         |
                         v

                  CourseIterator
                         |
                         | reference
                         v
                  CourseCatalog


Step 4:

    it->hasNext();


                         |
                         v

                  CourseIterator
                         |
                         | checks
                         v

                  index < size


Step 5:

    it->next();


                         |
                         v

                  CourseIterator
                         |
                         | gets
                         v

                     Course


                         |
                         v

                      CLIENT


====================================================================
                  SECOND COLLECTION SAME IDEA
====================================================================


    StudentDirectory directory;

                 |
                 v

        map<int, Student>

                 |
                 |
        createIterator()
                 |
                 v

        StudentIterator

                 |
                 | traverses
                 v

        map<int, Student>

                 |
                 | next()
                 v

              Student

                 |
                 v

              CLIENT


====================================================================
                         FINAL PICTURE
====================================================================


                         CLIENT
                           |
                 +---------+---------+
                 |                   |
                 | uses              | uses
                 v                   v
          Iterator<Course>     Iterator<Student>
                 |                   |
                 | implemented by     | implemented by
                 v                   v
        CourseIterator        StudentIterator
                 |                   |
                 | has-a             | has-a
                 v                   v
         CourseCatalog        StudentDirectory
                 |                   |
                 | stores            | stores
                 v                   v
        vector<Course>        map<int,Student>
                 |                   |
                 v                   v
              Course              Student


                         DATA FLOW

    Course data:

    Course
       ↓
    vector<Course>
       ↓
    CourseCatalog
       ↓
    CourseIterator
       ↓
    next()
       ↓
    Client


    Student data:

    Student
       ↓
    map<int,Student>
       ↓
    StudentDirectory
       ↓
    StudentIterator
       ↓
    next()
       ↓
    Client


====================================================================
                     CORE IDEA TO REMEMBER
====================================================================


        COLLECTION
            |
            | "Mujhe traverse karna hai"
            v
         ITERATOR
            |
            | "Main ek-ek element dunga"
            v
         ELEMENT
            |
            v
          CLIENT


Collection:

    Data ko store karta hai.


Iterator:

    Data ko one-by-one bahar deta hai.


Client:

    Data ko consume karta hai.


Aur sabse important:

    CLIENT KO COLLECTION KA INTERNAL DATA STRUCTURE
    PATA NAHI HOTA.


Isi wajah se Iterator Pattern:

    "Traversal logic ko collection se separate karta hai
     aur collection ki internal representation ko hide karta hai."


====================================================================