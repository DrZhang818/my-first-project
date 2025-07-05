#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    priority_queue<int> pq;
    for(int i = 1; i <= n; i++) {
        if(cnt[i]) {
            pq.push(cnt[i]);
        }
    }
    for(int i = 0; i < k && !pq.empty(); i++) pq.pop();
    ll sum = 0;
    while(!pq.empty()) {
        sum += pq.top();
        pq.pop();
    }
    cout << sum << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
