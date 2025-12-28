#include "../../AOC.h"


int incI[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int incJ[] = {-1, 0, 1, -1, 1, -1, 0, 1};

signed main(signed argc, char* argv[]) {    
    AoCTimer timer(argc, argv);

    vector<string> board;
    string s;
    while(getline(cin, s)) {
        if(!s.empty())
            board.push_back(s);
    }

    int n = board.size(), m = board[0].size();

    int ans = 0, nans = -1;
    while(nans != 0) {
        nans = 0;
    
        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                if(board[i][j] != '@')
                    continue;
                int e = 0;
                for(int k=0; k<8; ++k) {
                    int ni = i + incI[k], nj = j + incJ[k];
                    if(0 <= ni && ni < n
                    && 0 <= nj && nj < m
                    && board[ni][nj] == '@')
                        e++;
                }

                if(e < 4) {
                    nans++;
                    board[i][j] = '.';
                }
            }
        }

        ans += nans;
    }
    
    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}