// Этот код написан для операций добавления на отрезке, изменения на отрезке и суммы

#include <bits/stdc++.h>

using namespace std;
usimg ll = long long;

struct node {
    bool is_set = 0;
    ll add = 0, set, sum = 0;
};

struct segment_tree {
    vector<node> tree;
    int size = 0;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, node());
    }

    void push(int x, int lx, int rx) {
        int m = (lx + rx) / 2;
        if (tree[x].is_set) {
            tree[2 * x + 1].is_set = true;
            tree[2 * x + 1].set = tree[x].set;
            tree[2 * x + 2].is_set = true;
            tree[2 * x + 2].set = tree[x].set;
            tree[2 * x + 1].sum = tree[2 * x + 1].set * (m - lx);
            tree[2 * x + 2].sum = tree[2 * x + 2].set * (rx - m);
            tree[2 * x + 1].add = tree[2 * x + 2].add = 0;
            tree[x].is_set = false;
        }
        tree[2 * x + 1].add += tree[x].add;
        tree[2 * x + 2].add += tree[x].add;
        tree[2 * x + 1].sum += tree[x].add * (m - lx);
        tree[2 * x + 2].sum += tree[x].add * (rx - m);
        tree[x].add = 0;
    }

    void set(int l, int r, ll v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        if (l <= lx && rx <= r) {
            tree[x].is_set = true;
            tree[x].set = v;
            tree[x].add = 0;
            tree[x].sum = v * (rx - lx);
            return;
        }
        push(x, lx, rx);
        int m = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, m);
        set(l, r, v, 2 * x + 2, m, rx);
        tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum + tree[x].add * (rx - lx);
    }

    void set(int l, int r, ll v) {
        set(l, r, v, 0, 0, size);
    }

    void add(int l, int r, ll v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        if (l <= lx && rx <= r) {
            tree[x].add += v;
            tree[x].sum += v * (rx - lx);
            return;
        }
        push(x, lx, rx);
        int m = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, m);
        add(l, r, v, 2 * x + 2, m, rx);
        tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum + tree[x].add * (rx - lx);
    }

    void add(int l, int r, ll v) {
        add(l, r, v, 0, 0, size);
    }

    ll get_sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        if (l <= lx && rx <= r) {
            return tree[x].sum;
        }
        int m = (lx + rx) / 2;
        push(x, lx, rx);
        ll temp = get_sum(l, r, 2 * x + 1, lx, m) + get_sum(l, r, 2 * x + 2, m, rx);
        if (tree[x].is_set) {
            return (min(r, rx) - max(l, lx)) * (tree[x].set + tree[x].add);
        }
        return temp + (min(r, rx) - max(l, lx)) * tree[x].add;
    }

    ll get_sum(int l, int r) {
        return get_sum(l, r, 0, 0, size);
    }
};
