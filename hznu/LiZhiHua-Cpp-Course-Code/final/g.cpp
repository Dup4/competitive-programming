#include <iostream>
using namespace std;

#include <cmath>
#include <cstdio>
#define ll long long
class Rational {
public:
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
    ll getNumerator() {
        return a;
    }
    ll getDenominator() {
        return b;
    }
    Rational add(Rational &other) {
        sim();
        other.sim();
        Rational res = Rational();
        res.a = a * other.b + other.a * b;
        res.b = b * other.b;
        res.sim();
        return res;
    }
    Rational subtract(Rational &other) {
        sim();
        other.sim();
        Rational res = Rational();
        res.a = a * other.b - other.a * b;
        res.b = b * other.b;
        res.sim();
        return res;
    }
    Rational multiply(Rational &other) {
        sim();
        other.sim();
        Rational res = Rational();
        res.a = a * other.a;
        res.b = b * other.b;
        res.sim();
        return res;
    }
    Rational divide(Rational &other) {
        sim();
        other.sim();
        Rational res = Rational();
        res.a = a * other.b;
        res.b = b * other.a;
        res.sim();
        return res;
    }
    bool equals(Rational &other) {
        sim();
        other.sim();
        return a == other.a && b == other.b;
    }
    double doubleValue() {
        sim();
        return a * 1.0 / b;
    }
    void print() {
        sim();
        if (!b) {
            cout << "Inf\n";
        } else if (b == 1) {
            cout << a << endl;
        } else {
            cout << a << "/" << b << endl;
        }
    }
};

int main() {
    int x, y;
    char ignore;
    cin >> x >> ignore >> y;
    Rational a(x, y);
    cin >> x >> ignore >> y;
    Rational b(x, y);
    Rational c;
    a.print();
    b.print();
    c = a.add(b);
    c.print();
    c = a.subtract(b);
    c.print();
    c = a.multiply(b);
    c.print();
    c = a.divide(b);
    c.print();
    cout << (a.equals(b) ? "a==b" : "a!=b") << endl;
    cout << b.doubleValue() << endl;
    return 0;
}
