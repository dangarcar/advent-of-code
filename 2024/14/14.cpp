#include "../../AOC.h"

// Optimized version using modular arithmethic

struct vec2 {
    int x, y;
};

int ny = 103, nx = 101;

signed main() {
    AoCTimer timer;
    
    string buf;
    vector<vec2> pos, vel;
    while(getline(cin, buf)) {
        if(buf.empty()) break;

        stringstream ss;
        ss << buf;

        vec2 p, v;
        ss.ignore(2);
        ss >> p.x;
        ss.ignore();
        ss >> p.y;
        ss.ignore(3);
        ss >> v.x;
        ss.ignore();
        ss >> v.y;

        pos.push_back(p);
        vel.push_back(v);
    }

    int score = INT_MAX;
    int t = 1;
    int ansX = 0;
    vector<vec2> vx = pos, vy;
    while(t < nx) { // nx is the smaller of nx and ny
        int dst = 0;
        for(int i=0; i<vx.size(); ++i) {
            vx[i].x = (vx[i].x + vel[i].x + 2*nx) % nx;
            vx[i].y = (vx[i].y + vel[i].y + 2*ny) % ny;
        }
            
        for(auto e: vx)
            dst += abs(e.x - nx/2);

        if(dst < score) {
            score = dst;
            ansX = t;
            vy = vx;
        }

        t++;
    }

    int ans = 0;
    score = INT_MAX;
    t = ansX;
    while(t < nx*ny) {
        t += nx; // Find in the numbers ansX mod nx
        long dst = 0;
        for(int i=0; i<vy.size(); ++i) {
            vy[i].y = ((vy[i].y + vel[i].y*nx) % ny + 2*ny) % ny;
        }

        for(auto e: vy)
            dst += (e.x - nx/2)*(e.x - nx/2) + (e.y - ny/2)*(e.y - ny/2);

        if(dst < score) {
            score = dst;
            ans = t;
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}