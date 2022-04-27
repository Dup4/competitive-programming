#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
char s[N];
int n;
map<string, int> f[2];
map<char, string> mp;

int main() {
    mp['Y'] = "QQQ";
    mp['V'] = "QQW";
    mp['G'] = "EQQ";
    mp['C'] = "WWW";
    mp['X'] = "QWW";
    mp['Z'] = "EWW";
    mp['T'] = "EEE";
    mp['F'] = "EEQ";
    mp['D'] = "EEW";
    mp['B'] = "EQW";
    while (scanf("%s", s + 1) != EOF) {
        f[0].clear(), f[1].clear();
        int n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) {
            int p = i & 1;
            if (i > 1 && s[i] == s[i - 1]) {
                f[p] = f[p ^ 1];
                continue;
            }
            f[p].clear();
            string s1 = mp[s[i]];
            //	cout << s1 << endl;
            do {
                if (i == 1) {
                    f[p][s1] = 3;
                    continue;
                }
                f[p][s1] = 1e9;
                for (auto &it : f[p ^ 1]) {
                    string s2 = it.first;
                    //	cout << s1 << " " << s2 << endl;
                    int w = it.second;
                    if (s2[1] == s1[0] && s2[2] == s1[1]) {
                        f[p][s1] = min(f[p][s1], w + 1);
                    } else if (s2[2] == s1[0]) {
                        f[p][s1] = min(f[p][s1], w + 2);
                    } else {
                        f[p][s1] = min(f[p][s1], w + 3);
                    }
                }
            } while (next_permutation(s1.begin(), s1.end()));
        }
        int res = 1e9;
        for (auto &it : f[n & 1]) {
            //	cout << it.first << " " << it.second << endl;
            res = min(res, it.second);
        }
        printf("%d\n", res + n);
    }
    return 0;
}
