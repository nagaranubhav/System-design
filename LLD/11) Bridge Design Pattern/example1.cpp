# PART 2 — CODE + DETAILED EXPLANATION + FLOW + DRY RUN


============================================================
CODE
============================================================

#include <iostream>
using namespace std;


// ==========================================================
// 1. IMPLEMENTATION INTERFACE
// ==========================================================

class Renderer {
public:

    virtual void renderCircle() = 0;
    virtual void renderSquare() = 0;

    virtual ~Renderer() = default;
};


// ==========================================================
// 2. CONCRETE IMPLEMENTATIONS
// ==========================================================

class OpenGLRenderer : public Renderer {

public:

    void renderCircle() override {
        cout << "Drawing Circle using OpenGL\n";
    }

    void renderSquare() override {
        cout << "Drawing Square using OpenGL\n";
    }
};


class DirectXRenderer : public Renderer {

public:

    void renderCircle() override {
        cout << "Drawing Circle using DirectX\n";
    }

    void renderSquare() override {
        cout << "Drawing Square using DirectX\n";
    }
};


// ==========================================================
// 3. ABSTRACTION
// ==========================================================

class Shape {

protected:

    Renderer* renderer;

public:

    Shape(Renderer* renderer) {
        this->renderer = renderer;
    }

    virtual void draw() = 0;

    virtual ~Shape() = default;
};


// ==========================================================
// 4. REFINED ABSTRACTIONS
// ==========================================================

class Circle : public Shape {

public:

    Circle(Renderer* renderer)
        : Shape(renderer) {}

    void draw() override {

        renderer->renderCircle();
    }
};


class Square : public Shape {

public:

    Square(Renderer* renderer)
        : Shape(renderer) {}

    void draw() override {

        renderer->renderSquare();
    }
};


// ==========================================================
// 5. CLIENT
// ==========================================================

int main() {

    OpenGLRenderer openGL;
    DirectXRenderer directX;


    Circle circle1(&openGL);

    Circle circle2(&directX);


    Square square1(&openGL);

    Square square2(&directX);


    circle1.draw();
    circle2.draw();

    square1.draw();
    square2.draw();


    return 0;
}


============================================================
AB CODE KO BASIC SE SAMJHO
============================================================


STEP 1 — Renderer interface kyun banaya?
------------------------------------------------------------

Humare paas ek question hai:

    "Shape ko DRAW kaise karna hai?"


Iske multiple answers ho sakte hain:

    OpenGL
    DirectX
    Vulkan
    etc.


Isliye humne common interface banaya:

    class Renderer


Aur usme:

    renderCircle()
    renderSquare()


Rakha.


Matlab Renderer bol raha hai:

    "Jo bhi rendering karega,
     usko Circle aur Square render karna aana chahiye."


============================================================
STEP 2 — OpenGLRenderer
============================================================

class OpenGLRenderer : public Renderer


Matlab:

    OpenGLRenderer IS-A Renderer


Ye OpenGL ke according rendering karega.


    renderCircle()
        ↓
    OpenGL se Circle draw


    renderSquare()
        ↓
    OpenGL se Square draw


============================================================
STEP 3 — DirectXRenderer
============================================================

class DirectXRenderer : public Renderer


Matlab:

    DirectXRenderer IS-A Renderer


Ye bhi same kaam karega:

    Circle render
    Square render


Lekin DirectX ke according.


Yahan Bridge ka first important part aa gaya:

    Renderer
       │
       ├── OpenGLRenderer
       │
       └── DirectXRenderer


============================================================
STEP 4 — Shape class
============================================================

Ab doosri side dekho.


Humare paas:

    Circle
    Square


Dono Shape hain.


Isliye:

    class Circle : public Shape
    class Square : public Shape


Ab Shape ke andar:

    Renderer* renderer;


KYUN?


Ye Bridge ka sabse important point hai.


Shape khud decide nahi karega ki:

    OpenGL use karna hai
    DirectX use karna hai


Shape bas Renderer ko use karega.


Therefore:

    Shape HAS-A Renderer


Ye hi actual BRIDGE hai.


============================================================
STEP 5 — Shape constructor
============================================================

Shape(Renderer* renderer) {

    this->renderer = renderer;
}


Jab Shape banega, hum usko renderer de denge.


Example:

    OpenGLRenderer openGL;

    Circle circle(&openGL);


Ab Circle ke andar:

    renderer → openGL


So internally:

    Circle
       |
       | renderer
       ↓
    OpenGLRenderer


Agar:

    Circle circle(&directX);


To:

    Circle
       |
       | renderer
       ↓
    DirectXRenderer


Circle ka code same hai.

Sirf renderer change hua.


============================================================
STEP 6 — Circle::draw()
============================================================

Circle mein:

    void draw() override {

        renderer->renderCircle();
    }


Circle bol raha hai:

    "Mujhe draw hona hai."

Lekin Circle khud drawing nahi kar raha.


Wo bol raha hai:

    renderer, tum Circle ko render karo.


Agar renderer OpenGL hai:

    OpenGLRenderer::renderCircle()


Agar renderer DirectX hai:

    DirectXRenderer::renderCircle()


Yahi runtime flexibility Bridge deta hai.


============================================================
STEP 7 — Square::draw()
============================================================

Same concept:

    renderer->renderSquare();


Square ko fark nahi padta:

    OpenGL
    DirectX


Jo renderer object mila hai,
wo uska kaam karega.


============================================================
COMPLETE FLOW
============================================================


                  CLIENT
                    |
                    ↓
          OpenGLRenderer openGL
                    |
                    ↓
          Circle circle(&openGL)
                    |
                    ↓
              circle.draw()
                    |
                    ↓
        renderer->renderCircle()
                    |
                    ↓
      OpenGLRenderer::renderCircle()
                    |
                    ↓
        "Drawing Circle using OpenGL"


============================================================
DRY RUN 1 — Circle + OpenGL
============================================================


Code:

    OpenGLRenderer openGL;

Memory mein:

    openGL
       ↓
    OpenGLRenderer object


Then:

    Circle circle1(&openGL);


Circle constructor call:

    Circle(Renderer* renderer)


renderer mein:

    &openGL


pass hua.


Phir:

    Shape(renderer)


Shape constructor:

    this->renderer = renderer;


Ab:

    circle1.renderer
            |
            ↓
      OpenGLRenderer


Then:

    circle1.draw();


Circle ka draw():

    renderer->renderCircle();


renderer OpenGLRenderer ko point kar raha hai.


Therefore:

    OpenGLRenderer::renderCircle()


call hoga.


Output:

    Drawing Circle using OpenGL


============================================================
DRY RUN 2 — Circle + DirectX
============================================================


Code:

    DirectXRenderer directX;

Then:

    Circle circle2(&directX);


Ab:

    circle2.renderer
           |
           ↓
      DirectXRenderer


Then:

    circle2.draw();


Circle ke andar:

    renderer->renderCircle();


Lekin renderer ab DirectXRenderer hai.


Therefore:

    DirectXRenderer::renderCircle()


call hoga.


Output:

    Drawing Circle using DirectX


IMPORTANT:

Circle class mein kuch bhi change nahi hua.


Sirf:

    renderer


change hua.


Yahi Bridge ka magic hai.


============================================================
DRY RUN 3 — Square + OpenGL
============================================================


    Square square1(&openGL);


square1 ke andar:

    renderer → OpenGLRenderer


Then:

    square1.draw();


Square:

    renderer->renderSquare();


Therefore:

    OpenGLRenderer::renderSquare()


Output:

    Drawing Square using OpenGL


============================================================
DRY RUN 4 — Square + DirectX
============================================================


    Square square2(&directX);


renderer:

    square2
       |
       ↓
    DirectXRenderer


Then:

    square2.draw();


Call:

    renderer->renderSquare();


Therefore:

    DirectXRenderer::renderSquare()


Output:

    Drawing Square using DirectX


============================================================
FINAL OUTPUT
============================================================

Drawing Circle using OpenGL
Drawing Circle using DirectX
Drawing Square using OpenGL
Drawing Square using DirectX


============================================================
CODE KO EK LINE MEIN SAMJHO
============================================================


Shape decides:

    WHAT?

Renderer decides:

    HOW?


So:

    Circle
       |
       | HAS-A
       ↓
    Renderer
       |
       ├── OpenGL
       └── DirectX


Shape aur Renderer independently grow kar sakte hain.


============================================================
AGAR KAL NEW SHAPE AAYE
============================================================

Example:

    Triangle


Bas:

    class Triangle : public Shape

banani hai.


Renderer side ko unnecessarily modify karne ki zarurat
nahi, except agar Renderer interface mein Triangle ka
specific operation required ho.


Similarly...


============================================================
AGAR KAL NEW RENDERER AAYE
============================================================

Example:

    VulkanRenderer


Bas:

    class VulkanRenderer : public Renderer

banani hai.


Existing:

    Circle
    Square

ko change karne ki zarurat nahi.


============================================================
INTERVIEW THINKING
============================================================

Problem:

    Shapes badhenge
    +
    Renderers badhenge


Agar inheritance se dono ko combine kiya:

    Shapes × Renderers


classes banengi.


Bridge:

    Shapes
       +
    Renderers


ko separate rakhta hai.


Isliye:

    LESS COUPLING
    MORE FLEXIBILITY
    LESS CLASS EXPLOSION


============================================================
TIME TO REMEMBER
============================================================

Bridge ka core:

    "WHAT" aur "HOW" ko separate karo.


Example:

    Shape = WHAT
    Renderer = HOW


Aur:

    Shape HAS-A Renderer


Bas ye 3 cheezein yaad rakhoge,
Bridge Pattern ka core samajh aa jayega.