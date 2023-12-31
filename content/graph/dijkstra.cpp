const int INF = 1e9;
vector<pair<int, int>> L[100005];
int n, m;

void dijkstra(int s, vector<int>& d, vector<int>& p) {
    d.assign(n + 1, INF);
    p.assign(n + 1, -1);

    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({ 0, s });
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : L[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({ d[to], to });
            }
        }
    }
}