#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int dir[5] = {-1, 0, 1, 0, -1};
void solve() { 
    string s;
    cin >> s;
    string en = "123804765";
    unordered_map<string,int> mp;
    queue<string> q;
    q.push(s), mp[s] = 0;
    while(!q.empty()) {
        string u = q.front();
        int cur = mp[u];
        q.pop();
        if(u == en) {
            cout << mp[u] << "\n";
            return;
        }
        auto pos = u.find('0');
        int x = pos / 3, y = pos % 3;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
            swap(u[pos], u[nx * 3 + ny]);
            if(mp.find(u) == mp.end()) q.push(u), mp[u] = cur + 1;
            swap(u[pos], u[nx * 3 + ny]);            
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
    
