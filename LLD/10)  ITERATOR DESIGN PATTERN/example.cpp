/*
====================================================================
              ITERATOR DESIGN PATTERN - COMPLEX EXAMPLE
====================================================================

Example:
--------

Hum maan lo hum ek UNIVERSITY MANAGEMENT SYSTEM bana rahe hain.

University ke paas 2 alag collections hain:

1. CourseCatalog
   -> University ke saare courses store karta hai.

2. StudentDirectory
   -> University ke saare students store karta hai.


Dono collections ka internal data structure DIFFERENT hai:

CourseCatalog:
    vector<Course>

StudentDirectory:
    map<int, Student>


Aur hum chahte hain ki Client ko ye pata hi na chale ki
andar vector use ho raha hai ya map.

Isliye hum 2 alag Iterators banayenge:

1. CourseIterator
   -> Courses ko traverse karega.

2. StudentIterator
   -> Students ko traverse karega.


Aur 2 Iterables / Collections:

1. CourseCatalog
2. StudentDirectory


====================================================================
                         HIGH LEVEL IDEA
====================================================================


                    +-------------------+
                    |      Client       |
                    +---------+---------+
                              |
                    uses      |      uses
                    ----------+-----------
                    |                     |
                    v                     v

          +------------------+    +----------------------+
          | CourseIterator   |    |   StudentIterator    |
          +--------+---------+    +----------+-----------+
                   |                         |
                   | traverses               | traverses
                   v                         v
          +------------------+    +----------------------+
          |  CourseCatalog   |    |  StudentDirectory    |
          +------------------+    +----------------------+
                   |                         |
                   v                         v
             vector<Course>              map<int, Student>


IMPORTANT:

Client ko ye nahi pata:

    CourseCatalog -> vector use karta hai
    StudentDirectory -> map use karta hai

Client sirf ye jaanta hai:

    Iterator ke paas:

        hasNext()
        next()


====================================================================
                        COMPLETE CODE
====================================================================
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;


/*
====================================================================
                         DATA CLASSES
====================================================================

Ye actual data hai.

Course = ek course ki information
Student = ek student ki information
*/


class Course {

private:
    int id;
    string name;

public:

    Course(int id, string name)
        : id(id), name(name) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }
};


class Student {

private:
    int id;
    string name;

public:

    Student(int id, string name)
        : id(id), name(name) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }
};


/*
====================================================================
                         ITERATOR INTERFACE
====================================================================

Iterator ka main purpose:

    "Collection ke andar elements ko one-by-one traverse karna."

Hum ek common interface bana rahe hain.

Har iterator ko ye 2 kaam karne hi padenge:

    hasNext()
    next()


Ye interface hone ki wajah se Client ko nahi pata ki actual
iteration kaise ho rahi hai.
*/


template <typename T>
class Iterator {

public:

    // Kya next element available hai?
    virtual bool hasNext() = 0;

    // Next element return karo
    virtual T next() = 0;

    virtual ~Iterator() = default;
};


/*
====================================================================
                      ITERABLE INTERFACE
====================================================================

Iterable ka matlab:

    "Main collection apne liye Iterator provide kar sakta hoon."


Har collection jo Iterable hai usko:

    createIterator()

implement karna padega.
*/


template <typename T>
class Iterable {

public:

    virtual Iterator<T>* createIterator() = 0;

    virtual ~Iterable() = default;
};


/*
====================================================================
                       ITERABLE #1
                    COURSE CATALOG
====================================================================

CourseCatalog ke andar courses vector mein stored hain.

Client ko ye vector directly expose nahi karna hai.

Instead:

    CourseCatalog
           |
           | createIterator()
           v
    CourseIterator


Ye hamara FIRST ITERABLE hai.
*/


class CourseCatalog : public Iterable<Course> {

private:

    vector<Course> courses;

public:

    void addCourse(const Course& course) {

        courses.push_back(course);
    }


    /*
    ---------------------------------------------------------------
    IMPORTANT

    CourseCatalog khud traversal ka kaam nahi karega.

    Ye sirf CourseIterator banakar dega.

    Yaani:

        CourseCatalog
              |
              | creates
              v
        CourseIterator
    ---------------------------------------------------------------
    */

    Iterator<Course>* createIterator() override;


    /*
    CourseIterator ko private data access dene ke liye friend
    banaya hai.

    Isse CourseIterator courses vector ko access kar sakta hai.
    */

    friend class CourseIterator;
};


/*
====================================================================
                       ITERATOR #1
                    COURSE ITERATOR
====================================================================

Ye CourseCatalog ke courses ko traverse karega.

Iske paas 2 cheezein hain:

1. CourseCatalog ka reference
2. Current index

Example:

courses:

    [C++]
    [Java]
    [System Design]

initially:

    index = 0

next():

    courses[0]

then:

    index = 1

next():

    courses[1]

and so on.
*/


class CourseIterator : public Iterator<Course> {

private:

    CourseCatalog& catalog;

    // Batata hai ki abhi hum kis course par hain.
    int index;

public:

    CourseIterator(CourseCatalog& catalog)
        : catalog(catalog), index(0) {}


    /*
    ---------------------------------------------------------------
    hasNext()

    Check:

        kya current index ke baad koi course available hai?
    ---------------------------------------------------------------
    */

    bool hasNext() override {

        return index < catalog.courses.size();
    }


    /*
    ---------------------------------------------------------------
    next()

    Current course return karo.

    Aur uske baad index ko aage badha do.

    Ye bahut important hai:

        return catalog.courses[index++];

    Matlab:

        pehle current element do
        phir index++

    ---------------------------------------------------------------
    */

    Course next() override {

        return catalog.courses[index++];
    }
};


/*
CourseCatalog ka createIterator() implementation.

Jab Client bolega:

    catalog.createIterator()

toh ye CourseIterator return karega.
*/


Iterator<Course>* CourseCatalog::createIterator() {

    return new CourseIterator(*this);
}


/*
====================================================================
                       ITERABLE #2
                  STUDENT DIRECTORY
====================================================================

Ab hamara second collection.

StudentDirectory students ko map mein store karta hai:

    map<int, Student>

Example:

    101 -> Rahul
    102 -> Aman
    103 -> Priya


Notice:

CourseCatalog ke andar vector tha.

StudentDirectory ke andar map hai.

Dono ka internal structure different hai.

Lekin Client ko dono ko traverse karne ka same style milega:

    hasNext()
    next()


Ye hi Iterator Pattern ki power hai.


Ye hamara SECOND ITERABLE hai.
*/


class StudentDirectory : public Iterable<Student> {

private:

    map<int, Student> students;

public:

    void addStudent(const Student& student) {

        students[student.getId()] = student;
    }


    /*
    StudentDirectory khud iteration nahi karega.

    Ye StudentIterator create karega.
    */

    Iterator<Student>* createIterator() override;


    /*
    StudentIterator ko private map access karna hai.
    */

    friend class StudentIterator;
};


/*
====================================================================
                       ITERATOR #2
                    STUDENT ITERATOR
====================================================================

Yahan thoda interesting part hai.

CourseIterator mein humne:

    vector + index

use kiya tha.

Lekin StudentDirectory mein:

    map

use ho raha hai.

Map ko traverse karne ke liye hum:

    map<int, Student>::iterator

use karenge.

Yaani:

CourseIterator ka internal implementation:

    int index


StudentIterator ka internal implementation:

    map<int, Student>::iterator current


Client ko iska koi idea nahi hoga.

Client ko sirf:

    hasNext()
    next()

dikhega.
*/


class StudentIterator : public Iterator<Student> {

private:

    StudentDirectory& directory;

    /*
    Map ka iterator.

    Ye map ke current element ko point karega.
    */

    map<int, Student>::iterator current;

    /*
    End iterator.

    Jab:

        current == end

    tab koi student remaining nahi hai.
    */

    map<int, Student>::iterator end;

public:

    StudentIterator(StudentDirectory& directory)
        : directory(directory) {

        current = directory.students.begin();

        end = directory.students.end();
    }


    /*
    ---------------------------------------------------------------
    hasNext()

    Agar current end tak nahi pahucha:

        TRUE

    Otherwise:

        FALSE
    ---------------------------------------------------------------
    */

    bool hasNext() override {

        return current != end;
    }


    /*
    ---------------------------------------------------------------
    next()

    Current student return karo.

    Phir map iterator ko aage move karo.
    ---------------------------------------------------------------
    */

    Student next() override {

        Student student = current->second;

        ++current;

        return student;
    }
};


/*
StudentDirectory ka createIterator().

Client:

    directory.createIterator()

karega.

Aur internally:

    StudentIterator

create hoga.
*/


Iterator<Student>* StudentDirectory::createIterator() {

    return new StudentIterator(*this);
}


/*
====================================================================
                            CLIENT
====================================================================

Ab sabse important part.

Client ko:

    CourseCatalog ke andar vector hai

ya

    StudentDirectory ke andar map hai

iska kuch bhi idea nahi hai.


Client sirf Iterator interface ke through kaam karega.
*/


int main() {


    /*
    ================================================================
                       CREATE COURSE CATALOG
    ================================================================
    */

    CourseCatalog catalog;

    catalog.addCourse(Course(1, "Data Structures"));
    catalog.addCourse(Course(2, "Operating Systems"));
    catalog.addCourse(Course(3, "System Design"));
    catalog.addCourse(Course(4, "Database Systems"));


    /*
    ================================================================
                    CREATE STUDENT DIRECTORY
    ================================================================

    Ye internally map use karega.
    ================================================================
    */

    StudentDirectory directory;

    directory.addStudent(Student(101, "Rahul"));
    directory.addStudent(Student(102, "Aman"));
    directory.addStudent(Student(103, "Priya"));
    directory.addStudent(Student(104, "Neha"));


    /*
    ================================================================
                      CREATE ITERATOR #1
    ================================================================
    */

    Iterator<Course>* courseIterator =
        catalog.createIterator();


    cout << "===== COURSES =====\n";


    /*
    Client ko sirf ye pata hai:

        hasNext()
        next()

    Client ko ye nahi pata:

        vector use hua hai
        index use ho raha hai
    */

    while (courseIterator->hasNext()) {

        Course course = courseIterator->next();

        cout << course.getId()
             << " -> "
             << course.getName()
             << endl;
    }


    /*
    ================================================================
                      CREATE ITERATOR #2
    ================================================================
    */

    Iterator<Student>* studentIterator =
        directory.createIterator();


    cout << "\n===== STUDENTS =====\n";


    /*
    Again:

        same interface

            hasNext()
            next()

    Lekin andar StudentIterator map ko traverse kar raha hai.
    */

    while (studentIterator->hasNext()) {

        Student student = studentIterator->next();

        cout << student.getId()
             << " -> "
             << student.getName()
             << endl;
    }


    /*
    ================================================================
                           CLEANUP
    ================================================================
    */

    delete courseIterator;
    delete studentIterator;


    return 0;
}


/*
====================================================================
                         EXPECTED OUTPUT
====================================================================

===== COURSES =====
1 -> Data Structures
2 -> Operating Systems
3 -> System Design
4 -> Database Systems

===== STUDENTS =====
101 -> Rahul
102 -> Aman
103 -> Priya
104 -> Neha


====================================================================
                    AB POORA FLOW SAMAJHO
====================================================================


                         CLIENT
                           |
              +------------+------------+
              |                         |
              | createIterator()        | createIterator()
              v                         v
       CourseCatalog             StudentDirectory
              |                         |
              | creates                 | creates
              v                         v
       CourseIterator             StudentIterator
              |                         |
              | traverses               | traverses
              v                         v
       vector<Course>              map<int,Student>


====================================================================
                  COURSE WALA FLOW - DRY RUN
====================================================================


CourseCatalog ke andar:

    courses =

    index
      |
      v
    +----------------------------+
    | 0 | Data Structures        |
    | 1 | Operating Systems      |
    | 2 | System Design          |
    | 3 | Database Systems       |
    +----------------------------+


Step 1:

    CourseIterator banaya.

    index = 0


Step 2:

    hasNext()

    0 < 4

    TRUE


Step 3:

    next()

    courses[0]

    Data Structures

    index++

    index = 1


Step 4:

    hasNext()

    1 < 4

    TRUE


Step 5:

    next()

    courses[1]

    Operating Systems

    index = 2


Aise hi:

    System Design
    Database Systems


Last mein:

    index = 4


hasNext():

    4 < 4

    FALSE


Traversal khatam.


====================================================================
                  STUDENT WALA FLOW - DRY RUN
====================================================================


StudentDirectory ke andar:

    map<int, Student>

    +----------------+
    | 101 -> Rahul   |
    | 102 -> Aman    |
    | 103 -> Priya   |
    | 104 -> Neha    |
    +----------------+


StudentIterator banaya:

    current = begin()
    end     = end()


Step 1:

    hasNext()

    current != end

    TRUE


Step 2:

    next()

    current->second

    Rahul


    ++current


Ab current:

    102 -> Aman


Step 3:

    next()

    Aman

    ++current


Aise hi:

    Priya
    Neha


Finally:

    current == end


hasNext():

    FALSE


Traversal khatam.


====================================================================
              SABSE IMPORTANT OBSERVATION
====================================================================


Dono Iterators internally COMPLETELY DIFFERENT hain.


CourseIterator:

    vector
       +
    index


StudentIterator:

    map
       +
    map iterator


Lekin Client ke liye:

    CourseIterator
          |
          | hasNext()
          | next()
          v


    StudentIterator
          |
          | hasNext()
          | next()
          v


DONO SAME LAGTE HAIN.


Client ko internal implementation se koi lena-dena nahi hai.


====================================================================
                  2 ITERABLES + 2 ITERATORS
====================================================================


ITERABLE #1
-----------

CourseCatalog

        |
        | creates
        v

ITERATOR #1
-----------

CourseIterator

        |
        | traverses
        v

vector<Course>


---------------------------------------------------------------


ITERABLE #2
-----------

StudentDirectory

        |
        | creates
        v

ITERATOR #2
-----------

StudentIterator

        |
        | traverses
        v

map<int, Student>


====================================================================
                    UML FROM THIS CODE
====================================================================


                    <<interface>>
                    Iterable<T>
              +------------------------+
              | + createIterator()     |
              +-----------^------------+
                          |
             +------------+-------------+
             |                          |
             | implements               | implements
             |                          |
    +--------+---------+      +---------+-----------+
    |  CourseCatalog   |      | StudentDirectory    |
    +------------------+      +---------------------+
    | - courses        |      | - students          |
    |   vector<Course> |      |   map<int, Student> |
    +--------+---------+      +---------+-----------+
             |                          |
             | creates                  | creates
             v                          v
    +--------+---------+      +---------+-----------+
    | CourseIterator   |      | StudentIterator     |
    +------------------+      +---------------------+
    | - catalog        |      | - directory         |
    | - index          |      | - current           |
    +--------+---------+      +---------+-----------+
             |                          |
             | implements               | implements
             v                          v
          <<interface>>              <<interface>>
            Iterator<T>                Iterator<T>
          +-----------+              +-----------+
          | hasNext() |              | hasNext() |
          | next()    |              | next()    |
          +-----------+              +-----------+


====================================================================
                     WHY THIS IS USEFUL?
====================================================================


Imagine kal hum CourseCatalog ko change kar dein:

    vector<Course>

             ↓

    list<Course>


Client code mein:

    while(iterator->hasNext()) {
        auto course = iterator->next();
    }

Koi change nahi.


Similarly StudentDirectory:

    map<int, Student>

             ↓

    unordered_map<int, Student>


Client ko koi change nahi.


Kyun?

Because traversal ka logic collection se nikal kar
Iterator ke andar chala gaya hai.


====================================================================
                  WITHOUT ITERATOR PROBLEM
====================================================================


Agar Iterator Pattern use nahi karte:

    Client
      |
      +----> CourseCatalog.courses
      |
      +----> StudentDirectory.students


Client ko pata hota:

    vector kaise traverse karna hai
    map kaise traverse karna hai
    index kaise maintain karna hai
    iterator kaise use karna hai


Agar internal structure change hua:

    Client ka code bhi change.


====================================================================
                    WITH ITERATOR
====================================================================


                     Client
                        |
                        |
                common interface
                        |
              +---------+---------+
              |                   |
              v                   v
       CourseIterator       StudentIterator
              |                   |
              v                   v
          vector              map


Client ko sirf:

        hasNext()
        next()

pata hai.


Internal complexity Iterator sambhalta hai.


====================================================================
                       INTERVIEW ANSWER
====================================================================


Agar interviewer pooche:

"Why do we use Iterator Design Pattern?"


Tum bol sakte ho:


"Iterator Pattern allows us to traverse a collection without
exposing its internal representation.

For example, in our system CourseCatalog uses a vector while
StudentDirectory uses a map. Their traversal logic is different,
so we encapsulate that logic inside CourseIterator and
StudentIterator.

The client only depends on the common Iterator interface,
which provides hasNext() and next(). Therefore the client
remains independent of the underlying data structure."


====================================================================
                    ONE-LINE MEMORY TRICK
====================================================================


Collection ka kaam:

        DATA RAKHNA


Iterator ka kaam:

        DATA KO ONE-BY-ONE GHUMANA


Client ka kaam:

        DATA USE KARNA


Aur sabse important:

        "Collection ka internal structure hide karo,
         traversal ko Iterator mein daal do."


====================================================================