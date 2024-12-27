#include <bits/stdc++.h>
using namespace std;

#define IDX(i, j) (i*2*n + j)

string board, newBoard;
vector<vector<bool>> visited;

int incI[] = {0, 0, 1, -1};
int incJ[] = {1, -1, 0, 0};

int x, y, n;

bool canMove(int i, int j, int k) {
    if(visited[i][j])
        return true;
    visited[i][j] = true;

    int ni = i + incI[k], nj = j + incJ[k];
    if(board[IDX(ni, nj)] == '.')
        return true;
    if(board[IDX(ni, nj)] == '#')
        return false;
    else {
        if(board[IDX(ni, nj)] == '[') {
            return canMove(ni, nj, k) && canMove(ni, nj + 1, k);
        }
        if(board[IDX(ni, nj)] == ']') {
            return canMove(ni, nj - 1, k) && canMove(ni, nj, k);
        }
    }

    //Can't reach here
    return true;
};

int main(int argc, char const *argv[]) {
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty())
            break;
        
        board += buf;
        n = buf.size();
    }

    string s;
    for(auto c: board) {
        switch(c) {
            case '.': s += ".."; break;
            case '@': s += "@."; break;
            case 'O': s += "[]"; break;
            case '#': s += "##"; break;
        }
    }
    board = std::move(s);

    newBoard = string(n*2*n, ' ');
    vector<int> moves;
    while(getline(cin, buf)) {
        for(auto c: buf) {
            switch (c) {
                case '>': moves.push_back(0);
                break;
                case '<': moves.push_back(1);
                break;
                case 'v': moves.push_back(2);
                break;
                case '^': moves.push_back(3);
                break;
            }
        }
    }

    for(int i=0; i<n; ++i) {
        for(int j=0; j<2*n; ++j) {
            if(board[IDX(i, j)] == '@') {
                x = j;
                y = i;
            }
        }
    }

    for(auto k: moves) {
        visited.assign(n, vector<bool>(2*n, false));
        if(canMove(y, x, k)) {
            memset(newBoard.data(), ' ', n*2*n);
            x += incJ[k];
            y += incI[k];
            
            for(int i=0; i<n; ++i) {
                for(int j=0; j<2*n; ++j) {
                    int ni = i + incI[k], nj = j + incJ[k];
                    if(0 <= ni && ni < n && 0 <= nj && nj < 2*n) {
                        if(visited[i][j])
                            newBoard[IDX(ni, nj)] = board[IDX(i, j)];
                        else if(visited[ni][nj])
                            newBoard[IDX(ni, nj)] = '.';
                    }
                }
            }
            
            for(int i=0; i<n; ++i) {
                for(int j=0; j<2*n; ++j) {
                    if(newBoard[IDX(i, j)] == ' ')
                        newBoard[IDX(i, j)] = board[IDX(i, j)];
                }
            }

            swap(board, newBoard);
        }
    }

    /*for(int i=0; i<n; ++i) {
        for(int j=0; j<2*n; ++j) {
            cout << board[IDX(i, j)];
        }
        cout << '\n';
    }
    cout << endl;*/

    int ans = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<2*n; ++j) {
            if(board[IDX(i, j)] == '[')
                ans += 100*i + j;
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}