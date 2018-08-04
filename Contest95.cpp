#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned long long ull;
typedef long long ll;

using namespace std;

// middle of the linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Nth Magical Number
typedef long long int64;
const int MOD = 1e9 + 7;
int gcd(int a , int b)  // 最大公约数
{
    if(b==0) return a;
    a%=b;
    return gcd(b,a);
}

// Returns LCM of array elements
ll findlcm(int arr[], int n)  //最大公倍数
{
    // Initialize result
    ll ans = arr[0];

    // ans contains LCM of arr[0], ..arr[i]
    // after i'th iteration,
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
               (gcd(arr[i], ans)));

    return ans;
}


class Solution {
public:
    //1. middle of the linked list
    ListNode* middleNode(ListNode* head) {
        ListNode* post = head;
        int len = 1;
        while(post->next){
            len += 1;
            post = post->next;
        }
        int middle = len/2 + 1;
        ListNode* pre = head;
        for(int i = 1; i< middle; i++){
            pre = pre->next;
        }
        return pre;
    }

    //2. stone game
    bool stoneGame(vector<int>& piles) {
        if(piles.size()%2){
            return false;
        }else{
            return true;
        }
    }

    //3. Nth Magical Number
    int nthMagicalNumber(int N, int A, int B) {
        if (N == 0) return 0;
        int64 low = 0, high = 1LL << 50;
        int G = A / gcd(A, B) * B;
        while (low != high) {
            int64 mid = (low + high) / 2;
            int64 cnt = mid / A + mid / B - mid / G;
            if (cnt < N) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return (int)(high % MOD);
    }

    //4. Profitable Schemes    : g crimes   p minimum total profit for one combination
    // return how many schemes can be chosen
    int profitableSchemes(int G, int P, vector<int>& grp, vector<int>& prf) {
        vector<vector<int>> dp(P + 10, vector<int>(G + 10));
        dp[0][0] = 1;

        for (int i = 0; i < grp.size(); ++i) {
            int ng = grp[i];
            int pr = prf[i];

            for (int j = P; j >= 0; --j) {

                for (int k = G; k >= 0; --k) {

                    if (k + ng > G) continue;   // what we need exceeds what we have

                    if (!dp[j][k]) continue;

                    int j1 = min(P, j + pr);
                    (dp[j1][k + ng] += dp[j][k]) %= MOD;
                }
            }
        }

        int result = 0;
        for (int i = 0; i <= G; ++i) //  add all possible number of people to commit crime need
            (result += dp[P][i]) %= MOD;
        return result;
    }
};
int main() {
    Solution solve;
    vector<int> group = {2,3,5};
    vector<int> profit = {6, 7, 8};
    cout << solve.profitableSchemes(10, 5, group, profit);
    return 0;
}
