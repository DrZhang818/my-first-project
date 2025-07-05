#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int w, ans = -1;
    scanf("%d", &w);
    if(w <= 100) {
        if(w % 10 != 0) ans = w - (w % 10);
        else ans = w - 10;
    } else {
        ans = 100;
    }
    printf("Gong xi nin! Nin de ti zhong yue wei: %d duo jin\n", ans);
}

int main()
{

    solve();
    return 0;
}
    
