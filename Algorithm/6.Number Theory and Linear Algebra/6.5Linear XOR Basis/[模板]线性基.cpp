class XorBasis {
    vector<i64> b;

    int num;
    i64 _or;
    
    bool canBeZero;
    vector<i64> basis;

    vector<int> rightMost;
    int rightMostZero;
public:
    XorBasis(vector<i64> &a) {
        b.resize(64);
        rightMost.resize(b.size(), 0);
        rightMostZero = -1;
        num = 0;
        _or = 0;
        canBeZero = false;

        for(i64 v : a) {
            insert(v);
        }
    };
    XorBasis() {
        b.resize(64);
        rightMost.resize(b.size(), 0);
        rightMostZero = -1;
        num = 0;
        _or = 0;
        canBeZero = false;
    }
    bool insert(i64 v) {
        _or |= v;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                num++;
                return true;
            }
            v ^= b[i];
        }
        canBeZero = true;
        return false;
    }
    bool insertRightMost(int idx, i64 v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                rightMost[i] = idx;
                num++;
                return true;
            }
            if(idx > rightMost[i]) {
                swap(idx, rightMost[i]);
                swap(v, b[i]);
            }
            v ^= b[i];
        }
        canBeZero = true;
        rightMostZero = max(rightMostZero, idx);
        return false;
    }
    bool decompose(i64 v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                return false;
            }
            v ^= b[i];
        }
        return true;
    }
    i64 maxXor() {
        i64 res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    i64 maxXorWithVal(i64 v) {
        i64 res = v;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    i64 maxXorWithLowerIndex(int lowerIndex) {
        i64 res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(res >> i & 1) && rightMost[i] >= lowerIndex) {
                res = max(res, res ^ b[i]);
            }
        }
        return res;
    }
    i64 minXor() {
        if(canBeZero) {
            return 0;
        }
        for(int i = 0; i < b.size(); i++) {
            if(b[i] > 0) {
                return b[i];
            }
        }
        return -1; //基为空
    }
    void initOnce() {
        if(!basis.empty()) {
            return;
        }
        vector<i64> tmp = b;
        for(int i = 0; i < tmp.size(); i++) {
            if(tmp[i] == 0) {
                continue;
            }
            for(int j = i - 1; j >= 0; j--) {
                if(tmp[i] >> j & 1) {
                    tmp[i] ^= tmp[j];
                }
            }
            basis.push_back(tmp[i]);
        }
    }
    i64 kthXor(i64 k) {
        initOnce();
        if(canBeZero) {
            k--;
        }
        if(k >= (1LL << basis.size())) {
            return -1;
        }
        i64 _xor = 0;
        for(int i = 0; i < basis.size(); i++) {
            if(k >> i & 1) {
                _xor ^= basis[i];
            }
        }
        return _xor;
    }
    XorBasis get(int lowerIndex) {
        XorBasis res;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(rightMost[i] >= lowerIndex) {
                res.insert(b[i]);
            }
        }
        return res;
    }
    void merge(const XorBasis& other) {
        for(int i = other.b.size() - 1; i >= 0; i--) {
            i64 v = other.b[i];
            if(v > 0) {
                insert(v);
            }
        }
    }
};