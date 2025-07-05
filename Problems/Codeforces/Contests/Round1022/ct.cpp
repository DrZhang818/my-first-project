#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> a;
int n;
int solve1() {
    vector<int> aa = a;
    vector<int> b = {0};
    for(int i = 0; i < n; i++) {
        if(aa[i] != aa[i - 1]) b.push_back(aa[i]); 
    }
    int nn = b.size() - 1;
    vector<int> idx(nn + 1);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin() + 1, idx.end(), [&](auto x, auto y){
        if(b[x] == b[y]) return x < y;
        return b[x] > b[y];
    });
    int ans = 0;
    set<int> st;
    for(int i = 1; i <= nn; i++) {
        if(!st.count(idx[i] - 1) && !st.count(idx[i] + 1)) ans++;
        st.insert(idx[i]);
    }
    return ans;
}
int solve2() {
    
    vector<int> c = a;
    c.erase(std::unique(c.begin(), c.end()), c.end());
    int nn = c.size();
    
    int ans = 0;
    for (int i = 0; i < nn; i++) {
        if ((i == 0 || c[i] > c[i - 1]) && (i + 1 == nn || c[i] > c[i + 1])) {
            ans++;
        }
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    srand(time(0));
    n = 10000;
    a.resize(n);
    for(int i = 0; i < 100000; i++) {
        for(int j = 0; j < n; j++) {
            a[j] = rand() % 1000 + 1;
        }
        int p1 = solve1();
        int p2 = solve2();
        if(p1 != p2) {
            cerr << "WA!\n";
            for(int x : a) {
                cerr << x << " ";
            }
            cerr << "\n";
            cerr << p1 << "\n";
            cerr << p2 << "\n";
            cerr << "\n";
        }
    }
    return 0;
}
