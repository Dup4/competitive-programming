#include <bits/stdc++.h>
using namespace std;

class GeneralException {
	public:
		virtual void print() {
			cout << "G" << endl;
		}
};
class SpecialException : public GeneralException {
	public:
		void print() {
			cout << "S" << endl;
		}
};
void f() {
	throw SpecialException();
}
int main() {
	try {
		f();
	} catch (GeneralException e) {
		e.print();
	}
	return 0;
}
