#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using namespace std;
using db = long long;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
}
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
// head
const db eps = 1e-10;
const db PI = acos(-1.0);
int sgn(db x) {
    if (x == 0)
        return 0;
    return x < 0 ? -1 : 1;
}
int n;
db S;

struct Point {
    db x, y;
    Point(db x = 0, db y = 0) : x(x), y(y) {}
    void scan() {
        rd(x, y);
    }
    void print() {
        pt(x, y);
    }
    bool operator==(const Point &b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator<(const Point &b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    Point operator*(const db &b) const {
        return Point(x * b, y * b);
    }
    Point operator/(const db &b) const {
        return Point(x / b, y / b);
    }
    db operator^(const Point &b) const {
        return x * b.y - y * b.x;
    }
    db operator*(const Point &b) const {
        return x * b.x + y * b.y;
    }
    db len() {
        return norm(complex<db>(x, y));
    }
    db len2() {
        return x * x + y * y;
    }
    db dis(Point b) {
        return norm(complex<db>(x - b.x, y - b.y));
    }
    db dis2(Point b) {
        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
    }
    int quad() {
        int _x = sgn(x), _y = sgn(y);
        if (_x > 0 && _y >= 0)
            return 1;
        if (_x <= 0 && _y > 0)
            return 2;
        if (_x < 0 && _y <= 0)
            return 3;
        if (_x >= 0 && _y < 0)
            return 4;
    }
    //求PA和PB构成的夹角 lightOJ 1203
    db getRad(Point a, Point b) {
        Point p = *this;
        return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
    }
    //单位法向量
    Point normal() {
        return Point(-y, x) / len();
    }
    //化为长度为r的向量
    Point trunc(db r) {
        db l = len();
        if (!sgn(l))
            return *this;
        r /= l;
        return Point(x * r, y * r);
    }
    //逆时针旋转90度
    Point rotleft() {
        return Point(-y, x);
    }
    //顺时针旋转90度
    Point rotright() {
        return Point(y, -x);
    }
    //绕点p旋转rad弧度
    Point rotate(Point p, db rad) {
        Point v = (*this) - p;
        db c = cos(rad), s = sin(rad);
        return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
};

namespace minTriangle {
struct E {
    int a, b;
    double slop;
    bool operator<(const E &other) const {
        return slop < other.slop;
    }
};
inline db area(Point a, Point b, Point c) {
    return abs((b - a) ^ (c - a));
}
void gao(vector<Point> &p) {
    int n = p.size();
    sort(p.begin(), p.end());
    vector<E> vec;
    // rk[i]表示排名为i的点的标号
    // pos[i]表示点i的排名
    vector<int> rk(n), pos(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            vec.push_back({i, j, atan2((p[j].y - p[i].y), (p[j].x - p[i].x))});
        }
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; ++i) rk[i] = pos[i] = i;
    for (int i = 0; i < (int)vec.size(); ++i) {
        int a = vec[i].a, b = vec[i].b;
        if (pos[a] > pos[b])
            swap(a, b);
        if (pos[a] > 0) {
            int l = 0, r = pos[a] - 1, res = 0;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (area(p[a], p[b], p[rk[mid]]) >= S) {
                    res = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if (area(p[a], p[b], p[rk[res]]) == S) {
                pt("Yes");
                p[a].print();
                p[b].print();
                p[rk[res]].print();
                return;
            }
        }
        if (pos[b] < n - 1) {
            int l = pos[b] + 1, r = n - 1, res = n - 1;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (area(p[a], p[b], p[rk[mid]]) >= S) {
                    res = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (area(p[a], p[b], p[rk[res]]) == S) {
                pt("Yes");
                p[a].print();
                p[b].print();
                p[rk[res]].print();
                return;
            }
        }
        swap(pos[a], pos[b]);
        swap(rk[pos[a]], rk[pos[b]]);
    }
    pt("No");
}
}  // namespace minTriangle

void run() {
    S <<= 1;
    vector<Point> vec(n);
    for (auto &it : vec) it.scan();
    minTriangle::gao(vec);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> S) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
