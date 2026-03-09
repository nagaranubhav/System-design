// =====================================================
//        FACTORY DESIGN PATTERN - QUICK REVISION
// =====================================================

// --------------------
// WHAT IS FACTORY?
// --------------------
// Factory ek Creational Design Pattern hai.
// Iska kaam hota hai object creation ko client se hide karna.
// Client ko nahi pata hota kaunsa concrete class ban raha hai.
// Client bas factory se object maangta hai.

// One line:
// Factory decides "KYA banana hai".

// --------------------
// CORE PROBLEM IT SOLVES
// --------------------
// Client khud new use karta hai.
// Tight coupling hoti hai.
// Naya type add karna hard hota hai.
// Code scalable nahi hota.
// Open Closed Principle break hota hai.

// --------------------
// SOLUTION BY FACTORY
// --------------------
// Object creation centralize karta hai.
// Client ko new se free karta hai.
// Loose coupling deta hai.
// Runtime par object decide hota hai.
// Polymorphism properly kaam karta hai.

// --------------------
// STRUCTURE
// --------------------
// Interface / Abstract Class  -> Common behavior.
// Concrete Classes           -> Real implementations.
// Factory Class              -> Decide karta hai kaunsa object.
// Client                     -> Factory se object leta hai.

// Flow:
// Client -> Factory -> Concrete Object -> Interface ke form me.

// --------------------
// STAR (*) MOST IMPORTANT
// --------------------
// C++ me `new` object nahi deta.
// `new` heap me object banata hai aur ADDRESS return karta hai.
// Address ko hold/return karne ke liye pointer chahiye.
// Pointer declare karne ke liye * use hota hai.

// Matlab:
// Factory object ka copy nahi deta,
// Factory object ka ADDRESS deta hai.

// One line:
// Factory ghar nahi deta, ghar ka address deta hai.

// --------------------
// WHY POINTER RETURN?
// --------------------
// new address return karta hai.
// Polymorphism sahi chalta hai.
// Object slicing avoid hoti hai.
// Runtime behavior milta hai.
// Object lifetime safe rehta hai.

// --------------------
// POLYMORPHISM
// --------------------
// Same pointer, different behavior.
// Base pointer child object ko point karta hai.
// Runtime par correct method call hota hai.
// Factory ka main power yahi hai.

// --------------------
// OBJECT SLICING
// --------------------
// Child object ko parent object me copy karna.
// Child ka extra part cut ho jata hai.
// Behavior lose ho jata hai.
// Pointer use karne se slicing nahi hoti.

// --------------------
// WHEN TO USE FACTORY
// --------------------
// Multiple object types ho.
// Runtime par decide ho kaunsa banana hai.
// Client ko concrete class na pata ho.
// Creation logic hide karna ho.

// Keywords in problem:
// "based on type"
// "depending on input"
// "runtime decision"
// "multiple implementations"
// "create instance dynamically"

// --------------------
// REAL USE CASES
// --------------------
// Payment system (UPI, Card, Wallet)
// Notification system (Email, SMS, Push)
// Vehicle system (Bike, Car, Truck)
// Parser system (JSON, XML, CSV)
// Logger system

// --------------------
// FACTORY VS STRATEGY
// --------------------
// Factory = Object creation.
// Strategy = Behavior change.

// Factory poochta:
// "KYA banana hai?"

// Strategy poochta:
// "KAISE kaam kare?"

// Factory = Creational Pattern.
// Strategy = Behavioral Pattern.

// Real systems me:
// Factory Strategy object banata hai,
// Strategy behavior execute karta hai.

// --------------------
// SIMPLE FACTORY VS FACTORY METHOD
// --------------------
// Simple Factory:
// Ek class object decide karti hai.

// Factory Method:
// Subclasses decide karti hain object.

// Simple = easy.
// Factory Method = scalable.

// --------------------
// INTERVIEW ONE-LINERS
// --------------------
// Factory hides object creation.
// It reduces coupling.
// It follows Single Responsibility.
// It supports Open Closed Principle.
// It enables runtime polymorphism.

// Killer line:
// Factory handles object creation, Strategy handles behavior variation.

// --------------------
// MEMORY TRICKS
// --------------------
// Factory client se `new` chheen leta hai.
// Star (*) means address, not object.
// Factory = Kya banana hai.
// Strategy = Kaise chalana hai.
// Pointer = ghar ka address.

// =====================================================
//                END QUICK REVISION
// =====================================================
