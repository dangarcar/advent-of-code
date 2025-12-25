#include "../../AOC.h"




struct Point { int x, y; };
vector<string> board;
int n, m;
int incI[] = {0, 1, 0, -1};
int incJ[] = {1, 0, -1, 0};

void floodFill(int i, int j) {
    board[i][j] = 'O';

    for(int k=0; k<4; ++k) {
        int ni = i + incI[k], nj = j + incJ[k];
        if(0 <= ni && ni < n
        && 0 <= nj && nj < m
        && board[ni][nj] == '.')
            floodFill(ni, nj); 
    }
}

signed main() {
    AoCTimer timer;

    string buf;
    vector<Point> v;
    while(getline(cin, buf)) {
        istringstream iss(buf);
        int a, b;
        char ch;
        iss >> a >> ch >> b;

        v.push_back({a, b});
    }


    vector<int> sx, sy;
    sx.push_back(0); sy.push_back(0);
    for(int i=0; i<v.size(); ++i) {
        sx.push_back(v[i].x);
        sy.push_back(v[i].y);
    }
    
    unordered_set<int> usx, usy;
    for(auto x: sx) 
        usx.insert(x);
    sx.assign(usx.begin(), usx.end());
    sort(sx.begin(), sx.end());

    for(auto y: sy) 
        usy.insert(y);
    sy.assign(usy.begin(), usy.end());
    sort(sy.begin(), sy.end());
    n = sy.size(), m = sx.size();
    

    board.assign(n, string(m, '.'));
    for(auto [x, y]: v) {
        auto i = lower_bound(sy.begin(), sy.end(), y) - sy.begin();
        auto j = lower_bound(sx.begin(), sx.end(), x) - sx.begin();
        board[i][j] = '#';
    }


    bool inX=false;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(board[i][j] == '#')
                inX = !inX;
            else if(inX)
                board[i][j] = 'H';
        }
    }

    bool inY=false;
    for(int j=0; j<m; ++j) {
        for(int i=0; i<n; ++i) {
            if(board[i][j] == '#')
                inY = !inY;
            else if(inY)
                board[i][j] = 'V';
        }
    }

    floodFill(n/3, m/2);


    int ans = 0;
    for(int ii=0; ii<v.size(); ++ii) {
        for(int jj=ii+1; jj<v.size(); ++jj) {
            int x11 = min(v[ii].x, v[jj].x), x22 = max(v[ii].x, v[jj].x);
            int y11 = min(v[ii].y, v[jj].y), y22 = max(v[ii].y, v[jj].y);
            
            auto x1 = lower_bound(sx.begin(), sx.end(), x11) - sx.begin();
            auto x2 = lower_bound(sx.begin(), sx.end(), x22) - sx.begin();
            auto y1 = lower_bound(sy.begin(), sy.end(), y11) - sy.begin();
            auto y2 = lower_bound(sy.begin(), sy.end(), y22) - sy.begin();

            bool holes = false;
            for(int i=y1; i<=y2; ++i)
                for(int j=x1; j<=x2; ++j)
                    if(board[i][j] == '.') {
                        holes = true;
                        break;
                    }
            
            int ar = (x22-x11+1) * (y22-y11+1);
            if(holes == false && ans < ar)
                ans = ar;
        }
    }


    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}