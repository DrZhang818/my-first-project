#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1), idx(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        idx[a[i]] = i;
    }
    vector<int> mxL1(n + 1, 0), mxR1(n + 1, n + 1), mxL2(n + 1, 0), mxR2(n + 1, n + 1);
    stack<int> stk;
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[i] >= a[stk.top()]) {
            mxR1[stk.top()] = i;
            stk.pop();
        }
        if(!stk.empty()) mxL1[i] = stk.top();
        stk.push(i);
    }
    const int N = log2(n);
    vector<vector<int>> st(n + 1, vector<int>(N + 1));
    for(int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }
    for(int s = 1; s <= N; s++) {
        for(int i = 1; i + (1 << s - 1) <= n; i++) {   
            st[i][s] = max(st[i + (1 << s - 1)][s - 1], st[i][s - 1]);
        }
    }
    auto goL = [&](int l, int r, int x) -> int {
        int ans = 0;
        while(l < r) {
            int len = log2(r - l);
            if(st[r - (1 << len) + 1][len] > x) {
                l = r - (1 << len) + 1;
            } else {
                r = l + (1 << len) - 1;
            }
        }
        if(a[l] > x) ans = l;
        return ans;
    };
    auto goR = [&](int l, int r, int x) -> int {
        int ans = n + 1;
        while(l < r) {
            int len = log2(r - l);
            if(st[l][len] > x) {
                r = l + (1 << len) - 1;
            } else {
                l = r - (1 << len) + 1;
            }
        }
        if(a[l] > x) ans = l;
        return ans;
    };
    for(int i = 1; i <= n; i++) {
        int l1 = mxL1[i], r1 = mxR1[i], l2 = 0, r2 = n + 1;
        if(l1 > 1) l2 = goL(1, l1 - 1, a[i]);
        if(r1 < n) r2 = goR(r1 + 1, n, a[i]);
        mxL2[i] = l2;
        mxR2[i] = r2; 
    }

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += (ll)a[i] * (mxL1[i] - mxL2[i]) * (mxR1[i] - i);
        ans += (ll)a[i] * (mxR2[i] - mxR1[i]) * (i - mxL1[i]);
    }
    cout << ans << "\n";
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
