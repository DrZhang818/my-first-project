#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int s, c;
    cin >> s >> c;
    vector<vector<int>> a(105);
    for(int i = 1; i <= s; i++) {
        int x;
        cin >> x;
        a[1].push_back(x);
    }
    int idx = 1;
    while(1) {
        bool ok = true;
        for(int i = 1; i < a[idx].size(); i++) {
            a[idx + 1].push_back(a[idx][i] - a[idx][i - 1]);
            if(a[idx][i] != a[idx][i - 1]) {
                ok = false;
            }
        }
        if(ok) break;
        idx++;
    }
    for(int i = 0; i < c; i++) {
        for(int j = idx; j >= 1; j--) {
            if(j == idx) {
                a[j].push_back(a[j].back());
            } else {
                a[j].push_back(a[j].back() + a[j + 1].back());
            }
        }
        cout << a[1].back() << " \n"[i == c - 1];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
