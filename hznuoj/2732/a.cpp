#include <bits/stdc++.h>
using namespace std;
#define all(A) A.begin(), A.end()
int main() {
    int n;
    cin >> n;
    vector<int> A, B;
    for (int i = 1, x; i <= n; ++i) {
        scanf("%d", &x);
        x > 0 ? A.push_back(x) : B.push_back(x);
    }
    B.size() % 2 == 0 ? (A.empty() ? cout << *min_element(all(B)) : cout << *min_element(all(A)))
                      : cout << *max_element(all(B));
    cout << endl;
    return 0;
}
