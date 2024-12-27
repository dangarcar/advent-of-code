#include <bits/stdc++.h>
using namespace std;

//UGLY BUT IT WORKS

vector<string> board;
int ways = 0;
int n;

int incI[] = { 0, 0, 1, -1 };
int incJ[] = { 1, -1, 0, 0 };

bool dfs(int i, int j) {
    if(board[i][j] == '9') {
        return true;
    }

    vector<pair<int,int>> v;
    for(int k=0; k<4; ++k) {
        int ni = i + incI[k], nj = j + incJ[k];
        if(0 <= ni && ni < n
        && 0 <= nj && nj < n) {
            if(board[ni][nj] == board[i][j] + 1) {
                v.push_back({ni, nj});
            }
        }
    }

    bool ret = false;
    if(!v.empty()) {
        int innerWays = 0;
        for(auto [ni, nj]: v) {
            if(dfs(ni, nj)) {
                innerWays++;
                ret |= true;
            }
        }

        if(innerWays > 0)
            ways += innerWays - 1;
    }

    return ret;
}

int main(int argc, char const *argv[]) {
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty())
            continue;
    
        board.push_back(buf);
    }
    n = board.size();

    int ans = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '0') {
                //visited.assign(n, vector<bool>(n, false));
                ways = 0;

                if(dfs(i, j))
                    ways++;

                //cout << ways << endl;
                ans += ways;
            }
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}