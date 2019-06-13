#include <iostream>
using namespace std;

class A{
public :
	virtual void fun() {
		cout << "Call class A's fun";
	}
	void g() {
		fun();
	}
	A() {
		cout << "A constructor";
		g();
	}
	virtual ~A() {
		cout << "A destructor";
	}
};
class B : public A{
public :
	B() {
		cout << "B constructor";
	}
	~B() {
		cout << "B destructor";
	}
};
class C : public B{
public :
	C() {
		cout << "C constructor";
	}
	~C() {
		cout << "C destructor";
	}
	void fun() {
		cout << "Call class C's fun";
	}
};

int main() {  
    A *a = new C;
    a->g();
    delete a;
    return 0;
}
