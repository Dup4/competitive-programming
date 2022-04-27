#include <bits/stdc++.h>
using namespace std;

int cnt[220];
char s[110];
vector<char> vec;

bool ok(string &s) {
    for (int i = 1, len = (int)s.size(); i < len; ++i) {
        if (abs(s[i] - s[i - 1]) == 1) {
            return false;
        }
    }
    return true;
}

bool work1() {
    int mid = ((int)vec.size() + 1) / 2;
    string res = "";
    for (int i = 0, j = mid, sze = (int)vec.size(); i < mid || j < sze; ++i, ++j) {
        if (j < sze) {
            for (int k = 0; k < cnt[vec[j]]; ++k) {
                res += vec[j];
            }
        }
        if (i < mid) {
            for (int k = 0; k < cnt[vec[i]]; ++k) {
                res += vec[i];
            }
        }
    }
    if (ok(res)) {
        cout << res << "\n";
        return true;
    } else {
        return false;
    }
}

bool work2() {
    int mid = ((int)vec.size() + 1) / 2;
    string res = "";
    for (int i = 0, j = mid, sze = (int)vec.size(); i < mid || j < sze; ++i, ++j) {
        if (i < mid) {
            for (int k = 0; k < cnt[vec[i]]; ++k) {
                res += vec[i];
            }
        }
        if (j < sze) {
            for (int k = 0; k < cnt[vec[j]]; ++k) {
                res += vec[j];
            }
        }
    }
    if (ok(res)) {
        cout << res << "\n";
        return true;
    } else {
        return false;
    }
}

void solve() {
    if (!work1() && !work2()) {
        puts("No answer");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        memset(cnt, 0, sizeof cnt);
        vec.clear();
        for (int i = 1, len = strlen(s + 1); i <= len; ++i) {
            if (cnt[s[i]] == 0) {
                vec.push_back(s[i]);
            }
            ++cnt[s[i]];
        }
        sort(vec.begin(), vec.end());
        solve();
    }
    return 0;
}
