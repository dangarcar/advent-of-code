#include <bits/stdc++.h>
using namespace std;

struct vec2 {
    long x, y;
};

struct mat2 {
    long a11, a12, a21, a22;
};

ostream& operator<<(ostream& os, const vec2& v) {
    os << v.x << ',' << v.y;
    return os;
}

vec2 operator*(vec2 v, long n) {
    return {v.x*n, v.y*n};
}

vec2 operator+(vec2 a, vec2 b) {
    return {a.x+b.x , a.y+b.y};
}

bool operator==(vec2 a, vec2 b) {
    return a.x == b.x && a.y == b.y;
}

long determin(mat2 m) {
    return m.a11*m.a22 - m.a12*m.a21;
}

int main(int argc, char const *argv[]) {
    string buf;
    long ans = 0;
    while(getline(cin, buf)) {
        if(buf.empty()) continue;
        vec2 u, v, w; // a*u +  b*v = w; a,b <= 100
        u.x = (buf[12] - '0')*10 + (buf[13] - '0');
        u.y = (buf[18] - '0')*10 + (buf[19] - '0');

        getline(cin, buf);

        v.x = (buf[12] - '0')*10 + (buf[13] - '0');
        v.y = (buf[18] - '0')*10 + (buf[19] - '0');

        getline(cin, buf);

        stringstream ss(string(buf.begin() + 9, buf.end()));
        ss >> w.x; 
        ss.ignore(4);
        ss >> w.y;
        w.x += 10000000000000;
        w.y += 10000000000000;

        long a, b;
        mat2 mat { 
            u.x, v.x,
            u.y, v.y
        };
        auto det = determin(mat);

        if(det != 0) {
            mat = {
                w.x, v.x,
                w.y, v.y
            };
            auto a = determin(mat) / det;

            mat = {
                u.x, w.x,
                u.y, w.y
            };

            auto b = determin(mat) / det;

            if(u*a + v*b == w) {
                ans += a*3 + b;
            }
        }
    }

    cout << ans << endl;

    return 0;
}