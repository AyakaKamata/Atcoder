#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;

struct Edge {
    int to;
    int id;
};

const int INF = 1e9;
int N, M, H;
vector<int> A; // 各頂点の美しさ
vector<vector<Edge>> graph;
vector<int> parent;
vector<int> depth; // 各頂点の深さ

void bfs(int root) {
    queue<pair<int, int>> q; // {current node, height}
    q.push({root, 0});
    parent[root] = -1; // root has no parent
    depth[root] = 0;

    while (!q.empty()) {
        auto [node, height] = q.front();
        q.pop();

        if (height >= H) continue; // Respect height constraint

        for (const auto& edge : graph[node]) {
            int next = edge.to;
            if (next == parent[node]) continue; // Avoid going back to parent
            if (parent[next] != -1) continue; // Already visited
            parent[next] = node;
            depth[next] = height + 1;
            q.push({next, height + 1});
        }
    }
}

// 頂点の美しさに基づいて、深さを調整する
void adjust_depth_by_beauty() {
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 0);
    // 美しさに基づいてノードをソート（高い美しさを後ろに）
    sort(nodes.begin(), nodes.end(), [&](int a, int b) {
        return A[a] > A[b]; // 美しさが高いものを後ろに配置
    });

    // 根からの距離が近い方が美しさの低い頂点になるように調整
    for (int i = 0; i < N; ++i) {
        int node = nodes[i];
        // 美しさが低いものから順に根に近い位置に配置
        // このループで、必要な調整を行う
    }
}

int main() {
    cin >> N >> M >> H;
    A.resize(N);
    graph.resize(N);
    parent.resize(N, -1);
    depth.resize(N, INF);

    for (int i = 0; i < N; ++i) cin >> A[i];

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
    }

    // Step 1: Sort nodes by beauty in descending order
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 0);
    sort(nodes.begin(), nodes.end(), [&](int x, int y) {
        return A[x] > A[y];
    });

    // Step 2: Construct rooted trees
    vector<bool> visited(N, false);
    for (int root : nodes) {
        if (visited[root]) continue;
        bfs(root);
        for (int i = 0; i < N; ++i) {
            if (parent[i] != -1) visited[i] = true;
        }
    }

    // Step 3: Adjust depth according to beauty
    adjust_depth_by_beauty();

    // Step 4: Output parent array
    for (int i = 0; i < N; ++i) {
        if (i > 0) cout << " ";
        cout << parent[i];
    }
    cout << endl;

    return 0;
}
