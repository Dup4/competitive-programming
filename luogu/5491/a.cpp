#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
mt19937 rd(time(NULL));
struct Square_Remind {
    ll w;
    struct num {
        ll x, y;
    };
    inline num mul(num a, num b, ll p) {
        num ans = {0, 0};
        ans.x = ((a.x * b.x % p + a.y * b.y % p * w % p) % p + p) % p;
        ans.y = ((a.x * b.y % p + a.y * b.x % p) % p + p) % p;
        return ans;
    }
    inline ll qpow(ll base, ll n, ll p) {
        ll ans = 1;
        while (n) {
            if (n & 1)
                ans = ans * base % p;
            base = base * base % p;
            n >>= 1;
        }
        return ans;
    }
    inline ll qpow(num base, ll n, ll p) {
        num ans = {1, 0};
        while (n) {
            if (n & 1)
                ans = mul(ans, base, p);
            base = mul(base, base, p);
            n >>= 1;
        }
        return ans.x % p;
    }
    // x^2 = n % p
    inline ll gao(ll n, ll p) {
        n %= p;
        n = (n + p) % p;
        if (!n)
            return 0;
        if (p == 2)
            return n;
        if (qpow(n, (p - 1) / 2, p) == p - 1)
            return -1;
        ll a;
        while (1) {
            a = rd() % p;
            w = ((a * a % p - n) % p + p) % p;
            if (qpow(w, (p - 1) / 2, p) == p - 1)
                break;
        }
        num x = {a, 1};
        return qpow(x, (p + 1) / 2, p);
    }
} square_remind;

int main() {
    ll n, p;
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%lld%lld", &n, &p);
        ll ans = square_remind.gao(n, p);
        if (ans == -1)
            puts("Hola!");
        else {
            ll ans2 = (p - ans) % p;
            if (ans > ans2)
                swap(ans, ans2);
            if (ans == ans2)
                printf("%lld\n", ans);
            else
                printf("%lld %lld\n", ans, ans2);
        }
    }
    return 0;
}
