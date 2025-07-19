#include <vector>
#include <string>
#include <iostream>

struct MyClass {
    std::string name;
    MyClass(const std::string& n) : name(n) {
        std::cout << "MyClass Constructor: " << name << std::endl;
    }
    MyClass(const MyClass& other) : name(other.name) {
        std::cout << "MyClass Copy Constructor: " << name << std::endl;
    }
    MyClass(MyClass&& other) noexcept : name(std::move(other.name)) {
        std::cout << "MyClass Move Constructor: " << name << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass Destructor: " << name << std::endl;
    }
};

int main() {
    std::vector<MyClass> vec;

    std::cout << "--- Using push_back with lvalue ---" << std::endl;
    MyClass obj1("Alice"); // Constructor called
    vec.push_back(obj1);   // Copy Constructor called (obj1 already exists)
    std::cout << "Vector size: " << vec.size() << std::endl;

    std::cout << "\n--- Using push_back with rvalue (temporary) ---" << std::endl;
    vec.push_back(MyClass("Bob")); // Constructor called (for temporary), then Move Constructor
                                  // then Destructor (for temporary)
    std::cout << "Vector size: " << vec.size() << std::endl;

    // Output will also show destructors when vec goes out of scope
    return 0;
}
