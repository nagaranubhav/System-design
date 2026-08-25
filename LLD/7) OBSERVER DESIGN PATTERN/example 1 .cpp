#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// ============================================================
// 1. OBSERVER
// ============================================================

// Observer interface
// Jo bhi class YouTube channel ki notification receive
// karna chahti hai, usse Observer implement karna hoga.

class Observer {
public:

    virtual void update(string videoTitle) = 0;

    virtual ~Observer() = default;
};


// ============================================================
// 2. CONCRETE OBSERVER
// ============================================================

// YouTube Subscriber
// Ye actual observer hai.

class Subscriber : public Observer {

private:
    string name;

public:

    Subscriber(string name) {
        this->name = name;
    }

    void update(string videoTitle) override {

        cout << name
             << " received notification: "
             << "New video uploaded - "
             << videoTitle
             << endl;
    }
};


// ============================================================
// 3. SUBJECT
// ============================================================

// YouTube Channel = Subject
//
// Channel ke paas subscribers ki list hai.
// Isliye:
//
// YouTubeChannel HAS-A list of Observers

class YouTubeChannel {

private:

    string channelName;

    vector<Observer*> subscribers;


public:

    YouTubeChannel(string channelName) {
        this->channelName = channelName;
    }


    // --------------------------------------------------------
    // Subscribe
    // --------------------------------------------------------

    void subscribe(Observer* observer) {

        subscribers.push_back(observer);
    }


    // --------------------------------------------------------
    // Unsubscribe
    // --------------------------------------------------------

    void unsubscribe(Observer* observer) {

        subscribers.erase(
            remove(
                subscribers.begin(),
                subscribers.end(),
                observer
            ),
            subscribers.end()
        );
    }


    // --------------------------------------------------------
    // Upload Video
    // --------------------------------------------------------

    void uploadVideo(string videoTitle) {

        cout << "\n"
             << channelName
             << " uploaded: "
             << videoTitle
             << endl;

        // New video uploaded
        // Notify all subscribers.

        notify(videoTitle);
    }


private:

    // --------------------------------------------------------
    // Notify
    // --------------------------------------------------------

    void notify(string videoTitle) {

        for (Observer* subscriber : subscribers) {

            subscriber->update(videoTitle);
        }
    }
};


// ============================================================
// 4. CLIENT
// ============================================================

int main() {

    // Create YouTube Channel
    YouTubeChannel channel("CodeWithAnubhav");


    // Create subscribers
    Subscriber user1("Rahul");
    Subscriber user2("Aman");
    Subscriber user3("Priya");


    // --------------------------------------------------------
    // Users subscribe to the channel
    // --------------------------------------------------------

    channel.subscribe(&user1);
    channel.subscribe(&user2);
    channel.subscribe(&user3);


    // --------------------------------------------------------
    // Channel uploads first video
    // --------------------------------------------------------

    channel.uploadVideo("Observer Design Pattern");


    // --------------------------------------------------------
    // Aman unsubscribes
    // --------------------------------------------------------

    channel.unsubscribe(&user2);


    // --------------------------------------------------------
    // Channel uploads second video
    // --------------------------------------------------------

    channel.uploadVideo("Strategy Design Pattern");


    return 0;
}
```

# YouTube Example — Intuition

Imagine YouTube par ek channel hai:

```
CodeWithAnubhav
```

Uske 3 subscribers hain:

```
Rahul
Aman
Priya
```

Ab channel ek new video upload karta hai:

```
"Observer Design Pattern"
```

Channel ko manually ye nahi karna:

```
Rahul ko message bhejo
Aman ko message bhejo
Priya ko message bhejo
```

Instead channel ke paas subscribers ki list hai.

```
Channel
   ↓
Subscribers
   ↓
notify()
```

Har subscriber ko notification mil jaati hai.

# Pattern Mapping

Real World              Observer Pattern

YouTube Channel      →   Subject
Subscriber           →   Observer
Subscriber class     →   Concrete Observer
Subscribe            →   attach()
Unsubscribe          →   detach()
New Video Upload     →   State/Event Change
Notification         →   update()
Notify Subscribers   →   notify()

# Relationships

YouTubeChannel HAS-A subscribers

Because:

```
vector<Observer*> subscribers;
```

Subscriber IS-A Observer

Because:

```
class Subscriber : public Observer
```

# Complete Flow

1. YouTube Channel create hota hai.

2. Subscribers create hote hain.

3. Subscribers channel ko subscribe karte hain.

   ```
   channel.subscribe(&user1);

   channel.subscribe(&user2);

   channel.subscribe(&user3);
   ```

4. Channel new video upload karta hai.

   ```
   channel.uploadVideo("Observer Design Pattern");
   ```

5. Video upload hone ke baad notify() call hota hai.

6. notify() subscribers list par loop karta hai.

7. Har subscriber ka update() call hota hai.

8. Sabko notification mil jaati hai.

# Dry Run

Initially:

```
Subscribers:

[Rahul, Aman, Priya]
```

Video:

```
Observer Design Pattern
```

notify():

```
Rahul  → update()
Aman   → update()
Priya  → update()
```

Output:

```
Rahul received notification:
New video uploaded - Observer Design Pattern

Aman received notification:
New video uploaded - Observer Design Pattern

Priya received notification:
New video uploaded - Observer Design Pattern
```

# Now Aman Unsubscribes

```
channel.unsubscribe(&user2);
```

Subscribers list:

```
[Rahul, Priya]
```

Channel uploads:

```
Strategy Design Pattern
```

notify():

```
Rahul  → update()
Priya  → update()
```

Aman ko notification nahi milegi.

# Why Observer Pattern?

Without Observer Pattern:

YouTubeChannel directly depends on:

```
Rahul
Aman
Priya
OtherSubscriber
EmailService
MobileNotificationService
...
```

This creates HIGH COUPLING.

With Observer:

```
YouTubeChannel
      ↓
   Observer
      ↑
┌─────┼─────┐
│     │     │
```

Subscriber  FutureObserver
│
└── update()

Channel ko sirf Observer interface ke baare mein pata hai.

Isliye new subscriber/notification type add karna easy hai.

# Interview One-Liner

"Observer Pattern defines a one-to-many dependency where when the Subject changes its state or an event occurs, all registered Observers are automatically notified."

```
```
