#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

struct StringHash {
    struct Hash {
        int n = 0;
        i64 hash = 0;
        Hash() = default;
        Hash(i64 hash, int n) : hash(hash), n(n) {}
        Hash operator+(const Hash &rhs) {
            return Hash(StringHash::add(rhs.hash, StringHash::mul(hash, StringHash::p[rhs.n])), n + rhs.n);
        }
        auto operator<=>(const Hash &rhs) const = default;
    };
    constexpr static i64 base = 114514;
    constexpr static i64 mod = (1ll << 61) - 1;
    inline static vector<i64> p{1};
    inline static int n = 0;
    vector<i64> h;

    StringHash() = default;
    StringHash(const string &s) {
        int n = s.size();
        h.resize(n + 1);
        init(2 * n);
        for (int i = 1; i <= n; i++) {
            h[i] = add(s[i - 1], mul(h[i - 1], base));
        }
    }
    StringHash(char c) : StringHash(string(1, c)) {}

    Hash getHash(int l, int r) {
        return Hash(sub(h[r + 1], mul(h[l], p[r - l + 1])), r - l + 1);
    }
private:
    void init(int m) {
        if (n > m) return;
        p.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            p[i] = mul(p[i - 1], base);
        }
        n = m;
    }
    static i64 mul(i64 a, i64 b) {
        i128 c = (i128)a * b;
        return add(c >> 61, c & mod);
    }
    static i64 add(i64 a, i64 b) {
        i64 c = a + b;
        if (c >= mod) {
            c -= mod;
        }
        return c;
    }
    static i64 sub(i64 a, i64 b) {
        i64 c = a - b;
        if (c < 0) {
            c += mod;
        }
        return c;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    set<StringHash::Hash> st;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        st.insert(StringHash(s).getHash(0, s.size() - 1));
    }
    cout << (1ll << 61) - 1 << '\n';
    return 0;
}
