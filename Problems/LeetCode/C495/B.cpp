#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct Info {
    int id, rk;
    friend bool operator<(const Info& a, const Info& b) {
        if(a.rk != b.rk) {
            return a.rk < b.rk;
        }
        return a.id > b.id;
    }
};

class EventManager {
public:
    priority_queue<Info> pq;    
    vector<Info> a;
    vector<int> id, rk;
    EventManager(vector<vector<int>>& events) {
        a.resize(events.size());
        for(int i = 0; i < events.size(); i++) {
            pq.push(Info(events[i][0], events[i][1]));
            a[i] = Info(events[i][0], events[i][1]);
        }
        sort(a.begin(), a.end(), 
            [&](auto x, auto y) {
                return x.id < y.id;
            });
        id.resize(events.size());
        rk.resize(events.size());
        for(int i = 0; i < events.size(); i++) {
            id[i] = a[i].id;
            rk[i] = a[i].rk;
        }
    }
    
    void updatePriority(int eventId, int newPriority) {
        int idx = lower_bound(id.begin(), id.end(), eventId) - id.begin();
        rk[idx] = newPriority;
        pq.push(Info(eventId, newPriority));
    }
    
    int pollHighest() {
        while(!pq.empty()) {
            auto [x, y] = pq.top(); pq.pop();
            int idx = lower_bound(id.begin(), id.end(), x) - id.begin();
            if(rk[idx] != y) {
                continue;
            }
            rk[idx] = -1;
            return x;
        }
        return -1;
    }
};