#include "../../AOC.h"

int incX[] = {0, 1, 0, -1 };
int incY[] = {-1, 0, 1, 0 };

vector<string> board;
vector<vector<int>> rowObs, colObs;
vector<vector<bitset<4>>> visited;
int n;

bool move(int& i, int& j, int k) {
    if(k == 0) { //UP -i
        for(auto ei: ranges::views::reverse(colObs[j])) {
            if(ei < i) {
                i = ei + 1;
                return true;
            }
        }
    } else if(k == 1) { //RIGHT +j
        for(auto ej: rowObs[i]) {
            if(ej > j) {
                j = ej - 1;
                return true;
            }
        }
    } else if(k == 2) { //DOWN +i
        for(auto ei: colObs[j]) {
            if(ei > i) {
                i = ei - 1;
                return true;
            }
        }
    } else if(k == 3) { //LEFT -j
        for(auto ej: ranges::views::reverse(rowObs[i])) {
            if(ej < j) {
                j = ej + 1;
                return true;
            }
        }
    }

    return false;
}

bool inLoop(int i, int j) {
    int k = 0;

    while(!visited[i][j][k]) {
        visited[i][j][k] = true;
        if(move(i, j, k))
            k = (k+1) % 4;
        else
            return false;
    }

    return true;
}

signed main() {
    AoCTimer timer;
    
    string buf;
    while(getline(cin, buf)) {
        if(!buf.empty()) {
            board.push_back(buf);
        }
    }

    int begI, begJ;
    n = board.size();
    rowObs.assign(n, {});
    colObs.assign(n, {});

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '^') {
                begI = i;
                begJ = j;
            } else if(board[i][j] == '#') {
                rowObs[i].push_back(j);
                colObs[j].push_back(i);
            }
        }
    }

    for(int i=0; i<n; ++i) {
        sort(rowObs[i].begin(), rowObs[i].end());
        sort(colObs[i].begin(), colObs[i].end());
    }

    int ans = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '.') {
                visited.assign(n, vector<bitset<4>>(n, 0));
                auto vi = rowObs[i], vj = colObs[j];
                vi.insert(upper_bound(vi.begin(), vi.end(), j), j);
                vj.insert(upper_bound(vj.begin(), vj.end(), i), i);
                
                swap(rowObs[i], vi);
                swap(colObs[j], vj);

                if(inLoop(begI, begJ))
                    ans++;
                
                swap(rowObs[i], vi);
                swap(colObs[j], vj);
            }
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}