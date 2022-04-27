#include <bits/stdc++.h>
using namespace std;

#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 1e5 + 10;
ll n, m;
int q;
ll sx, sy, ex, ey, id1, id2;
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
void run() {
    ll G = gcd(n, m);
    n /= G;
    m /= G;
    while (q--) {
        cin >> sx >> sy >> ex >> ey;
        id1 = (sy - 1) / (sx == 1 ? n : m);
        id2 = (ey - 1) / (ex == 1 ? n : m);
        cout << (id1 == id2 ? "YES" : "NO") << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n >> m >> q) run();
    return 0;
}
