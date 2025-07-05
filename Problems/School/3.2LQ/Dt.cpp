#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


string norm(string &s) {
    int i = 0, n = s.size();
    while(i < n && s[i] == '0') i++;
    return i == n ? "0" : s.substr(i);
}
string add(string &s, string &t) {
    int i = s.size() - 1, j = t.size() - 1, c = 0;
    string res;
    while(i >= 0 || j >= 0 || c) {
        if(i >= 0) c += s[i--] - '0';
        if(j >= 0) c += t[j--] - '0';
        res += '0' + c % 10;
        c /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}
string sub(string &s, string &t) {
    int i = s.size() - 1, j = t.size() - 1, c = 0;
    string res;
    while(i >= 0) {
        int d = s[i--] - '0' - c;
        if(j >= 0) d -= t[j--] - '0';
        if(d < 0) c = 1, d += 10;
        else c = 0;
        res += '0' + d;
    }
    reverse(res.begin(), res.end());
    return res;
}
int cmp(string &s, string &t) {
    if(s.size() != t.size()) return s.size() - t.size();
    return s.compare(t);
}
string add_big(string x, string y) {
    int sx = 1, sy = 1;
    if(x[0] == '-') {
        sx = -1;
        x = x.substr(1);
    }
    if(y[0] == '-') {
        sy = -1;
        y = y.substr(1);
    }
    x = norm(x);
    y = norm(y);
    string res;
    if(sx == sy) {
        res = add(x, y);
        if(sx < 0 && res != "0") {
            res = "-" + res;
        }
    } else {
        if(cmp(x, y) >= 0) {
            res = sub(x, y);
            if(sx < 0 && res != "0") {
                res = "-" + res;
            }
        } else {
            res = sub(y, x);
            if(sy < 0 && res != "0") {
                res = "-" + res;
            }
        }
    }
    return norm(res);
}
void solve() { 
    string tot = "0", cost = "0", inc = "0";
    string s;
    while(cin >> s) {
        tot = add_big(tot, s);
        if(s[0] == '-') cost = add_big(cost, s);
        else inc = add_big(inc, s);
    }
    cout << tot << "\n" << cost << "\n" << inc << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
