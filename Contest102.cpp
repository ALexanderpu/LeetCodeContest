#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    // 905. Sort Array By Parity
    vector<int> sortArrayByParity(vector<int>& A) {
        vector<int> odd;
        vector<int> even;
        for(auto ele: A){
            if(ele%2){
                odd.push_back(ele);
            }else{
                even.push_back(ele);
            }
        }
        even.insert(even.end(), odd.begin(), odd.end() );
        return even;
    }
    //904. Fruit Into Baskets
    int totalFruit(vector<int>& tree) {
        // two type for a search from left to right if third income stop or
        if(tree.size() <= 2)
            return tree.size();
        int result = 0;
        for(int start_pos = 0; start_pos < tree.size()-2; start_pos++){
            if(result == tree.size())
                break;
            int first = INT_MAX;
            int second = INT_MAX;
            int cur = 0;
            for(int end_pos = start_pos; end_pos < tree.size(); end_pos++){
                if(first != INT_MAX && second != INT_MAX){
                    if(tree[end_pos] == first || tree[end_pos] == second)
                        cur++;
                    else
                        break;
                }else if(first == INT_MAX || tree[end_pos] == first){
                    first = tree[end_pos];
                    cur++;
                }else if(second == INT_MAX || tree[end_pos] == second){
                    second = tree[end_pos];
                    cur++;
                }
            }
            result = max(cur, result);
        }
        return result;
    }
    // 907. Sum of Subarray Minimums
    int sumSubarrayMins(vector<int>& A) {
        int n = A.size();
        stack<int> mono_stack;
        stack<int> count;
        stack<int> sum;
        sum.push(0);
        int result = 0;
        const int M = 1e9+7;
        for (int i = 0; i < A.size(); i++) {
            int cur = 1;
            while (!mono_stack.empty() && A[i] <= mono_stack.top()) {
                mono_stack.pop();
                cur += count.top();
                count.pop();
                sum.pop();
            }
            mono_stack.push(A[i]);
            count.push(cur);
            sum.push((sum.top() % M) + (cur * A[i] % M) % M);
            result += sum.top();
            result %= M;
        }
        return result;
    }
};
int main() {
    Solution solve;
    vector<int> test = {3,1,2,4};
    solve.sumSubarrayMins(test);

    return 0;
}
