// Задача "Своппер"
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

struct Node {
    ll x, y, size = 1, sum;
    Node* L = nullptr;
    Node* R = nullptr;
};

ll sz(Node* r) {
    if (r == nullptr) {
        return 0;
    }
    return r->size;
}

ll sm(Node* r) {
    if (r == nullptr) {
        return 0;
    }
    return r->sum;
}

void update(Node* r) {
    if (r == nullptr) {
        return;
    }
    r->size = sz(r->L) + sz(r->R) + 1;
    r->sum = sm(r->L) + sm(r->R) + r->x;
}

pair<Node*, Node*> split(Node* r, int k) {
    if (r == nullptr) {
        return {nullptr, nullptr};
    }
    if (sz(r->L) >= k) {
        auto p = split(r->L, k);
        r->L = p.second;
        update(r);
        return {p.first, r};
    } else {
        auto p = split(r->R, k - sz(r->L) - 1);
        r->R = p.first;
        update(r);
        return {r, p.second};
    }
}

Node* merge(Node* a, Node* b) {
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

Node* insert(Node* r, int k, int v) {
    auto p = split(r, k);
    Node* n = new Node;
    n->x = v;
    n->sum = v;
    n->y = rand() % 1000000000;
    return merge(p.first, merge(n, p.second));
}

Node* erase(Node* r, int k) {
    auto p = split(r, k);
    auto q = split(p.second, 1);
    return merge(p.first, q.second);
}

pair<Node*, pair<Node*, Node*>> cut(Node* r, ll ql, ll qr) {
    auto p = split(r, ql);
    auto q = split(p.second, qr - ql);
    return {p.first, {q.first, q.second}};
}

ll div_up(ll a, ll b) { return (a + b - 1) / b; }

ll div_down(ll a, ll b) { return a / b; }

void swap_segments(Node*& r1, Node*& r2, ll ql, ll qr) {
    ll ql1 = div_up(ql, 2), qr1 = div_up(qr, 2), ql2 = div_down(ql, 2),
       qr2 = div_down(qr, 2);
    auto p1 = cut(r1, ql1, qr1);
    auto p2 = cut(r2, ql2, qr2);
    auto s1_1 = p1.first, s1_2 = p1.second.first, s1_3 = p1.second.second;
    auto s2_1 = p2.first, s2_2 = p2.second.first, s2_3 = p2.second.second;
    swap(s1_2, s2_2);
    r1 = merge(s1_1, merge(s1_2, s1_3));
    r2 = merge(s2_1, merge(s2_2, s2_3));
}

ll get_sum(Node*& r, ll ql, ll qr) {
    auto p = split(r, ql);
    auto q = split(p.second, qr - ql);
    ll ans = sm(q.first);
    r = merge(p.first, merge(q.first, q.second));
    return ans;
}

ll get_sum(Node*& r1, Node*& r2, ll ql, ll qr) {
    ll ql1 = div_up(ql, 2), qr1 = div_up(qr, 2), ql2 = div_down(ql, 2),
       qr2 = div_down(qr, 2);
    return get_sum(r1, ql1, qr1) + get_sum(r2, ql2, qr2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Node* root_1 = nullptr;
    Node* root_2 = nullptr;
    ll n, m, cnt = 1;
    cin >> n;
    while (n != 0) {
        cout << "Swapper " << cnt << ":" << '\n';
        cnt++;
        cin >> m;
        for (int i = 0; i < n; i++) {
            ll temp;
            cin >> temp;
            if (i % 2 == 0) {
                root_1 = insert(root_1, i / 2, temp);
            } else {
                root_2 = insert(root_2, i / 2, temp);
            }
        }
        while (m--) {
            ll type;
            cin >> type;
            if (type == 1) {
                ll l, r;
                cin >> l >> r;
                swap_segments(root_1, root_2, l - 1, r);
            } else {
                ll l, r;
                cin >> l >> r;
                cout << get_sum(root_1, root_2, l - 1, r) << '\n';
            }
        }
        cin >> n;
        cout << '\n';
    }
    return 0;
}
