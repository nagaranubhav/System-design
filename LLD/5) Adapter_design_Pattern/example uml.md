┌─────────────────────────────────────────────────────────────────────┐
│              ADAPTER PATTERN — PAYMENT SYSTEM UML                  │
└─────────────────────────────────────────────────────────────────────┘


                         «interface»
                    ┌─────────────────────┐
                    │  PaymentProcessor   │
                    │      <<Target>>     │
                    ├─────────────────────┤
                    │ + pay(amount): void │
                    └──────────▲──────────┘
                               │
                               │ implements
                               │  IS-A
                               │
                    ┌──────────┴──────────┐
                    │   PaymentAdapter    │
                    │     <<Adapter>>     │
                    ├─────────────────────┤
                    │ - oldPaymentSystem  │
                    │   : OldPaymentSystem│
                    ├─────────────────────┤
                    │ + pay(amount): void │
                    └──────────┬──────────┘
                               │
                               │ HAS-A
                               │
                               │ uses
                               ▼
                    ┌─────────────────────┐
                    │  OldPaymentSystem   │
                    │     <<Adaptee>>     │
                    ├─────────────────────┤
                    │                     │
                    ├─────────────────────┤
                    │ + makePayment()     │
                    │   (amount): void    │
                    └─────────────────────┘


                    ▲
                    │
                    │ uses
                    │
          ┌─────────┴──────────┐
          │      Checkout      │
          │      <<Client>>    │
          ├────────────────────┤
          │                    │
          ├────────────────────┤
          │ + makePayment(     │
          │   processor,       │
          │   amount): void    │
          └────────────────────┘


=====================================================================
                         COMPLETE FLOW
=====================================================================

                         CLIENT
                       ┌──────────┐
                       │ Checkout │
                       └────┬─────┘
                            │
                            │ pay(5000)
                            ▼
                    ┌────────────────┐
                    │ PaymentAdapter │
                    └───────┬────────┘
                            │
                            │ makePayment(5000)
                            ▼
                    ┌─────────────────┐
                    │ OldPaymentSystem│
                    └─────────────────┘


=====================================================================
                     RELATIONSHIPS EXPLAINED
=====================================================================

1. PaymentAdapter ────────▷ PaymentProcessor

   IS-A relationship

   PaymentAdapter inherits/implements PaymentProcessor.

   Code:

       class PaymentAdapter : public PaymentProcessor


2. PaymentAdapter ────────→ OldPaymentSystem

   HAS-A relationship

   Adapter ke andar OldPaymentSystem ka object hai.

   Code:

       OldPaymentSystem oldPaymentSystem;


3. Checkout ──────────────→ PaymentProcessor

   USES relationship

   Checkout ko sirf PaymentProcessor ka interface pata hai.

   Code:

       PaymentProcessor* processor;


=====================================================================
                         MAIN IDEA
=====================================================================

Client ko chahiye:

        pay(amount)

Lekin old system deta hai:

        makePayment(amount)

Adapter beech mein translation karta hai:

        pay(amount)
             │
             ▼
        PaymentAdapter
             │
             ▼
        makePayment(amount)


             Adapter
          ┌─────────────┐
          │             │
          │  IS-A       │──────► PaymentProcessor
          │             │
          │  HAS-A      │──────► OldPaymentSystem
          │             │
          └─────────────┘


                    ADAPTER = TRANSLATOR

Client ko old system ka interface change
karne ki zarurat nahi padti.


=====================================================================