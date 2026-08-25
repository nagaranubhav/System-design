# Strategy Design Pattern — UML Diagram

                    ┌──────────────────────────┐
                    │         Context          │
                    ├──────────────────────────┤
                    │ - strategy: Strategy     │
                    ├──────────────────────────┤
                    │ + setStrategy()           │
                    │ + executeStrategy()       │
                    └────────────┬─────────────┘
                                 │
                                 │ HAS-A
                                 │
                                 ▼
                    ┌──────────────────────────┐
                    │       <<interface>>      │
                    │         Strategy         │
                    ├──────────────────────────┤
                    │ + algorithm()            │
                    └────────────┬─────────────┘
                                 △
                    ┌────────────┴────────────┐
                    │                         │
                    │ implements              │ implements
                    │                         │
        ┌───────────┴──────────┐   ┌──────────┴───────────┐
        │   ConcreteStrategyA  │   │   ConcreteStrategyB  │
        ├──────────────────────┤   ├──────────────────────┤
        │ + algorithm()        │   │ + algorithm()        │
        └──────────────────────┘   └──────────────────────┘


                    CORE IDEA
                    ──────────

Context
   │
   │ uses
   ▼
Strategy Interface
   ▲
   │
   ├─────────────── ConcreteStrategyA
   │
   └─────────────── ConcreteStrategyB


WHY THIS PATTERN?

Instead of putting multiple algorithms inside Context:

        if(type == A)
            algorithmA();
        else if(type == B)
            algorithmB();
        else if(type == C)
            algorithmC();

We extract each algorithm into its own class:

        Strategy
           ▲
           │
      ┌────┴────┐
      │         │
    Algo A    Algo B

And Context simply works with the Strategy interface.

The strategy can also be changed at runtime:

        Context
           │
           ├── Strategy A
           │
           └── Strategy B

So the main principle is:

        "Encapsulate interchangeable algorithms
         and make them interchangeable at runtime."