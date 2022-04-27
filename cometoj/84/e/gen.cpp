#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));

int main() {
    int n = 5;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        cout << rnd() % 10 + 1 << " \n"[i == n];
    }
}
