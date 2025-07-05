#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    deque<int> q;
    q.push_back(0);
    int mx = 0;    
    for(int i = 1; i <= n; i++) { 
        while(!q.empty() && a[q.back()] > a[i]) {
            q.pop_back();
        }
        q.push_back(i);
        while(!q.empty() && q.front() < i - k) {
            q.pop_front();
        }
        mx = max(mx, a[i] - a[q.front()]);
    }
    cout << mx << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

