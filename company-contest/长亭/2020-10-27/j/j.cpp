#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 10
char s[N];

    base64_list = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                   'K', 'L', 'M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 
                   'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 
                   'e', 'f','g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                   'o', 'p', 'q', 'r', 's', 't', 'u', 'v','w', 'x', 
                   'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', 
                   '8', '9', '+', '/']

map <char, int> mp, _mp;

void init() {
    int t = 0;
    mp.clear();
    for (int i = 'A'; i <= 'Z'; ++i) mp[i] = t++;   
    for (int i = 'a'; i <= 'z'; ++i) mp[i] = t++;
    for (int i = '0'; i <= '9'; ++i) mp[i] = t++;
    mp['+'] = t++;
    mp['/'] = t++;
    t = 0;
    for (int i = '0'; i <= '9'; ++i) _mp[i] = t++;
    for (int i = 'A'; i <= 'Z'; ++i) _mp[i] = t++;
}

int num2bit(int ch) {
    string t = "";
    for (int i = 5; i >= 0; --i) {
        t += ((ch >> i) & 1) + '0';
    }
    return t;
}

int main() {
    init();
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    string _s = "";
    for (int i = 1; i <= len; ++i) {
        if (s[i] == '=') break;
        _s += num2bit(mp[s[i]]); 
    }
    while (!s.empty() && s.back() != '0') s.pop_back();
    if (s.empty()) puts("0");
    else {

    }
    return 0;
}