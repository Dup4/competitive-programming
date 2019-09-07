#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
#define ALP 26
#define pii pair <int, int>
#define fi first
#define se second
int n, p[N], pre[110];
char s[N];
struct PAM{   
	//每个节点代表一个本质不同的回文串
	struct node {
		int Next[ALP];
		int fail;
		//以节点i最后一个字符结尾的回文串个数
		//节点i表示的回文串的长度
		//节点i表示的回文串在整串中的出现次数
		//以节点i最后一个字符结尾的回文串的长度和
		int num, len, cnt, sum;
		node(int _len = 0) {
			memset(Next, 0, sizeof Next);
			fail = 0;
			num = cnt = sum = 0;
			len = _len;
		}
	}t[N];	
    //存放添加的字符
	int s[N];         // 存放添加的字符
    //指向添加最后一个字符后的节点
	int last;         
    //已添加字符个数
	int n;            
    //节点个数
	int p;            
 
    int newnode(int len){ // 初始化节点，w=长度
        t[p] = node(len);
        return p++;
    }
    //0为长度为偶数的回文子串的根节点
    //1为长度为奇数的回文子串的根节点
    //最后节点总数是p，但是节点标号是[0, p - 1]
    void init(){
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1; 		 // 开头放一个字符集中没有的字符，减少特判
        t[0].fail = 1;
    }
    int get_fail(int x){ // 和KMP一样，失配后找一个尽量最长的
        while(s[n-t[x].len-1] != s[n]) x = t[x].fail;
        return x;
    }
    bool add(int c){
		bool F = 0;
		//设置偏移量
        c -= 'a';
        s[++n] = c;
		//通过上一个回文串找这个回文串的匹配位置
		int cur = get_fail(last);
		//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
		if(!t[cur].Next[c]){
            int now = newnode(t[cur].len + 2);//新建节点
			//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            t[now].fail = t[get_fail(t[cur].fail)].Next[c];
            t[cur].Next[c] = now;
            t[now].num = t[t[now].fail].num + 1;
            t[now].sum = t[t[now].fail].sum + t[now].len;
			F = 1;
		}
        last = t[cur].Next[c];
		++t[last].cnt;
        //返回的当前字符加入后是否新增了一个本质不同的回文串
		return F;
		//那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
    }
    void count(){
        // 最后统计一遍每个节点出现个数
        // 父亲累加儿子的cnt,类似SAM中parent树
        // 满足parent拓扑关系
		for (int i = p - 1;  i >= 0; --i) {
			t[t[i].fail].cnt += t[i].cnt;
		}
    }
}pam;
vector <vector<pii>> qvec;
struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a);}
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] += v;
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];
		return res;
	}
	void update(int l, int r, int v) {
		update(l, v);
		update(r + 1, -v);
	}
}bit;

int main() {
	while (scanf("%s", s + 1) != EOF) {
		n = strlen(s + 1);
		memset(pre, 0, sizeof pre);
	    qvec.clear(); qvec.resize(n + 1); 	
		pam.init();
		for (int i = 1; i <= n; ++i) {
			if (pam.add(s[i])) p[i] = pam.last;
			else p[i] = -1;
		}
		pam.count();
		for (int i = 1; i <= n; ++i) {
			if (p[i] != -1) {
				int len = pam.t[p[i]].len, cnt = pam.t[p[i]].cnt;
				qvec[i].push_back(pii(i - len + 1, cnt));
			}
		}
		ll res = 0;
		memset(pre, 0, sizeof pre);
		bit.init();
		for (int i = 1; i <= n; ++i) {
			int c = s[i] - 'a';
			bit.update(pre[c] + 1, i, 1);
			pre[c] = i;
			for (auto &it : qvec[i]) {
				res += 1ll * it.se * bit.query(it.fi);
			}	
		}
		printf("%lld\n", res); 
	}
	return 0;
}
