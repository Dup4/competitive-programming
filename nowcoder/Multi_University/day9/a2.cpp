#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i(a);i<=(b);++i)
#define FOL(i,a,b) for(int i(a);i>=(b);--i)
#define SZ(x) ((long long)(x).size())
#define REW(a,b) memset(a,b,sizeof(a))
 
const int64_t Mod (1000000000) ;
int64_t powEx(int64_t base,int64_t n,int64_t Mod = ::Mod ) {
    int64_t ret(1);
    while(n){
        if(n&1) ret = ret*base%Mod ;
        base = base * base %Mod ;
        n >>= 1 ;
    }
    return ret % Mod ;
}
 
class Linear_Seq {
using VI = vector<int64_t> ;
public:
    static const int N=10010;
    int64_t res[N],base[N],c[N],md[N];
    vector<int> Md;
    inline void mulEx(int64_t *a,int64_t *b,int k) {
        for(int i(0);i<k+k;++i) c[i]=0;
        for(int i(0);i<k;++i)if(a[i])for(int j(0);j<k;++j)
            c[i+j]=(c[i+j]+a[i]*b[j])%Mod;
        for (int i(k+k-1);i>=k;--i) if (c[i])for(int j(0);j<Md.size();++j)
            c[i-k+Md[j]]=(c[i-k+Md[j]]-c[i]*md[Md[j]])%Mod;
        copy(c,c+k,a) ;
    }
    int solve(int64_t n,VI a,VI b) { // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
        int64_t ans(0),cnt(0);
        int k(a.size());
        for(int i(0);i<k;++i) md[k-1-i]=-a[i];
        md[k]=1 ;  Md.clear() ;
        for(int i(0);i<k;++i) if (md[i]) Md.push_back(i);
        for(int i(0);i<k;++i) res[i] = base[i] = 0;
        res[0]=1;
        while ((1LL<<cnt)<=n) ++ cnt;
        for (int p(cnt);~p;-- p) {
            mulEx(res,res,k);
            if ((n>>p)&1) {
                for (int i(k-1);~i;--i) res[i+1]=res[i];res[0]=0;
                for(int j(0);j<Md.size();++j)
                    res[Md[j]]=(res[Md[j]]-res[k]*md[Md[j]])%Mod;
            }
        }
        for(int i(0);i<k;++i) ans=(ans+res[i]*b[i])%Mod;
        return ans+(ans<0?Mod:0);
    }
    VI BM(VI s) {
        VI ret(1,1),B(1,1);
        int L(0),m(1),b(1);
        for(int n(0);n<s.size();++n) {
            int64_t d(0);
            for(int i(0);i<=L;++i)
                d=(d+(int64_t)ret[i]*s[n-i])%Mod;
            if (!d) ++m;
            else if (2*L<=n) {
                VI T=ret;
                int64_t c(Mod-d*powEx(b,Mod-2)%Mod);
                while (ret.size()<B.size()+m) ret.push_back(0);
                for (int i(0);i<B.size();++i)
                    ret[i+m]=(ret[i+m]+c*B[i])%Mod;
                L=n+1-L; B=T; b=d; m=1;
            } else {
                int64_t c(Mod-d*powEx(b,Mod-2)%Mod);
                while (ret.size()<B.size()+m) ret.push_back(0);
                for(int i(0);i<B.size();++i)
                    ret[i+m]=(ret[i+m]+c*B[i])%Mod;
                ++m;
            }
        }
        return ret;
    }
    inline static void extand(VI &a, size_t d, int64_t value = 0) {
        if (d <= a.size()) return;
        a.resize(d, value);
    }
 
    inline static int64_t gcdEx(int64_t a, int64_t b, int64_t&x, int64_t& y)
    {
        if(!b) {x=1;y=0;return a;}
        int64_t d = gcdEx(b,a%b,y,x);
        y -= (a/b)*x;
        return d;
    }
 
 
    static int64_t CRT(const VI &c, const VI &m) {
        int n(c.size());
        int64_t M(1), ans(0);
        for (int i = 0; i < n; ++i) M *= m[i];
        for (int i = 0; i < n; ++i) {
            int64_t x,y,tM(M / m[i]);
            gcdEx(tM, m[i], x, y);
            ans = (ans + tM * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }
 
    static VI ReedsSloane(const VI &s, int64_t Mod) {
        auto Inv = [](int64_t a, int64_t Mod) {
            int64_t x, y;
            return gcdEx(a, Mod, x, y)==1?(x%Mod+Mod)%Mod:-1;
        };
        auto L = [](const VI &a, const VI &b) {
            int da = (a.size()>1||(a.size()== 1&&a[0]))?a.size()-1:-1000;
            int db = (b.size()>1||(b.size()== 1&&b[0]))?b.size()-1:-1000;
            return max(da, db + 1);
        };
        auto prime_power = [&](const VI &s, int64_t Mod, int64_t p, int64_t e) {
            // linear feedback shift register Mod p^e, p is prime
            vector<VI> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            VI t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);;
            pw[0] = 1;
            for (int i(pw[0] = 1); i <= e; ++i) pw[i] = pw[i - 1] * p;
            for (int64_t i(0); i < e; ++i) {
                a[i] = {pw[i]}; an[i] = {pw[i]};
                b[i] = {0}; bn[i] = {s[0] * pw[i] % Mod};
                t[i] = s[0] * pw[i] % Mod;
                if (!t[i]) {t[i] = 1; u[i] = e;}
                else for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
            }
            for (size_t k(1);k < s.size(); ++k) {
                for (int g(0); g < e; ++g) {
                    if (L(an[g], bn[g]) > L(a[g], b[g])) {
                        ao[g] = a[e-1-u[g]];
                        bo[g] = b[e-1-u[g]];
                        to[g] = t[e-1-u[g]];
                        uo[g] = u[e-1-u[g]];
                        r[g] = k - 1;
                    }
                }
                a = an; b = bn;
                for (int o(0); o < e; ++o) {
                    int64_t d(0);
                    for (size_t i(0); i < a[o].size() && i <= k; ++i)
                        d = (d + a[o][i] * s[k - i]) % Mod;
                    if (d == 0) {t[o] = 1;u[o] = e;}
                    else {
                        for (u[o]=0, t[o]=d;!(t[o]%p);t[o]/=p ,++u[o]);
                        int g (e-1-u[o]);
                        if (!L(a[g], b[g])) {
                            extand(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % Mod;
                        } else {
                            int64_t coef = t[o]*Inv(to[g],Mod)%Mod*pw[u[o]-uo[g]]%Mod;
                            int m(k-r[g]);
                            extand(an[o],ao[g].size()+m);
                            extand(bn[o],bo[g].size()+m);
                            for (size_t i(0);i < ao[g].size(); ++i) {
                                an[o][i+m] -= coef*ao[g][i]%Mod;
                                if (an[o][i + m]<0) an[o][i+m] += Mod;
                            }
                            while (an[o].size() && !an[o].back()) an[o].pop_back();
                            for (size_t i(0); i < bo[g].size(); ++i) {
                                bn[o][i+m] -= coef*bo[g][i]%Mod;
                                if (bn[o][i + m] < 0) bn[o][i + m] -= Mod;
                            }
                            while (bn[o].size()&& !bn[o].back()) bn[o].pop_back();
                        }
                    }
                }
            }
            return make_pair(an[0], bn[0]);
        };
        vector<tuple<int64_t, int64_t, int> > fac;
        for (int64_t i(2); i*i <= Mod; ++i)
            if (!(Mod % i)) {
                int64_t cnt(0),pw(1);
                while (!(Mod % i)) {Mod /= i; ++cnt; pw *= i;}
                fac.emplace_back(pw, i, cnt);
            }
        if (Mod > 1) fac.emplace_back(Mod, Mod, 1);
        vector<VI> as;
        size_t n = 0;
        for (auto &&x: fac) {
            int64_t Mod, p, e;
            VI a, b;
            std::tie(Mod, p, e) = x;
            auto ss = s;
            for (auto &&x: ss) x %= Mod;
            std::tie(a, b) = prime_power(ss, Mod, p, e);
            as.emplace_back(a);
            n = max(n, a.size());
        }
        VI a(n),c(as.size()),m(as.size());
        for (size_t i(0); i < n; ++i) {
            for (size_t j(0); j < as.size(); ++j) {
                m[j] = std::get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = CRT(c, m);
        }
        return a;
    }
    int64_t solve(VI a,int64_t n,int64_t Mod,bool prime=true) {
        VI c;
        if(prime) c = BM(a);
        else c = ReedsSloane(a,Mod);
        c.erase(c.begin());
        for(int i(0);i<c.size();++i) c[i] = (Mod-c[i])%Mod;
        return solve(n,c,VI(a.begin(),a.begin()+c.size()));
    }
}BM;
typedef long long ll;
ll sum;
ll a[1005];
int main()
{
    cin.tie(0);
    cout.tie(0);
    int64_t n, m;
	while (cin >> n >> m) {
   		 a[0]=a[1]=1;
   		 vector<int64_t> f;//({0, 1});
   		 //f.push_back(0);
   		 f.push_back(1);
   		 f.push_back(2);
   		 sum=2;
   		 for (int i = 2; i < 1000; i++)
   		 {
   		     a[i]=(a[i-1]+a[i-2])%Mod;
   		     sum =(sum+powEx(a[i],m,Mod))%Mod;
   		     f.push_back(sum);                         //这里是因为题意要求出和的值所以导入数列和
   		 }
   		 cout << BM.solve(f,n-1,Mod,false) << "\n";   //false-模数为合数
	}
    return 0;
}
