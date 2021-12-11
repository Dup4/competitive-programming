#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define ll long long
constexpr int N = 1e5 + 10;
int n, a, b;
int c[N];
ll rd() {
    ll x;
    scanf("%lld", &x);
    return x;
}

bool check() {
    n = rd(), a = rd(), b = rd();
    swap(a, b);
    for (int i = 1; i <= n; i++) {
        c[i] = i;
    }
    if (abs(a - b) > 1)
        return 0;
    if (a + b > n - 2)
        return 0;
    if (a > b) {
        for (int i = 1, j = 1; j <= a; i += 2, j++) {
            swap(c[i], c[i + 1]);
        }
    } else if (a < b) {
        for (int i = n, j = 1; j <= b; j++, i -= 2) {
            swap(c[i], c[i - 1]);
        }
    } else {
        for (int i = 2, j = 1; j <= b; i += 2, j++) {
            swap(c[i], c[i + 1]);
        }
    }
    for (int i = 2; i < n; i++) {
        a -= c[i] > c[i - 1] && c[i] > c[i + 1];
        b -= c[i] < c[i - 1] && c[i] < c[i + 1];
    }
    return a + b == 0;
}

int main() {
    int t = rd();
    while (t--) {
        if (check()) {
            for (int i = 1; i <= n; i++) {
                printf("%d%c", c[i], i == n ? '\n' : ' ');
            }
        } else {
            puts("-1");
        }
    }
    return 0;
}