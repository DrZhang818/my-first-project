#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> cnt(n + 1);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    vector<int> p;
    for(int i = 1; i <= n; i++) {
        if(!cnt[i]) {
            p.push_back(i);
        }
    }
    if(p.size() == 0) {
        for(int i = 1; i <= k; i++) {
            cout << a[i] << " \n"[i == k];
        }
        return;
    }
    if(p.size() == 1) {
        for(int i = 1; i <= n; i++) {
            if(cnt[a[i]] == 2) {
                cnt[a[i]] -= 1;
            } else {
                p.push_back(a[i]);
            }
        }
    } else {
        for(int i = 1; i <= n; i++) {
            if(cnt[i]) {
                p.push_back(i);
            }
        }
    }
    for(int i = 0; i < k; i++) {
        cout << p[i] << " \n"[i == k - 1];
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
