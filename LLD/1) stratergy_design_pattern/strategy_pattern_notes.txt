
======================================================
 STRATEGY DESIGN PATTERN - INTERVIEW NOTES
======================================================

1. WHAT IS STRATEGY PATTERN?

Strategy Pattern is a Behavioral Design Pattern which allows us to define a family of algorithms,
put them into separate classes, and make them interchangeable at runtime.

Simple words:
"Behavior ko alag classes me daal do aur runtime par choose karo."

------------------------------------------------------

2. WHY DO WE NEED IT?

Without Strategy:
- Too many if-else
- Hard to extend
- Violates Open/Closed Principle

With Strategy:
- Clean code
- Easy to add new behavior
- Runtime switching
- No modification of existing code

------------------------------------------------------

3. WHEN TO USE STRATEGY?

Use it when:
- Multiple ways to do same work
- Behavior changes at runtime
- Large if-else chains
- Future extensions expected

Examples:
- Payment methods
- Sorting algorithms
- Discount calculation
- Navigation routes

------------------------------------------------------

4. STRUCTURE

Client -> Context -> Strategy Interface
                     |
               Concrete Strategies

------------------------------------------------------

5. COMPONENTS

Strategy Interface:
Defines common method.

Concrete Strategy:
Implements algorithm.

Context:
Uses the strategy.

------------------------------------------------------

6. REAL LIFE EXAMPLES

- Google Maps (Car, Bike, Walk)
- Swiggy Payments
- Compression Algorithms
- Sorting Algorithms

------------------------------------------------------

7. BENEFITS

- Open Closed Principle
- Better code organization
- Reusable algorithms
- No large if-else

------------------------------------------------------

8. DISADVANTAGES

- Many small classes
- Over engineering for simple logic

------------------------------------------------------

9. INTERVIEW ANSWER FORMAT

"Strategy Pattern ek behavioral design pattern hai jo different algorithms ko encapsulate karta hai aur
runtime par interchangeable banata hai. Isme ek strategy interface hota hai, multiple concrete strategies
hoti hain aur ek context hota hai jo strategy use karta hai. Ye if-else complexity kam karta hai aur Open Closed Principle follow karta hai."

------------------------------------------------------

10. WHEN NOT TO USE

- Only one behavior
- Very small logic
- No future change

------------------------------------------------------

11. MEMORY TRICK

"Behavior alag karo, runtime par choose karo."

======================================================
END
======================================================
