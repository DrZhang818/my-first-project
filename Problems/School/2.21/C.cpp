#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    vector<int> cnt(26);
    int n;
    cin >> n;
    bool ok = true;
    while(n--) {
        string s;
        cin >> s;
        if(ok) {
            for(char c : s) {
                cnt[c - 'a']++;
            }
            ok = false;
        } else {
            vector<int> temp(26);
            for(char c : s) {
                temp[c - 'a']++;
            }
            for(int i = 0; i < 26; i++) {
                cnt[i] = min(cnt[i], temp[i]);
            }
        }
    }
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < cnt[i]; j++) {
            cout << (char)(i + 'a');
        }
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
    
