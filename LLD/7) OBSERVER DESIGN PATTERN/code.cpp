/*
================================================================================
                    OBSERVER PATTERN - CODE WALKTHROUGH
================================================================================

👉 Intuition:
We simulate a YouTube system:
- Channel = Subject
- Subscriber = Observer
- uploadVideo() = state change
- notifySubscribers() = event trigger

================================================================================
*/

// Observer Interface
class ISubscriber {
public:
    // Every subscriber MUST implement this
    virtual void update() = 0;

    // Virtual destructor → avoids memory issues
    virtual ~ISubscriber() {}
};


/*
================================================================================
WHY INTERFACE?

👉 We don't want Channel to depend on concrete Subscriber class
👉 It should depend on abstraction → loose coupling

================================================================================
*/


// Subject Interface
class IChannel {
public:
    virtual void subscribe(ISubscriber* subscriber) = 0;
    virtual void unsubscribe(ISubscriber* subscriber) = 0;
    virtual void notifySubscribers() = 0;
    virtual ~IChannel() {}
};


/*
================================================================================
Concrete Subject (Channel)
================================================================================
*/

class Channel : public IChannel {
private:
    vector<ISubscriber*> subscribers;   // List of observers
    string name;
    string latestVideo;

public:
    Channel(const string& name) {
        this->name = name;
    }

    /*
    ---------------------------------------------------------------------------
    subscribe()
    ---------------------------------------------------------------------------
    - Adds subscriber if not already present
    - Prevents duplicates (VERY IMPORTANT)
    */
    void subscribe(ISubscriber* subscriber) override {
        if (find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()) {
            subscribers.push_back(subscriber);
        }
    }

    /*
    ---------------------------------------------------------------------------
    unsubscribe()
    ---------------------------------------------------------------------------
    - Removes subscriber if exists
    */
    void unsubscribe(ISubscriber* subscriber) override {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    /*
    ---------------------------------------------------------------------------
    notifySubscribers()
    ---------------------------------------------------------------------------
    CORE OF OBSERVER PATTERN 🔥

    - Iterate over all observers
    - Call update() on each
    */
    void notifySubscribers() override {
        for (ISubscriber* sub : subscribers) {
            sub->update();   // Polymorphism magic ✨
        }
    }

    /*
    ---------------------------------------------------------------------------
    uploadVideo()
    ---------------------------------------------------------------------------
    - State change happens here
    - After update → notify all observers
    */
    void uploadVideo(const string& title) {
        latestVideo = title;

        cout << "\n[" << name << " uploaded \"" << title << "\"]\n";

        notifySubscribers();   // Trigger event
    }

    /*
    ---------------------------------------------------------------------------
    getVideoData()
    ---------------------------------------------------------------------------
    - Used in PULL MODEL
    - Observers fetch data themselves
    */
    string getVideoData() {
        return "\nCheckout our new Video : " + latestVideo + "\n";
    }
};


/*
================================================================================
Concrete Observer (Subscriber)
================================================================================
*/

class Subscriber : public ISubscriber {
private:
    string name;
    Channel* channel;   // Observer has reference to Subject

public:
    Subscriber(const string& name, Channel* channel) {
        this->name = name;
        this->channel = channel;
    }

    /*
    ---------------------------------------------------------------------------
    update()
    ---------------------------------------------------------------------------
    - Called by Subject
    - Pulls latest data from Channel
    */
    void update() override {
        cout << "Hey " << name << "," << this->channel->getVideoData();
    }
};


/*
================================================================================
MAIN FUNCTION FLOW
================================================================================
*/

int main() {

    // Step 1: Create Subject
    Channel* channel = new Channel("CoderArmy");

    // Step 2: Create Observers
    Subscriber* subs1 = new Subscriber("Varun", channel);
    Subscriber* subs2 = new Subscriber("Tarun", channel);

    // Step 3: Subscribe observers
    channel->subscribe(subs1);
    channel->subscribe(subs2);

    // Step 4: State change → notify all
    channel->uploadVideo("Observer Pattern Tutorial");

    // Step 5: Remove one observer
    channel->unsubscribe(subs1);

    // Step 6: Only remaining observer gets update
    channel->uploadVideo("Decorator Pattern Tutorial");

    return 0;
}


/*
================================================================================
🧪 DRY RUN (STEP BY STEP)
================================================================================

Initial:
Subscribers = []

After subscribe:
Subscribers = [Varun, Tarun]

---------------------------------------------------
UPLOAD 1: "Observer Pattern Tutorial"
---------------------------------------------------

Channel.uploadVideo()

→ latestVideo = "Observer Pattern Tutorial"

→ notifySubscribers()

Loop:
    Varun.update()
        → pulls data
        → prints:
        "Hey Varun, Checkout our new Video: Observer Pattern Tutorial"

    Tarun.update()
        → prints same

---------------------------------------------------
UNSUBSCRIBE Varun
---------------------------------------------------

Subscribers = [Tarun]

---------------------------------------------------
UPLOAD 2: "Decorator Pattern Tutorial"
---------------------------------------------------

Only Tarun gets notification

Output:
Hey Tarun, Checkout our new Video: Decorator Pattern Tutorial

================================================================================
⚠️ EDGE CASES (INTERVIEW IMPORTANT)
================================================================================

1. Duplicate subscription → handled using find()
2. Unsubscribing non-existent user → safe
3. Null pointer → not handled ❌ (can improve)
4. Memory leak → raw pointers ❌ (use smart pointers)

================================================================================
🚀 IMPROVEMENTS (FAANG LEVEL)
================================================================================

✔ Use smart pointers (shared_ptr / weak_ptr)
✔ Make thread-safe (mutex)
✔ Add event filtering
✔ Async notifications (queue)

================================================================================
*/