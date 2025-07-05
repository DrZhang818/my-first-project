#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int a, b, n;
    cin >> a >> b >> n;
    vector<int> ans(3);
    ans.reserve(n + 1);
    ans[1] = a, ans[2] = b;
    int i = 1;
    while(ans.size() <= n) {
        int res = ans[i] * ans[i + 1];
        string t = to_string(res);
        for(int j = 0; j < t.size(); j++) ans.push_back(t[j] - '0');
        i++;
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
