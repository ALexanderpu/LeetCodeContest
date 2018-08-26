#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
class Solution {
public:
    int numSpecialEquivGroups(vector<string>& A) {
        unordered_map<string, string> res;
        int result = 0;
        set<string> s;
        string first, second, final;
        for(auto str:A){
            first = "";
            second = "";
            for(auto c_index = 0; c_index < str.length(); c_index++){
                if(c_index % 2){  // == 1
                    first += str[c_index];
                }else{
                    second += str[c_index];
                }
            }
            sort(first.begin(), first.end());
            sort(second.begin(), second.end());
            final = first+"#"+second;
            res[str] = final;
        }

        for(auto iter:res){
            if(s.find(iter.second) == s.end()){
                result++;
                s.insert(iter.second);
            }
        }
        return result;
    }

    int surfaceArea(vector<vector<int>>& grid) {
        int count = 0;
        vector<int> dir_r = {1,0, -1, 0};
        vector<int> dir_c = {0,1, 0, -1};
        for(int row = 0; row < grid.size(); row++){
            for(int col = 0; col < grid[row].size(); col++) {
                if(grid[row][col] > 0) {
                    int base = 4 * grid[row][col] + 2;
                    for (int dir = 0; dir < 4; dir++) {
                        int new_row = row + dir_r[dir];
                        int new_col = col + dir_c[dir];
                        if (new_row >= 0 && new_col >= 0 && new_row < grid.size() && new_col < grid[row].size()) {
                            base -= min(grid[row][col], grid[new_row][new_col]);
                        }
                    }
                    count += base;
                }
            }
        }
        return count;
    }


    vector<TreeNode*> allPossibleFBT(int N) { // N should be odd
        vector<TreeNode*> res;
        if(N == 0) return res;
        if(N == 1){
            res.push_back(new TreeNode(0));
        }

        for(int left_sub = 1; left_sub < N-1; left_sub += 2){
            auto left = allPossibleFBT(left_sub);
            auto right = allPossibleFBT(N-left_sub-1);
            for(auto& l:left){
                for(auto& r:right){
                    auto tmp = new TreeNode(0);
                    tmp->left = l;
                    tmp->right =r;
                    res.push_back(tmp);
                }
            }
        }
        return res;
    }
};

class FreqStack {
public:
    int t = 0;
    // 1. frequency; 2.
    set<pair<int, pair<int, int>>> st;
    unordered_map<int, vector<int>> mp;
    FreqStack() {
        t = 0;
    }

    void push(int x) {
        if(mp.count(x)){
            assert(st.count({mp[x].size(),{mp[x].back(), x}}));
            st.erase({mp[x].size(),{mp[x].back(), x}});
        }

        mp[x].push_back(t++);
        st.insert({mp[x].size(),{mp[x].back(), x}});
    }

    int pop() {
        auto cur = *st.rbegin();
        int x = cur.second.second;
        assert(mp[x].back() == cur.second.first);
        st.erase(cur);
        mp[x].pop_back();
        if(mp[x].empty()) mp.erase(x);
        else st.insert({mp[x].size(),{mp[x].back(), x}});

        return x;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack obj = new FreqStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 */

int main(){
    Solution solve;
    vector<string>  test = {"abcd","cdab","adcb","cbad"};
    //cout << solve.numSpecialEquivGroups(test);

    vector<vector<int>> grid = {{1,0},{0,2}};
    solve.surfaceArea(grid);
    return 0;
}
