#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct node{
    int val, nxt;
    node(int x = 0, int n = 0) : val(x), nxt(n) {}
};
class List{
private:
    vector<node> a;
    unordered_map<int,int> mp;
    int size;
public:
    List(int n) {
        a.resize(n);
        size = 0;
    }   
    void ins_back(int x, int y) {
        int pos = mp[x];
        a[++size] = node(y, a[pos].nxt);
        a[pos].nxt = size;
        mp[y] = size;
    }
    void erase(int x) {
        int pos = mp[x];
        a[pos].nxt = a[a[pos].nxt].nxt;
    }
    int at(int x) {
        int pos = mp[x];
        return a[a[pos].nxt].val;
    }
};
void solve(){
    int n;
    cin >> n;
    List lst(n + 2);
    lst.ins_back(0, 1);
    for(int i = 0; i < n; i++) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int x, y;
            cin >> x >> y;
            lst.ins_back(x, y);
        }
        else if(flag == 2) {
            int x;
            cin >> x;
            cout << lst.at(x) << "\n";
        }
        else if(flag == 3) {
            int x;
            cin >> x;
            lst.erase(x);
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

