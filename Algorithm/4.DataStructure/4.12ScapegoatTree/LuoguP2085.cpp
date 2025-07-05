#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, m;
    cin >> n >> m;
    priority_queue<int> pq;
    for(int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if(i == 0) {
            for(int i = 1; i <= m; i++) {
                pq.push(a * i * i + b * i + c);
            }
        } else {
            int i = 1;
            int cur = a * i * i + b * i + c;
            while(cur <= pq.top()) {
                pq.pop();
                pq.push(cur);
            }
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
    
