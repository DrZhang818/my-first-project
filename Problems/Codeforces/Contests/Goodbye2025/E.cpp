#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

ll query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    ll s;
    cin >> s;
    return s;
}

void answer(int x) {
    cout << "! " << x << endl;
}

void solve() {  
    int n;
    cin >> n;
    int L = 1, R = n;
    ll sum = query(L, R);
    while(sum > 1) {
        int l = L - 1, r = R + 1;
        if(r - l - 1 == 1) {
            break;
        }
        while(l + 1 < r) {
            int mid = l + r >> 1;
            ll cur = query(L, mid);
            if(cur <= sum / 2) {
                l = mid;
            } else {
                r = mid;
            }
        }
        ll cur = query(L, l);
        if(cur != sum / 2) {
            break;
        }
        int len1 = l - L + 1;
        int len2 = R - l;
        if(len1 <= len2) {
            R = l;
        } else {
            L = l + 1;
        }
        sum >>= 1;
    }
    answer(sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
