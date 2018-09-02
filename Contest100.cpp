#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    vector<int> l;
public:
    // 896. Monotonic Array
    bool isMonotonic(vector<int>& A) {
        int flag = 0;
        for(int i = 1; i < A.size(); i++){
            if(A[i-1] == A[i])
                continue;
            if(A[i-1] < A[i]){
                if(flag == 0 || flag == 1)
                    flag = 1;
                else
                    return false;
                continue;
            }
            if(A[i-1] > A[i]){
                if(flag == 0 || flag == 2)
                    flag = 2;
                else
                    return false;
                continue;
            }
        }
        return true;
    }


    // 897. Increasing Order Search Tree
    TreeNode* increasingBST(TreeNode* root) {
        if(root == nullptr)
            return root;
        if(root->left == nullptr && root->right == nullptr)
            return root;
        inorder(root);
        TreeNode* new_root = new TreeNode(l[0]);
        TreeNode* cur = new_root;
        TreeNode* next = nullptr;
        for(int i = 1; i < l.size(); i++){
            next = new TreeNode(l[i]);
            cur->right = next;
            cur = next;
        }
        return new_root;
    }
    void inorder(TreeNode* root){
        if(root == nullptr)
            return;
        inorder(root->left);
        l.push_back(root->val);
        inorder(root->right);
    }

    // 898. Bitwise ORs of Subarrays
    // time-exceed if use two loop  (use set to add)
    int subarrayBitwiseORs(vector<int>& A) {
        int n = int(A.size());
        unordered_set<int> prev, ans;
        for(auto ele: A){
            unordered_set<int> cur;
            cur.insert(ele);
            for(auto x:prev)
                cur.insert(ele|x);
            ans.insert(cur.begin(), cur.end());
            prev=cur;
        }
        return int(ans.size());
    }
    
    // 899. Orderly Queue
    string orderlyQueue(string S, int K) {
        if(K > 1){
            sort(S.begin(), S.end());
            return S;
        }
        string temp = S;
        int len = int(S.size());
        S = S + S;
        for(int i = 0; i < len; i++){
            temp = min(temp, S.substr(i, len));
        }
        return temp;
    }
};
int main() {
    vector<int> test = {1,2,4};
    Solution solve = Solution();
    cout << solve.subarrayBitwiseORs(test);
    return 0;
}
