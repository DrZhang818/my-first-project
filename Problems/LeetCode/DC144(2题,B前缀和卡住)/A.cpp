#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/stone-removal-game/description/

/*
	模拟
	目标: n < pick时轮到谁操作
		  这里比较巧妙运用pick本身的奇偶性来表征"轮到谁操作"
*/
class Solution {
public:
    bool canAliceWin(int n) {
        int pick = 10;
        while(n >= pick){
        	n -= pick;
        	pick--;
        }
        return (10 - pick) % 2; // 或pick % 2
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    return 0;
}





