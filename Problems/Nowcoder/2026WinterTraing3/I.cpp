#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class XorBasis {
    vector<int> b;
    vector<ull> msk;
    vector<int> id;
    int num;
public:
    XorBasis() {
        b.resize(32);
        msk.assign(32, 0);
        id.assign(32, 0);
        num = 0;
    }
    bool insert(int v, int idx) {
        ull cur = 1ULL << num;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                msk[i] = cur;
                id[num] = idx;
                num++;
                return true;
            }
            v ^= b[i];
            cur ^= msk[i];
        }
        return false;
    }

    vector<int> decompose(int v) {
        ull cur = 0;

        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                return {};
            }
            v ^= b[i];
            cur ^= msk[i];
        }

        vector<int> vec;
        for(int i = 0; i < 32; i++) {
            if(cur >> i & 1) {
                vec.push_back(id[i]);
            }
        }
        return vec;
    }

};

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        b[i] ^= a[i];
    }

    int _xor = 0;
    for(int i = 1; i <= n; i++) {
        _xor ^= a[i];
    }

    auto c = a;
    if(_xor == 0) {
        for(int i = 1; i <= n; i++) {
            cout << c[i] << " \n"[i == n];
        }
        return;
    }

    XorBasis xb;
    for(int i = 1; i <= n; i++) {
        xb.insert(b[i], i);
    }

    auto vec = xb.decompose(_xor);
    if(vec.empty()) {
        cout << -1 << "\n";
        return;
    }
    
    for(int i : vec) {
        c[i] ^= b[i];
    }

    for(int i = 1; i <= n; i++) {
        cout << c[i] << " \n"[i == n];
    }
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
