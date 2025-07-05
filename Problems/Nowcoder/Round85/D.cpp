#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;



//https://ac.nowcoder.com/acm/contest/103948/D
//前缀异或和解法
void solve1() {
    int n;
    string s;
    cin >> n >> s;
    s = "#" + s;
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] ^ (s[i] == '1' ? 1 : 2);
    }
    unordered_set<int> st;
    int cnt = 0;
    for(int i = n; i >= 1; i--) {
        if(st.count(pre[i])) {
            cnt++;
        }
        st.insert(pre[i]);
    }
    cout << (db)cnt / n << "\n";
}

//状态机DP做法
void solve() { 
    int n;
    string s;
    cin >> n >> s;
    s = "#" + s;
    vector<int> dp(4);
    int c0 = 0, c1 = 0;
    for(int i = 1; i <= n; i++) {
        c0 += s[i] == '0';
        c1 += s[i] == '1';
        if(c0 % 2 == 0 && c1 % 2 == 0) dp[0]++;
        else if(c0 % 2 == 0 && c1 % 2 != 0) dp[1]++;
        else if(c1 % 2 == 0 && c0 % 2 != 0) dp[2]++;
        else dp[3]++;
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0') {
            dp[2]--;
            swap(dp[0], dp[2]);
            swap(dp[1], dp[3]);
        } else {
            dp[1]--;
            swap(dp[0], dp[1]);
            swap(dp[2], dp[3]);
        }
        if(dp[0] > 0) cnt++; 
    }
    cout << (db)cnt / n << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve1();
    return 0;
}
    
