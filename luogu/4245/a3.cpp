namespace NTT {
    using T = int;
 
    const int MAXB = 21;
    const int MAXN = 1 << MAXB;
 
    int rev[MAXN];
 
    void ntt(T* a, int K, bool inv) {
        const int n = 1 << K;
 
        rev[0] = 0;
        REPP(i, 1, n) {
            rev[i] = (rev[i >> 1] >> 1) ^ ((i & 1) << (K - 1)); 
        }
 
        REP(i, n) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }
 
        for (int len = 1; len < n; len *= 2) {
            vector<T> roots(len);
            
            roots[0] = 1;
            if  (len > 1) {
                roots[1] = mypow(3, (MOD - 1) / (2 * len));
            }
            
            REPP(i, 2, len) {
                roots[i] = mult(roots[i >> 1], roots[(i + 1) >> 1]);
            }
            
            for (int i = 0; i < n; i += len * 2) {
                REP(j, len) {
                    const auto& w = roots[j];
                    const auto x = a[i + j];
                    const auto y = mult(a[i + len + j], w);
                    a[i + j] = x;
                    add(a[i + j], y);
                    a[i + len + j] = x;
                    sub(a[i + len + j], y);
                    if  (inv) {
                        a[i + j] = mult(a[i + j], inv2);
                        a[i + len + j] = mult(a[i + j + len], inv2);
                    }
                }
            }
        }
        if  (inv) {
            reverse(a + 1, a + n);
        }
    }
 
    VI brut_mult(const VI& a, const VI& b) {
        VI c(SZ(a) + SZ(b));
        REP(i, SZ(a)) {
            REP(j, SZ(b)) {
                add(c[i + j], ::mult(a[i], b[j]));
            }
        }
        return c;
    }
    VI powr(const VI& a, int m){
        if(!m) return {1};
        int K = 0;
        while ((1 << K) < SZ(a)*m) {
            ++K;
        }
        ++K;
 
        vector<T> A(1 << K);
 
        REP(i, SZ(a)) {
            A[i] = a[i];
        }
        ntt(A.data(), K, false);
        REP(i, SZ(A)) {
            A[i] = mypow(A[i], m);
        }
        ntt(A.data(), K, true);
 
        VI res(SZ(A));
        REP(i, SZ(res)) {
            res[i] = A[i];
        }
        int len=SZ(res);
        while(len>1&&res[len-1]==0)len--;
        res.resize(len);
        return res;
    }
    VI mult(const VI& a, const VI& b) {
        int K = 0;
        while ((1 << K) < max(SZ(a), SZ(b))) {
            ++K;
        }
        ++K;
 
        vector<T> A(1 << K);
        vector<T> B(1 << K);
 
        REP(i, SZ(a)) {
            A[i] = a[i];
        }
        REP(i, SZ(b)) {
            B[i] = b[i];
        }
 
        ntt(A.data(), K, false);
        ntt(B.data(), K, false);
        REP(i, SZ(A)) {
            A[i] = ::mult(A[i], B[i]);
        }
        ntt(A.data(), K, true);
 
        VI res(SZ(A));
        REP(i, SZ(A)) {
            res[i] = A[i];
        }
        int len=SZ(res);
        while(len>1&&res[len-1]==0)len--;
        res.resize(len);
        return res;
    }
};
