#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://www.marscode.cn/practice/vkjwp462l6q75q?problem_id=7414004855076077612

/*
    状态机DP, 简单数论, 简单组合数学
*/
int solution(vector<int> numbers) {
    int n = numbers.size();
    vector<int> odd(n), even(n);
    for(int i = 0; i < n; i++){
        int& num = numbers[i];
        int cnto = 0, cnte = 0;
        while(num){
            int pop = num % 10;
            pop % 2 == 0 ? cnte++ : cnto++;
            num /= 10;
        }
        odd[i] = cnto;
        even[i] = cnte;
    }
    vector<int> pre(2);
    vector<int> cur(2);
    pre[0] = even[0], pre[1] = odd[0];
    for(int i = 1; i < n; i++){
        cur[0] = pre[0] * even[i] + pre[1] * odd[i];
        cur[1] = pre[0] * odd[i] + pre[1] * even[i];
        pre = cur;
    }
    return pre[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}




