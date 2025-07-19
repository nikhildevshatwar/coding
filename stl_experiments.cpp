#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

int main() {
    // 1. Constructors
    std::vector<int> vec1; // Default constructor: empty vector
    std::cout << "vec1 size: " << vec1.size() << ", capacity: " << vec1.capacity() << std::endl;

    std::vector<int> vec2(5, 100); // 5 elements, all initialized to 100
    std::cout << "vec2: ";
    for (int x : vec2) std::cout << x << " ";
    std::cout << std::endl;

    std::vector<int> vec3 = {1, 2, 3, 4, 5}; // Initializer list constructor (C++11)
    std::cout << "vec3: ";
    for (const auto& x : vec3) std::cout << x << " ";
    std::cout << std::endl;

    std::vector<int> vec4(vec3.begin(), vec3.end()); // Range constructor
    std::cout << "vec4 (copy of vec3): ";
    for (const auto& x : vec4) std::cout << x << " ";
    std::cout << std::endl;

    // 2. Modifiers
    vec1.push_back(10); // Add elements to the end
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.emplace_back(40); // C++11: construct in-place, generally preferred over push_back for complex objects

    std::cout << "vec1 after pushes: ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;

    vec1.pop_back(); // Remove last element (40)
    std::cout << "vec1 after pop_back: ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;

    vec1.insert(vec1.begin() + 1, 15); // Insert 15 at index 1 (after 10)
    std::cout << "vec1 after insert 15: ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;

    vec1.insert(vec1.begin() + 3, 2, 25); // Insert two 25s at index 3
    std::cout << "vec1 after insert two 25s: ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;

    vec1.erase(vec1.begin() + 2); // Erase element at index 2 (the first 25)
    std::cout << "vec1 after erase at index 2: ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;

    vec1.erase(vec1.begin(), vec1.begin() + 2); // Erase first two elements (10, 15)
    std::cout << "vec1 after erasing first two: ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;

    vec1.resize(2); // Resize to 2 elements, remaining elements are truncated
    std::cout << "vec1 after resize to 2: ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;

    vec1.resize(5, 99); // Resize to 5 elements, new elements initialized to 99
    std::cout << "vec1 after resize to 5 (fill 99): ";
    for (int x : vec1) std::cout << x << " ";
    std::cout << std::endl;

    vec1.clear(); // Clear all elements
    std::cout << "vec1 after clear: size=" << vec1.size() << ", empty=" << vec1.empty() << std::endl;

    // 3. Element Access
    std::vector<int> access_vec = {10, 20, 30, 40, 50};
    std::cout << "Element at index 0: " << access_vec[0] << std::endl; // No bounds check
    std::cout << "Element at index 1 (at): " << access_vec.at(1) << std::endl; // Bounds check

    try {
        std::cout << access_vec.at(10) << std::endl; // This will throw std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cerr << "Error accessing out of bounds: " << e.what() << std::endl;
    }

    std::cout << "First element: " << access_vec.front() << std::endl;
    std::cout << "Last element: " << access_vec.back() << std::endl;
    std::cout << "Raw data pointer (first element): " << *access_vec.data() << std::endl;

    // 4. Capacity
    std::cout << "access_vec size: " << access_vec.size() << ", capacity: " << access_vec.capacity() << std::endl;
    access_vec.reserve(100); // Reserve space for 100 elements
    std::cout << "access_vec after reserve(100): size=" << access_vec.size() << ", capacity=" << access_vec.capacity() << std::endl;
    access_vec.shrink_to_fit(); // Reduce capacity to current size
    std::cout << "access_vec after shrink_to_fit: size=" << access_vec.size() << ", capacity=" << access_vec.capacity() << std::endl;

    // 5. Iterators and Algorithms
    std::vector<int> iter_vec = {5, 2, 8, 1, 9, 4};
    std::cout << "iter_vec (original): ";
    for (auto it = iter_vec.begin(); it != iter_vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::sort(iter_vec.begin(), iter_vec.end()); // Sort using std::sort
    std::cout << "iter_vec (sorted): ";
    for (const auto& x : iter_vec) { // Range-based for loop for iteration
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cout << "iter_vec (reverse iteration): ";
    for (auto rit = iter_vec.rbegin(); rit != iter_vec.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    return 0;
}
