/*
 * LeetCode contest 93 submission
 * author: bo pu
 */
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b){
    return a.first > b.first;
}
class Solution {
public:
    // No. 1
    int binaryGap(int N) {
        int result = 0;
        int count = 1;
        bool start = false;
        while(N){
            if(N&1){
                // the last bit is 1
                if(start) {
                    result = std::max(count, result);
                    count = 1;
                }
                start = true;
            }else{
                // the last bit is 0
                if(start) {
                    count += 1;
                }
            }
            N = N >> 1;
        }
        return result;

    }
    // No. 2
    // after reorder the highest is 1
    int get_len(int num){
        int len = 0;
        while(num){
            num =num / 10;
            len += 1;
        }
        return len;
    }
    bool reorderedPowerOf2(int N) {
        if (N == 1) { return true; }
        int target_len = 0;
        int origin = N;
        int digits[10] = {0};
        while (origin) {
            digits[origin % 10] += 1;
            origin = origin / 10;
            target_len += 1;
        }
        int t = 1;
        int t_len = 1;
        while (t_len <= target_len) {
            t = t << 1;
            t_len = get_len(t);
            if (t_len == target_len) {
                // have the same number of digits
                int tmp = t;
                int tmp_digits[10] = {0};
                while (tmp) {
                    tmp_digits[tmp % 10] += 1;
                    tmp = tmp / 10;
                }
                bool flag = true;
                for (int i = 0; i < 10; i++) {
                    if (tmp_digits[i] != digits[i]) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    return true;
                }
            }
        }
        return false;

    }

    // No. 3
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        vector<pair<int, unsigned long>> sortedB;
        vector<int > result;
        vector<int > sortedA;
        vector<int> temp;
        for(int i = 0; i < B.size(); i++){
            sortedB.push_back(make_pair(B[i], i));
            sortedA.push_back(A[i]);
            result.push_back(-1);
        }
        sort(sortedB.begin(), sortedB.end());
        sort(sortedA.begin(), sortedA.end());
        int j = 0;
        int i = 0;
        while(i < sortedA.size()){
            if(sortedA[i] > sortedB[j].first){
                result[sortedB[j].second] = sortedA[i];
                j += 1;
            }else{
                temp.push_back(sortedA[i]);
            }
            i += 1;
        }
        j = 0;
        for(i = 0; i < result.size(); i++){
            if(result[i] == -1){
                //fill the empty
                result[i] = temp[j];
                j += 1;
            }
        }
        return result;
    }

    // N0. 4
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> Q;
        int result = 0;
        vector<pair<int, int>> remain_stations;
        remain_stations.emplace_back(make_pair(0, 0));
        for(int i = 0; i < stations.size(); i++){
            remain_stations.emplace_back(make_pair(target - stations[i][0], stations[i][1]));
        }
        sort(remain_stations.begin(), remain_stations.end(), cmp);
        for(int i = 0; i < remain_stations.size(); i++){
            int distance = target - remain_stations[i].first;
            while(!Q.empty() && startFuel < distance){
                startFuel += Q.top();
                Q.pop();
                result++;
            }
            if(Q.empty() && startFuel < distance){
                // cannot reach
                return -1;
            }
            startFuel -= distance;
            target = remain_stations[i].first;
            Q.push(remain_stations[i].second);
        }
        return result;
    }

};

int main(){
    Solution solve;
    //std::cout<<solve.binaryGap(6);
    int target = 100;
    int startFuel = 10;
    vector<vector<int> > stations;
    for(int i = 0; i < 4; i++){
        stations.push_back(vector<int>());
        for(int j = 0; j < 2; j++){
            stations[i].push_back(0);
        }
    }
    stations[0][0] = 10;
    stations[0][1] = 60;
    stations[1][0] = 20;
    stations[1][1] = 30;
    stations[2][0] = 30;
    stations[2][1] = 30;
    stations[3][0] = 60;
    stations[3][1] = 40;
    cout << solve.minRefuelStops(target, startFuel, stations);
    cout <<solve.reorderedPowerOf2(24);

    return 0;
}
