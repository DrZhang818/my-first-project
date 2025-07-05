class SegmentTree{
private:
    int n;
    vector<ll> sum;
    vector<ll> addArr;
    vector<ll> change;
    vector<bool> updateArr;
    void up(int i){
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    void down(int i, int ln, int rn){
        if(updateArr[i]){
            updateLazy(i << 1, change[i], ln);
            updateLazy(i << 1 | 1, change[i], rn);
            updateArr[i] = false;
        }
        if(addArr[i] != 0){
            addLazy(i << 1, addArr[i], ln);
            addLazy(i << 1 | 1, addArr[i], rn);
            addArr[i] = 0;
        }
    }
    void updateLazy(int i, ll v, int n){
        sum[i] = v * n;
        addArr[i] = 0;
        change[i] = v;
        updateArr[i] = true;
    }
    void addLazy(int i, ll v, int n){
        sum[i] += v * n;
        addArr[i] += v;
    }
    void build(vector<ll>& nums, int l, int r, int i){
        if(l == r){
            sum[i] = nums[l];
        }else{
            int mid = (l + r) >> 1;
            build(nums, l, mid, i << 1);
            build(nums, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    void updateHelp(int ul, int ur, ll v, int l, int r, int i){
        if(ul <= l && r <= ur){
            updateLazy(i, v, r - l + 1);
        }else{
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if(ul <= mid){
                updateHelp(ul, ur, v, l, mid, i << 1);
            }
            if(ur > mid){
                updateHelp(ul, ur, v, mid + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }
    void addHelp(int al, int ar, ll v, int l, int r, int i){
        if(al <= l && r <= ar){
            addLazy(i, v, r - l + 1);
        }else{
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if(al <= mid){
                addHelp(al, ar, v, l, mid, i << 1);
            }
            if(ar > mid){
                addHelp(al, ar, v, mid + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }
    ll queryHelp(int ql, int qr, int l, int r, int i){
        if(ql <= l && qr >= r){
            return sum[i];
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        ll ans = 0;
        if(ql <= mid){
            ans += queryHelp(ql, qr, l, mid, i << 1);
        }
        if(qr > mid){
            ans += queryHelp(ql, qr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
public:
    SegmentTree(vector<ll> &nums){
        n = nums.size();
        sum.resize(n << 2, 0);
        addArr.resize(n << 2, 0);
        change.resize(n << 2, 0);
        updateArr.resize(n << 2, false);
        build(nums, 0, n - 1, 1);   
    }
    SegmentTree(int x){
        n = x;
        sum.resize(n << 2, 0);
        addArr.resize(n << 2, 0);
        change.resize(n << 2, 0);
        updateArr.resize(n << 2, false);
    }
    void update(int l, int r, ll v){
        updateHelp(l, r, v, 0, n - 1, 1);
    }
    void add(int l, int r, ll v){
        addHelp(l, r, v, 0, n - 1, 1);
    }
    ll query(int ql, int qr){
        return queryHelp(ql, qr, 0, n - 1, 1);
    }
};
