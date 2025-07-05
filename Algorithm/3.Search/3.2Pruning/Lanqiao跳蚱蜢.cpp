#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    queue<pair<string,int>> q;
    q.push({"012345678",0});
    unordered_map<string,int> mp;
    while(!q.empty()) {
        int n = q.size();
        for(int i = 0; i < n; i++) {
            auto cur = q.front();
            q.pop();
            string s = cur.first;
            int cnt = cur.second;
            if(s == "087654321") {
                cout << cnt << "\n";
                return ;
            }
            mp[s]++;
            int idx = 0;
            while(s[idx] != '0') idx++;
            for(int j = idx - 2; j <= idx + 2; j++) {
                if(j == idx) continue;
                string temp = s;
                swap(temp[(j + 9) % 9], temp[idx]);
                if(mp[temp] == 0) {
                    q.push({temp, cnt + 1});
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

