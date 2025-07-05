#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;



int n;
vector<int> a;
struct info {
    int l, r, k;
};
void solve() { 
    cin >> n;
    a.assign(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    queue<info> q;
    q.push({1, n, __lg(n) + 1});
    vector<int> ans;
    while(!q.empty()) {
        info u = q.front(); q.pop();
        int l = u.l, r = u.r, k = u.k;
        ans.push_back(a[r]);
        cerr << l << " " << r << " " << k << "\n";
        if(l == r) continue;
        r--;
        if(r - l + 1 >= (1 << k - 1) + (1 << k - 2) - 2) {
            int mid = l + (1 << k - 1) - 2;
            if(mid >= l) q.push({l, mid, __lg(mid - l + 1) + 1});
            if(r > mid) q.push({mid + 1, r, __lg(r - mid) + 1});
        } else {
            int mid = r - (1 << k - 2) + 1;
            if(mid >= l) q.push({l, mid, __lg(mid - l + 1) + 1});
            if(r > mid) q.push({mid + 1, r, __lg(r - mid) + 1});
        }
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}

int main()
{

    solve();
    return 0;
}
    
