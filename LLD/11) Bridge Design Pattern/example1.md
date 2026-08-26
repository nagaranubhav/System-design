# PART 3 — EXAMPLE KA UML
# REAL-WORLD EXAMPLE: REMOTE CONTROL + DEVICE


============================================================
PROBLEM
============================================================

Humare paas 2 independent cheezein hain:

1. Remote ka type
2. Device ka type


Remote:

    BasicRemote
    AdvancedRemote


Device:

    TV
    Radio
    Projector


Agar inheritance se combine karenge:

    BasicTVRemote
    AdvancedTVRemote

    BasicRadioRemote
    AdvancedRadioRemote

    BasicProjectorRemote
    AdvancedProjectorRemote


Kal agar:

    5 Remote types
    10 Devices

aa gaye:

    5 × 10 = 50 classes


Ye problem hai.


============================================================
BRIDGE SOLUTION
============================================================


                    ┌──────────────────────────┐
                    │         Remote           │
                    │       <<abstract>>       │
                    ├──────────────────────────┤
                    │ - device: Device*       │
                    ├──────────────────────────┤
                    │ + Remote(Device*)        │
                    │ + power()                │
                    │ + volumeUp()             │
                    └────────────┬─────────────┘
                                 │
                          IS-A   │
                    ┌────────────┴────────────┐
                    │                         │
                    ▼                         ▼
          ┌─────────────────┐       ┌─────────────────┐
          │   BasicRemote   │       │ AdvancedRemote  │
          ├─────────────────┤       ├─────────────────┤
          │ + power()       │       │ + power()       │
          │ + volumeUp()    │       │ + volumeUp()    │
          └─────────────────┘       │ + mute()        │
                                    └─────────────────┘


                    Remote
                      │
                    HAS-A
                      │
                      ▼
              ┌─────────────────────┐
              │       Device        │
              │      <<interface>>  │
              ├─────────────────────┤
              │ + powerOn()        │
              │ + powerOff()       │
              │ + setVolume()      │
              └──────────┬──────────┘
                         │
                   IS-A  │
                ┌────────┼───────────┐
                │        │           │
                ▼        ▼           ▼
           ┌────────┐ ┌────────┐ ┌───────────┐
           │   TV   │ │  Radio │ │ Projector │
           ├────────┤ ├────────┤ ├───────────┤
           │+powerOn│ │+powerOn│ │ +powerOn  │
           │+powerOff││+powerOff││ +powerOff │
           │+setVolume│+setVolume││ +setVolume│
           └────────┘ └────────┘ └───────────┘


============================================================
RELATIONSHIPS
============================================================

BasicRemote IS-A Remote

AdvancedRemote IS-A Remote


TV IS-A Device

Radio IS-A Device

Projector IS-A Device


Remote HAS-A Device


Ye:

    Remote → Device

actual BRIDGE hai.


============================================================
YE BRIDGE KYON HAI?
============================================================

Remote side independently change ho sakti hai:

    BasicRemote
    AdvancedRemote
    SmartRemote
    GamingRemote


Device side independently change ho sakti hai:

    TV
    Radio
    Projector
    Speaker
    AC


Dono ko independently grow karne diya.


Example:

    BasicRemote + TV

    AdvancedRemote + Projector

    SmartRemote + Speaker


In combinations ke liye separate classes banane ki
zarurat nahi.


============================================================
IS EXAMPLE KA GOLDEN IDEA
============================================================

WITHOUT BRIDGE:

        Remote Types
              ×
        Device Types

              ↓

        Class Explosion


WITH BRIDGE:

        Remote
          |
          | HAS-A
          ↓
        Device

              ↓

        Independent Growth


============================================================
MEMORY TRICK
============================================================

BRIDGE =

    "Do alag families hain
     jo independently badhengi.

     Unko inheritance se mix mat karo.

     Dono ko separate rakho
     aur composition se connect karo."


Example:

    Remote = WHAT controls / type of control

    Device = WHAT is being controlled


Therefore:

    Remote HAS-A Device


==================== END ====================