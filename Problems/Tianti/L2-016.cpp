#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
int n, cnt = 0;
unordered_map<string,int> idx;
struct info {
    int s, fa, mo;
};
vector<info> a(100005, {-1, -1, -1});
void solve() { 
    cin >> n;
    for(int i = 1; i <= n; i++) {
        string id, s, fa, mo;
        cin >> id >> s >> fa >> mo;
        idx[id] = ++cnt;
        if(fa != "-1" && !idx.count(fa)) idx[fa] = ++cnt;
        if(mo != "-1" && !idx.count(mo)) idx[mo] = ++cnt;
        a[idx[id]] = {(s == "M" ? 1 : 0), (idx[fa] == 0 ? -1 : idx[fa]), (idx[mo] == 0 ? -1 : idx[mo])};
    }
    int q;
    cin >> q;
    while(q--) {
        string u, v;
        cin >> u >> v;
        int idu = idx[u], idv = idx[v];
        if(a[idu].s == a[idv].s) {
            cout << "Never Mind\n";
        } else {
            unordered_map<int,int> au;
            queue<int> q;
            q.push(idu);
            bool ok = true;
            for(int i = 0; i < 4; i++) {
                int sz = q.size();
                while(sz--) {
                    int cur = q.front(); q.pop();
                    if(a[cur].fa != -1) q.push(a[cur].fa), au[a[cur].fa]++;
                    if(a[cur].mo != -1) q.push(a[cur].mo), au[a[cur].mo]++;
                    if(a[cur].fa != -1 && a[cur].mo != -1 && a[a[cur].fa].s != -1 && a[a[cur].mo].s != -1 && a[a[cur].fa].s == a[a[cur].mo].s) ok = false;
                }
            }
            while(!q.empty()) q.pop();
            q.push(idv);
            for(int i = 0; i < 4; i++) {
                int sz = q.size();
                while(sz--) {
                    int cur = q.front(); q.pop();
                    if(a[cur].fa != -1) {
                        if(au.count(a[cur].fa)) {
                            ok = false;
                            break;
                        }
                        q.push(a[cur].fa);
                    }
                    if(a[cur].mo != -1) {
                        if(au.count(a[cur].mo)) {
                            ok = false;
                            break;
                        }
                        q.push(a[cur].mo);
                    }
                    if(a[cur].fa != -1 && a[cur].mo != -1 && a[a[cur].fa].s != -1 && a[a[cur].mo].s != -1 && a[a[cur].fa].s == a[a[cur].mo].s) ok = false;
                }
                if(!ok) break;
            }
            if(ok) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
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
    
