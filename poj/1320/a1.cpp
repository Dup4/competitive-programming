#include <cstdio>
#include <iostream>
using namespace std;
#define ll long long
ll x[20], y[20];

int main() {
    ll d = 8;
    x[0] = 3, y[0] = 1;
    for (int i = 1; i <= 10; ++i) {
        x[i] = x[0] * x[i - 1] + d * y[0] * y[i - 1];
        y[i] = y[0] * x[i - 1] + x[0] * y[i - 1];
        ll a = (x[i] - 1) / 2, b = y[i];
        printf("%10lld%10lld\n", b, a);
    }
    return 0;
}
