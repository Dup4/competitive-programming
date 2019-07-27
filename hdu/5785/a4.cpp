#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1000005
#define ALP 26
const int p = 1e9 + 7;
template <class T1, class T2>
void add(T1 &x, T2 y) {
	x += y;
	if (x >= p) x -= p;
}
struct PAM{         
	// 每个节点代表一个回文串
    int Next[N][ALP]; // next指针,参照Trie树
    int fail[N];      // fail失配后缀链接
    int num[N];       // 以节点i结尾的回文串个数
	int sum[N];       // 以节点i结尾的回文串的长度和
    int len[N];       // 节点i的回文串长度
    char s[N];         // 存放添加的字符
    int last;         //指向上一个字符所在的节点，方便下一次add
    int n;            // 已添加字符个数
    int p;            // 节点个数
 
    int newnode(int w){ // 初始化节点，w=长度
        for(int i=0;i<ALP;i++)
            Next[p][i] = 0;
        //cnt[p] = 0;
        num[p] = 0;
        len[p] = w;
        return p++;
    }
    void init(){
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1; 		 // 开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }
    int get_fail(int x){ // 和KMP一样，失配后找一个尽量最长的
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }
    bool insert(int c){
		bool F = 0;
        c -= 'a';
        s[++n] = c;
		int cur = get_fail(last);
		if(!Next[cur][c]){
            int now = newnode(len[cur]+2);//新建节点
            fail[now] = Next[get_fail(fail[cur])][c];
            Next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
			sum[now] = 0;
			add(sum[now], sum[fail[now]] + len[now]);
			F = 1;
		}
        last = Next[cur][c];
		return F;
    }
}pam; 
char s[N];
int prenum[N], presum[N];

int main() {
	while (scanf("%s", s + 1) != EOF) {
		pam.init();
		int len = strlen(s + 1);
		for (int i = 1; i <= len; ++i) {
			pam.insert(s[i]);
			prenum[i] = pam.num[pam.last];
			presum[i] = pam.sum[pam.last];
		}
		pam.init();
		ll res = 0;
		for (int i = len; i > 1; --i) {
			pam.insert(s[i]);
			int sufnum = pam.num[pam.last];
			int sufsum = pam.sum[pam.last];
			add(res, 1ll * prenum[i - 1] * sufnum % p * i % p * i % p);
			add(res, (1ll * sufsum * prenum[i - 1] % p - 1ll * prenum[i - 1] % p * sufnum % p - 1ll * sufnum * presum[i - 1] % p + p) % p * i % p);
			add(res, p - 1ll * presum[i - 1] * sufsum % p);
			add(res, 1ll * presum[i - 1] * sufnum % p);
		}
		printf("%lld\n", res);
	}
	return 0;
}
