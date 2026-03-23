#include <iostream>
using namespace std;

/*
====================== COMMAND DESIGN PATTERN (FULL FLOW) ======================

🧠 CORE IDEA:
"Encapsulate request as an object"

Invoker (Remote) ko nahi pata:
- Light kya hai
- Fan kya hai

Woh sirf bolta:
👉 execute()
👉 undo()

-------------------------------------------------------------------------------

📌 UML DIAGRAM (VERY IMPORTANT FOR INTERVIEW)

            +-------------------+
            |     Command       |  (Interface)
            |-------------------|
            | +execute()        |
            | +undo()           |
            +-------------------+
                    ▲
          -----------------------
          |                     |
+-------------------+   +-------------------+
|  LightCommand     |   |   FanCommand      |  (Concrete Commands)
|-------------------|   |-------------------|
| - Light*          |   | - Fan*            |
|-------------------|   |-------------------|
| +execute()        |   | +execute()        |
| +undo()           |   | +undo()           |
+-------------------+   +-------------------+
          |                     |
          v                     v
     +----------+         +----------+
     |  Light   |         |   Fan    |   (Receivers)
     +----------+         +----------+

                 ^
                 |
        +-------------------+
        | RemoteController  |  (Invoker)
        +-------------------+

Client (main) sab connect karta hai.

-------------------------------------------------------------------------------

📌 FLOW:
Client → create receiver
       → create command (receiver ke saath)
       → assign command to invoker

Invoker → execute()/undo()

Command → receiver ke method call karta hai

-------------------------------------------------------------------------------
*/


// ===================== COMMAND INTERFACE =====================
class Command {
public:
    // har command ko define karna hi padega
    virtual void execute() = 0;
    virtual void undo() = 0;

    virtual ~Command() {}
};


// ===================== RECEIVERS =====================
// Actual kaam yahan hota hai

class Light {
public:
    void on()  { 
        cout << "Light is ON" << endl; 
    }

    void off() { 
        cout << "Light is OFF" << endl;
    }
};

class Fan {
public:
    void on()  { 
        cout << "Fan is ON" << endl; 
    }

    void off() { 
        cout << "Fan is OFF" << endl; 
    }
};


// ===================== CONCRETE COMMAND =====================
// Ye actual bridge hai Invoker aur Receiver ke beech

class LightCommand : public Command {
private:
    Light* light;   // 🔥 receiver ka pointer

public:
    // constructor me receiver inject ho raha hai (Dependency Injection)
    LightCommand(Light* l) { 
        light = l; 
    }

    // execute = action perform karna
    void execute() { 
        /*
        FLOW:
        Remote → execute()
               → LightCommand → light->on()
        */
        light->on(); 
    }

    // undo = reverse action
    void undo() { 
        light->off(); 
    }
};


class FanCommand : public Command {
private:
    Fan* fan;

public:
    FanCommand(Fan* f) { 
        fan = f; 
    }

    void execute() { 
        fan->on(); 
    }

    void undo() { 
        fan->off(); 
    }
};


// ===================== INVOKER =====================
// Remote Controller

class RemoteController {
private:
    static const int numButtons = 4;

    /*
    buttons[i] → kaunsa command assign hai
    buttonPressed[i] → state kya hai (toggle ke liye)
    */
    Command* buttons[numButtons];
    bool buttonPressed[numButtons];

public:
    RemoteController() {
        for (int i = 0; i < numButtons; i++) {
            buttons[i] = nullptr;
            buttonPressed[i] = false;  // initial state = OFF
        }
    }

    // client command assign karega
    void setCommand(int idx, Command* cmd) {
        if (idx >= 0 && idx < numButtons) {

            // pehle old command delete (memory safe)
            if (buttons[idx] != nullptr)
                delete buttons[idx];

            buttons[idx] = cmd;
            buttonPressed[idx] = false;
        }
    }

    // 🔥 CORE FUNCTION
    void pressButton(int idx) {
        if (idx >= 0 && idx < numButtons && buttons[idx] != nullptr) {

            /*
            TOGGLE LOGIC:

            First press:
                state = false
                → execute()
                → ON

            Second press:
                state = true
                → undo()
                → OFF
            */

            if (buttonPressed[idx] == false) {
                buttons[idx]->execute();
            } else {
                buttons[idx]->undo();
            }

            // toggle state
            buttonPressed[idx] = !buttonPressed[idx];

        } else {
            cout << "No command assigned at button " << idx << endl;
        }
    }

    ~RemoteController() {
        for (int i = 0; i < numButtons; i++) {
            if (buttons[i] != NULL)
                delete buttons[i];
        }
    }
};


// ===================== CLIENT =====================
int main() {

    /*
    STEP 1: Receivers create
    */
    Light* livingRoomLight = new Light();
    Fan* ceilingFan = new Fan();

    /*
    STEP 2: Invoker create
    */
    RemoteController* remote = new RemoteController();

    /*
    STEP 3: Commands create and assign

    IMPORTANT:
    Remote ko nahi pata Light kya hai
    Remote ko bas Command diya gaya hai
    */
    remote->setCommand(0, new LightCommand(livingRoomLight));
    remote->setCommand(1, new FanCommand(ceilingFan));


    /*
    ================= EXECUTION FLOW =================

    pressButton(0)
    → Remote
    → LightCommand.execute()
    → Light.on()

    pressButton(0) again
    → undo()
    → Light.off()
    */

    cout << "--- Toggling Light Button 0 ---" << endl;
    remote->pressButton(0);  // ON
    remote->pressButton(0);  // OFF

    cout << "--- Toggling Fan Button 1 ---" << endl;
    remote->pressButton(1);  // ON
    remote->pressButton(1);  // OFF

    cout << "--- Pressing Unassigned Button 2 ---" << endl;
    remote->pressButton(2);


    /*
    CLEANUP
    */
    delete remote;
    delete livingRoomLight;
    delete ceilingFan;

    return 0;
}


/*
====================== FINAL INTERVIEW SUMMARY ======================

🔥 1 line answer:
Command Pattern = "Encapsulate request as object to decouple sender & receiver"

🔥 Key Points:
- Invoker doesn't know receiver
- Command acts as middle layer
- execute() + undo() = core

🔥 Most Asked Followups:
- Undo kaise implement karoge?
- Multiple commands ek saath kaise?
- Queueing kaise karoge?

🔥 Advanced:
- MacroCommand
- Command History Stack (Undo/Redo multiple steps)

====================================================================
*/