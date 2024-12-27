#include <bits/stdc++.h>
using namespace std;

//WTF IS THIS???
//Honestly I looked up what the tree looked like on Reddit before coming up with this solution, because it was a very vague description

struct vec2 {
    int x, y;
};

int ny = 103, nx = 101;

vector<vec2> pos;

int sqrDst(vec2 a, vec2 b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

int totalDst(int i) {
    int res = 0;
    auto p = pos[i];
    for(auto q: pos) {
        res += sqrDst(p, q);
    }

    return res;
}

int main(int argc, char const *argv[]) {
    string buf;
    vector<vec2> vel;
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
    int ans = 0;
    int t = 1;
    while(t < nx*ny) {
        vector<string> b(ny, string(nx, '.'));
        int dst = 0;
        for(int i=0; i<pos.size(); ++i) {
            pos[i].x = (pos[i].x + vel[i].x + 2*nx) % nx;
            pos[i].y = (pos[i].y + vel[i].y + 2*ny) % ny;
            
            b[pos[i].y][pos[i].x] = 'R';
            dst += totalDst(i);
        }

        if(dst < score) {
            score = dst;
            ans = t;
        }

        t++;
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}