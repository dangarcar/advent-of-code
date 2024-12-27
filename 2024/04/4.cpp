#include <bits/stdc++.h>
using namespace std;

int incX[4] = { 1, -1, 1, -1 };
int incY[4] = { -1,-1,1,1 };

int findXmas(const vector<string>& board, bool reverse) {
    int ans = 0;

    char up = 'M', down = 'S';
    if(reverse) swap(up, down);

    for(int y=0; y<board.size(); ++y) {
        for(int x=0; x<board[y].size(); ++x) {
            if(board[y][x] == 'A') {
                bool good = true; 
                
                for(int k=0; k<4; ++k) {
                    int i = y + incY[k], j = x + incX[k];                   
                    if(0 <= i && i < board.size()
                    && 0 <= j && j < board[i].size()) {                        
                        if(incY[k] < 0)
                            good &= board[i][j] == up;
                        else
                            good &= board[i][j] == down;
                    } else {
                        good = false;
                    }
                }

                if(good)
                    ans++;
            }
        }
    }

    return ans;
}

int main(int argc, char const *argv[]) {
    string buf;
    vector<string> board, boardTransposed;
    while(getline(cin, buf)) {
        if(!buf.empty())
            board.push_back(buf);
    }

    int n = board[0].size();

    boardTransposed.assign(n, string(n, ' '));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            boardTransposed[j][i] = board[i][j];
        }
    }

    int ans = 0;
    ans += findXmas(board, true);
    ans += findXmas(board, false);
    ans += findXmas(boardTransposed, true);
    ans += findXmas(boardTransposed, false);
    cout << "Part 2 answer: " << ans << endl;

    return 0;
}