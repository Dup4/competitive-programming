#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll a, b, c;

ll DFS(int cur, int a, int b, int c) {
    if (cur > 7) {
        cur = 1;
    }
    if (cur == 1 || cur == 4 || cur == 7) {
        if (a > 0) {
            return 1 + DFS(cur + 1, a - 1, b, c);
        } else {
            return 0;
        }
    } else if (cur == 2 || cur == 6) {
        if (b > 0) {
            return 1 + DFS(cur + 1, a, b - 1, c);
        } else {
            return 0;
        }
    } else {
        if (c > 0) {
            return 1 + DFS(cur + 1, a, b, c - 1);
        } else {
            return 0;
        }
    }
}

int main() {
    while (scanf("%lld%lld%lld", &a, &b, &c) != EOF) {
        ll t = min(a / 3, min(b / 2, c / 2));
        ll res = t * 7;
        a -= t * 3;
        b -= t * 2;
        c -= t * 2;
        ll Max = 0;
        for (int i = 1; i <= 7; ++i) {
            Max = max(Max, DFS(i, a, b, c));
        }
        printf("%lld\n", res + Max);
    }
    return 0;
}
