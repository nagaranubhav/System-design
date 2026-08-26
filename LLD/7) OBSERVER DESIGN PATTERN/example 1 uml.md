# YouTube Notification System — Observer Pattern
# FINAL POLISHED UML
#
# Subject = YouTubeChannel
# Observer = Observer interface
# Concrete Observer = Subscriber


┌──────────────────────────────────────────────────────────────┐
│                    <<interface>>                             │
│                       Observer                               │
├──────────────────────────────────────────────────────────────┤
│ + update(videoTitle : string) : void                         │
└───────────────────────────────▲──────────────────────────────┘
                                │
                                │ <<implements>>
                                │
                                │
┌───────────────────────────────┴──────────────────────────────┐
│                         Subscriber                            │
├──────────────────────────────────────────────────────────────┤
│ - name : string                                               │
├──────────────────────────────────────────────────────────────┤
│ + Subscriber(name : string)                                  │
│ + update(videoTitle : string) : void                         │
└───────────────────────────────┬──────────────────────────────┘
                                │
                    Concrete Observer
                                │
                 ┌──────────────┼──────────────┐
                 │              │              │
                 ▼              ▼              ▼
          ┌────────────┐ ┌────────────┐ ┌────────────┐
          │   Rahul    │ │    Aman    │ │   Priya    │
          │ Subscriber │ │ Subscriber │ │ Subscriber │
          └────────────┘ └────────────┘ └────────────┘



                         1        *
┌──────────────────────────────────────────────────────────────┐
│                      YouTubeChannel                          │
├──────────────────────────────────────────────────────────────┤
│ - channelName : string                                       │
│ - subscribers : vector<Observer*>                            │
├──────────────────────────────────────────────────────────────┤
│ + YouTubeChannel(channelName : string)                       │
│ + subscribe(observer : Observer*) : void                     │
│ + unsubscribe(observer : Observer*) : void                   │
│ + uploadVideo(videoTitle : string) : void                    │
│ - notify(videoTitle : string) : void                         │
└───────────────────────────────┬──────────────────────────────┘
                                │
                                │
                                │ HAS-A
                                │ 1 ──────────── * 
                                ▼
                     ┌─────────────────────┐
                     │       Observer      │
                     │      <<interface>>  │
                     └─────────────────────┘



# ============================================================
# RELATIONSHIPS
# ============================================================

YouTubeChannel  ──────────────── HAS-A ────────────────► Observer

Meaning:
YouTubeChannel ke paas multiple Observer objects ki list hai.

C++:
vector<Observer*> subscribers;


Subscriber  ─────────────── IS-A / IMPLEMENTS ─────────► Observer

Meaning:
Subscriber Observer interface ko implement karta hai.

C++:
class Subscriber : public Observer


# ============================================================
# ACTUAL OBJECT STRUCTURE
# ============================================================

                    YouTubeChannel
                           │
                           │ HAS-A
                           │
                           │ 1
                           │
                           │
                           │ *
                           ▼
                ┌────────────────────┐
                │   Observer List    │
                ├────────────────────┤
                │ Observer* Rahul    │
                │ Observer* Aman     │
                │ Observer* Priya    │
                └─────────┬──────────┘
                          │
             ┌────────────┼────────────┐
             ▼            ▼            ▼
          Subscriber   Subscriber   Subscriber
             Rahul        Aman         Priya


# ============================================================
# METHOD FLOW
# ============================================================

Client
  │
  │ uploadVideo("Observer Pattern")
  ▼
YouTubeChannel
  │
  │ notify(videoTitle)
  ▼
Observer List
  │
  ├──────────────► Rahul.update(videoTitle)
  │
  ├──────────────► Aman.update(videoTitle)
  │
  └──────────────► Priya.update(videoTitle)


# ============================================================
# SUBSCRIBE FLOW
# ============================================================

Rahul
  │
  │ subscribe()
  ▼
YouTubeChannel
  │
  ▼
subscribers.push_back(Rahul)


# ============================================================
# UNSUBSCRIBE FLOW
# ============================================================

Aman
  │
  │ unsubscribe()
  ▼
YouTubeChannel
  │
  ▼
Aman removed from subscribers


# ============================================================
# COMPLETE OBSERVER ARCHITECTURE
# ============================================================

                     SUBJECT
                        │
                        │
                        ▼
              ┌──────────────────┐
              │ YouTubeChannel   │
              ├──────────────────┤
              │ subscribers      │
              │ subscribe()      │
              │ unsubscribe()    │
              │ uploadVideo()    │
              │ notify()         │
              └────────┬─────────┘
                       │
                       │ HAS-A
                       │
                       ▼
                <<interface>>
                ┌──────────────┐
                │   Observer   │
                ├──────────────┤
                │ update()     │
                └──────▲───────┘
                       │
                       │ IS-A
                       │
                       ▼
                ┌──────────────┐
                │  Subscriber  │
                ├──────────────┤
                │ name         │
                │ update()     │
                └──────────────┘
                       │
             ┌─────────┼─────────┐
             ▼         ▼         ▼
           Rahul      Aman      Priya


# ============================================================
# MOST IMPORTANT POINT
# ============================================================

YouTubeChannel does NOT depend on:

    Rahul
    Aman
    Priya

directly.

It only depends on:

    Observer interface

Therefore:

YouTubeChannel
      ↓
   Observer
      ↑
 Subscriber

This gives us:

    LOW COUPLING
    +
    ONE-TO-MANY NOTIFICATION
    +
    DYNAMIC SUBSCRIBE / UNSUBSCRIBE


# PATTERN MAPPING

┌──────────────────────┬──────────────────────────────┐
│ Observer Pattern     │ YouTube Example              │
├──────────────────────┼──────────────────────────────┤
│ Subject              │ YouTubeChannel               │
│ Observer             │ Observer interface           │
│ ConcreteObserver     │ Subscriber                   │
│ attach()             │ subscribe()                  │
│ detach()             │ unsubscribe()                │
│ notify()             │ notify()                     │
│ State/Event Change   │ New video uploaded           │
│ update()             │ Receive notification          │
└──────────────────────┴──────────────────────────────┘