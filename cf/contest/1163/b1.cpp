#include <bits/stdc++.h>
using namespace std;

int main() {
    multiset<int> se;
    se.insert(1);
    se.insert(2);
    auto pos = se.rbegin();
    auto x = se.begin();
    cout << *(++x) << endl;
    cout << *(--x) << endl;
    cout << *pos << endl;
    cout << *(--pos) << endl;
    next(pos);
    cout << *pos << endl;
    return 0;
}
