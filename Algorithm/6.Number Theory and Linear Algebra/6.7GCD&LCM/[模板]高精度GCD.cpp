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
string add(string &a, string &b) {
    int i = a.size() - 1, j = b.size() - 1, c = 0;
    string res;
    while(i >= 0 || j >= 0 || c) {
        if(i >= 0) c += a[i--] - '0';
        if(j >= 0) c += b[j--] - '0';
        res += '0' + c % 10;
        c /= 10;
    }   
    reverse(res.begin(), res.end());
    return res;
}
string sub(string &a, string &b) {
    int i = a.size() - 1, j = b.size() - 1, c = 0;
    string res;
    while(i >= 0) {
        int t = a[i--] - '0' - c;
        if(j >= 0) t -= b[j--] - '0';
        if(t < 0) t += 10, c = 1;
        else c = 0;
        res += '0' + t;
    }
    reverse(res.begin(), res.end());
    return norm(res);
}
int cmp(string &a, string &b) {
    if(a.size() != b.size()) return a.size() - b.size();
    return a.compare(b);
}
string add_int(string x, string y) {
    int sx = 1, sy = 1;
    if(x[0] == '-') {
        sx = -1;
        x = x.substr(1);
    }
    if(y[0] == '-') {
        sy = -1;
        y = y.substr(1);
    }
    x = norm(x), y = norm(y);
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
    return res;
}
string mul(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<int> res(n + m, 0);
    for(int i = n - 1; i >= 0; i--) {
        for(int j = m - 1; j >= 0; j--) {
            int t = (a[i] - '0') * (b[j] - '0');
            int sum = res[i + j + 1] + t;
            res[i + j + 1] = sum % 10;
            res[i + j] = sum / 10;
        }
    }
    string s;
    for(int i = 0; i < res.size(); i++) {
        if(!(s.empty() && res[i] == 0)) {
            s += '0' + res[i];
        }
    }
    return s.empty() ? "0" : s;
}
string mul_big(string x, string y) {
    int sx = 1, sy = 1;
    if(x[0] == '-') {
        sx = -1;
        x = x.substr(1);
    }
    if(y[0] == '-') {
        sy = -1;
        y = y.substr(1);
    }
    x = norm(x), y = norm(y);
    string res = mul(x, y);
    if(sx * sy < 0 && res != "0") {
        res = "-" + res;
    }
    return res;
}
string div(string &a, string &b) {
    string res, cur;
    for(int i = 0; i < a.size(); i++) {
        cur += a[i];
        cur = norm(cur);
        int cnt = 0;
        while(cmp(cur, b) >= 0) {
            cur = sub(cur, b);
            cnt++;
        }
        res += '0' + cnt;
    }
    return norm(res);
}
string div_big(string x, string y) {
    int sx = 1, sy = 1;
    if(x[0] == '-') {
        sx = -1;
        x = x.substr(1);
    }
    if(y[0] == '-') {
        sy = -1;
        y = y.substr(1);
    }
    x = norm(x), y = norm(y);
    if(cmp(x, y) < 0) return "0";
    string res = div(x, y);
    if(sx * sy < 0 && res != "0") {
        res = "-" + res;
    }
    return res;
}
string mod_big(string x, string y) {
    string quo = div(x, y);
    string pro = mul(quo, y);
    string rem = sub(x, pro);
    return norm(rem);
}
string gcd_big(string a, string b) {
    a = norm(a), b = norm(b);
    return b != "0" ? gcd_big(b, mod_big(a, b)) : a;
}
string lcm_big(string a, string b) {
    if(a == "0" || b == "0") return "0";
    string g = gcd_big(a, b);
    string dr = div_big(a, g);
    return mul(dr, b);
}
void solve() {
    string a, b;
    cin >> a >> b;
    cout << gcd_big(a, b) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
