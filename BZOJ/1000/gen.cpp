#include <bits/stdc++.h>
using namespace std;
mt19937 rd(time(0));
inline int random(int l, int r) {
    return rd() % (r - l + 1) + l;
}
int main() {
    cout << rd() << " " << rd() << endl;
    return 0;
}
