#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    string s, t;
    cin >> s >> t;
    int n = s.size();
    auto dfs = [&](auto&& dfs, int l1, int r1, int l2, int r2){
        if(l1 > r1 || l2 > r2) return;
        char c = t[l2];
        int i = l1;
        for(; i <= r1; i++){
            if(s[i] == c){
                break;
            }
        }
        dfs(dfs, l1, i, l2 + 1, l2 + i - l1);
        dfs(dfs, i + 1, r1, l2 + i - l1 + 1, r2);
        cout << c;
    };
    dfs(dfs, 0, n - 1, 0, n - 1);
    cout << "\n"; 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
