#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = double;
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
constexpr int N = 1e5 + 10;

const db eps = 1e-10;
const db PI = acos(-1.0L);
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}

struct Point2 {
    db x, y;
    Point2(db x = 0, db y = 0) : x(x), y(y) {}
    bool operator<(const Point2 &b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    Point2 operator+(const Point2 &b) const {
        return Point2(x + b.x, y + b.y);
    }
    Point2 operator-(const Point2 &b) const {
        return Point2(x - b.x, y - b.y);
    }
    Point2 operator*(const db &b) const {
        return Point2(x * b, y * b);
    }
    Point2 operator/(const db &b) const {
        return Point2(x / b, y / b);
    }
    db operator^(const Point2 &b) const {
        return x * b.y - y * b.x;
    }
    db operator*(const Point2 &b) const {
        return x * b.x + y * b.y;
    }
    db len() {
        return hypot(x, y);
    }
    db dis(Point2 b) {
        return hypot(x - b.x, y - b.y);
    }
};

struct Line2 {
    Point2 s, e;
    Line2() {}
    Line2(Point2 s, Point2 e) : s(s), e(e) {}
    db length() {
        return s.dis(e);
    }
    //点到直线的距离
    db disPoint2ToLine2(Point2 p) {
        return fabs((p - s) ^ (e - s)) / length();
    }
    //点到线段的距离
    db disPoint2ToSeg(Point2 p) {
        if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e)) < 0)
            return min(p.dis(s), p.dis(e));
        return disPoint2ToLine2(p);
    }
};

class Solution {
public:
    /**
     * @param position: the position of circle A,B and point P.
     * @return: if two circle intersect return 1, otherwise -1.
     */
    int IfIntersect(vector<double> &position) {
        // write your code here
        db xa = position[0];
        db ya = position[1];
        db ra = position[2];
        db xb = position[3];
        db yb = position[4];
        db rb = position[5];
        db xp = position[6];
        db yp = position[7];
        Point2 A = Point2(xa, ya);
        Point2 B = Point2(xb, yb);
        Point2 P = Point2(xp, yp);
        Line2 l = Line2(A, P);
        //	dbg(l.disPoint2ToSeg(B), ra + rb);
        if (sgn(l.disPoint2ToSeg(B) - ra - rb) <= 0)
            return 1;
        return -1;
    }
};

void run() {
    vector<double> vec(8);
    for (auto &it : vec) rd(it);
    pt((new Solution())->IfIntersect(vec));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = 1;
    // nextInt();
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
