#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int val, w;
};
void solve() { 
    int k;
    cin >> k;
    vector<bool> vis(k, false);
    deque<info> q;
    q.push_front({1, 1});
    vis[1] = true;
    while(!q.empty()) {
        int x = q.front().val, w = q.front().w;
        q.pop_front();
        if(x == 0) {
            cout << w << "\n";
            return;
        }
        if(!vis[10 * x % k]) {
            q.push_front(info{10 * x % k, w});
            vis[10 * x % k] = true;
        }
        if(!vis[(x + 1) % k]) {
            q.push_back(info{(x + 1) % k, w + 1});
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
    
