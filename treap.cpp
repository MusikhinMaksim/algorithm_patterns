//Задача "Очередная" (декартово дерево по явному ключу)

#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
mt19937 rnd(time(0));

struct node {
    ll x, y, size, sum;  // x -> key, y -> priority
    node *L = nullptr;
    node *R = nullptr;
    node *P = nullptr;

    explicit node(ll x1) {
        x = x1;
        y = rnd();
        size = 1;
    }
};

ll sz(node *root) {
    if (root == nullptr) {
        return 0;
    }
    return root->size;
}

ll get_sum(node *root) {
    if (root == nullptr) {
        return 0;
    }
    return root->sum;
}

void update(node *root) {
    if (root == nullptr) {
        return;
    }
    root->size = sz(root->L) + sz(root->R) + 1;
    root->sum = get_sum(root->L) + get_sum(root->R) + root->x;
    if (root->L != nullptr) {
        root->L->P = root;
    }
    if (root->R != nullptr) {
        root->R->P = root;
    }
}

pair<node *, node *> split(node *root, ll k) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    if (sz(root->L) >= k) {
        auto p = split(root->L, k);
        root->L = p.second;
        update(root);
        return {p.first, root};
    } else {
        auto p = split(root->R, k - sz(root->L) - 1);
        root->R = p.first;
        update(root);
        return {root, p.second};
    }
}

node *merge(node *a, node *b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->y < b->y) {
        a->R = merge(a->R, b);
        update(a);
        return a;
    } else {
        b->L = merge(a, b->L);
        update(b);
        return b;
    }
}

void insert(node *&root, node *t, ll k) {
    // node *t = new node(n);
    auto p = split(root, k);
    root = merge(p.first, merge(t, p.second));
}

void erase(node *&root, ll k) {
    auto p = split(root, k);
    auto q = split(p.second, 1);
    root = merge(p.first, q.second);
}

node *get_kth(node *&root, ll k) {
    auto p = split(root, k);
    auto q = split(p.second, 1);
    node *ans = q.first;
    root = merge(p.first, merge(q.first, q.second));
    return ans;
}

ll get_idx(node *n) {
    ll ans = sz(n->L);
    while (n->P != nullptr) {
        ans += (n->P->R == n) * (sz(n->P->L) + 1);
        n = n->P;
    }
    return ans;
}

pair<node *, node *> split_after(node *root, node *x) {
    ll k = get_idx(x);
    return split(root, k + 1);
}

node *next(node *&root, node *x) {
    if (x == nullptr) {
        return nullptr;
    }
    auto p = split_after(root, x);
    node *ans = get_kth(p.second, 0);
    root = merge(p.first, p.second);
    return ans;
}

void swap_two_subsegments(node *&root, ll l1, ll r1, ll l2, ll r2) {
    auto a = split(root, l1);
    auto b = split(a.second, r1 - l1);
    auto c = split(b.second, l2 - r1);
    auto d = split(c.second, r2 - l2);
    root = merge(merge(a.first, merge(d.first, c.first)),
                 merge(b.first, d.second));
}

int main() {
    // freopen("swapper.in", "r", stdin);
    // freopen("swapper.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    node *root = nullptr;
    int n, m;
    cin >> n >> m;
    vector<node *> arr(n);
    for (int i = 0; i < n; i++) {
        ll t;
        cin >> t;
        arr[t - 1] = new node(t);
        insert(root, arr[t - 1], i);
    }
    while (m--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            swap_two_subsegments(root, l1 - 1, r1, l2 - 1, r2);
        } else {
            ll num;
            cin >> num;
            node *a = next(root, arr[num - 1]);
            node *b = next(root, a);
            node *c = next(root, b);
            if (a == nullptr) {
                cout << -1 << ' ';
            } else {
                cout << a->x << ' ';
            }
            if (b == nullptr) {
                cout << -1 << ' ';
            } else {
                cout << b->x << ' ';
            }
            if (c == nullptr) {
                cout << -1 << ' ';
            } else {
                cout << c->x << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}
