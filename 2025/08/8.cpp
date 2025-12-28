#include "../../AOC.h"


struct Point { int x, y, z; };
using edge_t = pair<int, pair<int,int>>; //c, u, v

int dist2(Point a, Point b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z);
}


struct ufds {
    vector<int> p;
    int numSets;

    ufds(int N): p(N, -1), numSets(N) {}

    int find(int i) {
        return (p[i] < 0)? i : p[i] = find(p[i]);
    }

    void join(int i, int j) {
        int x = find(i), y = find(j);
        if(x == y) return;
        if(x < y) 
            swap(x, y);
        p[y] += p[x];
        p[x] = y;
        numSets--;
    }
};


signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);

    string buf;
    vector<Point> points;
    while(getline(cin, buf)) {
        istringstream iss(buf);
        int a, b, c;
        char ch;
        iss >> a >> ch >> b >> ch >> c;
        points.push_back({a, b, c});
    }

    int n = points.size();
    priority_queue<edge_t> edges;
    for(int i=0; i<n; ++i) {
        for(int j=i+1; j<n; ++j) {
            edge_t e = {-dist2(points[i], points[j]), pair<int,int>{i, j}};
            edges.push(e);
        }
    }

    ufds uf(n);
    int ans;
    while(!edges.empty()) {
        auto [u, v] = edges.top().second;
        edges.pop();

        uf.join(u, v);

        if(uf.numSets == 1) {
            ans = points[u].x * points[v].x;
            break;
        }
    }
    
    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}