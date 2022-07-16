#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll l = 0;
ll r = 9999999999;

string get(ll x) {
    if (x == 0) {
        return "00";
    }

    auto gen = [](ll x) {
        string s = "";

        for (int i = 0; i < 10; i++) {
            int y = x % 10;

            s += string(y, char('0' + (i + 1)));

            x /= 10;
        }

        return s;
    };

    auto s = gen(x);
    auto t = gen(r - x);
    t += "0";

    if (s.length() <= t.length()) {
        return s;
    } else {
        return t;
    }
}

ll fGet(string s) {
    if (s == "00") {
        return 0;
    }

    ll base[] = {
            1,
            10,
            100,
            1000,
            10000,
            100000,
            1000000,
            10000000,
            100000000,
            1000000000,
    };

    bool has_zero = false;

    sort(s.begin(), s.end());

    ll x = 0;

    for (const auto& c : s) {
        if (c == '0') {
            has_zero = true;
        } else {
            x += base[c - '1'];
        }
    }

    if (has_zero) {
        x = r - x;
    }

    return x;
}

void gaoAlice() {
    ll x = 0;
    cin >> x;

    string s = get(x);
    cout << s << endl;
}

void gaoBob() {
    std::string s;
    cin >> s;

    cout << fGet(s) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s = "";
    cin >> s;

    if (s == "Alice") {
        gaoAlice();
    } else if (s == "Bob") {
        gaoBob();
    }

    return 0;
}
