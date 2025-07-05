#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Solution {
private:
    int lcm(int a, int b){
        return a / __gcd(a, b) * b;
    }
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        int Lcm = 1;
        for(int x : target){
            Lcm = lcm(Lcm, x);
        }
        
    }
};