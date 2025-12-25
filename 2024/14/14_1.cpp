#include "../../AOC.h"

struct vec2 {
    int x, y;
};

ostream& operator<<(ostream& os, const vec2& v) {
    os << v.x << ',' << v.y;
    return os;
}

int ny = 103, nx = 101;

signed main() {
    AoCTimer timer;
    
    string buf;
    vector<vec2> pos;
    vector<vec2> vel;
    while(getline(cin, buf)) {
        if(buf.empty()) continue;

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

    for(int t=0; t<100; ++t) {        
        for(int i=0; i<pos.size(); ++i) {
            pos[i].x = (pos[i].x + vel[i].x + 2*nx) % nx;
            pos[i].y = (pos[i].y + vel[i].y + 2*ny) % ny;
        }
    }

    int a = 0, b = 0, c = 0, d = 0;
    for(auto p: pos) {
        if(p.x < nx/2) {
            if(p.y < ny/2)
                a++;
            if(p.y > ny/2)
                b++;
        }
        if(p.x > nx/2) {
            if(p.y < ny/2)
                c++;
            if(p.y > ny/2)
                d++;
        }
    }

    int ans = a * b * c * d;
    cout << ans << endl;

    return 0;
}