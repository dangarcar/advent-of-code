#include "../../AOC.h"

int findXmas(const string& s) {
    int ans = 0;

    auto pos = s.find("XMAS", 0);
    while(pos != string::npos) {
        ans++;
        pos = s.find("XMAS", pos+1);
    }

    pos = s.find("SAMX", 0);
    while(pos != string::npos) {
        ans++;
        pos = s.find("SAMX", pos+1);
    }

    return ans;
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string buf;
    vector<string> board, boardTransposed, boardD1, boardD2;
    while(getline(cin, buf)) {
        if(!buf.empty())
            board.push_back(buf);
    }

    int n = board.size();

    boardTransposed.assign(n, string(n, ' '));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            boardTransposed[j][i] = board[i][j];
        }
    }

    boardD1.assign(2*n - 1, "");
    boardD2.assign(2*n - 1, "");
    for(int k=0; k<(2*n-1); ++k) {
        for(int i=k, j=0; j<n && i>=0; --i, ++j) {
            if(i < n && j < n)
                boardD1[k].push_back(board[i][j]);
        }
        for(int i=k, j=n-1; j>=0 && i>=0; --i, --j) {
            if(i < n && j < n)
                boardD2[k].push_back(board[i][j]);
        }
    }

    int ans = 0;
    for(auto& s: board)
        ans += findXmas(s);
    for(auto& s: boardTransposed)
        ans += findXmas(s);
    for(auto& s: boardD1)
        ans += findXmas(s);
    for(auto& s: boardD2)
        ans += findXmas(s);

    cout << ans << endl;

    return 0;
}