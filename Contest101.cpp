#include "bits/stdc++.h"
#define db(x) cout << x << endl
using namespace std;

//900. RLE Iterator
class RLEIterator {
private:
    vector<int> result;
    vector<int> count;
    int pos;
public:
    RLEIterator(vector<int> A) {
        for(int i = 0; i < A.size(); i+=2){
            count.push_back(A[i]);
            result.push_back(A[i+1]);
        }
        pos = 0;
    }

    int next(int n) {
        int last = -1;
        while(pos != result.size() && n > 0){
            // consume
            if(n > count[pos]){
                n -= count[pos];
                pos += 1;
            }else{
                count[pos] -= n;
                last = result[pos];
                break;
            }
        }
        return last;
    }
};

//901. Online Stock Span
class StockSpanner {
public:
    vector<pair<int,int> > result;
    StockSpanner() {
        result.clear();
    }
    // return stock span
    // defined as the maximum number of consecutive days (starting from today and going backwards)
    // for which the price of the stock was less than or equal to today's price.
    // ! is consecutive   not accumulate
    int next(int price) {
        int now=1;
        while(!result.empty() && result.back().first<=price){
            now += result.back().second;
            result.pop_back();  //small should be pop out  which is not accumulate
        }
        result.push_back(make_pair(price,now));
        return now;
    }
};

class Solution {
public:
    //902. Numbers At Most N Given Digit Set
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        int result = 0;
        int total_len = 0;
        size_t size = D.size();
        vector<int> pows;
        vector<int> N_arr;
        while(N){
            N_arr.push_back(N%10);
            N = N/10;
            total_len += 1;
            pows.push_back(pow(size, total_len));
            if(N > 0)
                result += pows[total_len - 1];
        }
        for(int cur_pos = total_len-1; cur_pos >= 0; cur_pos--){
            int small = 0;
            int equal = 0;
            for(int c = 0; c < size; c++){
                if((D[c][0]-'0') < N_arr[cur_pos])
                    small += 1;
                if((D[c][0]-'0') == N_arr[cur_pos])
                    equal += 1;
            }
            if(cur_pos > 0)
                result += small*pows[cur_pos-1];
            else{
                result += (small + equal);
                break;
            }
            if(equal == 0)
                break;
        }
        return result;
    }

    //903. Valid Permutations for DI Sequence
    // DP 
    int dp[205][205];
    int mod = 1e9+7;
    int numPermsDISequence(string S) {
        dp[0][0] = 1;
        for(int i = 0; i < S.size(); i++){
            int sum = 0;
            if(S[i] == 'D'){ // decrese  p[i] > p[i+1]
                for(int k = i; k >= 0; k--){ // k [i, 0]  dp[i+1][0] max sum
                    sum += dp[i][k];
                    sum %= mod;
                    dp[i+1][k] = sum;
                }
            }
            else{  // increase  p[i] < p[i+1]
                for(int k = 0; k <= i+1; k++){ // k [0, i+1]  dp[i+1][i+1] max sum
                    dp[i+1][k] = sum;
                    sum += dp[i][k];
                    sum %= mod;
                }
            }
        }
        int ans = 0;
        for(int i = 0; i <= S.size(); i++)
        {
            ans += dp[S.size()][i];
            ans %= mod;
        }
        return ans;
    }
};
int main() {
    Solution solve;
    vector<string> D ={"1","2","3","4","5","6","7","9"};
    int N = 1;
    // cout << solve.atMostNGivenDigitSet(D, N);
    //["StockSpanner","next","next","next","next","next"]
    //[[],[29],[91],[62],[76],[51]]
    /*
    StockSpanner spanner;
    db(spanner.next(29));
    db(spanner.next(91));
    db(spanner.next(62));
    db(spanner.next(76));
    db(spanner.next(51));
    */
    cout << solve.numPermsDISequence("DID");

    return 0;
}
