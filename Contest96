#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <queue>
using namespace std;

//886 Reachable Nodes In Subdivided Graph
typedef pair<int, int> pii;
struct Subedge{
    int node;
    int distance;
    Subedge(int node,int distance):node(node),distance(distance){}
    bool operator<(const Subedge& other) const { return distance>other.distance; }
};
class Solution {
public:
    //887. Projection Area of 3D Shapes
    int projectionArea(vector<vector<int>>& grid) {
        int xy = 0;
        int yz = 0;
        int zx = 0;
        if(grid.size() >=1 ){
            for(int i = 0; i < grid.size(); i++){
                int max = grid[i][0];
                for(int j = 0; j < grid[i].size(); j++){
                    if(grid[i][j])
                        xy += 1;
                    if(max < grid[i][j])
                        max = grid[i][j];
                }
                zx += max;
            }
            for(int j = 0; j < grid[0].size(); j++){
                int max = grid[0][j];
                for(int i = 0; i < grid.size(); i++){
                    if(max < grid[i][j]){
                        max = grid[i][j];
                    }
                }
                yz += max;
            }
        }
        return xy+yz+zx;
    }

    //885. Boats to Save People
    // each boat carries at most 2 people !!!!  two pointers method  after sort!
    int numRescueBoats(vector<int>& people, int limit) {
        int n = (int)people.size();
        sort(people.begin(), people.end());
        int start = 0;
        int num_boats = 0;
        for(int end = n-1; end >= start; end--){
            if(start < end && people[start] + people[end] <= limit){  //carry two people: start += 1 ; carry one people: start no change
                start++;
            }
            num_boats++;
        }
        return num_boats;
    }

    //884. Decoded String at Index
    string decodeAtIndex(string S, int K) {
        vector<long long> dp(S.size()+1, 0);  // dp from 1 ~ n
        for(int cur = 0; cur < S.size(); cur++){
            if(S[cur] >= '2' && S[cur] <= '9'){
                    dp[cur+1] = dp[cur] * (S[cur] - '0');
            }else{
                dp[cur+1] = dp[cur] + 1;
            }
        }
        K -= 1;   // convert from 1~n to 0~n-1
        for(int cur = (int)S.size()-1; cur >= 0; cur--){ // n-1 ~ 0
            K %= dp[cur+1];
            if(K+1 == dp[cur+1] && !(S[cur] >= '2' && S[cur] <= '9')){ // alphabeta character && index is the most forward
                return string(1, S[cur]);  // convert char to string
            }
        }
        return nullptr;
    }

    //886 Reachable Nodes In Subdivided Graph
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        vector<vector<pii>> undirected_edges = vector<vector<pii>>(N);
        for(auto edge:edges){
            undirected_edges[edge[0]].push_back({edge[1], edge[2]+1});
            undirected_edges[edge[1]].push_back({edge[0], edge[2]+1});
        }

        //dijkstra: BFS + Priority Queue 优先拓展最短路 更新
        vector<int> dist(N, numeric_limits<int>::max());
        vector<bool> visit(N, false);
        priority_queue<Subedge> pq;
        dist[0] = 0;
        pq.push(Subedge(0,0));
        while(!pq.empty()){
            int cur = pq.top().node;
            pq.pop();
            if(visit[cur])
                continue;
            visit[cur] = true;
            for(auto next: undirected_edges[cur]){
                int v = next.first;
                int w = next.second;
                if(dist[cur]+w < dist[v]){
                    // update the shortest length
                    dist[v] = dist[cur] + w;
                    pq.push(Subedge(v, dist[v]));
                }
            }
        }

        int num_nodes = 0;
        // for nodes
        for(int i = 0; i < N; i++)
            if(dist[i] <= M)
                num_nodes += 1;

        //for sub nodes
        for(auto e:edges){
            int l = M-dist[e[0]], r = M-dist[e[1]];
            num_nodes += min(e[2], max(l, 0)+max(r, 0));
        }
        return num_nodes;
    }
};

int main() {
    Solution solve;
    cout << solve.decodeAtIndex("leet2code3", 10);
    return 0;
}
