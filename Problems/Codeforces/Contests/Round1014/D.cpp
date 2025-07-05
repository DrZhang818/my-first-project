#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cl = 0, ci = 0, ct = 0;
    for(auto c : s) {
        cl += c == 'L';
        ci += c == 'I';
        ct += c == 'T';
    }
    for(int m = n; m <= 3 * n; m++) {
        if(m % 3 != 0) continue;
        int cnt = m / 3;
        if(cl > cnt || ci > cnt || ct > cnt) continue;
        int dl = cnt - cl, di = cnt - ci, dt = cnt - ct;
        vector<int> ans;
        string t = s;
        bool ok = true;
        while(dl > 0 || di > 0 || dt > 0) {
            bool can = false;
            for(int i = 0; i < t.size() - 1; i++) {
                char a = t[i], b = t[i + 1];
                if(a == b) continue;
                char x;
                if(a != 'L' && b != 'L') x = 'L';
                else if(a != 'I' && b != 'I') x = 'I';
                else if(a != 'T' && b != 'T') x = 'T';
                else continue;
                if(x == 'L' && dl > 0) {
                    t.insert(i + 1, 1, x);
                    ans.push_back(i + 1);
                    dl--;
                    can = true;
                    break;
                } else if(x == 'I' && di > 0) {
                    t.insert(i + 1, 1, x);
                    ans.push_back(i + 1);
                    di--;
                    can = true;
                    break;
                } else if(x == 'T' && dt > 0) {
                    t.insert(i + 1, 1, x);
                    ans.push_back(i + 1);
                    dt--;
                    can = true;
                    break;
                }
            }
            if(!can) {
                ok = false;
                break;
            }
        }
        if(ok) {
            cout << (int)ans.size() << "\n";
            for(int i = 0; i < ans.size(); i++) {
                cout << ans[i] << "\n";
            }
            return;
        }
    }
    cout << -1 << "\n";
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
    
