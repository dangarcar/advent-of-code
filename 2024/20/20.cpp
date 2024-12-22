#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000
#define CHEAT_LENGTH 20
#define THRESHOLD 100

int incI[] = {0, 0, 1, -1};
int incJ[] = {1, -1, 0, 0};

vector<string> board;
vector<vector<int>> dist;
vector<vector<bool>> visited;
int n;

int si, sj, ti, tj;

void bfs() {
    dist.assign(n, vector<int>(n, -1));
    queue<pair<int,int>> q;
    dist[si][sj] = 0;
    q.push({si, sj});

    while(!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        for(int k=0; k<4; ++k) {
            int ni = i + incI[k], nj = j + incJ[k];
            if(board[ni][nj] != '#' && dist[ni][nj] == -1) {
                dist[ni][nj] = dist[i][j] + 1;
                q.push({ni, nj});
            }
        }
    }
}

int manhattan(int i1, int j1, int i2, int j2) {
    return abs(i1 - i2) + abs(j1 - j2);
}

int dfs(int i, int j) {
    int ans = 0;
    visited[i][j] = true;
    
    for(int i2=1; i2<n-1; ++i2) {
        for(int j2=1; j2<n-1; ++j2) {
            if(board[i2][j2] != '#') {
                int mdst = manhattan(i, j, i2, j2);
                if(mdst <= CHEAT_LENGTH) {
                    int dst = dist[i2][j2] - dist[i][j] - mdst;
                    if(dst >= THRESHOLD)
                        ans++;
                } 
            }
        }
    }

    for(int k=0; k<4; ++k) {
        int ni = i + incI[k], nj = j + incJ[k];
        if(board[ni][nj] != '#' && visited[ni][nj] == false)
            ans += dfs(ni, nj);
    }

    return ans;
}

int main(int argc, char const *argv[]) {
    auto start = chrono::steady_clock::now();

    string buf;
    while(getline(cin, buf)) {
        if(buf.empty()) 
            continue;
        board.push_back(buf);
    }

    n = board.size();
    dist.assign(n*n, vector<int>(n*n, INF));
    for(int u=0; u<n*n; ++u)
        dist[u][u] = 0;

    for(int i=1; i<n-1; ++i) {
        for(int j=1; j<n-1; ++j) {
            if(board[i][j] == 'S') {
                si = i; sj = j;
            }

            if(board[i][j] == 'E') {
                ti = i; tj = j;
            }
        }
    }

    bfs();
    cout << dist[si][sj] << ' ' << dist[ti][tj] << endl;

    visited.assign(n, vector<bool>(n, false));
    cout << dfs(si, sj) << endl;

    auto t = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start);
    cout << t.count() << "ms" << endl;

    return 0;
}