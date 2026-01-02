#include "../../AOC.h"

//This solution is the one I'm using for the performance test, but this has been made in Jan 2025, not in Dec 2023, as the other are

using bigint = __int128_t;

struct bvec3 {
    bigint x, y, z;
};

struct vec3 {
    int x, y, z;

    operator bvec3() const { 
        return {bigint(x), bigint(y), bigint(z)}; 
    }
};

ostream& operator<<(ostream& oss, vec3 v) {
    oss << v.x << ',' << v.y << ',' << v.z;
    return oss;
}

vec3 operator-(vec3 u, vec3 v) {
    return {u.x-v.x, u.y-v.y, u.z-v.z};
}

vec3 operator+(vec3 u, vec3 v) {
    return {u.x+v.x, u.y+v.y, u.z+v.z};
}

vec3 operator*(int k, vec3 u) {
    return {u.x*k, u.y*k, u.z*k};
}

vec3 operator/(vec3 u, int k) {
    return {u.x/k, u.y/k, u.z/k};
}

bvec3 cross(bvec3 u, bvec3 v) {
    bvec3 ans;
    ans.x = u.y*v.z - v.y*u.z;
    ans.y = - u.x*v.z + v.x*u.z;
    ans.z = u.x*v.y - v.x*u.y;
    return ans;
}

bigint dot(bvec3 u, bvec3 v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);

    string str;
    vector<pair<vec3, vec3>> lines;

    while(getline(cin, str)) {
        if(str.empty()) continue;
        istringstream iss(str);

        int x, y, z, dx, dy, dz;
        char ch;
        iss >> x >> ch >> y >> ch >> z >> ch >> dx >> ch >> dy >> ch >> dz;
        lines.push_back({{x, y, z}, {dx, dy, dz}});
    }

    vec3 p1 = lines[1].first - lines[0].first;
    vec3 v1 = lines[1].second - lines[0].second;
    vec3 p2 = lines[2].first - lines[0].first;
    vec3 v2 = lines[2].second - lines[0].second;

    //cout << p1 << ' ' << v1 << '\n' << p2 << ' ' << v2 << endl;

    int t1 = -dot(cross(p1, p2), v2) / dot(cross(v1, p2), v2);
    int t2 = -dot(cross(p1, p2), v1) / dot(cross(p1, v2), v1);
    //cout << t1 << ' ' << t2 << endl;

    vec3 c1 = lines[1].first + t1*lines[1].second;
    vec3 c2 = lines[2].first + t2*lines[2].second;
    vec3 v = (c2 - c1) / (t2 - t1);
    vec3 p = c1 - t1*v;

    int ans = p.x + p.y + p.z;
    //cout << p << ' ' << v << endl;;
    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}