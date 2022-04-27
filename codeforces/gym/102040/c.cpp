#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<ll> vec;
map<ll, int> mp;

int f(ll x) {
    int res = 0;
    for (ll i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            vec.push_back(i);
            res++;
            if (i * i != x) {
                vec.push_back(x / i);
                res++;
            }
        }
    }
    return res;
}

int main() {
    int n;
    while (cin >> n) {
        vec.clear();
        mp.clear();
        ll x = 1;
        for (int i = 1; i <= n; ++i) {
            x *= i;
        }
        int res = 0;
        for (ll i = 1; i * i <= x; ++i) {
            if (x % i == 0) {
                res += f(i);
                if (i * i != x) {
                    res += f(x / i);
                }
            }
        }
        cout << res << endl;
        sort(vec.begin(), vec.end());
        for (auto it : vec) {
            mp[it]++;
        }
        for (auto it : mp) {
            cout << it.first << " " << it.second << endl;
        }
    }
    return 0;
}
