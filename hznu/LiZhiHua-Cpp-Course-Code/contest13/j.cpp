#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    while (cin >> s >> t) {
        char Max = 0;
        for (auto it : s) {
            Max = max(Max, it);
        }
        for (auto i : s) {
            cout << i;
            if (i == Max) {
                cout << t;
            }
        }
        cout << "\n";
    }
    return 0;
}
