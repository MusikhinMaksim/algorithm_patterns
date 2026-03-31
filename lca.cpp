#include <bits/stdc++.h>

using namespace std;

struct Sparse_table{
    int size;
    vector<int> powers, nums;
    vector<vector<int>> sparse;

    void build(vector<int>& arr){
        size = arr.size();
        powers.resize(size , 0);
        nums = arr;
        for (int i = 1; i < size; i++){
            powers[i] = powers[(i - 1) / 2] + 1;
        }
        sparse.resize(powers.back() + 1, vector<int>(size, -1));
        for (int i = 0; i < size; i++){
            sparse[0][i] = i;
        }
        for (int k = 1; (1 << k) <= size; k++){
            for (int i = 0; i < size; i++){
                if (i + (1 << k) - 1 >= size){
                    break;
                }
                if (nums[sparse[k - 1][i]] > nums[sparse[k - 1][i + (1 << (k - 1))]]){
                    sparse[k][i] = sparse[k - 1][i + (1 << (k - 1))];
                    continue;
                }
                sparse[k][i] = sparse[k - 1][i];
            }
        }
        for (int i = 1; i <= powers.back(); i++){
            for (int j = 0; j < size; j++){
                if (sparse[i][j] == -1){
                    sparse[i][j] = sparse[i - 1][j];
                }
            }
        }
    }

    int get_min(int l, int r){
        if (nums[sparse[powers[r - l]][l]] > nums[sparse[powers[r - l]][r - (1 << powers[r - l]) + 1]]){
            return sparse[powers[r - l]][r - (1 << powers[r - l]) + 1];
        }
        return sparse[powers[r - l]][l];
    }
};

struct LCA{

    int root;
    Sparse_table sparse;
    vector<int> a, d, idx;
    vector<vector<int>> graph;

    void dfs(int v, int depth){
        a.push_back(v);
        d.push_back(depth);
        for (auto u : graph[v]){
            dfs(u, depth + 1);
            a.push_back(v);
            d.push_back(depth);
        }
    }

    void init(int n){
        idx.resize(n, -1), graph.resize(n);
        for (int i = 0; i < n; i++){
            int temp;
            cin >> temp;
            if (temp == 0){
                root = i;
                continue;
            }
            graph[temp - 1].push_back(i);
        }
        dfs(root, 0);
        sparse.build(d);
        for (int i = 0; i < a.size(); i++){
            if(idx[a[i]] == -1){
                idx[a[i]] = i;
            }
        }
    }

    int get_ans(int u, int v){
        return a[sparse.get_min(min(idx[u], idx[v]), max(idx[u], idx[v]))];
    }
};

int main() {
    
    return 0;
}
