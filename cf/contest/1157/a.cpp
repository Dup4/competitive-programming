#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        mp.clear();
        mp[n] = 1;
        int x = n, res = 1;
        while (1) {
            ++x;
            while (x % 10 == 0) {
                x /= 10;
            }
            if (mp.find(x) != mp.end()) {
                break;
            }
            ++res;
            mp[x] = 1;
        }
        printf("%d\n", res);
    }
    return 0;
}
