#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class AuctionSystem {
private:
    unordered_map<int,set<PII>> val;
    unordered_map<int,unordered_map<int,int>> amt;
public:
    AuctionSystem() {
    }
    
    void addBid(int userId, int itemId, int bidAmount) {
        if(amt[userId].contains(itemId)) {
            PII cur = {amt[userId][itemId], userId};
            val[itemId].erase(cur);
        }
        amt[userId][itemId] = bidAmount;
        val[itemId].insert({bidAmount, userId});
    }
    
    void updateBid(int userId, int itemId, int newAmount) {
        PII cur = {amt[userId][itemId], userId};
        val[itemId].erase(cur);
        amt[userId][itemId] = newAmount;
        val[itemId].insert({newAmount, userId});
    }
    
    void removeBid(int userId, int itemId) {
        PII cur = {amt[userId][itemId], userId};
        val[itemId].erase(cur);
        amt[userId].erase(itemId);
    }
    
    int getHighestBidder(int itemId) {
        if(val[itemId].empty()) {
            return -1;
        }
        auto it = *val[itemId].rbegin();
        return it.second;
    }
};

