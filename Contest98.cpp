#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <unordered_map>
#define MOD 1000000007
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    //regular expression match
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.length()+1, vector<bool>(p.length()+1, false));

        dp[s.length()][p.length()] = true;

        for(unsigned long i = s.length(); i >= 0; i--){
            for(unsigned long j = p.length() - 1; j >= 0; j--){
                bool first_match = i < s.length() && (p[j] == s[i] || p[j] == '.');

                if(j+1 < p.length() && p[j+1] == '*'){
                    dp[i][j] = dp[i][j+2] || (first_match && dp[i+1][j]);
                }else{
                    dp[i][j] = first_match && dp[i+1][j+1];
                }
                print(dp, i, j);
            }
        }
        return dp[0][0];
    }

    //888. Fair Candy Swap
    void print(vector<vector<bool>>& dp, int i, int j){
        for(int iter_i = 0; iter_i < dp.size(); iter_i++){
            for (int iter_j = 0; iter_j < dp[iter_i].size(); iter_j++){
                if(iter_i == i && iter_j == j){
                    cout << "*" << dp[iter_i][iter_j] <<"*";
                }else{
                    cout << " " << dp[iter_i][iter_j] <<" ";
                }
            }
            cout << endl;
        }
    }


    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        long long sum_a = accumulate(A.begin(), A.end(), 0);
        long long sum_b = accumulate(B.begin(), B.end(), 0);
        vector<int> result;
        for(auto a:A){
            for(auto b:B){
                if(sum_a-a+b == sum_b-b+a){
                    result.push_back(a);
                    result.push_back(b);
                    return result;
                }
            }
        }
        return result;
    }

    //890. Find and Replace Pattern
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> result;
        for(auto& word:words){
            if(word.length() == pattern.length()) {
                bool flag = true;
                unordered_map<char, char> dict_w, dict_p;
                for (size_t index = 0; index < pattern.length(); index++) {
                    if (dict_w.find(word[index]) != dict_w.end()) { // has already mapped
                        if (dict_w[word[index]] != pattern[index]) { // not match
                            flag = false;
                            break;
                        }
                    } else { // map
                        dict_w[word[index]] = pattern[index];
                    }

                    if(dict_p.find(pattern[index]) != dict_p.end()){
                        if(dict_p[pattern[index]] != word[index]){
                            flag = false;
                            break;
                        }
                    }else { // map
                        dict_p[pattern[index]] = word[index];
                    }
                }
                if (flag) {
                    result.push_back(word);
                }
            }
        }
        return result;
    }

    //889. Construct Binary Tree from Preorder and Postorder Traversal
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        return buildTree(pre, post, 0, pre.size(), 0, post.size());
    }
    TreeNode* buildTree(vector<int>& pre, vector<int>& post, size_t pre_begin, size_t pre_end, size_t post_begin, size_t post_end){
        TreeNode* root = new TreeNode(pre[pre_begin]);
        if(pre_begin == pre_end)
            return nullptr;
        if(pre_end - pre_begin == 1)
            return root;
        // pre_end - pre_begin > 1
        size_t pre_pos, post_pos;
        for(size_t i = pre_begin + 1, j = post_begin; i <  pre_end; i++, j++){
            if(pre[pre_begin+1] == post[j]){
                pre_pos = i;
                post_pos  = j;
                break;
            }
        }
        root->left = buildTree(pre, post, pre_begin + 1, pre_pos + 1, post_begin, post_pos + 1);
        root->right = buildTree(pre, post, pre_pos + 1, pre_end, post_pos + 1, post_end - 1);
        return root;
    }

    // 891. Sum of Subsequence Widths
    int sumSubseqWidths(vector<int>& A) {
        vector<long long> pow2 = {1};
        int n = (int)A.size();
        while (pow2.size() <= n)
            pow2.push_back(pow2.back() * 2 % MOD);
        sort(A.begin(), A.end());
        long long ans = 0;
        for (int i = 0; i < A.size(); i++) {
            ans -= A[i] * (pow2[n-i-1] - 1) % MOD;
            ans += A[i] * (pow2[i] - 1) % MOD;
            ans = (ans + MOD) % MOD;
        }
        return (int)ans;
    }


};

int main() {
    /*
    string s = "missipp";
    string p = "mi.*p*";
    Solution solve;
    cout << solve.isMatch(s, p);
     */
    vector<int> input = {2,1,3,6,8};
    Solution solve;
    cout << solve.sumSubseqWidths(input);
    return 0;
}
