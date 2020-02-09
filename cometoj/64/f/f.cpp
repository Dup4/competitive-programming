#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e9 + 5, M = 1e4; 
int n, s, a[110];

template <size_t MAXN>
struct Bitset {
    typedef unsigned long long ull;
    const static int _BitNum = 64;
    const static ull _INF = (1ull << 63) - 1 + (1ull << 63); 
	int _len, _Size; 
	ull _Ary[MAXN / _BitNum + 5];
    ull _upceil;
	int _firstsize, lazy; 

	Bitset() {};

	void init(int __len) {
		_len = __len;
    	_Size = _len / _BitNum + ((_len % _BitNum) == 0 ? 0 : 1);
        memset(_Ary, 0, sizeof (_Ary[0]) * (_Size + 1));
        _firstsize = _len % _BitNum;
		if (!_firstsize) _upceil = _INF;
		else  _upceil |= (1ull << _firstsize) - 1;
		if (!_firstsize) _firstsize = _BitNum;
		lazy = 0;
    }

    void reset() { init(_len); }

	//operators                                                    
    void lftmve(const int &_v) {
        for (int i = 0; (i + _v) < _Size; ++i) this->_Ary[i] = this->_Ary[i + _v];
        for (int i = _Size - _v; i < _Size; ++i) this->_Ary[i] = 0;
    }
  
	Bitset& operator&=(const Bitset &_others) {
		lazy = 1;
		for (int i = _Size - 1; ~i; --i) {
			this->_Ary[i] &= _others._Ary[i];
		}
		return *this;
	}

    Bitset& operator<<=(int _v) {
        this->lftmve(_v / _BitNum);
        _v %= _BitNum;
        ull _tp = 0, _Pos = _BitNum - _v;
        for (int  i = 1; i <= _v; ++i) _tp |= 1ull << (_BitNum - i);
        ull _Lstv = 0;
        for (int i = _Size - 1; ~i; --i) {
            ull _Tp_Lstv = (_Ary[i] & _tp) >> _Pos;
            _Ary[i] <<= _v;
            _Ary[i] |= _Lstv;
            _Lstv = _Tp_Lstv;
        }
        this->_Ary[0] &= _upceil;
        return *this;
    }
    
	Bitset& operator|=(const Bitset &_others) {
		lazy = 1;
		for (int i = _Size - 1; ~i; --i) {
			this->_Ary[i] |= _others._Ary[i];
		}
		return *this;
	}

	//member functions
    void __GetPos(const ull &_pos, int &__Pos, int &_v) {
        __Pos = _Size - _pos / _BitNum - 1;
        _v = _pos % _BitNum;
    }
    
    void set() {
		lazy = 1;
        for (int i = 0; i < _Size; ++i) this->_Ary[i] = _INF;
        this->_Ary[0] &= _upceil;
    }
    
    void set(const int &_pos, const bool val = true) {
		lazy = 1;
		if (_pos >= (int)_len) return;
        int __Pos , _v;
        __GetPos(_pos,__Pos,_v);
        if (val) {
            this->_Ary[__Pos] |= (1ull << (_v));
        } else {
            this->_Ary[__Pos] |= (1ull << (_v));
            this->_Ary[__Pos] ^= (1ull << (_v));
        }
    }
    
    int count() {
        int _cnt = 0;
        for (int i = _Size - 1; ~i; --i) _cnt += __builtin_popcountll(this->_Ary[i]);          
        return _cnt;
    }
};
Bitset <N> f, t;
Bitset <M> g;   
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; } 

int main() {
	while (scanf("%d%d", &n, &s) != EOF) {
		f.init(n); 
		for (int i = 1; i <= s; ++i) scanf("%d", a + i);
		for (int i = 1; i <= s; ++i) {
			if (a[i] > 64) {
				for (int j = a[i]; j <= n; j += a[i])
					f.set(j - 1);   
			} else {
				int peroid = a[i] * 64 / gcd(a[i], 64);
				g.init(peroid);
				for (int j = a[i]; j <= peroid; j += a[i]) {
					g.set(j - 1); 
				}
				for (int j = f._Size - 1, k = g._Size - 1; j >= 0; --j) {
					f._Ary[j] |= g._Ary[k];
					--k;
					if (k < 0) k = g._Size - 1;
				}
				f._Ary[0] &= f._upceil;
			}
		}
		t = f;
		t <<= 1;
		f &= t;
		t <<= 1;
		f &= t;
		printf("%d\n", f.count());
	}
	return 0;
}
