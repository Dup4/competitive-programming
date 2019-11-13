#include <bits/stdc++.h>
using namespace std;
#define N 200010
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]

inline void swap(int&a,int&b) {
    int tmp(a); a=b,b=tmp;
}

namespace Summer {
    int ch[N][2],fa[N],rev[N],val[N],sumv[N],mark[N];
    inline void reverse(int x) {
        if(x) {
            swap(lc(x),rc(x));
            rev[x]^=1;
        }
    }
    inline void NaCly_Fish_Orz(int x) {
        if(x) {
            val[x]=sumv[x]=0;
            mark[x]=1;
        }
    }
    inline void up(int x) {
        sumv[x]=sumv[lc(x)]+sumv[rc(x)]+val[x];
    }
    inline void down(int x) {
        if(rev[x]) {
            reverse(lc(x));
            reverse(rc(x));
            rev[x]=0;
        }
        if(mark[x]) {
            NaCly_Fish_Orz(lc(x));
            NaCly_Fish_Orz(rc(x));
            mark[x]=0;
        }
    }
    inline int nrt(int x) {
        return x==lc(fa[x])||x==rc(fa[x]);
    }
    void psa(int x) {
        if(nrt(x)) psa(fa[x]);
        down(x);
    }
    inline void rotate(int x) {
        int y(fa[x]),z(fa[y]),k(x==rc(y));
        ch[y][k]=ch[x][k^1],ch[x][k^1]=y;
        if(nrt(y)) ch[z][y==rc(z)]=x;
        if(ch[y][k]) fa[ch[y][k]]=y;
        fa[y]=x,fa[x]=z,up(y);
    }
    inline void splay(int x) {
        int y,z;
        for(psa(x);nrt(x);rotate(x)) {
            y=fa[x],z=fa[y];
            if(nrt(y)) rotate(x==rc(y)^y==rc(z)?x:y);
        } up(x);
    }
    inline void access(int x) {
        for(int y=0;x;x=fa[y=x]) {
            splay(x); rc(x)=y; up(x);
        }
    }
    inline void mrt(int x) {
        access(x); splay(x); reverse(x);
    }
    inline void link(int x,int y) {
        mrt(x); fa[x]=y;
    }
    inline void cut(int x,int y) {
        mrt(x); access(y); splay(y);
        fa[x]=lc(y)=0; up(y);
    }
}

namespace Pockets {
    int ch[N][2],fa[N],rev[N],val[N],sumv[N],st[N],num;
    inline void reverse(int x) {
        if(x) {
            swap(lc(x),rc(x));
            rev[x]^=1;
        }
    }
    inline void up(int x) {
        sumv[x]=sumv[lc(x)]+sumv[rc(x)]+val[x];
    }
    inline void down(int x) {
        if(rev[x]) {
            reverse(lc(x));
            reverse(rc(x));
            rev[x]=0;
        }
    }
    inline int nrt(int x) {
        return x==lc(fa[x])||x==rc(fa[x]);
    }
    void psa(int x) {
        if(nrt(x)) psa(fa[x]);
        down(x);
    }
    inline void rotate(int x) {
        int y(fa[x]),z(fa[y]),k(x==rc(y));
        ch[y][k]=ch[x][k^1],ch[x][k^1]=y;
        if(nrt(y)) ch[z][y==rc(z)]=x;
        if(ch[y][k]) fa[ch[y][k]]=y;
        fa[y]=x,fa[x]=z,up(y);
    }
    inline void splay(int x) {
        int y,z;
        for(psa(x);nrt(x);rotate(x)) {
            y=fa[x],z=fa[y];
            if(nrt(y)) rotate(x==rc(y)^y==rc(z)?x:y);
        } up(x);
    }
    inline void access(int x) {
        for(int y=0;x;x=fa[y=x]) {
            splay(x); rc(x)=y; up(x);
        }
    }
    inline void mrt(int x) {
        access(x); splay(x); reverse(x);
    }
    inline void link(int x,int y) {
        mrt(x); fa[x]=y;
    }
    inline void cut(int x,int y) {
        mrt(x); access(y); splay(y);
        fa[x]=lc(y)=0; up(y);
    }
    void print(int now) {
        if(now) {
            down(now);
            print(lc(now));
            st[++num]=now;
            print(rc(now));
        }
    }
}

int n,q,opt,u,v,last,tot,ans,SummerPockets;

int fa[N];
inline int find(int x) {
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void getEdge(int u,int v) {
    int x=find(u),y=find(v);
    if(x!=y) {
        ans=-1;
        return;
    }
    Summer::mrt(u);
    Summer::access(v);
    Summer::splay(v);
    ans=Summer::sumv[v];
}

inline void getPoint(int u,int v) {
    int x=find(u),y=find(v);
    if(x!=y) {
        ans=-1;
        return;
    }
    Pockets::mrt(u);
    Pockets::access(v);
    Pockets::splay(v);
    ans=Pockets::sumv[v];
}

inline void link(int u,int v) {
    int x=find(u),y=find(v);
    if(x==y) {
        Summer::mrt(u);
        Summer::access(v);
        Summer::splay(v);
        Summer::NaCly_Fish_Orz(v);

        getPoint(u,v);
        if(ans>2) {
            ++SummerPockets;
            Pockets::mrt(u);
            Pockets::access(v);
            Pockets::splay(v);
            Pockets::num=0;
            Pockets::print(v);
            for(int i=1;i<Pockets::num;++i) {
				cout << "# " << Pockets::st[i] << " " << Pockets::st[i + 1] << endl;
                Pockets::cut(Pockets::st[i],Pockets::st[i+1]);
			}
            for(int i=1;i<=Pockets::num;++i)
                Pockets::link(Pockets::st[i],SummerPockets);
        }
    } else {
        ++tot; fa[y]=x;
        Summer::val[tot]=1;
        Summer::link(u,tot);
        Summer::link(tot,v);

        Pockets::link(u,v);
    }
}

int main() {
    scanf("%d%d",&n,&q);
    tot=SummerPockets=n;
    for(int i=1;i<=n;++i)
        fa[i]=i,Pockets::val[i]=1;
    while(q--) {
        scanf("%d%d%d",&opt,&u,&v);
        u^=last,v^=last;
        switch(opt) {
            case 1: {
                link(u,v);
                break;
            }
            case 2: {
                getEdge(u,v);
                if(ans!=-1) last=ans;
                printf("%d\n",ans);
                break;
            }
            default: {
                getPoint(u,v);
                if(ans!=-1) last=ans;
                printf("%d\n",ans);
                break;
            }
        }
    }
    return 0;
}
