#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class XorBasis {
    vector<ll> b;

    int num;
    ll _or;
    
    bool canBeZero;
    vector<ll> basis;

    vector<int> rightMost;
    int rightMostZero;
public:
    XorBasis(vector<ll> &a) {
        b.resize(64);
        rightMost.resize(b.size(), 0);
        rightMostZero = -1;
        num = 0;
        _or = 0;
        canBeZero = false;

        for(ll v : a) {
            insert(v);
        }
    };
    XorBasis() {
        b.resize(64);
        rightMost.resize(b.size(), 0);
        rightMostZero = -1;
        num = 0;
        _or = 0;
        canBeZero = false;
    }
    bool insert(ll v) {
        _or |= v;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                num++;
                return true;
            }
            v ^= b[i];
        }
        canBeZero = true;
        return false;
    }
    bool insertRightMost(int idx, ll v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                rightMost[i] = idx;
                num++;
                return true;
            }
            if(idx > rightMost[i]) {
                swap(idx, rightMost[i]);
                swap(v, b[i]);
            }
            v ^= b[i];
        }
        canBeZero = true;
        rightMostZero = max(rightMostZero, idx);
        return false;
    }
    bool decompose(ll v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                return false;
            }
            v ^= b[i];
        }
        return true;
    }
    ll maxXor() {
        ll res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    ll maxXorWithVal(ll v) {
        ll res = v;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    ll maxXorWithLowerIndex(int lowerIndex) {
        ll res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(res >> i & 1) && rightMost[i] >= lowerIndex) {
                res = max(res, res ^ b[i]);
            }
        }
        return res;
    }
    ll minXor() {
        if(canBeZero) {
            return 0;
        }
        for(int i = 0; i < b.size(); i++) {
            if(b[i] > 0) {
                return b[i];
            }
        }
        return -1; //基为空
    }
    void initOnce() {
        if(!basis.empty()) {
            return;
        }
        vector<ll> tmp = b;
        for(int i = 0; i < tmp.size(); i++) {
            if(tmp[i] == 0) {
                continue;
            }
            for(int j = i - 1; j >= 0; j--) {
                if(tmp[i] >> j & 1) {
                    tmp[i] ^= tmp[j];
                }
            }
            basis.push_back(tmp[i]);
        }
    }
    ll kthXor(ll k) {
        initOnce();
        if(canBeZero) {
            k--;
        }
        if(k >= (1LL << basis.size())) {
            return -1;
        }
        ll _xor = 0;
        for(int i = 0; i < basis.size(); i++) {
            if(k >> i & 1) {
                _xor ^= basis[i];
            }
        }
        return _xor;
    }
    XorBasis get(int lowerIndex) {
        XorBasis res;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(rightMost[i] >= lowerIndex) {
                res.insert(b[i]);
            }
        }
        return res;
    }
    void merge(const XorBasis& other) {
        for(int i = other.b.size() - 1; i >= 0; i--) {
            ll v = other.b[i];
            if(v > 0) {
                insert(v);
            }
        }
    }
};

void solve() {  
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    ll _xor = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        _xor ^= a[i];
    }
    XorBasis b;
    for(int i = 1; i <= n; i++) {
        a[i] &= ~_xor;
        b.insert(a[i]);
    }
    ll mx = b.maxXor();
    ll ans = max(_xor, (_xor ^ mx) & mx);
    cout << ans << "\n";
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
