#include <iostream>
#include <memory>
using namespace std;

/*
    Chain of Responsibility Example

    Problem:
    Employee leave request karta hai.

    Different authorities ki approval limit hai:

        Manager  -> up to 3 days
        Director -> up to 7 days
        VP       -> up to 15 days

    Agar current handler request handle nahi kar sakta,
    toh request next handler ko forward karega.
*/


// ============================================================
// Request
// ============================================================

class LeaveRequest {
public:
    string employeeName;
    int days;

    LeaveRequest(string name, int days)
        : employeeName(name), days(days) {}
};


// ============================================================
// Handler Interface
// ============================================================

class LeaveHandler {
protected:
    shared_ptr<LeaveHandler> next;

public:

    // Chain create karne ke liye
    void setNext(shared_ptr<LeaveHandler> nextHandler) {
        next = nextHandler;
    }

    // Every handler must implement this
    virtual void handleRequest(const LeaveRequest& request) = 0;

    virtual ~LeaveHandler() = default;
};


// ============================================================
// Concrete Handler 1 : Manager
// ============================================================

class Manager : public LeaveHandler {

public:

    void handleRequest(const LeaveRequest& request) override {

        // Manager maximum 3 days approve kar sakta hai
        if (request.days <= 3) {

            cout << "Manager approved "
                 << request.employeeName
                 << "'s leave of "
                 << request.days
                 << " days.\n";

        }
        else {

            cout << "Manager cannot approve "
                 << request.days
                 << " days.\n";

            // Request next handler ko forward
            if (next) {
                next->handleRequest(request);
            }
        }
    }
};


// ============================================================
// Concrete Handler 2 : Director
// ============================================================

class Director : public LeaveHandler {

public:

    void handleRequest(const LeaveRequest& request) override {

        // Director maximum 7 days approve kar sakta hai
        if (request.days <= 7) {

            cout << "Director approved "
                 << request.employeeName
                 << "'s leave of "
                 << request.days
                 << " days.\n";

        }
        else {

            cout << "Director cannot approve "
                 << request.days
                 << " days.\n";

            // Request next handler ko forward
            if (next) {
                next->handleRequest(request);
            }
        }
    }
};


// ============================================================
// Concrete Handler 3 : VP
// ============================================================

class VP : public LeaveHandler {

public:

    void handleRequest(const LeaveRequest& request) override {

        // VP maximum 15 days approve kar sakta hai
        if (request.days <= 15) {

            cout << "VP approved "
                 << request.employeeName
                 << "'s leave of "
                 << request.days
                 << " days.\n";

        }
        else {

            cout << "VP cannot approve "
                 << request.days
                 << " days.\n";

            // Chain khatam
            cout << "Leave request rejected.\n";
        }
    }
};


// ============================================================
// Client
// ============================================================

int main() {

    // Create handlers
    auto manager = make_shared<Manager>();
    auto director = make_shared<Director>();
    auto vp = make_shared<VP>();


    // ========================================================
    // Build Chain
    // ========================================================

    /*
            Manager
               |
               v
            Director
               |
               v
               VP
    */

    manager->setNext(director);
    director->setNext(vp);


    // ========================================================
    // Client only knows first handler
    // ========================================================

    LeaveRequest request1("Anubhav", 2);

    manager->handleRequest(request1);


    LeaveRequest request2("Rahul", 5);

    manager->handleRequest(request2);


    LeaveRequest request3("Aman", 10);

    manager->handleRequest(request3);


    LeaveRequest request4("Rohit", 20);

    manager->handleRequest(request4);


    return 0;
}


/*
============================================================
DRY RUN
============================================================

Request 1:
    Anubhav -> 2 days

    Manager
       |
       | 2 <= 3
       ↓
    APPROVED

    Chain stops.


------------------------------------------------------------

Request 2:
    Rahul -> 5 days

    Manager
       |
       | 5 > 3
       ↓
    Director
       |
       | 5 <= 7
       ↓
    APPROVED

    Chain stops.


------------------------------------------------------------

Request 3:
    Aman -> 10 days

    Manager
       |
       | 10 > 3
       ↓
    Director
       |
       | 10 > 7
       ↓
    VP
       |
       | 10 <= 15
       ↓
    APPROVED


------------------------------------------------------------

Request 4:
    Rohit -> 20 days

    Manager
       |
       | cannot handle
       ↓
    Director
       |
       | cannot handle
       ↓
    VP
       |
       | cannot handle
       ↓
    REJECTED


============================================================
IMPORTANT INTERVIEW POINT
============================================================

Client:

    manager->handleRequest(request);

Client ko ye nahi pata:

    Manager -> Director -> VP

Ye chain internally configured hai.

Agar kal hum HR ko chain mein add karna chahte hain:

    Manager
       ↓
    Director
       ↓
    HR
       ↓
    VP

Toh client ka code same reh sakta hai.

Isi ko loose coupling aur extensibility ka benefit bolte hain.


============================================================
CORE PATTERN IN CODE
============================================================

class Handler {

    Handler* next;

    void handle(Request request) {

        if (canHandle(request)) {

            // Handle request

        }
        else if (next) {

            next->handle(request);

        }
    }
};


Remember:

    if I can handle -> HANDLE

    else            -> NEXT


============================================================