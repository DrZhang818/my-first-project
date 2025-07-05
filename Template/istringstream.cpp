#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    string s;
    getline(cin, s);
    istringstream iss(s);
    int n;
    cin >> n;
    unordered_map<string, int> mp;
    for(int i = 0; i < n; i++) {
        cin >> s;
        mp[s] += 1;        
    }
    int ans = 0;
    string token;
    while(iss >> token) {
        char c = token.back();
        if(c == ',' || c == '.' || c == '!' || c == '?') {
            token.pop_back();
        }
        token[0] = tolower(token[0]);
        if(mp[token]) {
            continue;
        }
        ans++;
        mp[token]++;
    }
    cout << ans << "\n";
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
