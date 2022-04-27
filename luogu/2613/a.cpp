#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10010
char s[N];
const ll p = 19260817;

ll get(char *s) {
    int len = strlen(s + 1);
    ll res = 0;
    for (int i = 1; i <= len; ++i) res = (res * 10 + s[i] - '0') % p;
    return res;
}

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

int main() {
    while (scanf("%s", s + 1) != EOF) {
        ll a = get(s);
        scanf("%s", s + 1);
        ll b = get(s);
        if (__gcd(b, p) != 1)
            puts("Angry!");
        else {
            printf("%lld\n", a * qmod(b, p - 2) % p);
        }
    }
    return 0;
}
