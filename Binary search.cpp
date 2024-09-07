#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll binary_search(ll l, ll r) {
    while (l < r) {
        ll mid = l + r >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
int main() { return 0; }