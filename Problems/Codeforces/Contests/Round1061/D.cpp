#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int query(int i, int x) {
    cout << "? " << i << " " << x << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int x) {
    cout << "! " << x << endl;
}

void solve() {
    int n;
    cin >> n;
    vector<int> p(n - 1);
    iota(p.begin(), p.end(), 1);
    vector<int> val(n);
    iota(val.begin(), val.end(), 1);
    int j = n;
    for(int i = 0; i < 15; i++) {
        vector<int> p0, p1;
        int c0 = 0, c1 = 0;
        for(int x : p) {
            int res = query(x, 1 << i);
            if(res == 1) {
                c1++;
                p1.push_back(x);
            } else {
                c0++;
                p0.push_back(x);
            }
        }
        for(int k = 0; k < j; k++) {
            if(val[k] >> i & 1) c1--;
            else c0--;
        }
        assert(c0 == 0 || c1 == 0);
        if(c1 == -1) {
            for(int k = 0; k < j; k++) {
                if(~val[k] >> i & 1) {
                    swap(val[k--], val[--j]);
                } 
            }
            swap(p, p1);
        } else {
            for(int k = 0; k < j; k++) {
                if(val[k] >> i & 1) {
                    swap(val[k--], val[--j]);
                }
            }
            swap(p, p0);
        }
    }
    assert(j == 1);
    answer(val[0]);
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
    