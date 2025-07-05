#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


ull Hash(string &s) {
    ull P = 131, H = 0;
    for(auto c : s) H = H * P + c;
    return H;
}
void solve() { 
    int n;
    cin >> n;
    unordered_map<ull, set<int>> mp;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while(x--) {
            string t;
            cin >> t;
            ull H = Hash(t);
            mp[H].insert(i);
        }
    }
    int q;
    cin >> q;
    while(q--) {
        string t;
        cin >> t;
        ull H = Hash(t);
        for(int x : mp[H]) {
            cout << x << " ";
        }
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
