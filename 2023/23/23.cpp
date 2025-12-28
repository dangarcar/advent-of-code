#include "../../AOC.h"

vector<string> board;
map<pair<int,int>, int> nodes;
vector<vector<pair<int,int>>> adj; // cost, v
vector<bool> visited;

int n;
int incC[] = {0,0,1,-1};
int incR[] = {1,-1,0,0};

int ans = 0;

void dfs(int v, int l) {
    if(v == nodes.size() - 1) {
        ans = max(ans, l);
        return;
    }

    visited[v] = true;
    for(auto [c, w]: adj[v]) {
        if(!visited[w]) {
            dfs(w, l + c);
        }
    }

    visited[v] = false;
}

void findAdj(int oi, int oj, int i, int j, int v, int l) {
    if(board[i][j] == 'O' && l > 0) {
        int u = nodes[{i,j}];
        adj[v].push_back({l, u});
        return;
    }

    for(int k=0; k<4; ++k) {
        int ni = i + incR[k], nj = j + incC[k];
        if(0 <= ni && ni < n
        && 0 <= nj && nj < n
        && board[ni][nj] != '#'
        && (ni != oi || nj != oj)) {
            findAdj(i, j, ni, nj, v, l+1);
        }
    }
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
        
    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;
        board.push_back(str);
    }

    n = board.size();
    int id = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '#') 
                continue;

            int pass = 0;
            for(int k=0; k<4; ++k) {
                int ni = i + incR[k], nj = j + incC[k];
                if(0 <= ni && ni < n
                && 0 <= nj && nj < n
                && board[ni][nj] != '#')
                    pass++;
            }

            if(pass > 2 || i==0 || i==n-1) {
                board[i][j] = 'O';
                nodes[{i, j}] = id++;
            }
        }
    }

    adj.assign(nodes.size(), {});
    for(auto [loc, v]: nodes) {
        findAdj(-1, -1, loc.first, loc.second, v, 0);
    }

    visited.assign(nodes.size(), false);
    dfs(0, 0);
    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}