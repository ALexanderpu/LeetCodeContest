#include <iostream>
#include<vector>
#include<cstdlib>
#include<queue>
#include <set>
#include<unordered_set>
// max element in vector<> v  : *max_element(v.begin(), v.end())

using namespace std;
struct TreeNode {
    int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // Question 1
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        bool flag = false;
        vector<int> tree1, tree2;
        inorder(root1, tree1);
        inorder(root2, tree2);
        if(tree1.size() == tree2.size() && tree1.size() > 0){
            flag = true;
            for(int i=0; i < tree1.size();i++){
                if(tree1[i] != tree2[i]){
                    flag = false;
                    break;
                }
            }
        }
        return flag;
    }
    void inorder(TreeNode *node, vector<int> &seq){
        if(!node->left && !node->right){
            //left
            seq.push_back(node->val);
        }
        if(node->left)
            inorder(node->left, seq);
        if(node->right)
            inorder(node->right, seq);

    }


    // Question 2: imitate and break if it is in the set
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int x_coord = 0;
        int y_coord = 0;
        int dirx[4] = {0, 1, 0, -1};
        int diry[4] = {1, 0, -1, 0};
        int cur_dir_index = 0;
        set<pair<int, int> > obstacle_set;
        // -1 turn right  -2 turn left
        // put obstacles into set
        int result = 0;
        for(auto obstacle:obstacles){
            obstacle_set.insert({obstacle[0], obstacle[1]});
        }

        for (int command : commands) {
            if (command == -1) {
                cur_dir_index = (cur_dir_index + 1) % 4;
                continue;
            }
            if (command == -2) {
                cur_dir_index = (cur_dir_index - 1) % 4;
                if (cur_dir_index < 0) {
                    cur_dir_index += 4;
                }
                continue;
            }
            for(int step = 0; step < command; step++){
                int tmp_x = x_coord + dirx[cur_dir_index];
                int tmp_y = y_coord + diry[cur_dir_index];
                if(obstacle_set.count({tmp_x, tmp_y})){
                    break;
                }
                x_coord = tmp_x;
                y_coord = tmp_y;
            }
            result = max((x_coord*x_coord + y_coord*y_coord), result);
        }
        return result;
    }
    // Question 3: binary search
    int minEatingSpeed(vector<int>& piles, int H) {
        int count_piles = (int)piles.size();
        int low = 1, high = *max_element(piles.begin(), piles.end());
        while (low != high) {
            int mid = (low + high) / 2;
            long long sum = 0;
            for (int i = 0; i < count_piles; ++i) {
                sum += (piles[i] - 1) / mid + 1;
            }
            if (sum > H) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return high;
    }

    // Question 4: DP   {f(x) + f(x+1) = f(x+2)    using set to check if it is legal!}
    int lenLongestFibSubseq(vector<int>& A) {
        int result = 0;
        int dp[A.size()-1];
        unordered_set<int> mapa;
        for(auto a:A){mapa.insert(a);}
        for(int i = 0; i < A.size(); i++){
            for(int j = i+1; j < A.size(); j++){
                int a = A[i];
                int b = A[j];
                if(mapa.find(a+b) != mapa.end()){
                    int sub_len = 2;
                    while(mapa.find(a+b) != mapa.end()){
                        int tmp = a+b;
                        a = b;
                        b = tmp;
                        sub_len += 1;
                    }
                    result = max(sub_len, result);
                }
            }
        }
        return result;
    }
};

int main() {
    //[-2,-1,8,9,6]
    //[[-1,3],[0,1],[-1,5],[-2,-4],[5,4],[-2,-3],[5,-1],[1,-1],[5,5],[5,2]]
    vector<int> commands = {-2,-1,8,9,6};
    cout << *max_element(commands.begin(), commands.end());
    vector<vector<int>> obstacles;
    vector<int> obstacle1 = {0,1};
    vector<int> obstacle2 = {-1,3};
    vector<int> obstacle3 = {-1,5};
    vector<int> obstacle4 = {-2,-4};
    vector<int> obstacle5 = {5,4};
    vector<int> obstacle6 = {-2,-3};
    vector<int> obstacle8 = {5,-1};
    vector<int> obstacle9 = {1,-1};
    vector<int> obstacle10 = {5,5};
    vector<int> obstacle11 = {5,2};
    obstacles.push_back(obstacle2);
    obstacles.push_back(obstacle1);
    obstacles.push_back(obstacle3);
    obstacles.push_back(obstacle4);
    obstacles.push_back(obstacle5);
    obstacles.push_back(obstacle8);
    obstacles.push_back(obstacle9);
    obstacles.push_back(obstacle10);
    obstacles.push_back(obstacle11);

    //Solution* c = new Solution();
    //cout << c->robotSim(commands, obstacles);
    //cout << (-1%4);
    return 0;
}
