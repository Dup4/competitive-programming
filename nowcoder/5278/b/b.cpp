#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using db = double;

const db eps = 1e-8;

int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    else
        return x > 0 ? 1 : -1;
}

const int N = 1e5 + 10;

struct node {
    int date;
    int stu;
    db t;

    void input() {
        scanf("%d %d %lf", &date, &stu, &t);
    }
    void output() {
        printf("%8d %8d %.1f\n", date, stu, t);
    }

    bool operator<(const node& other) const {
        if (date != other.date) {
            return date > other.date;
        }
        if (sgn(t - other.t)) {
            return t > other.t;
        }
        return stu < other.stu;
    }
} a[N];

int n;

int main() {
    scanf("%d", &n);
    vector<node> vec;
    for (int i = 1; i <= n; ++i) {
        a[i].input();
        if (a[i].t >= 38) {
            vec.push_back(a[i]);
        }
    }
    sort(vec.begin(), vec.end());
    printf("%d\n", vec.size());
    for (auto it : vec) {
        it.output();
    }
    return 0;
}
