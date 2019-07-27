#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 2010010
const ll p = 1e9 + 7;
char s[N];
int len;
ll inv2 = 5e8 + 4;
void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
	else if (x < 0) x += p;
}
struct Manacher {  
	int len, l;       //原串的字符串长度和扩展后的字符串长度
	char Ma[N << 1];  //扩展后的字符串
	int Mp[N << 1];   //以i为回文中心的最长回文半径
	//S[0][i]表示以i结尾的所有回文串的左端点下标和
	//S[1][i]表示以i开头的所有回文串的右端点下标和
	ll S[2][N << 1], delta[2][N << 1];  
	void init(int len) {
		this->len = len;
	}
	void work(char *s) {
		l = 0;
		Ma[l++] = '$';
		Ma[l++] = '#';
		for (int i = 0; i < len; ++i) {
			Ma[l++] = s[i];
			Ma[l++] = '#';
		}
		Ma[l] = 0;
		int mx = 0, id = 0;
		for (int i = 0; i < l; ++i) {
			Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
			while (Ma[i + Mp[i]] == Ma[i - Mp[i]]) Mp[i]++;
			if (i + Mp[i] > mx) {
				mx = i + Mp[i];
				id = i;
			}
		}
	//	for (int i = 0; i < l; ++i) printf("%c ", Ma[i]); puts("");
	//	for (int i = 0; i < l; ++i) printf("%d ", Mp[i]); puts("");
	}
	void update() {
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < l; ++j)
				S[i][j] = delta[i][j] = 0;
		for (int i = 2; i < l; ++i) {
			int l = i - Mp[i] + 1;
			int r = i + Mp[i] - 1;
			//区间加等差数列
			add(S[0][l], r);
			add(S[0][i + 1], -i);
			add(delta[0][l + 1], -1);
			add(delta[0][i + 1], 1);
			add(S[1][i], i);
			add(S[1][r + 1], -l);
			add(delta[1][i + 1], -1);
			add(delta[1][r + 1], 1);
		}
		for (int i = 0; i < 2; ++i) {
			for (int j = 2; j < l; ++j) {
				add(delta[i][j], delta[i][j - 1]);
				add(S[i][j], S[i][j - 1]);
				add(S[i][j], delta[i][j]);
			}
		}
	}
	void solve() {
		ll res = 0;
		for (int i = 2; i < l - 2; i += 2) {
			add(res, (S[1][i] * inv2 % p) * (S[0][i + 2] * inv2 % p) % p);
		}
		printf("%lld\n", res); 
	}
}man;

int main() {
	while (scanf("%s", s) != EOF) {
		len = strlen(s);
		man.init(len); man.work(s); 
		man.update(); man.solve();  	
	}
	return 0;
}
