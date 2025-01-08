#include <bits/stdc++.h>
using namespace std;

struct file {
    int start, size;
};

int main(int argc, char const *argv[]) {
    string buf;
    cin >> buf;

    int total = 0;
    vector<file> vf, ve;
    int id = 0;
    for(auto c: buf) {
        int n = c - '0';
        
        if(id % 2 == 0) {
            ve.push_back({total, n});
        } else {
            vf.push_back({total, n});
        }
        
        total += n;
        id++;
    }

    for(int i=ve.size()-1; i>=0; --i) {
        for(int j=0; j<vf.size(); ++j) {
            if(vf[j].size >= ve[i].size && vf[j].start < ve[i].start) {
                ve[i].start = vf[j].start;

                vf[j].start += ve[i].size;
                vf[j].size -= ve[i].size;
                break;
            }
        }
    }

    long ans = 0;
    for(long i=0; i<ve.size(); ++i) {
        for(long j=0; j<ve[i].size; ++j) {
            ans += i * (ve[i].start + j);
        }
    }

    cout << "Part 2 answer: "  << ans << endl;

    return 0;
}