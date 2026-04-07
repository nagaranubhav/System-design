#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
=========================================================
MEDIATOR PATTERN - CHAT ROOM SYSTEM
=========================================================

GOAL:
Users directly ek dusre ko message nahi bhejenge.

Instead:
User -> Mediator -> Receiver

This removes direct coupling between users.
*/


// Forward declaration
class Colleague;


// =====================================================
// 1) MEDIATOR INTERFACE
// =====================================================

/*
Communication contract.

Any mediator must support:
1) register user
2) broadcast
3) private messaging
*/
class IMediator {
public:
    virtual ~IMediator() {}

    virtual void registerColleague(Colleague* c) = 0;
    virtual void send(const string& from, const string& msg) = 0;
    virtual void sendPrivate(const string& from,
                             const string& to,
                             const string& msg) = 0;
};


// =====================================================
// 2) COLLEAGUE BASE CLASS
// =====================================================

/*
Every participant keeps mediator reference.

IMPORTANT:
User dusre users ko directly nahi jaanta.
Only mediator ko jaanta hai.
*/
class Colleague {
protected:
    IMediator* mediator;

public:
    Colleague(IMediator* m) {
        mediator = m;

        /*
        Auto registration on creation
        */
        mediator->registerColleague(this);
    }

    virtual string getName() = 0;
    virtual void send(const string& msg) = 0;
    virtual void sendPrivate(const string& to,
                             const string& msg) = 0;
    virtual void receive(const string& from,
                         const string& msg) = 0;
};


// =====================================================
// 3) CONCRETE MEDIATOR
// =====================================================

/*
This is CENTRAL CHAT SERVER.

Responsibilities:
1) user registry
2) broadcast routing
3) private routing
4) mute rules
*/
class ChatMediator : public IMediator {
private:
    vector<Colleague*> colleagues;

    /*
    mute rule:
    (muter, muted)
    */
    vector<pair<string,string>> mutes;

public:
    void registerColleague(Colleague* c) override {
        colleagues.push_back(c);
    }

    /*
    Moderation feature
    */
    void mute(const string& who, const string& whom) {
        mutes.push_back({who, whom});
    }

    /*
    Broadcast message flow:
    sender -> all others
    */
    void send(const string& from, const string& msg) override {

        cout << "[" << from << " broadcasts]: " << msg << "\n";

        for (Colleague* c : colleagues) {

            /*
            sender ko khud mat bhejo
            */
            if (c->getName() == from) continue;

            bool isMuted = false;

            /*
            Check mute rules
            */
            for (auto& p : mutes) {
                if (from == p.second &&
                    c->getName() == p.first) {
                    isMuted = true;
                    break;
                }
            }

            if (!isMuted) {
                c->receive(from, msg);
            }
        }
    }

    /*
    Private routing:
    sender -> specific receiver
    */
    void sendPrivate(const string& from,
                     const string& to,
                     const string& msg) override {

        cout << "[" << from << "→" << to << "]: "
             << msg << "\n";

        for (Colleague* c : colleagues) {

            /*
            target user found
            */
            if (c->getName() == to) {

                /*
                Check mute
                */
                for (auto& p : mutes) {
                    if (from == p.second &&
                        to == p.first) {
                        cout << "[Message muted]\n";
                        return;
                    }
                }

                c->receive(from, msg);
                return;
            }
        }

        /*
        User not found case
        */
        cout << "[Mediator] User not found\n";
    }
};


// =====================================================
// 4) CONCRETE COLLEAGUE
// =====================================================

/*
Actual chat participant
*/
class User : public Colleague {
private:
    string name;

public:
    User(const string& n, IMediator* m)
        : Colleague(m) {
        name = n;
    }

    string getName() override {
        return name;
    }

    /*
    User directly kisi aur user ko nahi bhejta.
    Mediator handles routing.
    */
    void send(const string& msg) override {
        mediator->send(name, msg);
    }

    void sendPrivate(const string& to,
                     const string& msg) override {
        mediator->sendPrivate(name, to, msg);
    }

    /*
    Receiver endpoint
    */
    void receive(const string& from,
                 const string& msg) override {
        cout << "   " << name
             << " got from "
             << from << ": "
             << msg << "\n";
    }
};


// =====================================================
// 5) WORKING FLOW
// =====================================================
int main() {

    ChatMediator* chatRoom = new ChatMediator();

    /*
    Auto registration happens here
    */
    User* user1 = new User("Rohan", chatRoom);
    User* user2 = new User("Neha", chatRoom);
    User* user3 = new User("Mohan", chatRoom);

    /*
    Rohan muted Mohan
    */
    chatRoom->mute("Rohan", "Mohan");

    /*
    FLOW 1:
    Rohan -> Mediator -> everyone except self
    */
    user1->send("Hello Everyone!");

    /*
    FLOW 2:
    Mohan -> Mediator -> Neha only
    */
    user3->sendPrivate("Neha", "Hey Neha!");

    return 0;
}


/*
=========================================================
WORKING SUMMARY
=========================================================

1) Users created
2) Auto registered with mediator
3) Sender calls send()
4) Mediator routes message
5) mute rules applied
6) Receiver gets message

No user directly depends on another user.

That is MEDIATOR 🔥
=========================================================
*/