#include <bits/stdc++.h>
using namespace std;

#define N 10010
int n, a[N], b[N];
bool isprime(int x) {
    for (int i = 2; 1ll * i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
bool ok(int p) {
    if (a[0] % p) {
        return false;
    }
    for (int i = 0; i <= n; ++i) {
        b[i] = a[i];
    }
    for (int i = n; i >= p - 1; --i) {
        (b[i - (p - 1)] += b[i]) %= p;
        b[i] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        if (b[i] % p) {
            return false;
        }
    }
    return true;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        int G = 0;
        for (int i = 0; i <= n; ++i) {
            scanf("%d", a + i);
            G = gcd(G, abs(a[i]));
        }
        reverse(a, a + 1 + n);
        vector<int> res;
        for (int i = 2; 1ll * i * i <= G; ++i) {
            if (G % i == 0) {
                res.push_back(i);
                while (G % i == 0) {
                    G /= i;
                }
            }
        }
        if (G > 1) {
            res.push_back(G);
        }
        for (int i = 2; i <= n; ++i) {
            if (isprime(i) && ok(i)) {
                res.push_back(i);
            }
        }
        sort(res.begin(), res.end());
        res.erase(unique(res.begin(), res.end()), res.end());
        for (auto it : res) {
            printf("%d\n", it);
        }
        //	puts("------------");
    }
    return 0;
}
