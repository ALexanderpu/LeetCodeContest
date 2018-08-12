#include <iostream>
#include<numeric>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
private:
    // 888. Uncommon Words from Two Sentences
    void convertWord(string s, map<string, int> &result){
        string word = "";
        for (auto x : s)
        {
            if (x == ' ')
            {
                if(result.find(word) == result.end()){
                    result[word] = 1;
                }else {
                    result[word] += 1;
                }
                word = "";
            }
            else
            {
                word = word + x;
            }
        }
        if(result.find(word) == result.end()){
            result[word] = 1;
        }else {
            result[word] += 1;
        }
    }
public:
    vector<string> uncommonFromSentences(string A, string B) {
        map<string, int> tmp;
        vector<string> result;
        convertWord(A, tmp);
        convertWord(B, tmp);

        for(auto r:tmp){
            if(r.second == 1){
                result.push_back(r.first);
            }
        }
        return result;
    }

    //890. Possible Bipartition  DFS coloring to detect bipartition
    bool bfs(int s, int n, vector<int> &color, vector<vector<int>> &graph){
        queue<int > q;
        q.push(s);
        color[s]=1;
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(auto next:graph[cur]){
                if(color[next] == -1){
                    q.push(next);
                    color[next] = !color[cur];
                }
                if(color[next] == color[cur]){
                    return false;
                }
            }
        }
        return true;
    }

    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        if(N < 0) return false;
        // build the bidir graph using adjacent edges
        vector<vector<int>> graphs(N + 1, vector<int>());
        for (auto edge: dislikes) {
            graphs[edge[0]].push_back(edge[1]);
            graphs[edge[1]].push_back(edge[0]);
        }

        vector<int> color(N + 1, -1);
        bool flag = false;
        for (int i = 1; i <= N; i++)
            if (color[i] == -1 && !bfs(i, N, color, graphs)) {//遍历各个连通分支
                flag = true;
                break;
            }

        return flag ? false : true;
    }

    //889. Spiral Matrix III
    bool isValid(int x, int y, int R, int C){
        if(0 <= x && x< R && 0 <= y && y < C)return true;
        return false;
    }
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        vector<vector<int>> result;
        int dir_x[4] = {0, 1, 0, -1};
        int dir_y[4] = {1, 0, -1, 0};
        int totalLen = max(max(R-r0-1, r0),max(C-c0-1, c0));
        int cur_x = r0;
        int cur_y = c0;
        vector<int> tmp = {cur_x, cur_y};
        result.push_back(tmp);
        for(int len = 1; len <= 2*totalLen + 1; len += 2){
            for(int cur_dir = 0; cur_dir < 2; cur_dir++){
                for(int step = 1; step <= len; step++) {
                    int next_x = cur_x + dir_x[cur_dir];
                    int next_y = cur_y + dir_y[cur_dir];
                    if (isValid(next_x, next_y, R, C)) {
                        vector<int> tmp = {next_x, next_y};
                        result.push_back(tmp);
                    }
                    cur_x = next_x;
                    cur_y = next_y;
                }
            }
            for(int cur_dir = 2; cur_dir < 4; cur_dir++){
                for(int step = 1; step <= len+1; step++) {
                    int next_x = cur_x + dir_x[cur_dir];
                    int next_y = cur_y + dir_y[cur_dir];
                    if (isValid(next_x, next_y, R, C)) {
                        vector<int> tmp = {next_x, next_y};
                        result.push_back(tmp);
                    }
                    cur_x = next_x;
                    cur_y = next_y;
                }
            }
        }
        return result;
    }
    //891. Super Egg Drop  DP   !! not solve
    int superEggDrop(int K, int N) {
        vector<vector<int>> f(K + 1, vector<int>(N + 1, 0));
        for (int i = 1; i <= N; ++ i)
            f[1][i] = i;
        for (int i = 2; i <= K; ++ i)
            for (int j = 1; j <= N; ++ j) {
                if (j < i) {
                    f[i][j] = f[i - 1][j];
                    continue;
                }
                f[i][j] = min(N, f[i - 1][j - 1] + f[i][j - 1] + 1);
            }
        for (int i = 1; i <= N; ++ i)
            if (f[K][i] == N) return i;
        return -1;
    }



};
int main() {
    int R = 5;
    int C = 6;
    int r0 = 1;
    int c0 = 4;
    Solution solve;
    vector<vector<int>> result = solve.spiralMatrixIII(R, C, r0, c0);
    for(auto point:result){
        for(auto ele:point){
            cout << ele << " ";
        }
        cout << endl;
    }
    return 0;
}
