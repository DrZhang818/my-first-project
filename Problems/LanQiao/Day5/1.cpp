#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

bool ok1(string &s){
    string t = s;
    reverse(t.begin(), t.end());
    return t == s;
}
bool ok2(int y, int m, int d){
    if(m < 1 || m > 12) return false;
    if(d > 31) return false;
    auto isLunar = [&](int y) -> bool{
        return y % 400 == 0 || y % 4 == 0 && y % 100 != 0;
    };
    int ds[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLunar(y)) ds[2] = 29;
    return d > 0 && d <= ds[m];
}
bool ok3(string &s){
    unordered_map<int, int> mp;
    for(auto c : s){
        mp[c]++;
        if(mp[c] > 2){
            return false;
        }
    }
    return true;
}
void solve(){
    string s;
    for(int i = 0; i < 10; i++){
        char c;
        cin >> c;
        if(c != '/'){
            s += c;
        }
    }    
    int y, m, d;
    y = stoi(s.substr(0, 4));
    m = stoi(s.substr(4, 2));
    d = stoi(s.substr(6, 2));
    if(ok1(s) && ok2(y, m, d) && ok3(s)){
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}