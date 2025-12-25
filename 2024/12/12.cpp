#include "../../AOC.h"

#define NONE 0
#define UP 8
#define LEFT 4
#define DOWN 2
#define RIGHT 1

vector<string> board;
vector<vector<bool>> visited;
vector<vector<int>> directions, regions;
int n;
int id;

int incI[] = { 0,0,1, -1 };
int incJ[] = { 1,-1,0,0 };
int dirs[] = { RIGHT, LEFT, DOWN, UP };

struct region {
    int area, sides;
};

int areaDirsDfs(int i, int j) {
    visited[i][j] = true;
    regions[i][j] = id;
    int area = 1;

    for(int k=0; k<4; ++k) {
        int ni = i + incI[k], nj = j + incJ[k];
        if(0 <= ni && ni < n
        && 0 <= nj && nj < n
        && board[i][j] == board[ni][nj]) { 
            if(!visited[ni][nj]) {
                area += areaDirsDfs(ni, nj);
            }
        } else {
            directions[i][j] |= dirs[k];
        }
    }

    return area;
}

void regionDfs(int i, int j, int k) {
    visited[i][j] = true;

    int ti = i + incI[k], tj = j + incJ[k];
    if(0 <= ti && ti < n
    && 0 <= tj && tj < n
    && board[i][j] == board[ti][tj])
        return;
    
    int ni = i, nj = j;
    if(incI[k] == 0)
        ni++;
    else
        nj++;

    if(ni < n && nj < n && (directions[ni][nj] & dirs[k]) && board[i][j] == board[ni][nj])
        regionDfs(ni, nj, k);
}

signed main() {
    AoCTimer timer;
    
    string buf;
    while(getline(cin, buf)) {
        if(!buf.empty())
            board.push_back(buf);
    }

    n = board.size();

    visited.assign(n, vector<bool>(n, false));
    directions.assign(n, vector<int>(n, NONE));
    regions.assign(n, vector<int>(n, -1));

    vector<region> v;
    id = 0;

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(!visited[i][j]) {
                auto area = areaDirsDfs(i, j);
                v.push_back({area, 0});
                id++;
            }
        }
    }
    for(int k=0; k<4; ++k) {
        visited.assign(n, vector<bool>(n, false));

        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                if((directions[i][j] & dirs[k]) && !visited[i][j]) {
                    regionDfs(i, j, k);

                    v[regions[i][j]].sides++;
                }
            }
        }
    }

    int ans = 0;
    for(int i=0; i<v.size(); ++i) {
        ans += v[i].area * v[i].sides;
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}