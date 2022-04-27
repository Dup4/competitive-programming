#include <bits/stdc++.h>
#define forto(i, a, b) for (int i = (a); i <= (b); i++)
#define fordown(i, a, b) for (int i = (a); i >= (b); i--)
#define MP make_pair
#define PB push_back
using namespace std;
typedef double D;
typedef complex<D> P;
#define X real()
#define Y imag()
const D eps = 1e-8;
int dcmp(D x) {
    return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;
}

D sqr(D x) {
    return x * x;
}
D dis(P a, P b) {
    return abs(a - b);
}

D cross(P a, P b) {
    return a.X * b.Y - a.Y * b.X;
}
D cross(P a, P b, P c) {
    return cross(b - a, c - a);
}
D dot(P a, P b) {
    return a.X * b.X + a.Y * b.Y;
}
D dot(P a, P b, P c) {
    return dot(b - a, c - a);
}

struct line {
    P s, t;
    line(P s = P(), P t = P()) : s(s), t(t) {}
};

D len(P p) {
    return norm(p);
}
P dir(line ln) {
    return ln.t - ln.s;
}
D pos(P p, line ln) {
    return dot(p - ln.s, dir(ln)) / len(dir(ln));
}

D unionarea(vector<P> p[], int n) {
    D res = 0;
    for (int i = 0; i < n; ++i)
        for (size_t ii = 0; ii < p[i].size(); ++ii) {
            P A = p[i][ii], B = p[i][(ii + 1) % p[i].size()];
            line AB = line(A, B);
            vector<pair<double, int> > c;
            for (int j = 0; j < n; ++j)
                if (i != j)
                    for (size_t jj = 0; jj < p[j].size(); ++jj) {
                        P C = p[j][jj], D = p[j][(jj + 1) % p[j].size()];
                        line CD = line(C, D);
                        int f1 = dcmp(cross(A, B, C));
                        int f2 = dcmp(cross(A, B, D));
                        if (!f1 && !f2) {
                            if (i < j && dcmp(dot(dir(AB), dir(CD))) > 0) {
                                c.PB(MP(pos(C, AB), 1));
                                c.PB(MP(pos(D, AB), -1));
                            }
                            continue;
                        }
                        double s1 = cross(C, D, A);
                        double s2 = cross(C, D, B);
                        double t = s1 / (s1 - s2);
                        if (f1 >= 0 && f2 < 0)
                            c.PB(MP(t, 1));
                        if (f1 < 0 && f2 >= 0)
                            c.PB(MP(t, -1));
                    }
            c.PB(MP(0.0, 0));
            c.PB(MP(1.0, 0));
            sort(c.begin(), c.end());
            double s = 0.5 * cross(A, B), z = min(max((double)c[0].second, 0.0), 1.0);
            for (int j = 1, k = c[0].second; j < c.size(); ++j) {
                D w = min(max(c[j].first, 0.0), 1.0);
                if (k == 0)
                    res += s * (w - z);
                k += c[j].second;
                z = w;
            }
        }
    return res;
}

D get(vector<P> a) {
    D sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        P A = a[i], B = a[(i + 1) % a.size()];
        sum += cross(A, B);
    }
    return abs(sum / 2.0);
}

const int N = 150;
vector<P> a[N];

int main() {
    int x[4], y[4];
    while (scanf("%d%d%d%d", x, y, x + 1, y + 1) != EOF) {
        scanf("%d%d%d%d", x + 2, y + 2, x + 3, y + 3);
        a[1].clear();
        a[2].clear();
        a[1].PB(P(x[0], y[0]));
        a[1].PB(P(x[0], y[1]));
        a[1].PB(P(x[1], y[0]));
        a[2].PB(P(x[2], y[2]));
        a[2].PB(P(x[2], y[3]));
        a[2].PB(P(x[3], y[3]));
        a[2].PB(P(x[3], y[2]));
        if (dcmp(cross(a[1][0], a[1][1], a[1][2])) > 0)
            reverse(a[1].begin(), a[1].end());
        double All = get(a[1]) + get(a[2]);
        printf("%.10f\n", All - abs(unionarea(a + 1, 2)));
    }
    return 0;
}
