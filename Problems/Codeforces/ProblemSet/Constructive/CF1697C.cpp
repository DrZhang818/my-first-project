#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
//https://codeforces.com/contest/1697/problem/C
/*
    构造 
    题意:
        给定两个长度为N的字符串S和T, 字符串只含abc三种字符, 你可以对S进行任意次下列操作:
        op1: 把一个子串"ab"替换为"ba"
        op2: 把一个子串"bc"替换为"cb"
        问能否通过以上操作, 使得S与T相同
        范围: n∈[1,1e5]
    关键思考: 
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一半
        观察两种操作的性质, 我们发现:
        (1)操作不会改变每种字符的数量
        (2)a,c直接无法交换, 意味着字符串中a,c的出现顺序不会改变
        (3)a只能向右调整, c只能向左调整
        利用这三种显而易见的性质, 我们竟然就可以解决这道题目
        性质(1)告诉我们, 两个字符串每种字符的数量必须相同, 因此不相同就输出NO
        性质(2)告诉我们, 两个字符串a,c的出现顺序必须相同, 我们可以收集起来并判断
        性质(3)告诉我们, S中的a必须比T中的a出现的更早, c必须比T中的c出现的更晚
        实现时只需要完成三个性质的验证, 如果成立就一定可以转化
        下面给出充分性证明:
            当满足性质(1)(2)(3)时, 我们可以采取以下策略进行操作:
            从最后一个a出发, 向前把所有a调整归位
            从第一个c出发,   向后把所有c调整归位
            由于性质(2)(3), a的调整路径上一定不会有c出现, c的调整路径上一定不会有a出现
            否则试想以下情况
            ...ac....
                 a...
            当a往右调整时, 如果路径上有c:
            1.这个c要往前调整, 那么违反了性质(2), 因为c'在a'左, 而c在a右, 顺序不一
            2.这个c要往后调整, 那么违反了性质(3), 因为c'在a'右, 而c在a'左, 则c在c'左, 不合法
            综上, 路径上存在障碍的情况被排除, 那么只要按照策略顺序进行, 已经能够转化成T
*/              
void solve1() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    for(auto c : {'a', 'b', 'c'}) {
        if(count(s.begin(), s.end(), c) != count(t.begin(), t.end(), c)) {
            cout << "NO\n";
            return;
        }
    }
    string sl, tl;
    vector<int> a, b;
    for(int i = 0; i < n; i++) {
        if(s[i] != 'b') {
            sl += s[i];
            a.push_back(i);
        }
        if(t[i] != 'b') {
            tl += t[i];
            b.push_back(i);
        }
    }
    if(sl != tl) {
        cout << "NO\n";
        return;
    }
    for(int i = 0; i < a.size(); i++) {
        if(sl[i] == 'a' ? (a[i] > b[i]) : (a[i] < b[i])) {
            cout << "NO\n";
            return;
        } 
    }
    cout << "YES\n";
}   


void solve() { 
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;

    bool ok = true;
    for(int i = 0; i < n && ok; i++) {
        if(s[i] == t[i]) continue;
        if(s[i] == 'a') {
            if(t[i] == 'c') {
                ok = false;
                break;
            }
            for(int j = i + 1; j < n; j++) {
                if(s[j] == 'c') {
                    ok = false;
                    break;
                }
                if(s[j] == t[i]) {
                    swap(s[i], s[j]);
                    break;
                }
            }
            if(s[i] != t[i]) ok = false;
        } else if(s[i] == 'b') {
            if(t[i] == 'a') {
                ok = false;
                break;
            }
            for(int j = i + 1; j < n; j++) {
                if(s[j] == 'a') {
                    ok = false;
                    break;
                }
                if(s[j] == t[i]) {
                    swap(s[i], s[j]);
                    break;
                }
            }
            if(s[i] != t[i]) {
                ok = false;
            }
        } else {
            ok = false;
        }
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve1();
    }
    return 0;
}
    
