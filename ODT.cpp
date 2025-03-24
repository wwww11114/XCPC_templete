#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct ODT {
    struct Node {
        i64 l, r, v;
        bool operator<(const Node &a) const {
            return l == a.l ? r < a.r : l < a.l;
        }
    };
    i64 n;
    set<Node> st;
    ODT(vector<i64> &a) {
        n = a.size() - 1;
        i64 r = 1, l = 1;
        while (r < n) {
            if (a[r] != a[r + 1]) {
                st.insert({l, r, a[r]});
                l = r + 1;
            }
            r++;
        }
        st.insert({l, r, a[r]});
    }
    void spilt(i64 ins) {
        if (ins <= 1 || ins > n) {
            return;
        }
        auto it = st.upper_bound({ins, n + 1, 0});
        it--;
        if (it->l == ins)
            return;
        i64 l = it->l, r = it->r, v = it->v;
        st.erase(it);
        st.insert({l, ins - 1, v});
        st.insert({ins, r, v});
    }
    void merge(i64 ins) {
        if (ins <= 1 || ins > n) {
            return;
        }
        auto it1 = st.lower_bound({ins, 0, 0});
        auto it2 = it1;
        it1--;
        if (it2->v == it1->v) {
            st.insert({it1->l, it2->r, it1->v});
            st.erase(it1);
            st.erase(it2);
        }
    }
    void range_add(i64 l, i64 r, i64 x) {
        spilt(l);
        spilt(r + 1);
        auto it = st.lower_bound({l, 0, 0});
        while (it != st.end() && it->r <= r) {
            i64 il = it->l, ir = it->r, iv = it->v;
            st.erase(it++);
            st.insert({il, ir, iv + x});
        }
        merge(l);
        merge(r + 1);
    }
    void range_set(i64 l, i64 r, i64 x) {
        spilt(l);
        spilt(r + 1);
        auto it = st.lower_bound({l, 0, 0});
        while (it != st.end() && it->r <= r) {
            st.erase(it++);
        }
        st.insert({l, r, x});
        merge(l);
        merge(r + 1);
    }
    i64 range_find_kth(i64 l, i64 r, i64 k) {
        vector<pair<i64, i64>> v;
        auto it = st.upper_bound({l, 0, 0});
        if (it != st.begin())
            it--;
        while (it != st.end() && it->l <= r) {
            i64 il = it->l, ir = it->r, iv = it->v;
            if (il < l) {
                il = l;
            }
            if (ir > r) {
                ir = r;
            }
            i64 len = ir - il + 1;
            v.push_back({iv, len});
            it++;
        }
        sort(v.begin(), v.end());
        for (auto i : v) {
            if (k <= i.second) {
                return i.first;
            }
            k -= i.second;
        }
        return -1;
    }
    i64 range_sum(i64 l, i64 r) {
        i64 sum = 0;
        auto it = st.upper_bound({l, 0, 0});
        if (it != st.begin())
            it--;
        while (it != st.end() && it->l <= r) {
            i64 il = it->l, ir = it->r, iv = it->v;
            if (il < l) {
                il = l;
            }
            if (ir > r) {
                ir = r;
            }
            i64 len = ir - il + 1;
            sum = sum + iv * len;
            it++;
        }
        return sum;
    }
};