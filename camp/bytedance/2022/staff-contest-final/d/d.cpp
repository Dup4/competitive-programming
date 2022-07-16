#include <bits/stdc++.h>
using namespace std;

const int ALP = 26;
const int N = 1e5 + 10;

template <unsigned int ALPHA_SIZE>
class SubSequenceAutomaton {
public:
    struct node {
        int nx[ALPHA_SIZE];

        node() {
            Init();
        }

        void Init() {
            memset(nx, -1, sizeof nx);
        }
    };

public:
    SubSequenceAutomaton() = default;

    SubSequenceAutomaton(const size_t n) {
        next_.reserve(n);
        pre_.reserve(n);
    }

    virtual size_t GetCharHashCode(const char c) const {
        return c - 'a';
    }

    void Init() {
        pos_ = 0;
        next_[0].Init();
        memset(last_, 0, sizeof last_);
    }

    void Init(const size_t n) {
        Init();
        next_.resize(n + 1);
        pre_.resize(n + 1);
    }

    void Extend(unsigned int c) {
        int cur = ++pos_;
        next_[cur].Init();
        pre_[cur] = last_[c];

        for (int i = cur - 1; i >= pre_[cur]; --i) {
            next_[i].nx[c] = cur;
        }

        last_[c] = cur;
    }

    void Build(const char* s, const size_t len_s) {
        Init(len_s);

        for (size_t i = 0; i < len_s; i++) {
            Extend(GetCharHashCode(s[i]));
        }
    }

    void Build(const std::string& s) {
        Build(s.c_str(), s.length());
    }

    const std::vector<node>& GetNext() const {
        return next_;
    }

    bool MatchSubSequence(const char* s, const size_t len_s) const {
        int cur = 0;
        for (size_t i = 0; i < len_s; i++) {
            if (cur >= pos_) {
                return false;
            }

            int nx = next_[cur].nx[GetCharHashCode(s[i])];
            if (nx == -1) {
                return false;
            }

            cur = nx;
        }

        return true;
    }

    bool MatchSubSequence(const std::string& s) const {
        return MatchSubSequence(s.c_str(), s.length());
    }

protected:
    void init(const size_t n) {
        next_.reserve(n);
    }

    std::vector<node> next_;
    std::vector<int> pre_;
    int last_[ALPHA_SIZE], pos_;
};

auto sub_sequence_automaton = SubSequenceAutomaton<ALP>(N);

int gao() {
    string s, t;
    cin >> s >> t;

    sub_sequence_automaton.Build(s);
    const auto& nx = sub_sequence_automaton.GetNext();

    int lens = int(s.length());
    int lent = int(t.length());

    int res = lens;
    int cost = 0;
    int l = 0;

    for (int i = 0; l < lens && i < lent; i++) {
        char cs = s[l];
        char ct = t[i];

        res = min(res, cost + lens - l);

        if (cs < ct) {
            res = min(res, cost);
            break;
        }

        for (int j = ct - 'a' - 1; j >= 0; j--) {
            int _nx = nx[l + 1].nx[j];

            if (_nx != -1) {
                int _res = cost + _nx - l - 1;
                res = min(res, _res);
            }
        }

        if (cs > ct) {
            int _nx = nx[l + 1].nx[ct - 'a'];
            if (_nx == -1) {
                break;
            }

            cost += _nx - l - 1;
            l = _nx - 1;
        }

        if (i + 1 < lent) {
            res = min(res, cost + lens - l - 1);
        }

        ++l;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(20);

    cout << gao() << endl;

    return 0;
}
