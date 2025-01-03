#include <bits/stdc++.h>
using namespace std;

int incX[] = {0, 1, 0, -1 };
int incY[] = {-1, 0, 1, 0 };

vector<string> board;
int n;

int pathLenght(int i, int j) {
    int v = 0;
    int len = 0;

    while(len <= n*n) {
        int ni = i + incY[v], nj = j + incX[v];
        if(0 > ni || ni >= n || 0 > nj || nj >= n)
            return len;
        while(board[ni][nj] == '#') {
            v = (v + 1) % 4;
            ni = i + incY[v];
            nj = j + incX[v];

            if(0 > ni || ni >= n || 0 > nj || nj >= n)
                return len;
        }

        i = ni;
        j = nj;
        len++;
    }

    return -1;
}

int main(int argc, char const *argv[]) {
    string buf;
    while(getline(cin, buf)) {
        if(!buf.empty()) {
            board.push_back(buf);
        }
    }

    int begI, begJ;
    n = board.size();

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '^') {
                begI = i;
                begJ = j;
                break;
            }
        }
    }

    int ans = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '.') {
                board[i][j] = '#';

                if(pathLenght(begI, begJ) == -1)
                    ans++;

                board[i][j] = '.';
            }
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}