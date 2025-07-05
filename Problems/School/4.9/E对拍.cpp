#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
#define lowbit(x) x&-x
    
int n;
string s;
vector<int> tr;
void add(int o, int d) { for(; o <= n; o += o & -o) tr[o] += d; }
int query(int o) {
    int res = 0;
    for(; o > 0; o -= o & -o) res += tr[o];
    return res;
}

int solve1() { 
    string ss = "#" + s;
    tr.assign(n + 2, 0);
    vector<int> c(26);
    for(int i = 1; i <= n; i++) c[ss[i] - 'a']++;
    int odd = 0;
    char tar;
    for(int i = 0; i < 26; i++) if(c[i] % 2 == 1) odd++, tar = i + 'a';
    if(odd > 1) {
        return -1;
    }
    int cnt = 0;
    vector<deque<int>> dq(26);
    for(int i = 1; i <= n; i++) {
        dq[ss[i] - 'a'].push_back(i);
    }
    vector<bool> vis(n + 1);
    int i = 1, cur = 1, flag = 0;
    ll ans = 0;
    for(; i <= n / 2; i++) {
        while(vis[cur]) cur++;
        int it = dq[ss[cur] - 'a'].back();
        if(it == cur) {
            flag = 1;
            vis[cur] = true;
            i--;
            continue;
        }
        int en = it - query(it);
        // cerr << i << " " << cur << " " << en << "\n";
        ans += n - i + 1 - en + flag;
        vis[it] = vis[cur] = true;
        add(it, 1);
        dq[ss[cur] - 'a'].pop_back();
    }
    return ans;
}

const int maxn=200005,maxk=30;
int all,flg,now;
long long ans;
int a[maxn],used[maxn],t[maxn];
vector<int>v[maxk];
void update(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i))
        t[i]+=v;
}
int qy(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i))
        res+=t[i];
    return res;
}
int solve2(){
    all = flg = now = ans = 0;
    for(int i = 0; i < maxn; i++) a[i] = used[i] = t[i] = 0;
    memset(v, 0, sizeof(v));
    for(int i=0;i<s.size();i++){
        a[i+1]=s[i]-96;
        v[s[i]-96].push_back(i+1);
    }
    for(int i=1;i<=26;i++)
        if(v[i].size()&1)
            all++;
    if(all>1){
        return -1;
    }
    for(int i=1;i<=n;i++)
        update(i,1),now++;
    for(int i=1;i<=n;i++){
        if(used[i])
            continue;
        int x=v[a[i]][v[a[i]].size()-1];
        if(x==i){
            v[a[i]].pop_back(),flg=1;
            used[i]=1,update(i,-1),now--;
            continue;
        }
        v[a[i]].pop_back();
        ans+=1ll*(now-qy(x))+flg;
        used[i]=used[x]=1;
        update(i,-1),update(x,-1),now-=2;
    }
    return ans;
}
string gene(int len) {
    string rdms = "";
    rdms.reserve(len);
    for(int i = 0; i < len; i++) {
        int num = rand() % 26;
        char c = num + 'a';
        rdms += c;
    }
    return rdms;
}
int main()
{
    srand(time(0));
    for(int i = 0; i < 10000000; i++) {
        int len = rand() % 20;
        s = gene(len);
        n = len;
        int a = solve1();
        int b = solve2();
        if(a != b){
            cerr << "WA\n";
            cerr << s << "\n";
            cerr << a << " " << b << "\n";
        }
    }
    return 0;
}
    
