#include <bits/stdc++.h>

using namespace std;

template <typename T>
void print_vec(string name, vector<T> v)
{
	cout << "  [" << name << "] size=" << v.size() << ", capacity=" << v.capacity() << ", content={";
	for (auto x : v)
	{
		cout << x << ", ";
	}
	cout << "}" << endl;
};

#define PRINT_VEC(name) print_vec(#name, name)

int vector_expt()
{
	vector<int> def;
	vector<int> fill(5, 20);
	vector<int> ilist{2, 7, -3, 54, 7};
	vector<int> copy = ilist;
	vector<int> move = fill;

	fill[0] = 99;
	ilist[0] = 9999;
	PRINT_VEC(def);
	PRINT_VEC(fill);
	PRINT_VEC(ilist);
	PRINT_VEC(copy);
	PRINT_VEC(move);

	auto a = ilist;
	for (int i = 0; i < a.size(); i++)
	{
		cout << i << ", " << a[i] << endl;
	}

	for (auto i = a.begin(); i != a.end(); i++)
	{
		cout << *i << endl;
	}

	PRINT_VEC(a);
	a.insert(a.begin() + 3, 12);
	PRINT_VEC(a);
	a.insert(a.begin() + 3, 5, -1);
	a.erase(a.end() - 1);
	PRINT_VEC(a);
	a.insert(a.end(), fill.begin(), fill.end());
	PRINT_VEC(a);

	auto i = lower_bound(a.begin(), a.end(), 61);
	sort(a.begin(), a.end());
	PRINT_VEC(a);

	sort(a.begin(), a.end(), [](int x, int y)
		 { return abs(x) < abs(y); });
	PRINT_VEC(a);

	vector<string> s1{"asd", "trump", "elon", "transitor", "vitamin", "cache"};
	print_vec("s1", s1);

	return 0;
}

int main()
{
	string s = "abcdefghig";
	cout << "hello C++ STL" << endl;
	cout << s.substr(3, 4) << endl;

	vector_expt();
	return 0;
}