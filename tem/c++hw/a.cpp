#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
string f[N]; 
int cnt;
map <string, int> mp;
ll last[N]; 
ll tot[N];
int getid(string s) {
	if (mp.find(s) == mp.end()) {
		mp[s] = ++cnt;
		f[cnt] = s;
	}
	return mp[s];
}
int getTime(string y, string t) {
	int mon[] = {
		0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	};
    int M = 0, D = 0, H = 0, I = 0, S = 0;
	int i = 0, len = y.size();
	for (; i < len; ++i) {
		if (y[i] == '/') {
			++i;
			break;
		}
	}	
	for (; i < len; ++i) {
		if (y[i] == '/') {
			++i;
			break;
		}
		M = M * 10 + y[i] - '0';
	}
	for (; i < len; ++i) {
		D = D * 10 + y[i] - '0';
	}
	i = 0, len = t.size();
	for (; i < len; ++i) {
		if (t[i] == ':') {
			++i;
			break; 
		}
		H = H * 10 + t[i] - '0';
	}
	for (; i < len; ++i) {
		if (t[i] == ':') {
			++i;
			break;
		}
		I = I * 10 + t[i] - '0';
	}
	for (; i < len; ++i) {
		S = S * 10 + t[i] - '0';
	}
	ll tot = 0;
	tot = H * 3600 + I * 60 + S;
	for (int i = 1; i < M; ++i) {
		tot += mon[i] * 86400;
	}
	tot += (D - 1) * 86400;
	//cout << M << " " << D << " " << H << " " << I << " " << S << endl;
	return tot;
}

int main() {
	ifstream in("log.txt");
	ofstream out("times.txt");	
	mp.clear(); cnt = 0; 
	string y, t, name, sta;
	while (in >> y >> t >> name >> sta) {
		//cout << y << " " << t << " " << name << " " << sta << endl;
		int Time = getTime(y, t);
		int id = getid(name);
		if (sta == "LOGIN") {
			last[id] = Time;
		} else {
			tot[id] += Time - last[id];
		}

	}
	for (int i = 1; i <= cnt; ++i) {
		out << f[i] << " " << tot[i] << endl;
	}
	return 0;
}
