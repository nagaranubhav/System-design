===========================================================
              FACADE DESIGN PATTERN - UML
===========================================================

Example: Home Theater System


                         ┌─────────────────────────┐
                         │   HomeTheaterFacade     │
                         ├─────────────────────────┤
                         │ - dvdPlayer             │
                         │ - projector             │
                         │ - soundSystem           │
                         ├─────────────────────────┤
                         │ + watchMovie()          │
                         │ + stopMovie()           │
                         └───────────┬─────────────┘
                                     │
                                     │ HAS-A
                    ┌────────────────┼────────────────┐
                    │                │                │
                    ▼                ▼                ▼
          ┌────────────────┐ ┌────────────────┐ ┌────────────────┐
          │   DVDPlayer    │ │   Projector    │ │  SoundSystem   │
          ├────────────────┤ ├────────────────┤ ├────────────────┤
          │ + on()         │ │ + on()         │ │ + on()         │
          │ + play()       │ │ + wideScreen() │ │ + setVolume()  │
          │ + off()        │ │ + off()        │ │ + off()        │
          └────────────────┘ └────────────────┘ └────────────────┘
                    ▲                ▲                ▲
                    │                │                │
                    └────────────────┼────────────────┘
                                     │
                              Subsystems


                         ┌──────────────┐
                         │    Client    │
                         ├──────────────┤
                         │              │
                         └──────┬───────┘
                                │
                                │ USES
                                ▼
                    ┌─────────────────────────┐
                    │   HomeTheaterFacade     │
                    └─────────────────────────┘



===========================================================
                    COMPONENT EXPLANATION
===========================================================


1. CLIENT
----------

Client wo hai jo system ko use karna chahta hai.

Example:

User movie dekhna chahta hai.

Normally user ko khud:

    DVDPlayer ON
    Projector ON
    SoundSystem ON
    DVD Play
    Volume Set

jaise multiple kaam karne padte.

Facade Pattern mein client ko ye sab directly
handle nahi karna padta.

Client simply Facade ko bolta hai:

    watchMovie()


Flow:

    Client
       |
       | USES
       ▼
    HomeTheaterFacade


-----------------------------------------------------------

2. HOMETHEATERFACADE
---------------------

Ye Facade Pattern ki MAIN class hai.

Iska kaam hai:

    Complex system ko client ke liye SIMPLE banana.

Client ko multiple subsystem classes ke baare mein
directly nahi pata hota.

Client sirf Facade se baat karta hai.

Example:

    Client
       |
       | watchMovie()
       ▼
    Facade
       |
       ├── DVDPlayer ko ON + PLAY karega
       ├── Projector ko ON karega
       └── SoundSystem ko ON + Volume set karega


IMPORTANT:

HomeTheaterFacade ke andar:

    dvdPlayer
    projector
    soundSystem

ke objects/references hain.

Isliye:

    HomeTheaterFacade HAS-A DVDPlayer
    HomeTheaterFacade HAS-A Projector
    HomeTheaterFacade HAS-A SoundSystem


HAS-A kyun?

Kyunki Facade ke PAAS ye objects hain.

Matlab:

    Facade "is" DVDPlayer nahi hai.
    Facade "has" DVDPlayer hai.


-----------------------------------------------------------

3. DVDPLAYER
-------------

DVDPlayer movie play karne ka kaam karta hai.

Methods:

    + on()
    + play()
    + off()

Ye ek SUBSYSTEM hai.

Facade iske methods ko internally call karta hai.


-----------------------------------------------------------

4. PROJECTOR
------------

Projector movie ko screen par display karta hai.

Methods:

    + on()
    + wideScreen()
    + off()

Ye bhi ek SUBSYSTEM hai.

Facade isko internally manage karta hai.


-----------------------------------------------------------

5. SOUNDSYSTEM
--------------

SoundSystem movie ka sound handle karta hai.

Methods:

    + on()
    + setVolume()
    + off()

Ye bhi ek SUBSYSTEM hai.

Facade isko bhi internally manage karta hai.


===========================================================
                 HAS-A RELATIONSHIP
===========================================================

HomeTheaterFacade
        |
        ├──── HAS-A ────> DVDPlayer
        |
        ├──── HAS-A ────> Projector
        |
        └──── HAS-A ────> SoundSystem


HAS-A kyun?

Kyuki HomeTheaterFacade ke paas in objects ke
references hain.

Simple language mein:

    Facade KE PAAS
        ↓
    DVDPlayer
    Projector
    SoundSystem


Isliye HAS-A.


===========================================================
                  IS-A RELATIONSHIP
===========================================================

Is example mein koi IS-A relationship nahi hai.

Ye galat hoga:

    HomeTheaterFacade IS-A DVDPlayer        ❌
    HomeTheaterFacade IS-A Projector        ❌
    HomeTheaterFacade IS-A SoundSystem      ❌


Kyun?

Kyunki Facade inmein se koi bhi cheez NAHI hai.

Facade sirf in objects ko USE/MANAGE karta hai.


IS-A generally inheritance ko represent karta hai.

Example:

    Car IS-A Vehicle

Agar:

    class Car : public Vehicle

toh Car ka Vehicle ke saath IS-A relationship hai.


Lekin Facade example mein:

    Facade HAS-A DVDPlayer
    Facade HAS-A Projector
    Facade HAS-A SoundSystem


===========================================================
                    MAIN IDEA
===========================================================

Without Facade:

    Client
      |
      ├── DVDPlayer
      ├── Projector
      ├── SoundSystem
      ├── DVDPlayer ke methods
      ├── Projector ke methods
      └── SoundSystem ke methods


Client ko bahut saari complexity handle karni padti hai.


With Facade:

    Client
      |
      |  watchMovie()
      ▼
    Facade
      |
      ├── DVDPlayer
      ├── Projector
      └── SoundSystem


Client ke liye poora complex system ek SIMPLE
INTERFACE ban jaata hai.


                    CLIENT
                       |
                       ▼
              ┌────────────────┐
              │     FACADE     │
              └───────┬────────┘
                      /|\
                     / | \
                    /  |  \
                   ▼   ▼   ▼
                 DVD  PROJ  SOUND
                Player ector System


                    CORE IDEA:

        "Complex system ko ek simple interface
         ke peeche hide kar do."

===========================================================