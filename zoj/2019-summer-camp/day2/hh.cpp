#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll getcnt(ll x) {
    ll res = 0;
    while (x) {
        res += x % 2;
        x /= 2;
    }
    return res;
}

int main() {
    vector<ll> vec;
    for (int i = 1; i <= 1000000; ++i) {
        if (getcnt(i) & 1)
            vec.push_back(i);
    }
    int T;
    cin >> T;
    ll n;
    while (T--) {
        cin >> n;
        cout << vec[n - 1] << endl;
    }
}
