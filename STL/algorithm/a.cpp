#include <bits/stdc++.h>
using namespace std;

int main() {
	vector <int> vec(10), vec2(10);
	iota(vec.begin(), vec.end(), 1);
	iota(vec2.begin(), vec2.end(), 1);

	copy(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "});
	cout << endl;

	

	
//	copy(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "});
//	cout << endl;
//	cout << (*max_element(vec.begin(), vec.end())) << endl;
//	cout << (*min_element(vec.begin(), vec.end())) << endl;


//	copy(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "});
//	cout << endl;
//	copy(vec2.begin(), vec2.end(), ostream_iterator<int>{cout, " "});
//	cout << endl;
//	cout << boolalpha << includes(vec.begin(), vec.end(), vec2.begin(), vec2.end()) << endl;
//	cout << boolalpha << includes(vec2.begin(), vec2.end(), vec.begin(), vec.end()) << endl;	

	//内积
//	cout << inner_product(vec.begin(), vec.end(), vec2.begin(), 0) << endl;


//	adjacent_difference(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "});
//	cout << endl;
//	partial_sum(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "});
//	cout << endl;
//	partial_sum(vec.begin(), vec.end(), vec.begin() + 2);
//	copy(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "});
//	cout << endl;


	return 0;
}
