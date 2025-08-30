#include <bits/stdc++.h>

using namespace std;

// Overload operator<< for std::pair to teach cout how to print it.
template <typename K, typename V>
ostream &operator<<(ostream &os, const pair<K, V> &p)
{
	os << p.first << ":" << p.second;
	return os;
}

template <typename T, typename Container>
void printAdapter(stack<T, Container> s) // Pass by value to print without modifying original
{
	cout << "stack: ";
	while (!s.empty()) {
		cout << s.top() << " / ";
		s.pop();
	}
	cout << endl;
}

template <typename T, typename Container>
void printAdapter(queue<T, Container> q) // Pass by value to print without modifying original
{
	cout << "queue: ";
	while (!q.empty()) {
		cout << q.front() << " <= ";
		q.pop();
	}
	cout << endl;
}

// Generic printer for std::priority_queue (non-destructive)
template <typename T, typename Container, typename Compare>
void printAdapter(priority_queue<T, Container, Compare> pq) // Pass by value
{
	cout << "priority_queue (popped order): ";
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

template <typename Container>
void printContainer(const Container &container)
{

	for (const auto &element : container)
	{
		cout << element << ", ";
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////

 /**
  * vector is backed by contiguous memory array that gets resized and elements
  * need to be moved for all insert/erase operations
  */
void vector_expt()
{
	cout << "\n--- vector ---\n";
	vector<int> vec = {1, 2, 3, 4, 5};	  // assign using vector of initializer list
	vector<int> vec2{1, 1, 0, 0, 0};	  // alternate initializer list
	vector<int> vec3(5);			  // 5 elements default initialized (0 for int)
	vector<int> vec4(10, 42);		  // 10 elements initialized to 42
	vector<int> vec5(vec.begin(), vec.end()); // range constructor
	vector<int> vec6(vec2);			  // copy constructor
	int *ptr = vec.data();

	vec[0] = 10;
	vec.at(1) = 20; // at() does extra bounds check
	// vec.at(100) = 100;	// Throws out_of_range exception

	vec.front() = 30; // first element
	vec.back() = 40;  // last element
	vec.push_back(99);
	vec.pop_back();

	vec.reserve(10);
	printContainer(vec); // 30, 20, 3, 4, 40,
	cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;
	// Size: 5, Capacity: 10

	vec.resize(15, 999);
	vec.insert(vec.begin(), 0);
	vec.insert(vec.begin() + 3, 10, -1);
	vec.insert(vec.end(), {7, 8, 9});

	auto match = find(vec.begin(), vec.end(), 3);
	if (match != vec.end())
	{
		*match = 33;
	}

	vec.erase(vec.end() - 2);
	vec.erase(vec.begin() + 10, vec.begin() + 15); // erase range
	printContainer(vec);
	// 0, 30, 20, -1, -1, -1, -1, -1, -1, -1, 40, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 7, 9, 

	vec.clear();			      // clear all elements
	vec.assign(vec2.begin(), vec2.end()); // assign from another vector

	auto itr = remove(vec.begin(), vec.end(), 0); // move all 0s to the end
	vec.erase(itr, vec.end());		      // actually remove them from the vector

	reverse(vec.begin(), vec.end());
	sort(vec.begin(), vec.end());
	printContainer(vec);

	// Different ways to iterate through the vector
	for (int i = 0; i < vec.size(); i++)
		vec[i] += 0; // index-based for loop
	for (auto val : vec)
		val += 0; // range-based for loop
	for (auto &val : vec)
		val += 0; // range-based for loop with reference
	for (auto it = vec.begin(); it != vec.end(); it++)
		*it += 0; // iterator
	for (auto it = vec.rbegin(); it != vec.rend(); it++)
		*it += 0; // reverse iterator
	int sum = 0;
	for (auto it = vec.cbegin(); it != vec.cend(); it++)
		sum += *it; // const iterator, cannot modify elements

	// All containers support above methods of iterations with following exceptions:
	// * index access NOT allowed for list, set, map (and variations)
	// * range-based for loop NOT allowed for sets and maps
	// * reverse iterators NOT allowed for forward_list, unordered_set, unordered_map
	// * const iterators NOT allowed for forward_list, unordered_set, unordered_map
}



/**
 * deque (double-ended queue) is backed by collection of fixed-size arrays (chunks).
 * random access is slightly slower, insertion/deletion at either end is fast
 * O(1) modifications at either end, references to front/end stay valid after modification
 */
void deque_expt()
{
	cout << "\n--- deque ---\n";
        deque<int> deq{1,2,3,4,5};

        // deque does NOT support reserve() capacity() or data()

	deq.push_front(-1);
	deq.pop_front();
	printContainer(deq);

	// Here the reference to the first element is saved and used later
	int &first_elem_ref = deq.front();
	first_elem_ref = 999;
	for (int i = 0; i < 20; ++i)
		deq.push_front(0);

	cout << "reference is valid after many modifications " << first_elem_ref << endl;
	cout << "vector refences get invalidated as part of modifications" << endl;
	// Only front/back references stay valid. middle references can get invalidated like vector
	printContainer(deq);

}

/**
 * list is a doubly-linked list. Each element is a separate allocation.
 * insertion/deletion at any place is O(1) but random access is O(N)
 * All itertors stay valid after modifications
 * dedicated sort, merge, splice, unique implementation which is better than global algo
 */
void list_expt()
{
	cout << "\n--- list ---\n";
	list<int> lst{1, 2, 3, 4, 5};

	// lst[2] = 0;  // No random access. This would be ERROR
	// auto it = lst.begin() + 2; // Also ERROR. Only it++ and it-- allowed

	// Move iterators by looping with next function
	auto it = next(lst.begin(), 2);
	cout << *it << endl;
	lst.insert(it, 99); // Adds before the iterator
	printContainer(lst);

	lst.push_front(0);
	lst.push_back(6);
	cout << "Iterator is still valid: " << *it << endl;

	list<int> other_list{100, 200};
	lst.splice(it, other_list);
	lst.sort(); // Must use this way to sort. global sort does not work
	lst.remove(2); // better than erase-remove idom
	printContainer(lst);
	printContainer(other_list); // empty now
}

 /**
 * forward_list is singly-linked list. Almost same as list but with some limitations
 * All insertions/deletions are "after" an iterator. This requires special handling with a "before" iterator to modify the list.
 * Forward iterators only (only `++it` is supported).
 */
void forward_list_expt()
{
	cout << "\n--- forward_list ---\n";
	forward_list<int> flist{2, 3, 4, 5};

	flist.push_front(1);
	flist.push_front(0);
	flist.pop_front();
	printContainer(flist);

	// does NOT support size() capacity() push_back()
	// cout << flist.size(); // compilation ERROR
	// flist.push_back(5);   // compilation ERROR

	// use prev element iterator to erase current element
	auto it = next(flist.begin(), 2);
	cout << "to be deleted: " << *next(it) << endl;
	flist.erase_after(it);
	forward_list<int> other_flist{100, 200};
	flist.splice_after(it, other_flist);
	printContainer(flist);
}



/**
 * std::set: Stores unique, sorted keys.
 * std::map: Stores unique, sorted key-value pairs sorted by keys.
 * Implemented as balanced binary search trees (e.g., Red-Black Trees).
 * Operations like insert, erase, find are O(log N).
 */
void setmap_expt()
{
	cout << "\n--- set ---\n";
	set<int> set{5, 3, 8, 1, 3, 8}; // Duplicates are ignored, elements are sorted

	set.insert(4);
	set.erase(set.find(3));
	printContainer(set);

	cout << "\n--- unordered_set ---\n";
	unordered_set<int> uset{5, 3, 8, 1, 3, 8};
	printContainer(uset);


	cout << "\n--- map ---\n";
	map<string, int> ages{{"trump", 72}, {"modi", 70}, {"yogi", 60}};

	ages["Bob"] = 25; // Inserts or updates
	ages["Alice"] = 30;
	ages.insert({"Charlie", 40});
	ages["Alice"] = 99;  // overrides the value
	ages.insert({"Charlie", 90});  //fails becasue Charlie exists (no update)
	printContainer(ages);

	cout << "\n--- unordered_map ---\n";
	unordered_map<string, int> colors{{"white", 100}, {"green", 70}, {"red", 50}};
	colors.rehash(10);
	printContainer(colors);

	cout << "\n--- multi_map ---\n";
	multimap<string, string> phonebook{
		{"Alice", "555-1234"}, {"Bob", "555-8765"},
		{"Alice", "555-3333"}, {"Charlie", "555-4321"},
	};
	printContainer(phonebook);

	// [] operator is NOT allowed on multimap
	// cout << phonebook["Alice"]    // this is compile ERROR
	cout << "Search results for Alice:-" << endl;
	auto match = phonebook.equal_range("Alice");
	for (auto it = match.first; it != match.second; it++)
		cout << "    " << it->first << ": " << it->second << endl;



	// iterating over map (and variants) uses key/value like following
	int sum = 0;
	// iterator manipulation
	for (auto it = ages.begin(); it != ages.end(); it++)
		sum +=  it->first.size() + it->second;

  	// range based iterator
  	for (const auto &pair : ages)
		sum +=  pair.first.size() + pair.second;

		// range based iterator with structure bindings
	for (const auto &[key, value] : ages)
		sum +=  key.size() + value;
}

/**
 * 
 */
void string_expt()
{
	cout << "\n--- string ---\n";
	string s1 = "hello";
	string s2("world", 3); // "wor"
	string s3(5, '!');     // "!!!!!"
	cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << endl;
	cout << "s1 length: " << s1.length() << endl;

	string sentence = s1 + " " + "world";
	sentence.append("!!!");
	cout << "Concatenated: " << sentence << endl;

	sentence.push_back('?');
	sentence.pop_back(); // Removes the '?'

	string sub = sentence.substr(6, 5); // "world"
	cout << "Substring: " << sub << endl;

	size_t pos = sentence.find("world");
	if (pos != string::npos) {
		cout << "'world' found at position: " << pos << endl;
	}

	sentence.replace(pos, 5, "C++");
	
	cout << "After replace: " << sentence << endl;

	sentence.erase(0, 6); // erase "hello "
	cout << "After erase: " << sentence << endl;

	string num_str = "123.45";
	int i_val = stoi(num_str);
	double d_val = stod(num_str);
	cout << "stoi: " << i_val << ", stod: " << d_val << endl;
	cout << "to_string: " << to_string(987) << endl;
}

/**
 * Container adapters provide a specific interface by wrapping an underlying container.
 * - stack: LIFO (Last-In, First-Out). Default underlying container is deque.
 * - queue: FIFO (First-In, First-Out). Default underlying container is deque.
 * - priority_queue: Elements are ordered by priority (max-heap by default). Default is vector.
 */
void adapters_expt()
{
	cout << "\n--- stack ---\n";
	stack<int> s;			// Must start empty, no init list
	bool before = s.empty();	// true
	s.push(1);			// push() instead of push_back()
	s.push(2);
	s.push(3);
	bool after = s.empty();		// false
	int top_val = s.top();		// this does not really pop it

	printAdapter(s);
	while (!s.empty())
		s.pop();
	printAdapter(s);

	cout << "\n--- queue ---\n";
	queue<int> q;			// Must start empty, no init list
	q.push(10);			// push() instead of push_back()
	q.push(20);
	q.push(30);

	int head = q.front();		// this does not really pop it
	int tail = q.back();		// equivalant of stack's top()
	printAdapter(q);
	while (!q.empty())
		q.pop();
	printAdapter(q);

	cout << "\n--- priority_queue max heap ---\n";
	priority_queue<int> max_pq;	// must start empty, no init list
	for(int n : {30, 100, 25, 50, 75})
		max_pq.push(n);
	printAdapter(max_pq);

	cout << "\n--- priority_queue min heap ---\n";
	priority_queue<int, vector<int>, greater<int>> min_pq;
	for(int n : {30, 100, 25, 50, 75})
		min_pq.push(n);
	printAdapter(min_pq);
}


void pair_expt()
{
	cout << "\n--- pair ---\n";
	pair<int, string> p = {1, "one"};
	cout << "  Pair: " << p.first << ", " << p.second << endl;

	tuple<int, double, string> t = {2, 2.0, "two"};
	cout << "  Tuple: " << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << endl;
	auto& [i, d, s] = t; // Structured binding (C++17)
	s = "TWO";

}

////////////////////////////////////////////////////////////////////////////////

/*
 * Here are some useful global methods from std namespace:
 * - find(begin, end, value) - returns iterator to first occurrence of value, or end if not found
 * - remove(begin, end, value) - moves all occurrences of value to the end, returns iterator to new end
 * - reverse(begin, end) - reverses the elements in the range
 * - sort(begin, end) - sorts the elements in the range
 * - unique(begin, end) - removes consecutive duplicates, returns iterator to new end
 * - lower_bound(begin, end, value) - returns iterator to first element not less than value
 * - upper_bound(begin, end, value) - returns iterator to first element greater than value
 * - binary_search(begin, end, value) - checks if value exists in the sorted range
 * - accumulate(begin, end, initial_value) - computes the sum of elements in the range
 * - count(begin, end, value) - counts occurrences of value in the range
 * - for_each(begin, end, func) - applies func to each element in the range
 * - transform(begin, end, output_begin, func) - applies func to each element and stores result in output
 * - adjacent_find(begin, end) - finds first pair of adjacent elements that are equal
 * - partition(begin, end, predicate) - rearranges elements so that those satisfying predicate come first
 * - is_sorted(begin, end) - checks if the range is sorted
 * - next_permutation(begin, end) - generates the next lexicographical permutation of the range
 * - prev_permutation(begin, end) - generates the previous lexicographical permutation of the range
 * - nth_element(begin, end, n) - rearranges elements so that the nth element is in its sorted position
 * - merge(begin1, end1, begin2, end2, output_begin) - merges two sorted ranges into one sorted range
 * - includes(begin1, end1, begin2, end2) - checks if the first range includes all elements of the second range
 * - equal_range(begin, end, value) - returns a pair of iterators representing the range of elements equal to value
 * - random_shuffle(begin, end) - randomly shuffles the elements in the range
 * - shuffle(begin, end, rng) - randomly shuffles the elements in the range using a random number generator
 * - partition_point(begin, end, predicate) - returns iterator to the first element satisfying predicate
 * - is_heap(begin, end) - checks if the range satisfies the heap property
 * - make_heap(begin, end) - transforms the range into a heap
 * - push_heap(begin, end) - adds an element to the heap
 * - pop_heap(begin, end) - removes the largest element from the heap
 * - sort_heap(begin, end) - sorts the elements in the heap
 * - stable_sort(begin, end) - sorts the elements while preserving the relative order of equal elements
 * - partial_sort(begin, end, middle) - partially sorts the range so that the first middle elements are sorted
 * - partial_sort_copy(begin1, end1, begin2, end2) - copies and partially sorts elements from one range to another
 * - is_sorted_until(begin, end) - returns iterator to the first element that breaks the sorted order
 * - stable_partition(begin, end, predicate) - rearranges elements so that those satisfying predicate come first while preserving relative order
 * - is_partitioned(begin, end, predicate) - checks if the range is partitioned according to the predicate
 * - rotate(begin, middle, end) - rotates the elements in the range
 * - rotate_copy(begin, middle, end, output_begin) - copies and rotates the elements in the range
 * - shift_left(begin, end, n) - shifts elements to the left by n positions
 * - shift_right(begin, end, n) - shifts elements to the right by n positions
 * - is_heap_until(begin, end) - returns iterator to the first element that breaks the heap property
 */
void algo_expt() {
	cout << "\n--- <algorithm> examples ---\n";

	vector<int> v = {5, 2, 8, 1, 9, 5, 4};

	auto it_find = find(v.begin(), v.end(), 8);
	if (it_find != v.end()) {
		cout << " found 8 at index: " << distance(v.begin(), it_find) << endl;
	}

	int fives = count(v.begin(), v.end(), 5);
	cout << " count of 5s: " << fives << endl;

	bool has_even = any_of(v.begin(), v.end(), [](int i){ return i % 2 == 0; });
	cout << " any even numbers? " << boolalpha << has_even << endl;

	sort(v.begin(), v.end());
	cout << "after sorting:- ";
	printContainer(v);

	bool found_binary = binary_search(v.begin(), v.end(), 4);
	cout << " binary search result: " << boolalpha << found_binary << endl;

	rotate(v.begin(), v.begin() + 2, v.end());
	cout << "after roation: ";
	printContainer(v);

	// Use a random device for a better shuffle
	random_device rd;
	mt19937 g(rd());
	shuffle(v.begin(), v.end(), g);
	cout << "after shiffling: ";
	printContainer(v);

	// --- Partitioning ---
	cout << "\n--- Partitioning ---\n";
	auto partition_point_it = partition(v.begin(), v.end(), [](int i){ return i < 5; });
	cout << "Partitioned (< 5): ";
	printContainer(v);
	cout << "Partition point is at index: " << distance(v.begin(), partition_point_it) << endl;

	// --- Numeric operations ---
	cout << "\n--- Numeric algorithms ---\n";
	int sum = accumulate(v.begin(), v.end(), 0);
	cout << "Sum of elements: " << sum << endl;

	vector<int> squares(v.size());
	transform(v.begin(), v.end(), squares.begin(), [](int i){ return i * i; });
	cout << "Squares of elements: ";
	printContainer(squares);

	vector<int> iota_vec(5);
	iota(iota_vec.begin(), iota_vec.end(), 10);
	cout << "Vector from iota(10): ";
	printContainer(iota_vec);
}

int main()
{
	vector_expt();
	deque_expt();
	list_expt();
	forward_list_expt();
	setmap_expt();
	adapters_expt();
	string_expt();
	pair_expt();
	algo_expt();

	cout << endl << endl;
}
