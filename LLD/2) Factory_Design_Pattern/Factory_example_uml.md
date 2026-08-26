# Factory Pattern — Vehicle Example UML

                    ┌─────────────────────────────┐
                    │           Client            │
                    │          <<main>>           │
                    ├─────────────────────────────┤
                    │                             │
                    │ Vehicle* v1                 │
                    │ Vehicle* v2                 │
                    │                             │
                    │ + getVehicle("bike")       │
                    │ + getVehicle("truck")      │
                    │ + drive()                   │
                    └──────────────┬──────────────┘
                                   │
                                   │ uses
                                   ▼
                    ┌─────────────────────────────┐
                    │      VehicleFactory         │
                    ├─────────────────────────────┤
                    │ + getVehicle(type):         │
                    │   Vehicle*                  │
                    └──────────────┬──────────────┘
                                   │
                                   │ creates
                    ┌──────────────┼──────────────┐
                    │              │              │
                    │              │              │
                    ▼              ▼              ▼
             ┌────────────┐ ┌────────────┐ ┌────────────┐
             │    Bike    │ │    Car     │ │   Truck    │
             ├────────────┤ ├────────────┤ ├────────────┤
             │ + drive()  │ │ + drive()  │ │ + drive()  │
             └──────┬─────┘ └──────┬─────┘ └──────┬─────┘
                    │              │              │
                    │ inherits     │ inherits     │ inherits
                    │              │              │
                    └──────────────┼──────────────┘
                                   │
                                   ▼
                    ┌─────────────────────────────┐
                    │          Vehicle            │
                    │       <<interface>>         │
                    ├─────────────────────────────┤
                    │ + drive() : void            │
                    │ + ~Vehicle()                │
                    └─────────────────────────────┘


# Relationships

Vehicle
   ▲
   │
   │ inheritance
   │
   ├────────── Bike
   │
   ├────────── Car
   │
   └────────── Truck


Client
   │
   │ uses
   ▼
VehicleFactory


VehicleFactory
   │
   │ creates
   ├──────────► Bike
   ├──────────► Car
   └──────────► Truck


# Actual Flow

Client
   │
   │ getVehicle("bike")
   ▼
VehicleFactory
   │
   │ new Bike()
   ▼
Bike object
   │
   │ returned as
   ▼
Vehicle*


Similarly:

Client
   │
   │ getVehicle("truck")
   ▼
VehicleFactory
   │
   │ new Truck()
   ▼
Truck object
   │
   │ returned as
   ▼
Vehicle*


# Most Important Point

Factory ka relation Concrete Classes ke saath hai:

        VehicleFactory
          │    │    │
       creates creates creates
          │    │    │
          ▼    ▼    ▼
        Bike  Car  Truck


Aur Client ka relation Factory ke saath hai:

        Client
           │
          uses
           ▼
        Factory


Client directly ye nahi karta:

        Client ──X──► new Bike()
        Client ──X──► new Car()
        Client ──X──► new Truck()


Instead:

        Client
           │
           ▼
        Factory
           │
           ▼
        Required Vehicle


# One-Line Understanding

Client → Factory se object maangta hai

Factory → decide karti hai kaunsa object banana hai

Bike / Car / Truck → actual object hota hai

Vehicle → common interface hai