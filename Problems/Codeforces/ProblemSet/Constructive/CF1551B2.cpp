#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/1551/problem/B2
//优化解法(jiangly)
void solve1() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), cnt(n);
    vector<int> p;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        cnt[a[i]]++;
        if(cnt[a[i]] <= k) {
            p.push_back(i);
        }
    }
    while(p.size() % k != 0) p.pop_back();
    sort(p.begin(), p.end(), [&](int i, int j) -> bool{
        return a[i] < a[j];
    });
    vector<int> ans(n);
    for(int i = 0; i < p.size(); i++) {
        ans[p[i]] = i % k + 1;
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}


struct info {
    int cnt;
    vector<int> idx;
};
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x].cnt++;
        a[x].idx.push_back(i);
    }
    sort(a.begin() + 1, a.end(), [](auto &a, auto &b) -> bool {
        return a.cnt > b.cnt;
    });
    vector<int> ans(n + 1);
    int id = 0;
    for(int i = 1; i <= n; i++) {
        int cur = 0;
        while(a[i].cnt > 0 && cur < k) {
            ans[a[i].idx[cur]] = id + 1;
            id = (id + 1) % k;
            a[i].cnt--;
            cur++;
        }
    }
    vector<bool> vis(id + 1, false);
    for(int i = 1; i <= n; i++) {
        if(ans[i] <= id && !vis[ans[i]]) {
            cout << 0 << " ";
            vis[ans[i]] = true;
            continue;
        }
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve1();
    }
    return 0;
}
    
