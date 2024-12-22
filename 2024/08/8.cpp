#include <bits/stdc++.h>
using namespace std;

vector<string> board;
vector<vector<bool>> visited;
int n;

void solve(int y, int x) {
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(y != i && x != j && board[y][x] == board[i][j]) {
                int di = i - y, dj = j - x;
                int ni = i, nj = j;

                while(0 <= ni && ni < n
                && 0 <= nj && nj < n) {
                    visited[ni][nj] = true;

                    ni += di;
                    nj += dj;
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty())
            continue;

        board.push_back(buf);
    }

    n = board.size();
    visited.assign(n, vector<bool>(n, false));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] != '.')
                solve(i, j);
        }
    }

    int ans = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(visited[i][j])
                ans++;
        }
    }

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(visited[i][j])
                cout << '#';
            else
                cout << board[i][j];
        }
        cout << endl;
    }

    cout << ans << endl;

    return 0;
}