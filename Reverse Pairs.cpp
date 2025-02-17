class SegTree {
private:
    int tree_size;
    vector<int> tree;

    void update(int lx, int rx, int ni, int idx) {

        if (rx - lx == 1) {
            tree[ni]++;
            return;
        }

        int m = (lx + rx) >> 1;

        if (idx < m)
            update(lx, m, ni * 2 + 1, idx);
        else
            update(m, rx, ni * 2 + 2, idx);

        tree[ni] = tree[ni * 2 + 1] + tree[ni * 2 + 2];
    }

    int query(int l, int r, int lx, int rx, int ni) {

        if (l >= rx || r <= lx)
            return 0;
        
        if (l <= lx && r >= rx)
            return tree[ni];

        int m = (lx + rx) >> 1;
        return query(l, r, lx, m, ni * 2 + 1) + query(l, r, m, rx, ni * 2 + 2);
    }

public:
    SegTree(int n) {
        tree_size = 1;

        while (tree_size < n)
            tree_size <<= 1;

        tree = vector<int>(tree_size * 2);
    }

    void update(int idx) {
        update(0, tree_size, 0, idx);
    }

    int query(int l, int r) {
        return query(l, r + 1, 0, tree_size, 0);
    }
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {

        int n = nums.size();
        set<long long> values;

        for(const auto& num : nums) {
            values.insert(num);
            values.insert(2LL * num);
        }
        
        int last_index = 0;
        unordered_map<long long, int> values_indices;
        
        for(const auto& val : values) 
            values_indices[val] = last_index++;

        SegTree seg_tree(last_index);
        int ans = 0;

        for(int i = 0; i < n; ++i) {
            ans += seg_tree.query(values_indices[2LL * nums[i]] + 1, last_index);
            seg_tree.update(values_indices[nums[i]]);
        }

        return ans;
    }
};