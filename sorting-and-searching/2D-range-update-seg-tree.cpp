const int SIZE = 2507;

struct TREE {
    int size;
    long long* vals;
 
    void setup(int s = SIZE) {
        size = s;
        vals = new long long [size * 2] {0};
    }
 
    void updateVal(int a, int b, int v) {
        a += size;
        b += size;
 
        int tmp, add, tmps;
        while (a <= b) {
            tmp = a;
            add = 1;
            while (add * 2 + a < b) {
                add *= 2;
                tmps = tmp / 2;
                if (tmps * add < a) {
                    add /= 2;
                    break;
                }
                tmp = tmps;
            }
            vals[tmp] ^= v;
            a += add;
        }
    }
 
    long long getVal(int a) {
        a += size;
        long long out = 0;
        while (a) {
            out ^= vals[a];
            a /= 2;
        }
 
        return out;
    }
};

struct TTree{
    int size;
    TREE* vals;
 
    void setup(int s = SIZE) {
        size = s;
        vals = new TREE [size * 2] {};
        for(int i = 0; i<size*2; i++){
            vals[i].setup(size);
        }
    }
 
    void updateVal(int a, int ay, int b, int by, int v) {
        a += size;
        b += size;
 
        int tmp, add, tmps;
        while (a <= b) {
            tmp = a;
            add = 1;
            while (add * 2 + a < b) {
                add *= 2;
                tmps = tmp / 2;
                if (tmps * add < a) {
                    add /= 2;
                    break;
                }
                tmp = tmps;
            }
            vals[tmp].updateVal(ay, by, v);
            a += add;
        }
    }
 
    long long getVal(int a, int b) {
        a += size;
        long long out = 0;
        while (a) {
            out ^= vals[a].getVal(b);
            a /= 2;
        }
 
        return out;
    }
};