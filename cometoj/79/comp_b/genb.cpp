#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));

int main() {
    int n = 2000, m = 1000000001;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        cout << rnd() % m << " " << rnd() % m << endl;
    }
    return 0;
}
