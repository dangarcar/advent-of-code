#include "../../AOC.h"



int ans;
vector<string> board;
vector<vector<int>> dp;
int n, m;


int solve(int i, int j) {
    if(dp[i][j] != -1)
        return dp[i][j];

    int ni = i + 1;

    if(ni < n) {
        if(board[ni][j] == '.')
            return dp[i][j] = solve(ni, j);
        else if(board[ni][j] == '^') {
            ans++;
            return dp[i][j] = solve(ni, j-1) + solve(ni, j+1);
        }
    }

    return 1;
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);

    string buf;
    while(getline(cin, buf)) {
        board.push_back(buf);
    }

    n = board.size();
    m = board[0].size();
    ans = 0;

    dp.assign(n, vector<int>(m, -1));

    int ans2;
    for(int j=0; j<m; ++j) {
        if(board[0][j] == 'S') {
            board[0][j] = '.';
            ans2 = solve(0, j);
            break;
        }
    }
    
    cout << "Part 1 answer: " << ans << '\n';
    cout << "Part 2 answer: " << ans2 << '\n';

    return 0;
}