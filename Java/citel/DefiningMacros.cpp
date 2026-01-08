#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    string line;
    getline(cin, line);
    map<string,int> mp;
    auto norm = [&](string s) {
        string t;
        for(char c : s) if(c != ' ') t += c;
        return t;
    };
    auto dfs = [&](this auto &&self, string s) -> int {
        if(s.empty()) return 2;
        if(s.front() == '(' && s.back() == ')') {
            int cnt = 0;
            bool ok = true;
            for(int i = 0; i < s.size() - 1; i++) {
                if(s[i] == '(') cnt++;
                if(s[i] == ')') cnt--;
                if(cnt == 0) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                int res = self(s.substr(1, s.size() - 2));
                return res == -1 ? -1 : 2;
            }
        }
        int cnt = 0, p1 = -1, p2 = -1;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(') {
                cnt++;
            } else if(s[i] == ')') {
                cnt--;
            } else if(cnt == 0) {
                if(s[i] == '+' || s[i] == '-') p1 = i;
                if(s[i] == '*' || s[i] == '/') p2 = i;
            }
        }
        if(p1 != -1) {
            int l = self(s.substr(0, p1));
            int r = self(s.substr(p1 + 1));
            if(l == -1 || r == -1) return -1;
            if(s[p1] == '-' && r == 0) return -1;
            return 0;
        }
        if(p2 != -1) {
            int l = self(s.substr(0, p2));
            int r = self(s.substr(p2 + 1));
            if(l <= 0 || r <= 0) return -1;
            if(s[p2] == '/' && r == 1) return -1;
            return 1;
        }
        return mp.count(s) ? mp[s] : 2;
    };

    for(int i = 1; i <= n; i++) {
        getline(cin, line);
        stringstream ss(line);
        string t, name, expr;
        vector<string> parts;
        while(ss >> t) {
            parts.push_back(t);
        }
        int k = 0; 
        while(parts[k] != "define" && parts[k] != "#define") {
            k++;
        }
        name = parts[k + 1];
        for(int j = k + 2; j < parts.size(); j++) {
            expr += parts[j];
        }
        mp[name] = dfs(expr);
    }
    getline(cin, line);
    if(dfs(norm(line)) == -1) {
        cout << "Suspicious\n";
    } else {
        cout << "OK\n";
    }
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
