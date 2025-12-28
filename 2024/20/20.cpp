#include "../../AOC.h"

#define CHEAT_LENGTH 20
#define THRESHOLD 100

int incI[] = {0, 0, 1, -1};
int incJ[] = {1, -1, 0, 0};

vector<string> board;
vector<pair<int,int>> path;

int manhattan(int i1, int j1, int i2, int j2) {
    return abs(i1 - i2) + abs(j1 - j2);
}

void dfs(int oi, int oj, int i, int j) {
    path.push_back({i, j});

    for(int k=0; k<4; ++k) {
        int ni = i + incI[k], nj = j + incJ[k];
        if(board[ni][nj] != '#' && (oi != ni || oj != nj))
            dfs(i, j, ni, nj);
    }
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty()) 
            continue;
        board.push_back(buf);
    }

    int n = board.size();
    int si, sj;
    for(int i=1; i<n-1; ++i) {
        for(int j=1; j<n-1; ++j) {
            if(board[i][j] == 'S') {
                si = i; sj = j;
                break;
            }
        }
    }

    dfs(-1, -1, si, sj);
    
    int ans = 0;
    for(int i=0; i<path.size(); ++i) {
        auto [i1, j1] = path[i];
        
        for(int j=i+THRESHOLD; j<path.size(); ++j) {
            auto [i2, j2] = path[j];
            int mdst = manhattan(i1, j1, i2, j2);
            if(mdst <= CHEAT_LENGTH) {
                int dst = j - i - mdst;
                if(dst >= THRESHOLD)
                    ans++;
            } 
        }
    }
    
    cout << "Part 2 answer: " << ans << endl;

    return 0;
}