#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    vector<int> ca(14), cb(14);
    for(int i = 1; i <= 4; i++) {
        int x;
        cin >> x;
        ca[x]++;
    }
    for(int i = 1; i <= 4; i++) {
        int x;
        cin >> x;
        cb[x]++;
    }
    int win = 0, tie = 0, lose = 0;
    for(int i = 1; i <= 13; i++) {
        for(int j = 1; j <= 13; j++) {
            ca[i]++;
            cb[j]++;
            vector<int> vala, valb;
            for(int k = 1; k <= 13; k++) {
                if(ca[k] > 0) vala.push_back(ca[k]);
                if(cb[k] > 0) valb.push_back(cb[k]);
            }
            sort(vala.begin(), vala.end());
            sort(valb.begin(), valb.end());
            int taga = 0, tagb = 0;
            if(vala.back() >= 4) {
                taga = 2;
            } else if(vala.size() == 2) {
                taga = 1;
            }
            if(valb.back() >= 4) {
                tagb = 2;
            } else if(valb.size() == 2) {
                tagb = 1;
            }
            
            if(taga == tagb) {
                tie++;
            } else if(taga > tagb) {
                win++;
            } else {
                lose++;
            }
            ca[i]--;
            cb[j]--;
        }
    }
    int tot = 13 * 13;
    int g = gcd(win, tot);
    cout << win / g << "/" << tot / g << " ";
    g = gcd(tie, tot);
    cout << tie / g << "/" << tot / g << " ";
    g = gcd(lose, tot);
    cout << lose / g << "/" << tot / g << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
