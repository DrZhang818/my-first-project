#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int k, n;
};
void solve() { 
    vector<info> a, b;
    string s;
    getline(cin, s);
    istringstream ss(s);
    int x, y;
    while(ss >> x >> y) {
        a.push_back({x, y});
    }
    getline(cin, s);
    ss = istringstream(s);
    while(ss >> x >> y) {
        b.push_back({x, y});
    }
    map<int,int> ans;
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b.size(); j++) {
            int k = a[i].k * b[j].k;
            int n = a[i].n + b[j].n;
            ans[n] += k;
        }
    }
    for(auto it = ans.rbegin(); it != ans.rend(); it++) {
        cout << it->second << " " << it->first << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
