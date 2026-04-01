#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/*
=========================================================
FLYWEIGHT PATTERN - ASTEROID GAME EXAMPLE
=========================================================

PROBLEM:
1,000,000 asteroids create karne hain.

Agar har asteroid me:
- size
- color
- texture
- material
- position
- velocity

sab duplicate rakhenge → huge memory waste ❌

SOLUTION:
Shared state → Flyweight
Unique state → Context
*/


// =====================================================
// 1) FLYWEIGHT (INTRINSIC STATE)
// =====================================================

/*
Ye shared asteroid TYPE ko represent karta hai.

Intrinsic state:
- length
- width
- weight
- color
- texture
- material

Same type ke sab asteroids ye object share karenge.
*/
class AsteroidFlyweight {
private:
    int length;
    int width;
    int weight;
    string color;
    string texture;
    string material;

public:
    /*
    Constructor shared immutable state set karta hai.
    */
    AsteroidFlyweight(int l, int w, int wt,
                      string col,
                      string tex,
                      string mat) {

        this->length = l;
        this->width = w;

        /*
        IMPORTANT BUG IN ORIGINAL CODE:
        this->weight = w;

        Correct:
        wt assign hona chahiye
        */
        this->weight = wt;

        this->color = col;
        this->texture = tex;
        this->material = mat;
    }

    /*
    render() me extrinsic state bahar se pass ho rahi hai:
    - position
    - velocity

    This is pure Flyweight spirit 🔥
    */
    void render(int posX, int posY,
                int velocityX, int velocityY) {

        cout << "Rendering " << color
             << ", " << texture
             << ", " << material
             << " asteroid at ("
             << posX << "," << posY << ")"
             << " Size: " << length << "x" << width
             << " Velocity: ("
             << velocityX << "," << velocityY << ")"
             << endl;
    }
};


// =====================================================
// 2) FLYWEIGHT FACTORY
// =====================================================

/*
Factory ka kaam:
same flyweight dobara create na ho

Cache maintain karta hai:
key -> flyweight
*/
class AsteroidFactory {
private:
    static unordered_map<string, AsteroidFlyweight*> flyweights;

public:
    static AsteroidFlyweight* getAsteroid(
        int length, int width, int weight,
        string color, string texture, string material) {

        /*
        Unique key identifies shared object type.
        */
        string key =
            to_string(length) + "_" +
            to_string(width) + "_" +
            to_string(weight) + "_" +
            color + "_" + texture + "_" + material;

        /*
        Agar object already cache me hai,
        same return karo.
        */
        if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = new AsteroidFlyweight(
                length, width, weight,
                color, texture, material
            );
        }

        return flyweights[key];
    }
};

// static storage
unordered_map<string, AsteroidFlyweight*> AsteroidFactory::flyweights;


// =====================================================
// 3) CONTEXT (EXTRINSIC STATE)
// =====================================================

/*
Ye actual asteroid instance hai.

Shared type + unique runtime data
*/
class AsteroidContext {
private:
    AsteroidFlyweight* flyweight;

    /*
    Unique per asteroid
    */
    int posX, posY;
    int velocityX, velocityY;

public:
    AsteroidContext(AsteroidFlyweight* fw,
                    int posX, int posY,
                    int velX, int velY) {

        this->flyweight = fw;
        this->posX = posX;
        this->posY = posY;
        this->velocityX = velX;
        this->velocityY = velY;
    }

    /*
    Context shared object ko unique data ke saath call karta hai
    */
    void render() {
        flyweight->render(posX, posY, velocityX, velocityY);
    }
};


// =====================================================
// 4) CLIENT SYSTEM - SPACE GAME
// =====================================================

/*
Ye लाखों asteroid instances manage karta hai.
*/
class SpaceGameWithFlyweight {
private:
    vector<AsteroidContext*> asteroids;

public:
    void spawnAsteroids(int count) {

        /*
        Only 3 shared asteroid types
        */
        vector<string> colors = {"Red", "Blue", "Gray"};
        vector<string> textures = {"Rocky", "Metallic", "Icy"};
        vector<string> materials = {"Iron", "Stone", "Ice"};
        int sizes[] = {25, 35, 45};

        for (int i = 0; i < count; i++) {

            /*
            Reuse 3 types repeatedly
            */
            int type = i % 3;

            AsteroidFlyweight* flyweight =
                AsteroidFactory::getAsteroid(
                    sizes[type],
                    sizes[type],
                    sizes[type] * 10,
                    colors[type],
                    textures[type],
                    materials[type]
                );

            /*
            Unique context created every time
            */
            asteroids.push_back(
                new AsteroidContext(
                    flyweight,
                    100 + i * 50,
                    200 + i * 30,
                    1,
                    2
                )
            );
        }
    }

    void renderAll() {
        for (int i = 0; i < min(5, (int)asteroids.size()); i++) {
            asteroids[i]->render();
        }
    }
};


// =====================================================
// 5) CLIENT
// =====================================================
int main() {

    /*
    Massive scale use case
    */
    const int ASTEROID_COUNT = 1000000;

    SpaceGameWithFlyweight* game =
        new SpaceGameWithFlyweight();

    game->spawnAsteroids(ASTEROID_COUNT);

    /*
    First few render karke pattern samjho
    */
    game->renderAll();

    return 0;
}


/*
=========================================================
FINAL UNDERSTANDING
=========================================================

3 shared flyweights only:
- Red Rocky Iron
- Blue Metallic Stone
- Gray Icy Ice

But:
1,000,000 contexts

Huge memory saved 🔥

This is textbook Flyweight.
=========================================================
*/