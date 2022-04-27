
#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;

int main() {
    mp.clear();
    int x;
    while (cin >> x, x) {
        ++mp[x];
    }
    for (auto it : mp) {
        cout << it.first << ": " << it.second << endl;
    }
    return 0;
}
