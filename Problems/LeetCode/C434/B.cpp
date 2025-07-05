#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


struct info{
    int flag;
    int t;
    int id;
};
class Solution {
public:
    vector<int> countMentions(int n, vector<vector<string>>& events) {
        vector<int> ans(n);
        int size = events.size();
        vector<info> infos(size);
        for(int i = 0; i < size; i++){
            int flag = events[i][0] == "MESSAGE" ? 0 : 1;
            int time = stoi(events[i][1]);
            if(flag == 0){
                if(events[i][2] == "HERE"){
                    info a;
                    a.flag = 0;
                    a.t = time;
                    a.id = -1;
                    infos.push_back(a);
                }
                else if(events[i][2] == "ALL"){
                    info a;
                    a.flag = 0;
                    a.t = time;
                    a.id = -2;
                    infos.push_back(a);
                }
                else{
                    string s;
                    for(auto c : events[i][2]){
                        if(c == ' '){
                            info a;
                            a.flag = 0;
                            a.t = time;
                            a.id = stoi(s);
                            infos.push_back(a);
                            s.clear();
                        }
                        if(c >= '0' && c <= '9') s += c;
                    }
                    if(s != ""){
                        info a;
                        a.flag = 0;
                        a.t = time;
                        a.id = stoi(s);
                        infos.push_back(a);
                        s.clear();
                    }
                }
            }
            else{
                info a;
                a.flag = 1;
                a.t = time;
                a.id = stoi(events[i][2]);
                infos.push_back(a);
            }
        }
        sort(infos.begin(), infos.end(), [](const info& a, const info& b){
            return a.t < b.t;
        });
        vector<int> vis(101, -1);
        for(int i = 0; i < size; i++){
            auto &cur = infos[i];
            if(cur.flag == 1){
                vis[cur.id] = cur.t + 60;
            }
            else{
                int curt = cur.t;
                if(cur.id == -1){
                    for(int i = 0; i < n; i++){
                        if(vis[i] < curt){
                            ans[i]++;
                        }
                    }
                }
                else if(cur.id == -2){
                    for(int i = 0; i < n; i++){
                        ans[i]++;
                    }
                }
                else{
                    int id = cur.id;
                    if(vis[id] < curt){
                        ans[id]++;
                    }
                }
            }
        }
        return ans;
    }
};