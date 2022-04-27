#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))
#define mkp make_pair
const int N = 4e5 + 10;
int n;
char s[N];
int cnt[320];

void gao(int k) {
    cout << k << "\n";
    vector<string> pre(k, ""), mid(k, "");
    vector<char> DB;
    if ((n / k) % 2) {
        vector<char> single;
        for (int i = 1; i < 255; ++i) {
            if (cnt[i] & 1) {
                single.push_back(char(i));
                --cnt[i];
            }
        }
        for (int i = 1; i < 255; ++i) {
            while (cnt[i] > 0 && SZ(single) + 2 <= k) {
                cnt[i] -= 2;
                single.push_back(char(i));
                single.push_back(char(i));
            }
        }
        for (int i = 0; i < k; ++i) {
            mid[i] += single.back();
            single.pop_back();
        }
    }
    for (int i = 1; i < 255; ++i) {
        assert(cnt[i] % 2 == 0);
        while (cnt[i] >= 2) {
            cnt[i] -= 2;
            DB.push_back(char(i));
        }
    }
    for (int i = 0; i < k; ++i) {
        while (SZ(pre[i]) * 2 + SZ(mid[i]) + 2 <= n / k) {
            pre[i] += char(DB.back());
            DB.pop_back();
        }
    }
    for (int i = 0; i < k; ++i) {
        assert(SZ(pre[i]) + SZ(mid[i]) + SZ(pre[i]) == n / k);
        if (SZ(pre[i]))
            cout << pre[i];
        if (SZ(mid[i]))
            cout << mid[i];
        if (SZ(pre[i])) {
            reverse(pre[i].begin(), pre[i].end());
            cout << pre[i];
        }
        cout << " \n"[i == k - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(cnt, 0, sizeof cnt);
    cin >> n >> (s + 1);
    for (int i = 1; i <= n; ++i) {
        assert(int(s[i]) <= 255);
        ++cnt[int(s[i])];
    }
    int a = 0;
    for (int i = 1; i < 255; ++i)
        if (cnt[i] & 1)
            ++a;
    for (int i = 1; i <= n; ++i)
        if (n % i == 0) {
            if (i == n) {
                gao(i);
                break;
            }
            if (a == 0 && (n / i) % 2 == 0) {
                gao(i);
                break;
            }
            if (a > 0 && i >= a && (i - a) % 2 == 0 && ((n / i) - 1) % 2 == 0) {
                gao(i);
                break;
            }
        }
    return 0;
}
