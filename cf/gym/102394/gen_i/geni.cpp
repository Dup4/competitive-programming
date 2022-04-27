#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(time(NULL));

int main() {
    int T = 10;
    cout << T << endl;
    while (T--) {
        int n = rnd() % 10 + 1;
        cout << n << endl;
        vector<int> vec;
        for (int i = 0; i < n; ++i) {
            vec.push_back(rnd() % n);
        }
        sort(vec.begin(), vec.end());
        for (int i = 0; i < n; ++i) {
            cout << vec[i] << " \n"[i == n - 1];
        }
    }
    return 0;
}
