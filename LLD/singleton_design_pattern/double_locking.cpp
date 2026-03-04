#include<iostream>
#include <mutex>

using namespace std;

class Singleton {
private:
    // Static pointer that will hold the single instance
    static Singleton* instance;

    // Mutex for thread-safety
    static mutex mtx;

    // Private constructor prevents object creation from outside
    Singleton() { 
        cout << "Singleton Constructor Called!" << endl; 
    }
 
public:
    // Static method to provide global access
    static Singleton* getInstance() {

        // First check (without locking)
        // This avoids locking every time after instance is created
        if (instance == nullptr) {  

            // Lock only if instance not created
            lock_guard<mutex> lock(mtx);

            // Second check (important!)
            // Another thread might have created instance 
            // while current thread was waiting for lock
            if (instance == nullptr) {  
                instance = new Singleton();
            }
        }

        return instance;
    }
};
 
// Static member initialization
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {

    // Both calls return same object
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    // Prints 1 (true)
    cout << (s1 == s2) << endl;
}