#include<iostream>
#include<unordered_map>
#include<queue>
#include<algorithm>
#include<iomanip>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    string s;
    while(getline(cin, s) && s != "END") {
        unordered_map<char, int> mp;
        for(int i = 0; i < s.size(); i++) mp[s[i]]++;
        priority_queue<int, vector<int>, greater<int>> pq;
        for(auto it = mp.begin(); it != mp.end(); it++) {
            char c = it->second;
            pq.push(c);
        }
        int ans = 0;
        if(pq.size() == 1) {
            ans = s.size();
        } else {
            while(pq.size() > 1) {
                int a = pq.top();
                pq.pop();
                int b = pq.top();
                pq.pop();
                ans += a + b;
                pq.push(a + b);
            }
        }
        cout << fixed << setprecision(1) << (db)8 * s.size() / (db)ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

