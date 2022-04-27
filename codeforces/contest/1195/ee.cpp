#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> se;
    for (int i = 1; i <= 10; ++i) se.insert(i);
    cout << *se.begin() << endl;
    return 0;
}
