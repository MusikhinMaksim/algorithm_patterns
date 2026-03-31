//Задачечка на строчечки

#include <bits/stdc++.h>

using namespace std;
//---------------------------------------------------
//#define int long long
//#pragma GCC optimize("O3")
//#pragma GCC optimize("avx2")
//#pragma GCC optimize("Ofast")
#define all(arr) arr.begin(), arr.end()
#define rall(arr) arr.rbegin(), arr.rend()
#define file_in freopen("input.txt", "r", stdin)
#define file_out freopen("output.txt", "w", stdout)
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define cout_float cout.setf(ios::fixed); cout.precision(16)
//---------------------------------------------------
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
//---------------------------------------------------
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
//---------------------------------------------------
template<typename T>
istream& operator>>(istream& in, pair<T, T>& a){in >> a.first >> a.second; return in;}
template<typename T>
ostream& operator<<(ostream& out, pair<T, T> a){out << a.first << ' ' << a.second; return out;}
template<typename T>
istream& operator>>(istream& in, vector<T>& arr){for (int i = 0; i < arr.size(); i++){in >> arr[i];}return in;}
template<typename T>
ostream& operator<<(ostream& out, vector<T> arr){for (int i = 0; i < arr.size(); i++){out << arr[i] << ' ';}return out;}
//---------------------------------------------------

struct node{
    int cnt = 0, pred = 0, link = -1, up = -1, last_ch = -1, d = 0;
    int sons[26] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int go[26] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    vector<int> idx;
};

struct Trie{
    int size = 1;
    node bor[1000001];

    void push(string s, int idx){
        int curr = 0;
        bor[0].link = bor[0].up = 0;
        for (int i = 0; i < s.size(); i++){
            if (bor[curr].sons[s[i] - 'a'] == -1){
                bor[curr].sons[s[i] - 'a'] = size++;
                bor[size - 1].pred = curr;
                bor[size - 1].d = bor[curr].d + 1;
                bor[size - 1].last_ch = s[i] - 'a';
            }
            curr = bor[curr].sons[s[i] - 'a'];
        }
        bor[curr].cnt++;
        bor[curr].idx.push_back(idx);
    }

    int get_link(int v){
        if (bor[v].link != -1){
            return bor[v].link;
        }
        if (v == 0 || bor[v].pred == 0){
            bor[v].link = 0;
            return 0;
        }
        bor[v].link = letsgo(get_link(bor[v].pred), bor[v].last_ch);
        return bor[v].link;
    }

    int letsgo(int v, int ch){
        if (bor[v].go[ch] != -1){
            return bor[v].go[ch];
        }
        if (bor[v].sons[ch] != -1){
            bor[v].go[ch] = bor[v].sons[ch];
            return bor[v].go[ch];
        }
        if (v == 0){
            bor[v].go[ch] = 0;
            return 0;
        }
        bor[v].go[ch] = letsgo(get_link(v), ch);
        return bor[v].go[ch];
    }

    int getUp(int v){
        if (bor[v].up != -1){
            return bor[v].up;
        }
        if (bor[get_link(v)].cnt > 0){
            bor[v].up = get_link(v);
            return bor[v].up;
        }
        if (get_link(v) == 0){
            bor[v].up = 0;
            return 0;
        }
        bor[v].up = getUp(get_link(v));
        return bor[v].up;
    }
};

void solve() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    Trie tr;
    for  (int i = 0; i < n; i++){
        string t;
        cin >> t;
        tr.push(t, i);
    }
    int curr = 0;
    vector<vector<int>> ans(n);
    for (int i = 0; i < s.size(); i++){
        curr = tr.letsgo(curr, s[i] - 'a');
        int x = curr;
        while (x > 0){
            for (int j = 0; j < tr.bor[x].idx.size(); j++){
                ans[tr.bor[x].idx[j]].push_back(i - tr.bor[x].d + 2);
            }
            x = tr.getUp(x);
        }
    }
    for (auto e : ans){
        cout << e.size() << ' ';
        for (auto el : e){
            cout << el << ' ';
        }
        cout << '\n';
    }
}

signed main() {
    fast;
    cout_float;
#ifdef ONLINE_JUDGE

#else
    //file_in;
    //file_out;
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
    return 0;
}
