#include <bits/stdc++.h>
using namespace std;

//BRUTE FORCE THAT I'M NOT PROUD OF

int incX[] = {0, 1, 0, -1 };
int incY[] = {-1, 0, 1, 0 };

vector<string> board;
vector<vector<bool>> visited;
int n;

int begX, begY;
int maxL = 0;

int pathLenght() {
    int i = begY, j = begX;
    int v = 0;
    int len = 0;

    while(len <= n*n) {
        visited[i][j] = true;

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

    n = board.size();

    visited.assign(n, vector<bool>(n, false));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '^') {
                begX = j;
                begY = i;
                break;
            }
        }
    }

    maxL = 1 << 30;
    maxL = pathLenght();

    int ans1 = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(visited[i][j]) {
                ans1++;
            }
        }
    }

    int ans2 = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '.') {
                board[i][j] = '#';

                if(pathLenght() == -1)
                    ans2++;

                board[i][j] = '.';
            }
        }
    }

    cout << "Part 1 answer: " << ans1 << endl;
    cout << "Part 2 answer: " << ans2 << endl;

    return 0;
}