#include<bits/stdc++.h>

using namespace std;

struct DSU{
    vector<int> parents, rang;

    void init(int n){
        for (int i = 0; i < n; i++){
            rang.push_back(1);
            parents.push_back(i);
        }
    }

    int get_pred(int v){
        if (v == parents[v]){
            return v;
        }
        int p = get_pred(parents[v]);
        parents[v] = p;
        return p;
    }

    void union_trees(int v1, int v2){
        int p1 = get_pred(v1), p2 = get_pred(v2);
        if (rang[p2] > rang[p1]){
            swap(p1, p2);
        }
        parents[p2] = p1;
        rang[p1] += rang[p2];
    }
};