#include <bits/stdc++.h>
using namespace std;

#define N 110
int n;
struct node {
    string name;
    int a, id;
    void scan(int id) {
        this->id = id;
        cin >> name >> a;
    }
    bool operator<(const node &other) const {
        if (name != other.name) {
            return name < other.name;
        }
        return a > other.a;
    }
} arr[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            arr[i].scan(i);
        }
        sort(arr + 1, arr + 1 + n);
        for (int i = 1; i <= n; ++i) {
            cout << arr[i].id << "\n";
        }
    }
    return 0;
}
