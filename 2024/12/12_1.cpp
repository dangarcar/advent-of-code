#include "../../AOC.h"

vector<string> board;
vector<vector<bool>> visited;
int n;

int incI[] = { 0,0,1, -1 };
int incJ[] = { 1,-1,0,0 };

struct region {
    int area, perimeter;
};

region dfs(int i, int j) {
    visited[i][j] = true;
    region r;
    r.area = 1;
    r.perimeter = 4;

    for(int k=0; k<4; ++k) {
        int ni = i + incI[k], nj = j + incJ[k];
        if(0 <= ni && ni < n
        && 0 <= nj && nj < n
        && board[i][j] == board[ni][nj]) {
            r.perimeter--;   
            if(!visited[ni][nj]) {
                auto tmp = dfs(ni, nj);
                r.area += tmp.area;
                r.perimeter += tmp.perimeter;
            }
        }
    }

    return r;
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string buf;
    while(getline(cin, buf)) {
        if(!buf.empty())
            board.push_back(buf);
    }

    n = board.size();

    visited.assign(n, vector<bool>(n, false));
    int ans = 0;

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(!visited[i][j]) {
                auto r = dfs(i, j);
                ans += r.area * r.perimeter;
            }
        }
    }

    cout << ans << endl;

    return 0;
}