#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    cin.ignore();
    string s;
    vector<string> ans;
    for(int i = 0; i < n; i++) {
        getline(cin, s);
        if(s.find("qiandao") == -1 && s.find("easy") == -1) {
            ans.push_back(s);
        }
    }
    if(m >= ans.size()) {
        cout << "Wo AK le\n";
    } else {
        cout << ans[m] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
