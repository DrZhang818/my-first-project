#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;
const int inf = INT_MAX / 2;


//https://codeforces.com/contest/2043/problem/C
/*
    动态规划 —— 前缀最值
    题意:
        给定一个数组, 数组中至多有一个元素既不是-1也不是1, 其余元素全部为-1或1
        目标是求出所有子数组(可能为空)的sum组成的集合大小, 并按升序输出集合元素
    关键思考:
        1.朴素双循环写法时间复杂度为O(n^2)
        2.涉及到子数组的sum问题, 往往试着考虑前缀和优化
        3.思考如果不考虑special元素的话, 怎么快速计算呢?
            由于数字的abs全部为1, 意味着每次步长都为1, 换句话说, 在整数域上的值域是连续的
            只需要找到子数组最小值和最大值, 介于二者之间的数都是可达的
        4.以上情况是不包含special元素的, 如果包含怎么计算呢?
            首先, 比较容易想到的是前后缀分解
                let p = i of speEle
                最小值就是nums[p] + p前面的最小值 + p后面的最小值
                最大值同理
            而在此基础上可以继续优化
                本质上, 我们是在计算包含nums[p]的子数组的最大值和最小值
                可以用包含nums[p]的最大子数组 - p之前最小子数组, 这样就得到了最大值
                最小值同理
*/

//优化写法
void solve1(){
    int n, l1, r1, l2, r2, p = 0;
    cin >> n;
    vector<int> nums(n), prefix(n + 1);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        if(nums[i] != -1 && nums[i] != 1){
            p = i;
        }
        prefix[i + 1] = prefix[i] + nums[i];
    }


    l1 = r1 = 0;
    l2 = r2 = nums[p];
    int mn = inf, mx = -inf;
    for(int i = 0; i <= n; i++){
        if(i == p + 1){
            mn = mx = prefix[i];//跳过计算nums[p]
            continue;
        }
        l1 = min(l1, prefix[i] - mx);
        r1 = max(r1, prefix[i] - mn);
        mn = min(mn, prefix[i]);
        mx = max(mx, prefix[i]);
    }

    mn = inf, mx = -inf;
    for(int i = 0; i <= p; i++) mn = min(mn, prefix[i]);
    for(int i = p + 1; i <= n; i++) mx = max(mx, prefix[i]);
    r2 = mx - mn;
    mn = inf, mx = -inf;
    for(int i = 0; i <= p; i++) mx = max(mx, prefix[i]);
    for(int i = p + 1; i <= n; i++) mn = min(mn, prefix[i]);
    l2 = mn - mx;

    if(l1 < l2){
        swap(l1, l2);
        swap(r1, r2);
    }
    ll len = r2 - l2 + 1 + r1 - max(r2 + 1, l1) + 1;
    cout << len << "\n";
    for(int i = l2; i <= r2; i++) cout << i << " ";
    for(int i = max(r2 + 1, l1); i <= r1; i++) cout << i << " ";
    cout << "\n";
}

//优化写法2
PII dp(const vector<int>& a){
    int f = 0, g = 0;
    int minF = 0, maxF = 0;
    for(auto v : a){
        f = min(f, 0) + v;
        g = max(g, 0) + v;
        minF = min(minF, f);
        maxF = max(maxF, g);
    }
    return {minF, maxF};
}
void solve2(){
    int n;
    cin >> n;
    vector<int> a(n);
    int idx = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] < -1 || a[i] > 1){
            idx = i;
        }
    }
    vector<int> ans;
    auto add = [&](int l, int r){
        if(l > r) swap(l, r);
        for(int i = l; i <= r; i++){
            ans.push_back(i);
        }
    };
    PII p1 = dp(vector<int>(a.begin(), a.begin() + idx));
    add(p1.first, p1.second);
    PII p2 = dp(vector<int>(a.begin() + idx + 1, a.end()));
    add(p2.first, p2.second);
    int l_sum = 0, minL = 0, maxL = 0;
    for(int i = idx - 1; i >= 0; i--){
        l_sum += a[i];
        minL = min(minL, l_sum);
        maxL = max(maxL, l_sum);
    }
    int r_sum = 0, minR = 0, maxR = 0;
    for(int i = idx + 1; i < n; i++){
        r_sum += a[i];
        minR = min(minR, r_sum);
        maxR = max(maxR, r_sum);
    }
    int total_L = minL + a[idx] + minR;
    int total_R = maxL + a[idx] + maxR;
    add(total_L, total_R);
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}

//比赛时写法(赛后写完，屎山)
void solve(){
    int n;
    cin >> n;
    std::vector<ll> nums(n);;
    for(int i = 0; i < n; i++) cin >> nums[i];
    if(n == 1){
        if(nums[0] != 0){
            cout << "2\n";
            if(nums[0] > 0){
                cout << 0 << " " << nums[0] << "\n";
            }else{
                cout << nums[0] << " " << 0 << "\n";
            }
        }
        else{
            cout << "1\n";
            cout << "0\n";
        }
        return;
    }
    ll premin, premax, sufmin, sufmax;
    premin = 0;
    premax = 0;
    ll lmin, lmax, rmin, rmax;
    lmin = rmin = INT_MAX;
    lmax = rmax = INT_MIN;
    ll num;
    bool ok = false;
    for(int i = 0; i < n; i++){
        if(nums[i] != -1 && nums[i] != 1){
            ok = true;
            num = nums[i];
            break;
        }
        lmin = min(lmin, premin);
        lmax = max(lmax, premax);
        premin = min(premin + nums[i], nums[i]);
        premax = max(nums[i] + premax, nums[i]);
        lmin = min(lmin, premin);
        lmax = max(lmax, premax);
    }
    
    sufmin = 0;
    sufmax = 0;
    for(int i = n - 1; i >= 0; i--){
        if(!ok || nums[i] != -1 && nums[i] != 1){
            break;
        }
        rmin = min(rmin, sufmin);
        rmax = max(rmax, sufmax);
        sufmin = min(sufmin + nums[i], nums[i]);
        sufmax = max(nums[i] + sufmax, nums[i]);
        rmin = min(rmin, sufmin);
        rmax = max(rmax, sufmax);
    }

    if(!ok){
        cout << lmax - lmin + 1 << "\n";
        for(int i = lmin; i <= lmax; i++){
            cout << i << " ";
        }
        cout << "\n";
        return;
    }
    vector<pair<ll, ll>> a;
    ll mi = min({0LL, premin, sufmin, premin + sufmin});
    ll ma = max({0LL, premax, sufmax, premax + sufmax});
    a.push_back({num + mi, num + ma});
    if(lmin!=INT_MAX) a.push_back({lmin, lmax});
    if(rmin!=INT_MAX) a.push_back({rmin, rmax});
    sort(a.begin(), a.end(), [](auto &a, auto &b){
        return a.first < b.first;
    });
    ll size = 0;
    ll cur = a[0].first;
    for(int i = 0; i < a.size(); i++){
        cur = max(cur, a[i].first);
        while(cur <= a[i].second){
            cur++;
            size++;
        }
    }
    cout << size << "\n";
    cur = a[0].first;
    for(int i = 0; i < a.size(); i++){
        cur = max(cur, a[i].first);
        while(cur <= a[i].second){
            cout << cur << " ";
            cur++;
        }
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve2();
    }
    return 0;    
}
