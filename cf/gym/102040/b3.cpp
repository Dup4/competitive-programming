#include <bits/stdc++.h>

using namespace std;

int a[20];

int f(int x) {
    *a = 0;
    while (x) {
        a[++*a] = x % 10;
        x /= 10;
    }
    int res = 0;
    for (int i = 1; i <= *a; ++i) {
        for (int j = i + 1; j <= *a; ++j) {
            res += (a[i] > a[j]);
        }
    }
    return res;
}

int main() {
    int n;
    while (cin >> n) {
        int res = 0;
        for (int i = 1; i <= n; ++i) res += f(i);
        cout << res << endl;
    }
    return 0;
}
