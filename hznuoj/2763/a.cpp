#include <bits/stdc++.h>
using namespace std;
string mp[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        long long x;
        cin >> x;
        if (x <= 9)
            cout << mp[x] << endl;
        else
            cout << "oh my god!\n";
    }
    return 0;
}
