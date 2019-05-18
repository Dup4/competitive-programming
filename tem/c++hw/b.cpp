#include <iostream>
#include <string>
#include <vector>
using namespace std;
void Print(int n) {
    cout << n * n << ",";
}
class MyPrint {
public:
    void operator()(const string & s) {
	cout << s << ",";
    }
};

template <class InputIterator, class Function>
void my_for_each(InputIterator l, InputIterator r, Function f) {
	for (; l != r; ++l) {
		f(*l);
	}
}

int main() {
    int t;
    int a[5];
    vector<string> vt;
    cin >> t;
    while(t--) {
	vt.clear();
	for(int i = 0;i < 5; ++i)
	    cin >> a[i];
	for(int i = 0;i < 5; ++i) {
	    string s;
	    cin >> s;
	    vt.push_back(s);
        }
	my_for_each(a, a + 5, Print);
	cout << endl;
	my_for_each(vt.begin(), vt.end(), MyPrint());
	cout << endl;
    }	
    return 0;
}
