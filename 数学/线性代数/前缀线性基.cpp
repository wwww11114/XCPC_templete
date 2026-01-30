#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using u128 = __uint128_t;

template <typename T, int B = numeric_limits<T>::digits>
struct Basis {
    array<T, B> Base
        int sz = 0;

    bool insert(T x) {
        for (int i = B - 1; i >= 0; i--) {
            if (!(x >> i & 1)) {
                continue;
            }
            if (!Base[i]) {
                sz++;
                Base[i] = x;
                return true;
            }
            x ^= Base[i];
        }
        return false;
    }
    int size() { return sz; }
    bool contains(T x) {
        for (int i = B - 1; i >= 0; i--) {
            if (x >> i & 1) {
                x ^= Base[i];
            }
        }
        return x == 0;
    }
    T queryMax(T res = 0) {
        for (int i = B - 1; i >= 0; i--) {
            res = max(res, res ^ Base[i]);
        }
        return res;
    }
    T queryMin(T res = 0) {
        for (int i = B - 1; i >= 0; i--) {
            res = min(res, res ^ Base[i]);
        }
        return res;
    }
    //第k小
    T kth(T k) {
        if (k < 1 || k >(T(1) << sz)) {
            return -1;
        }
        k--;
        T res = 0;
        int len = sz - 1;
        for (int i = B - 1; i >= 0; i--) {
            if (!Base[i]) {
                continue;
            }
            if ((k >> len & 1) ^ (res >> i & 1)) {
                res ^= Base[i];
            }
            len--;
        }
        return res;
    }

    friend Basis<T> operator+(Basis<T> res, const Basis<T> &rhs) {
        for (int i = 0; i < Basis<T>::B; i++) {
            res.insert(rhs.Base[i]);
        }
        return res;
    }

    friend Basis<T> operator&(Basis<T> lhs, Basis<T> rhs) {
        Basis<T> res;
        array<T, Basis<T>::B> Base{};
        for (int i = Basis<T>::B - 1; i >= 0; i--) {
            T x = rhs.Base[i];
            T cur = rhs.Base[i];
            bool flag = false;
            for (int j = Basis<T>::B - 1; j >= 0; j--) {
                if (!(x >> j & 1)) {
                    continue;
                }
                if (!lhs.Base[j]) {
                    flag = true;
                    lhs.Base[j] = x;
                    Base[j] = cur;
                    break;
                }
                x ^= lhs.Base[j];
                cur ^= Base[j];
            }
            if (!flag) {
                res.insert(cur);
            }
        }
        return res;
    }
};

template <typename T, int B = numeric_limits<T>::digits>
struct PreBasis {
    array<pair<T, int>, B> Base{};

    bool insert(T x, int pos) {
        for (int i = B - 1; i >= 0; i--) {
            auto &[y, id] = Base[i];
            if (x >> i & 1) {
                if (!y) {
                    Base[i] = {x, pos};
                    return true;
                } else if (pos > id) {
                    swap(x, y);
                    swap(id, pos);
                }
                x ^= y;
            }
        }
        return false;
    }

    Basis<T> query(int l) {
        Basis<T> res;
        for (int i = B - 1; i >= 0; i--) {
            const auto &[x, id] = Base[i];
            if (x && id >= l) {
                res.Base[i] = x;
                res.sz++;
            }
        }
        return res;
    }
};
int main() {
    return 0;
}