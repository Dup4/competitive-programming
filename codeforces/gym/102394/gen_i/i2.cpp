#include <bits/stdc++.h>

using namespace std;

const int p = 1e9 + 7;
const int N = 1e5 + 10;

int n;
int h[N];
vector<int> vec;

bool ok() {
    int f = vec[0], g = vec[0];
    for (int i = 0; i < n; ++i) {
        f = max(f, vec[i]);
        g = min(g, vec[i]);
        if (f - g != h[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        vec.clear();
        for (int i = 0; i < n; ++i) {
            vec.push_back(i);
        }
        int res = 0;
        do {
            if (ok()) {
                res = (res + 1) % p;
            }
        } while (next_permutation(vec.begin(), vec.end()));
        cout << res << endl;
    }
    return 0;
}
