#include <bits/stdc++.h>
using namespace std;
using pSS = pair<string, string>;
#define all(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
#define fi first
#define se second
#define endl "\n"

bool isPunc(char ch) {
    return !isdigit(ch) && !isalpha(ch) && ch != ' ';
}

bool match(string &s, int l, int r, string &t) {
    if (SZ(t) != r - l + 1 || l < 0 || r >= SZ(s)) return false;
    for (int i = l, j = 0; i <= r; ++i, ++j) {
        if (s[i] != t[j]) return false;
    }
    return true;
}

string trim(string &s) {
    while (s.end()[-1] == ' ') s.pop_back();
    reverse(all(s));
    while (s.end()[-1] == ' ') s.pop_back();
    reverse(all(s));
    return s;
}

string delSpace(string &s) {
    string res = "";
    int num = 0;
    for (int i = 0; i < SZ(s); ++i) {
        if (s[i] == ' ') {
            ++num;
        } else {
            if (num && !isPunc(s[i])) res += " ";
            res += s[i];
            num = 0;
        }
    }
    return res;
}

string toLower(string &s) {
    for (int i = 0; i < SZ(s); ++i) {
        if (isupper(s[i]) && s[i] != 'I') {
            s[i] = s[i] - 'A' + 'a';
        }
    }
    return s;
}

string change(string &s, vector<pSS> vec) {
    string res = "";
    for (int i = -1; i < SZ(s); ++i) {
        if (i == -1 || isPunc(s[i]) || s[i] == ' ') {
            int ok = 0;
            for (auto &it : vec) {
                int len = SZ(it.fi);
                if (match(s, i + 1, i + len, it.fi) && (i + len + 1 == SZ(s) || isPunc(s[i + len + 1]) || s[i + len + 1] == ' ')) {
                    if (i != -1) res += s[i];
                    res += it.se;
                    i += len;
                    ok = 1;
                    break;
                }
            }
            if (ok) continue;
        }
        if (i != -1) res += s[i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int _T; cin >> _T;
    string s;
    getline(cin, s);
    while (_T--) {
        getline(cin, s);
        cout << s << endl;
        s = trim(s);
        s = delSpace(s);
        s = toLower(s);
        s = change(s, vector<pSS>({pSS("can you", "@ can"), pSS("could you", "@ could")}));
        s = change(s, vector<pSS>({pSS("I", "you"), pSS("me", "you")}));
        for (int i = 0; i < SZ(s); ++i) {
            if (s[i] == '?') s[i] = '!';
            if (s[i] == '@') s[i] = 'I';
        }
        cout << "AI: " + s << endl;
    }
    return 0;
}