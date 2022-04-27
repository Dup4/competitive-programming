#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> vec;
    vec.resize(n);
    for (auto &it : vec) cin >> it;
    sort(vec.begin(), vec.end());
    cout << *vec.begin() << "\n";
    return 0;
}
