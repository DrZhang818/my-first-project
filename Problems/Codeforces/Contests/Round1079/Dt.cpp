#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int solve(const string& s) {  
    int n = s.size();

    stack<int> stk0, stk1;
    vector<int> pos0, pos1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            stk0.push(i);
        } else if(s[i] == ')') {
            if(!stk0.empty()) {
                stk0.pop();
            } else {
                pos0.push_back(i);
            }
        } else if(s[i] == '[') {
            stk1.push(i);
        } else {
            if(!stk1.empty()) {
                stk1.pop();
            } else {
                pos1.push_back(i);
            }
        }
    }

    vector<int> p;
    for(int i : pos0) p.push_back(i);
    for(int i : pos1) p.push_back(i);
    int rem = p.size();
    while(!stk0.empty()) {
        p.push_back(stk0.top());
        stk0.pop();
    }
    while(!stk1.empty()) {
        p.push_back(stk1.top());
        stk1.pop();
    }

    sort(p.begin(), p.end());

    int ans = 0;
    int L = 0, R = 0;
    for(int i : p) {
        if(s[i] == '(' || s[i] == '[') {
            L++;
        } else {
            if(R > 0) {
                R--;
                continue;
            }
            if(rem > 1) {
                R++;
                rem -= 2;
                ans++;
            } else if(L > 0) {
                L--;
                rem--;
                ans++;
            } 
        }
    }

    assert(R == 0);
    assert(rem <= 1);

    if(rem == 1) {
        ans += 2;
        L--;
    }

    ans += L / 2;

    return ans;
}

int brute(const string& s) {  
    int ans = inf;
    int n = s.size();

    auto dfs = [&](this auto&& self, int i, int cnt, int s0, int s1) {
        if(i == n) {
            if(s0 == 0 && s1 == 0) {
                ans = min(ans, cnt);
            }
            return;
        }

        if(s[i] == '(') {
            self(i + 1, cnt, s0 + 1, s1);
            if(s0 - 1 >= 0) self(i + 1, cnt + 1, s0 - 1, s1);
            self(i + 1, cnt + 1, s0, s1 + 1);
            if(s1 - 1 >= 0) self(i + 1, cnt + 1, s0, s1 - 1);
        } else if(s[i] == ')') {
            if(s0 - 1 >= 0) self(i + 1, cnt, s0 - 1, s1);
            self(i + 1, cnt + 1, s0 + 1, s1);
            self(i + 1, cnt + 1, s0, s1 + 1);
            if(s1 - 1 >= 0) self(i + 1, cnt + 1, s0, s1 - 1);
        } else if(s[i] == '[') {
            self(i + 1, cnt, s0, s1 + 1);
            if(s1 - 1 >= 0) self(i + 1, cnt + 1, s0, s1 - 1);
            self(i + 1, cnt + 1, s0 + 1, s1);
            if(s0 - 1 >= 0) self(i + 1, cnt + 1, s0 - 1, s1);
        } else {
            if(s1 - 1 >= 0) self(i + 1, cnt, s0, s1 - 1);
            self(i + 1, cnt + 1, s0, s1 + 1);
            self(i + 1, cnt + 1, s0 + 1, s1);
            if(s0 - 1 >= 0) self(i + 1, cnt + 1, s0 - 1, s1);
        }
    };
    dfs(0, 0, 0, 0);

    return ans;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rng() % (R - L + 1) + L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s = "#######";
    int n = 7;

    for(int _ = 0; _ < 100000; _++) {
        for(int i = 0; i < n; i++) {
            int x = get(1, 4);
            s[i] = x == 1 ? '(' : x == 2 ? ')' : x == 3 ? '[' : ']';
        }

        int ans1 = solve(s);
        int ans2 = brute(s);

        if(ans1 != ans2) {
            cout << "WA!\n";
            cerr << s << "\n";
            cerr << ans1 << " " << ans2 << "\n";
        }

    }

    return 0;
}
