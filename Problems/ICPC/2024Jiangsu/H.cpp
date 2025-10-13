#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

#include <bits/stdc++.h>
using namespace std;

template<class T>
struct MaxAssignment {
    public:
        T solve(int nx, int ny, vector<vector<T>> a) {
            assert(0 <= nx && nx <= ny);
            assert(int(a.size()) == nx);
            for(int i = 0; i < nx; i++) {
                assert(int(a[i].size()) == ny);
                for(auto x : a[i]) 
                    assert(x >= 0);
            }
            auto update = [&](int x) {
                for(int y = 0; y < ny; y++) {
                    if(lx[x] + ly[y] - a[x][y] < slack[y]) {
                        slack[y] = lx[x] + ly[y] - a[x][y];
                        slackx[y] = x;
                    }
                }
            };

            costs.resize(nx + 1);
            costs[0] = 0;
            lx.assign(nx, numeric_limits<T>::max());
            ly.assign(ny, 0);
            xy.assign(nx, -1);
            yx.assign(ny, -1);
            slackx.resize(ny);
            for(int cur = 0; cur < nx; cur++) {
                queue<int> que;
                visx.assign(nx, false);
                visy.assign(ny, false);
                slack.assign(ny, numeric_limits<T>::max());
                p.assign(nx, -1);

                for(int x = 0; x < nx; x++) {
                    if(xy[x] == -1) {
                        que.push(x);
                        visx[x] = true;
                        update(x);
                    }
                }
                
                int ex, ey;
                bool found = false;
                while(!found) {
                    while(!que.empty() && !found) {
                        auto x = que.front();
                        que.pop();
                        for(int y = 0; y < ny; y++) {
                            if(a[x][y] == lx[x] + ly[y] && !visy[y]) {
                                if(yx[y] == -1) {
                                    ex = x;
                                    ey = y;
                                    found = true;
                                    break;
                                }
                                que.push(yx[y]);
                                p[yx[y]] = x;
                                visy[y] = visx[yx[y]] = true;
                                update(yx[y]);
                            }
                        }
                    }
                    if(found) 
                        break;
                    T delta = numeric_limits<T>::max();
                    for(int y = 0; y < ny; y++) 
                        if(!visy[y]) 
                            delta = min(delta, slack[y]);
                    for(int x = 0; x < nx; x++) 
                        if(visx[x]) 
                            lx[x] -= delta;
                    for(int y = 0; y < ny; y++) {
                        if(visy[y]) {
                            ly[y] += delta;
                        } else {
                            slack[y] -= delta;
                        }
                    }
                    for(int y = 0; y < ny; y++) {
                        if(!visy[y] && slack[y] == 0) {
                            if(yx[y] == -1) {
                                ex = slackx[y];
                                ey = y;
                                found = true;
                                break;
                            }
                            que.push(yx[y]);
                            p[yx[y]] = slackx[y];
                            visy[y] = visx[yx[y]] = true;
                            update(yx[y]);
                        }
                    }
                }

                costs[cur + 1] = costs[cur];
                for(int x = ex, y = ey, ty; x != -1; x = p[x], y = ty) {
                    costs[cur + 1] += a[x][y];
                    if(xy[x] != -1) 
                        costs[cur + 1] -= a[x][xy[x]];
                    ty = xy[x];
                    xy[x] = y;
                    yx[y] = x;
                }
            }
            return costs[nx];
        }
        vector<int> assignment() {
            return xy;
        }
        pair<vector<T>, vector<T>> labels() {
            return make_pair(lx, ly);
        }
        vector<T> weights() {
            return costs;
        }
    private:
        vector<T> lx, ly, slack, costs;
        vector<int> xy, yx, p, slackx;
        vector<bool> visx, visy;
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            cin >> a[i];
        }
    }

    vector costs(n, vector<int>(3 * n));
    for(int i = 0; i < n; i++) {
        if(a[i] == 0) {
            continue;
        }
        for(int j = i + 1; j < n; j++) {
            if(a[j] > 0) {
                continue;
            }
            costs[i][3 * j] = a[i] - 1;
            costs[i][3 * j + 1] = a[i] - (a[i] + 9) / 10;
            costs[i][3 * j + 2] = a[i];
        }
    }
    int ans = MaxAssignment<int>().solve(n, 3 * n, costs);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
