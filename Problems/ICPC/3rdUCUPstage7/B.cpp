#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int l, r;
};

void solve() {
    int n, len;
    cin >> n >> len;
    vector<info> a(n + 1);
    map<int,int> pos;
    int cnt = 0;
    ll sum = 0;
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        a[i] = {l, r};
        if(l != -1) {
            if(pos[l]) {
                ok = false;
            }
            pos[l] = i;
        }
        if(r != -1 && r != l) {
            if(pos[r]) {
                ok = false;
            } 
            pos[r] = i;
        }
        if(l == -1 && r == -1) {
            cnt++;
        } else if(l != -1 && r != -1) {
            sum += r - l + 1;
        } else {
            sum += 1;
        }
    }
    if(!ok || len - sum < cnt) {
        cout << "NIE\n";
        return;
    }
    int cur = 1, rid = -1, tag = 0;
    for(auto [x, id] : pos) {
        if(x < cur) {
            if(id != rid) {
                ok = false;
                break;
            } 
            continue;
        }
        auto [L, R] = a[id];
        if(tag == 0 && x != cur && L != -1) {
            if(cnt == 0) {
                ok = false;
                break;
            }
            cnt--;
        }
        if(R == -1) {
            cur = x + 1;
            tag = 1;
        } else {
            cur = R + 1;
            tag = 0;
        }
        rid = id;
    }
    if(cur != len + 1 && tag == 0 && cnt == 0) {
        ok = false;
    }
    if(!ok) {
        cout << "NIE\n";
    } else {
        cout << "TAK\n";
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
