#include <bits/stdc++.h>
using namespace std;

class Base {
public :
	virtual ~Base();
};
Base::~Base() {
	cout << "Base";
}
class Derived: public Base {
	public :
		virtual ~Derived();
};
Derived::~Derived() {
	cout << "Derived";
}
void fun(Base *b) {
	delete b;
}
int main() {
	Base *b = new Derived();
	fun(b);
	return 0;
}
