#include <iostream>
#include <stdexcept>
using namespace std;


#include <cmath>
#include <cstdio>
#define ll long long
class Rational {
public :
	// a 分子 b 分母
	ll a, b;
	ll gcd(ll a, ll b) {
		return b ? gcd(b, a % b) : a;
	}
	void sim() {
		ll G = gcd(abs(a), abs(b)); 
		a /= G;
		b /= G;
		if (a == 0) {
			b = 1;
		}
	}
	Rational(ll a = 0, ll b = 1) {
		this->a = a;
		this->b = b;
		sim();
	}
	int compare(Rational &other) {
		sim(); other.sim();
		ll x = a * other.b;
		ll y = b * other.a;
		if (x > y) {
			return 1;
		} else if (x == y) {
			return 0;
		} else {
			return -1;
		}
	}
	ll getNumerator() {
		return a;
	}
	ll getDenominator() {  
		return b;
	}
	Rational operator + (Rational &other) {
		sim(); other.sim();
		Rational res = Rational();
		res.a = a * other.b + other.a * b;
		res.b = b * other.b;
		res.sim();
		return res;
	}
	Rational &operator += (Rational &other) {
		sim(); other.sim();
		a = a * other.b + other.a * b;
		b = b * other.b;
		sim();
		return *this;
	}
	Rational operator - (Rational &other) {
		sim(); other.sim();
		Rational res = Rational();
		res.a = a * other.b - other.a * b;
		res.b = b * other.b;
		res.sim();
		return res;
	}
	Rational operator * (Rational &other) {
		sim(); other.sim();
		Rational res = Rational();
		res.a = a * other.a;
		res.b = b * other.b;
		res.sim();
		return res;
	}
    Rational operator / (Rational &other) {
		sim(); other.sim();
		Rational res = Rational();
		res.a = a * other.b;
		res.b = b * other.a;
		res.sim();
		return res;
	}
	void inc() {
		a += b;
		sim();
	}
	//前置++
	Rational &operator++() {
		inc();
		return *this;
	}
	//后置++
	Rational &operator ++(int) {
		Rational temp = *this;
		inc();
		return temp; 
	}
	bool operator < (Rational &other) {
		return compare(other) == -1;
	}
	bool operator <= (Rational &other) {
		return compare(other) <= 0;
	}
	bool operator > (Rational &other) {
		return compare(other) == 1;
	}
	bool operator >= (Rational &other) {
		return compare(other) >= 0;
	}
	bool operator == (Rational &other) {
		return compare(other) == 0;
	}
	bool operator != (Rational &other) {
		return compare(other) != 0;
	}
	friend istream &operator >> (istream &in, Rational &x) {
		in >> x.a >> x.b;
		return in;
	}
	friend ostream &operator << (ostream &out, Rational &x) {
		x.sim();
		if (x.b == 1) {
			out << x.a;
		} else {
			out << x.a << "/" << x.b;
		}
		return out;
	}
	bool equals(Rational &other) {
		sim(); other.sim();
		return a == other.a && b == other.b;
	}	
	operator double()  {
		return a * 1.0 / b;
	} 
};


int main() {
    Rational a, b;
    cin >> a;
    cin >> b;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << a << "+" << b << "=" << a + b << endl;
    cout << a << "-" << b << "=" << a - b << endl;
    cout << a << "*" << b << "=" << a * b << endl;
    cout << a << "/" << b << "=" << a / b << endl;
    cout << boolalpha << a << "<" << b << "=" << (a < b) << endl;
    cout << boolalpha << a << ">" << b << "=" << (a > b) << endl;
    cout << boolalpha << a << "==" << b << "=" << (a == b) << endl;
    cout << boolalpha << a << "!=" << b << "=" << (a != b) << endl;
    Rational c(1, 2);
    cout << "c=" << c << endl;
    cout << 2.5 << "+" << c << "=" << (2.5 + c) << endl;
    cout << ++c << endl;
    cout << c << endl;
    cout << c++ << endl;
    cout << c << endl;
    cout << (c += b) << endl;
    return 0;
}
