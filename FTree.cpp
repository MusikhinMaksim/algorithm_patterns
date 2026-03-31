#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

struct Fenwick_tree{
    ll size;
    vector<ll> F;

    void inc(int i, ll v){
        while (i < size){
            F[i] += v;
            i += (i & -i);
        }
    }

    ll sum(int i){
        ll res = 0;
        while (i > 0){
            res += F[i];
            i -= (i & -i)
        }
        return res;
    }

    ll sum(int l, int r){   // [l; r)
        return sum(r) - sum(l);
    }

    void init(vector<ll>& arr){
        size = arr.size() + 1;
        F.resize(size, 0);
        for (int i = 0; i < size - 1; i++){
            inc(i + 1, arr[i]);
        }
    }

};
