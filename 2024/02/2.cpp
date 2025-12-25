#include "../../AOC.h"

bool checkFor(vector<int> a, int k) {
    vector<int> diff;

    a.erase(a.begin() + k);

    for(int i=0; i<a.size()-1; ++i)
        diff.push_back(a[i] - a[i+1]);

    bool pos = diff[0] > 0;
    for(auto e: diff) {
        if(abs(e) < 1 || abs(e) > 3 || ((e > 0) != pos))
            return false;
    }

    return true;
}

signed main() {
    AoCTimer timer;
    
    string buf;
    vector<vector<int>> nums;
    while(getline(cin, buf)) {
        stringstream ss;
        ss << buf;
        int n;
        vector<int> v;
        while(ss >> n)
            v.push_back(n);

        nums.push_back(v);
    }

    //cout << endl;

    int ans = 0;
    for(auto& n: nums) {
        for(int i=0; i<n.size(); ++i) {
            if(checkFor(n, i)) {
                ans++; 
                break;
            }
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}