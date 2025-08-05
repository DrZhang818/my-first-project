#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18 + 9;

void solve() {
    int q;
    cin >> q;
    vector<int> l(q + 2), r(q + 2);
    vector<array<int,21>> son(q + 2);
    vector<array<ll,21>> sum(q + 2);
    vector<ll> len(q + 2);
    len[0] = len[1] = 1;
    for(int i = 2; i <= q + 1; i++) {
        ll x;
        cin >> l[i] >> r[i] >> x;
        len[i] = min(inf, len[l[i]] + len[r[i]]);
        if(len[l[i]] >= len[r[i]]) {
            son[i][0] = l[i];
        } else {
            son[i][0] = r[i];
            sum[i][0] = len[l[i]];
        }
        for(int s = 1; s <= 20; s++) {
            son[i][s] = son[son[i][s - 1]][s - 1];
            sum[i][s] = min(sum[son[i][s - 1]][s - 1] + sum[i][s - 1], inf); 
        }
        int p = i;
        while(p > 1) {
            for(int s = 20; s >= 0; s--) {
                if(son[p][s] > 1 && x > sum[p][s] && x - sum[p][s] <= len[son[p][s]]) {
                    x -= sum[p][s];
                    p = son[p][s];
                }
            }
            if(x <= len[l[p]]) {
                p = l[p];
            } else {
                x -= len[l[p]];
                p = r[p];
            }
        }
        cout << p << "\n";
    }   
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
