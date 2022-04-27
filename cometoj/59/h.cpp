#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n;
ll a[N];
vector<vector<ll>> vec;

ll f(vector<ll> &vec) {
    int sze = (int)vec.size();
    if (sze <= 1)
        return 1;
    ll Max = vec[0] + sze - 1;
    ll res = 1;
    for (int i = sze - 1; i >= 0; --i) {
        res = res * (Max - vec[i] + 1 - (sze - 1 - i)) % p;
    }
    return res;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        sort(a + 1, a + 1 + n);
        vec.clear();
        vector<ll> tmp;
        ll last = a[1];
        for (int i = 1; i <= n; ++i) {
            if (a[i] > last) {
                vec.push_back(tmp);
                tmp.clear();
                last = a[i];
            } else {
                last = last + 1;
            }
            tmp.push_back(a[i]);
        }
        if (!tmp.empty())
            vec.push_back(tmp);
        ll res = 1;
        for (auto it : vec) {
            res = res * f(it) % p;
        }
        printf("%lld\n", res);
    }
    return 0;
}
