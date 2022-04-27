#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <int N>
struct DET {
    ll a[N + 1][N + 1];
    DET() {}
    ll* operator[](int x) {
        return a[x];
    }
    ll calc() {
        ll res = 0;
        vector<int> vec;
        for (int i = 1; i <= N; ++i) vec.push_back(i);
        do {
            ll t = 1;
            for (int i = 0; i < N; ++i) {
                t *= a[i + 1][vec[i]];
                for (int j = 0; j < i; ++j) {
                    if (vec[j] > vec[i])
                        t *= -1;
                }
            }
            res += t;
        } while (next_permutation(vec.begin(), vec.end()));
        return res;
    }
};

ll a[4][4] = {
        6,
        5,
        -1,
        -3,
        3,
        0,
        6,
        7,
        4,
        -5,
        7,
        8,
        4,
        3,
        9,
        1,
};

int main() {
    DET<4> det;
    int l, r;
    cin >> l >> r;
    ll res = 1e18;
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            det[i][j] = a[i - 1][j - 1];
        }
    }
    for (int i = l; i <= r; ++i) {
        det[2][2] = i;
        res = min(res, det.calc());
    }
    cout << res << endl;
    return 0;
}
