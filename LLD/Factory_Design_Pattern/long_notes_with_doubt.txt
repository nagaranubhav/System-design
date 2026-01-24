// ==========================================================
//                FACTORY DESIGN PATTERN NOTES
// ==========================================================

// --------------------
// WHAT IS FACTORY?
// --------------------
// Factory ek Creational Design Pattern hai.
// Iska kaam hota hai object creation logic ko client se hide karna.
// Client ko ye nahi pata hota kaunsa class ka object ban raha hai.
// Client bas factory se object maangta hai.

// Simple line:
// Factory decides "KYA banana hai".

// --------------------
// PROBLEM WITHOUT FACTORY
// --------------------
// Client khud object banata hai.
// Client ko sab concrete classes ka knowledge hota hai.
// Tight coupling hoti hai.
// Naya type aaya to har jagah code change.
// Open Closed Principle break hota hai.
// Code messy aur non-scalable hota hai.

// --------------------
// WHY FACTORY IS NEEDED
// --------------------
// Object creation ko centralize karna.
// Loose coupling banana.
// Client ko new keyword se free karna.
// Runtime par decide karna kaunsa object banana hai.
// Polymorphism properly use karna.

// --------------------
// FACTORY STRUCTURE
// --------------------
// 1. Interface / Abstract Class
//    -> Common behavior define karta hai.
// 2. Concrete Classes
//    -> Interface ko implement karti hain.
// 3. Factory Class
//    -> Decide karta hai kaunsa object banana hai.
// 4. Client
//    -> Factory se object leta hai, direct new nahi karta.

// Flow:
// Client -> Factory -> Concrete Object -> Interface ke form me return.

// --------------------
// STAR (*) DOUBT - MOST IMPORTANT
// --------------------
// C++ me `new` keyword object nahi return karta.
// `new` heap me object banata hai aur uska ADDRESS return karta hai.
// Address ko hold karne ke liye pointer chahiye.
// Pointer declare karne ke liye * use hota hai.

// Simple meaning:
// * ka matlab: "ye variable address rakhega".

// Factory object ka copy nahi deta.
// Factory object ka ADDRESS deta hai.

// Memory idea:
// Object heap me rehta hai.
// Pointer uska address store karta hai.

// One line yaad rakho:
// Factory ghar nahi deta, ghar ka address deta hai.

// --------------------
// WHY RETURN ADDRESS, NOT OBJECT?
// --------------------
// 1. new address return karta hai.
// 2. Polymorphism sahi kaam karta hai.
// 3. Object slicing avoid hoti hai.
// 4. Object ka lifetime safe rehta hai.
// 5. Runtime behavior milta hai.

// Agar object return kare:
// Child ka extra part cut ho jata hai.
// Isse object slicing bolte hain.

// --------------------
// POLYMORPHISM
// --------------------
// Polymorphism ka matlab:
// Same pointer, different behavior.

// Base class pointer child object ko point karta hai.
// Runtime par decide hota hai kaunsa function chalega.

// Matlab:
// Interface ka pointer use karo.
// Actual object ka method runtime pe call hota hai.

// Ye factory ka core benefit hai.

// --------------------
// OBJECT SLICING
// --------------------
// Jab child object ko parent object me copy kar dete hain,
// tab child ka extra data cut ho jata hai.
// Behavior lose ho jata hai.
// Isse object slicing kehte hain.

// Pointer use karne se slicing nahi hoti,
// kyunki object copy nahi hota,
// sirf address pass hota hai.

// --------------------
// FACTORY KA REAL KAAM
// --------------------
// Factory ka kaam:
// Object banana.
// Kaunsa class use hoga decide karna.
// Client ko concrete class se alag rakhna.

// Factory client se `new` keyword chheen leta hai.

// --------------------
// HOW SENIOR ENGINEER THINKS
// --------------------
// Main pehle poochta hoon:
// Kya multiple types ke objects hain?
// Kya runtime par decide hoga kaunsa banana hai?
// Kya client ko creation logic se free rakhna hai?
// Kya same interface follow hoga?

// Agar haan:
// Factory use karo.

// --------------------
// HINTS TO USE FACTORY
// --------------------
// Problem me words aate hain:
// "based on type"
// "depending on input"
// "runtime decision"
// "multiple implementations"
// "client should not know concrete class"
// "create instance dynamically"

// Example areas:
// Payment system
// Notification system
// Vehicle system
// Parser system
// Logger system

// --------------------
// FACTORY VS STRATEGY
// --------------------
// Factory ka kaam:
// Object creation.

// Strategy ka kaam:
// Behavior change.

// Factory poochta hai:
// "KYA banana hai?"

// Strategy poochta hai:
// "KAISE kaam kare?"

// Factory = Creational Pattern.
// Strategy = Behavioral Pattern.

// Factory object deta hai.
// Strategy algorithm/behavior swap karta hai.

// Real systems me dono saath use hote hain:
// Factory Strategy object banata hai,
// Strategy behavior execute karta hai.

// --------------------
// WHEN TO USE STRATEGY
// --------------------
// Jab:
// Algorithm vary karta ho.
// Same object ka behavior change karna ho.
// Runtime pe logic swap karna ho.
// Sorting, payment logic, discounts, compression.

// --------------------
// WHEN TO USE FACTORY
// --------------------
// Jab:
// Object creation complex ho.
// Multiple concrete classes ho.
// Input ke basis par object banana ho.
// Client ko new se bachana ho.

// --------------------
// SIMPLE FACTORY VS FACTORY METHOD
// --------------------
// Simple Factory:
// Ek class decide karti hai object kaunsa banega.

// Factory Method:
// Subclasses decide karti hain kaunsa object banega.

// Simple Factory = easy.
// Factory Method = scalable.

// --------------------
// INTERVIEW POINTS
// --------------------
// Factory benefits:
// Loose coupling
// Single Responsibility
// Open Closed Principle
// Better scalability
// Clean architecture
// Polymorphism usage

// Interview line:
// Factory handles object creation,
// Strategy handles behavior variation,
// and often Factory creates Strategy objects.

// --------------------
// ONE LINE MEMORY TRICKS
// --------------------
// Factory client se `new` chheen leta hai.
// Star isliye hai kyunki hum object nahi, address return karte hain.
// Factory = Kya banana hai.
// Strategy = Kaise chalana hai.
// Pointer = ghar ka address.

// ==========================================================
//                    END OF NOTES
// ==========================================================
