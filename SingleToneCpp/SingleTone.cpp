#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;  // Pointer to the single instance
    static std::mutex mutex;     // Mutex for thread safety

    // Private constructor to prevent instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

    // Delete copy constructor and assignment operator to prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Static method to get the instance of the Singleton
    static Singleton* getInstance() {
        if (instance == nullptr) {
            // Lock to ensure thread-safe access
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }

    // Example method
    void displayMessage() {
        std::cout << "Singleton instance in action!\n";
    }

    // Destructor
    ~Singleton() {
        std::cout << "Singleton instance destroyed.\n";
    }
};

// Initialize static members
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

int main() {
    // Get the singleton instance and call a method
    Singleton* s1 = Singleton::getInstance();
    s1->displayMessage();

    // Demonstrating that multiple calls return the same instance
    Singleton* s2 = Singleton::getInstance();
    if (s1 == s2) {
        std::cout << "Both pointers point to the same instance.\n";
    }

    return 0;
}


/*  Explanation
Private Constructor: Prevents direct instantiation of the class.
Static Instance Pointer: Holds the single instance of the class.
Thread Safety: Ensured with a std::mutex and double-checked locking to avoid race conditions.
Global Access: The getInstance() method provides access to the singleton instance.
Deleted Copy Constructor and Assignment Operator: Prevents copying of the singleton instance.

OUTPUT
Singleton instance created.
Singleton instance in action!
Both pointers point to the same instance.

Notes
Thread Safety: The std::mutex ensures that the instance is created safely in a multithreaded environment.
Lazy Initialization: The instance is created only when it's first accessed.
Destructor: In practical use cases, you may need to ensure proper clean-up of the singleton instance, especially in dynamically managed resources. */