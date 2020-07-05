#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))

void query(string op, vector <int> vec) {
    cout << op;
    for (int i = 0; i < SZ(vec); ++i) {
        cout << " " << vec[i];
    }
    cout << "\n";
    cout.flush();
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    query("get_num", {});
    int n; cin >> n;
    vector <int> res;
    auto binaryS = [](int id) {
        int l = 0, r = 1e7;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            query("guess", {id, mid});
            int res = 0; cin >> res;
            if (res == 0) return mid;
            if (res == -1) l = mid + 1;
            else r = mid - 1;
        }
        assert(0);
    };
    for (int i = 0; i < n; ++i) res.push_back(binaryS(i));
    query("submit", res); 
    return 0;
}