#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

auto query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    string s;
    cin >> s;
    return s == "YES";
}


auto answer(const string& s) {
    cout << "! " << s << endl;
}

void solve() {
    int n, q;
    cin >> n >> q;

    if(n == 2) {
        string ans = "()";
        answer(ans);
        return;
    }

    vector<int> a(n + 1);
    a[n] = 1;
    stack<int> stk;

    int sum = 1;
    stk.push(1);    
    for(int i = 2; i <= n - 2; i++) {
        if(stk.empty()) {
            a[i] = 0;
            stk.push(i);
            sum += 1;
            continue;
        }
        int L = stk.top(); 

        int res = query(L, i);
        if(res) {
            stk.pop();
            sum--;
            a[i] = 1;
        } else {
            stk.push(i);
            sum++;
            a[i] = 0;
        }
    }

    if(sum != 0) {
        a[n - 1] = 1;
    }

    string ans;
    for(int i = 1; i <= n; i++) {
        if(a[i] == 0) {
            ans += "(";
        } else {
            ans += ")";
        }
    }

    answer(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}