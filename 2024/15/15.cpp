#include "../../AOC.h"

vector<string> board;
vector<vector<bool>> visited;

int incI[] = {0, 0, 1, -1};
int incJ[] = {1, -1, 0, 0};

int x, y, n;

bool canMove(int i, int j, int k) {
    if(visited[i][j])
        return true;
    visited[i][j] = true;

    int ni = i + incI[k], nj = j + incJ[k];
    if(board[ni][nj] == '.')
        return true;
    if(board[ni][nj] == '#')
        return false;
    else {
        if(board[ni][nj] == '[') {
            return canMove(ni, nj, k) && canMove(ni, nj + 1, k);
        }
        if(board[ni][nj] == ']') {
            return canMove(ni, nj - 1, k) && canMove(ni, nj, k);
        }
    }

    //Can't reach here
    return true;
};

void move(int i, int j, int k) {
    if(board[i][j] == '.' || visited[i][j])
        return;

    visited[i][j] = true;
    int ni = i + incI[k], nj = j + incJ[k];
    
    if(board[ni][nj] == '[')
        move(ni, nj + 1, k);
    if(board[ni][nj] == ']')
        move(ni, nj - 1, k);
    
    move(ni, nj, k);

    board[ni][nj] = board[i][j];
    board[i][j] = '.';
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty())
            break;
        
        board.push_back(buf);
        n = buf.size();
    }

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

    for(auto& v: board) {
        v = regex_replace(v, regex("\\."), "..");
        v = regex_replace(v, regex("\\#"), "##");
        v = regex_replace(v, regex("\\@"), "@.");
        v = regex_replace(v, regex("\\O"), "[]");
    }

    for(int i=0; i<n; ++i) {
        for(int j=0; j<2*n; ++j) {
            if(board[i][j] == '@') {
                x = j;
                y = i;
            }
        }
    }

    for(auto k: moves) {
        visited.assign(n, vector<bool>(2*n, false));
        if(canMove(y, x, k)) {
            visited.assign(n, vector<bool>(2*n, false));
            move(y, x, k);
            
            x += incJ[k];
            y += incI[k];
        }    
    }

    int ans = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<2*n; ++j) {
            if(board[i][j] == '[')
                ans += 100*i + j;
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}