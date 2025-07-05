#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    priority_queue<db, vector<db>, greater<db>> q;
    for(int i = 1; i <= n; i++) {
        db x;
        cin >> x;
        q.push(x);
    }
    while(q.size() > 1) {
        db u = q.top();
        q.pop();
        db v = q.top();
        q.pop();
        db n = (u + v) / 2;
        q.push(n);
    }
    cout << q.top() << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
