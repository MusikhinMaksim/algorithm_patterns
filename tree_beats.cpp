//Это задача 438D на Codeforces

#include <bits/stdc++.h>

using namespace std;

//---------------------------------------------------
#define int long long
#define all(arr) arr.begin(), arr.end()
#define rall(arr) arr.rbegin(), arr.rend()
#define file_in freopen("input.txt", "r", stdin)
//#define file_out freopen("output.txt", "w", stdout)
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define cout_float cout.setf(ios::fixed); cout.precision(10)
//---------------------------------------------------
//typedef __int128 lll;
typedef long long ll;
typedef long double ld;
//---------------------------------------------------
mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
//---------------------------------------------------
template<typename T>
istream& operator>>(istream& in, vector<T>& arr){for (int i = 0; i < arr.size(); i++){in >> arr[i];}return in;}
template<typename T>
ostream& operator<<(ostream& out, vector<T>& arr){for (int i = 0; i < arr.size(); i++){out << arr[i] << ' ';}return out;}
//---------------------------------------------------

struct node{
    int sum = 0, ma = 0;

    explicit node(int v = 0){
        sum = v;
        ma = v;
    }
};

struct anime_tree{
    int size;
    vector<node> tree;

    void init(int n){
        size = 1;
        while (n > size) size *= 2;
        tree.resize(2 * size - 1);
    }

    void update(int x){
        tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
        tree[x].ma = max(tree[2 * x + 1].ma, tree[2 * x + 2].ma);
    }

    void build(int x, int lx, int rx, vector<int>& arr){
        if (rx - lx == 1){
            if (lx < arr.size()){
                tree[x] = node(arr[lx]);
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(2 * x + 1, lx, m, arr);
        build(2 * x + 2, m, rx, arr);
        update(x);
    }

    void build(vector<int>& arr){
        init(arr.size());
        build(0, 0, size, arr);
    }

    void set(int i, int v, int x, int lx, int rx){
        if (rx - lx == 1){
            tree[x] = node(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m){
            set(i, v, 2 * x + 1, lx, m);
        } else {
            set(i, v, 2 * x + 2, m, rx);
        }
        update(x);
    }

    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    void modify(int l, int r, int v, int x, int lx, int rx){
        if (rx <= l || r <= lx || tree[x].ma < v){
            return;
        }
        if (lx + 1 == rx){
            tree[x].sum %= v;
            tree[x].ma %= v;
            return;
        }
        int m = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);
        update(x);
    }

    void modify(int l, int r, int v){
        modify(l, r, v, 0, 0, size);
    }

    int get_sum(int l, int r, int x, int lx, int rx){
        if (rx <= l || r <= lx){
            return 0;
        }
        if (l <= lx && rx <= r){
            return tree[x].sum;
        }
        int m = (lx + rx) / 2;
        return get_sum(l, r, 2 * x + 1, lx, m) + get_sum(l, r, 2 * x + 2, m, rx);
    }

    int get_sum(int l, int r){
        return get_sum(l, r, 0, 0, size);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    cin >> arr;
    anime_tree DO;
    DO.build(arr);
    while (m--){
        int t;
        cin >> t;
        if (t == 1){
            int l, r;
            cin >> l >> r;
            cout << DO.get_sum(l - 1, r) << '\n';
        } else if (t == 2){
            int l, r, v;
            cin >> l >> r >> v;
            DO.modify(l - 1, r, v);
        } else {
            int i, v;
            cin >> i >> v;
            DO.set(i - 1, v);
        }
    }
}

signed main() {
    fast;
    cout_float;
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
    return 0;
}
