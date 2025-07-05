#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int pre, nxt;
};
void solve() { 
    vector<int> vis(256, 0);
    string s, t;
    getline(cin, s);
    for(char c : s) {
        if(vis[c]) continue;
        vis[c] = 1;
        t += c;
    }
    for(int i = 32; i <= 126; i++) {
        if(!vis[i]) {
            t += (char)i;
        }
    }
    int n = t.size();
    t = "#" + t;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i].pre = i == 1 ? n : i - 1;
        a[i].nxt = i == n ? 1 : i + 1;
    }
    int cur = 1;
    for(int i = 0; i < 94; i++) {
        int tmp = cur, len = (int)t[cur];
        a[a[cur].nxt].pre = a[cur].pre;
        a[a[cur].pre].nxt = a[cur].nxt;
        cur = a[cur].nxt;
        for(int j = 0; j < len - 1; j++) {
            cur = a[cur].nxt;
        }
        vis[t[tmp]] = t[cur];
    }
    vis[t[cur]] = t[1];
    for(int i = 32; i <= 126; i++) {
        cout << (char)i << " " << (char)vis[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
