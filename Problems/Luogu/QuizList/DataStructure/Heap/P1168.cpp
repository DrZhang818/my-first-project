#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    priority_queue<int> mx;
    priority_queue<int, vector<int>, greater<int>> mn;
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        if(mn.empty() || x >= mn.top()) mn.push(x);
        else mx.push(x);
        if(i & 1) {
            int k = (i + 1) / 2;
            while(mn.size() > k) mx.push(mn.top()), mn.pop();
            while(mn.size() < k) mn.push(mx.top()), mx.pop();
            cout << mn.top() << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
