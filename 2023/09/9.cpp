#include "../../AOC.h"

vector<int> getDerivative(const vector<int>& v){
    vector<int> dv(v.size()-1);
    for(int i=0; i<dv.size(); ++i) {
        dv[i] = v[i+1] - v[i];
    }

    return dv;
}

int next(vector<int> seq) {
    if(accumulate(seq.begin(), seq.end(), 0L) == 0L)
        return 0L;

    auto dv = getDerivative(seq);    
    return *seq.rbegin() + next(dv);
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string str;
    int ans = 0;

    while(getline(cin, str)) {
        istringstream iss(str);
        vector<int> v;

        int a;
        while(iss >> a)
            v.push_back(a);

        reverse(v.begin(), v.end());

        /*for(auto e: v)
            cout << e << ' ';
        cout << next(v) << '\n';*/
        ans += next(v);
    }
    
    cout << "Part 2 answer: " << ans << '\n';
    
    return 0;
}
