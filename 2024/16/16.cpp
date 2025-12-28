#include "../../AOC.h"

#define INF 1000000000

struct info {
    int i, j;
    int dir;
    int cost;
};

vector<string> board;
vector<vector<bitset<4>>> visited;
vector<vector<vector<vector<info>>>> parent;
int n;
int si, sj, ti, tj;

int incI[] = {0, 0, 1, -1};
int incJ[] = {1, -1, 0, 0};

bool operator<(const info& a, const info& b) {
    return a.cost > b.cost;
}

void visitParent(int i, int j, int k) {
    if(visited[i][j][k])
        return;

    visited[i][j][k] = true;
    if(i == si && j == sj)
        return;
    
    for(auto e: parent[i][j][k]) {
        visitParent(e.i, e.j, e.dir);
    }
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty()) continue;

        board.push_back(buf);
    }

    n = board.size();

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == 'S') {
                si = i; 
                sj = j;
            }
            if(board[i][j] == 'E') {
                ti = i; 
                tj = j;
            }
        }
    }

    vector<vector<array<int, 4>>> dist(n, vector<array<int, 4>>(n, {INF,INF,INF,INF}));
    priority_queue<info> pq;
    parent.assign(n, vector<vector<vector<info>>>(n, vector<vector<info>>(4)));
    dist[si][sj][0] = 0;
    pq.push({si, sj, 0});

    while(!pq.empty()) {
        auto [i, j, dir, cost] = pq.top();
        pq.pop();

        if(dist[i][j][dir] < cost)
            continue;

        for(int k=0; k<4; ++k) {
            if(k == dir)
                continue;
            if(dist[i][j][dir] + 1000 <= dist[i][j][k]) {
                auto c = dist[i][j][dir] + 1000;
                dist[i][j][k] = c;
                pq.push({i, j, k, c});

                parent[i][j][k].push_back(info{i, j, dir, c});
            }
        }

        int ni = i + incI[dir], nj = j + incJ[dir];
        if(0 <= ni && ni < n
        && 0 <= nj && nj < n
        && board[ni][nj] != '#') {
            if(dist[i][j][dir] + 1 <= dist[ni][nj][dir]) {
                auto c = dist[i][j][dir] + 1;
                dist[ni][nj][dir] = c;
                pq.push({ni, nj, dir, c});

                parent[ni][nj][dir].push_back(info{i, j, dir, c});
            }
        }
    }

    int ans1 = INF + 1;
    vector<pair<int,int>> s;
    for(int k=0; k<4; ++k) {
        ans1 = min(ans1, dist[ti][tj][k]);
        s.push_back({k, dist[ti][tj][k]});
    }

    int ans2 = 0;
    visited.assign(n, vector<bitset<4>>(n, 0));
    for(auto [k, dst]: s) {
        if(dst == ans1) {
            visitParent(ti, tj, k);

            ans2 = 0;
            for(int i=0; i<n; ++i) {
                for(int j=0; j<n; ++j) {
                    bool b = false;
                    for(int k=0; k<4; ++k)
                        b |= visited[i][j][k];
        
                    if(b) ans2++;
                }
            }

            break;
        }
    }

    cout << "Part 1 answer: " << ans1 << endl;
    cout << "Part 2 answer: " << ans2 << endl;

    return 0;
}