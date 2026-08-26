# PART 1 — BRIDGE PATTERN
# UML DIAGRAM + SHORT NOTES


                    ┌─────────────────────────┐
                    │         Shape           │
                    │      <<abstract>>       │
                    ├─────────────────────────┤
                    │ - renderer: Renderer*   │
                    ├─────────────────────────┤
                    │ + Shape(Renderer*)      │
                    │ + draw() = 0            │
                    └────────────┬────────────┘
                                 │
                       IS-A      │
                    ┌────────────┴────────────┐
                    │                         │
                    ▼                         ▼
          ┌─────────────────┐       ┌─────────────────┐
          │     Circle      │       │     Square      │
          ├─────────────────┤       ├─────────────────┤
          │ + draw()        │       │ + draw()        │
          └─────────────────┘       └─────────────────┘


                    Shape
                      │
                    HAS-A
                      │
                      ▼
          ┌─────────────────────────┐
          │       Renderer          │
          │       <<interface>>     │
          ├─────────────────────────┤
          │ + renderCircle()        │
          │ + renderSquare()        │
          └────────────┬────────────┘
                       │
                 IS-A  │
              ┌────────┴────────┐
              │                 │
              ▼                 ▼
     ┌────────────────┐  ┌────────────────┐
     │ OpenGLRenderer │  │ DirectXRenderer│
     ├────────────────┤  ├────────────────┤
     │ + renderCircle │  │ + renderCircle │
     │ + renderSquare │  │ + renderSquare │
     └────────────────┘  └────────────────┘


------------------------------------------------------------
SHORT NOTES
------------------------------------------------------------

1. Bridge Pattern ka main goal:

   2 independent cheezon ko alag karna
   taaki dono independently change ho sakein.

2. Yahan 2 dimensions hain:

   WHAT to draw?
       → Shape
       → Circle
       → Square

   HOW to draw?
       → Renderer
       → OpenGL
       → DirectX

3. Shape ke paas Renderer hai:

       Shape HAS-A Renderer

   Isliye Shape ke andar:

       Renderer* renderer;

4. Circle aur Square:

       Circle IS-A Shape
       Square IS-A Shape

5. OpenGL aur DirectX:

       OpenGLRenderer IS-A Renderer
       DirectXRenderer IS-A Renderer

6. Bridge ki wajah se:

       Circle + OpenGL
       Circle + DirectX
       Square + OpenGL
       Square + DirectX

   ke liye alag-alag classes nahi banani padti.

7. Kab use karna hai?

   Jab 2 independent dimensions hon aur dono future
   mein independently grow/change kar sakti hon.

8. Main problem jo Bridge solve karta hai:

       Class Explosion

   Example:

       CircleOpenGL
       CircleDirectX
       SquareOpenGL
       SquareDirectX
       ...

   ke bajaye:

       Shape hierarchy
              +
       Renderer hierarchy

9. Golden Rule:

       2 independent dimensions
                ↓
       Separate hierarchies
                ↓
       Composition se connect
                ↓
          Bridge Pattern