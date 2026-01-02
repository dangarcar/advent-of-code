#include "../../AOC.h"

#define SECRETS 2000

int op(int a) {
    a = (a xor (a * 64)) % 16777216;
    a = (a xor (a / 32)) % 16777216;
    a = (a xor (a * 2048)) % 16777216;

    return a;
}

constexpr int hashKey(int a, int b, int c, int d) {
    return ((a+10) << 15) | ((b+10) << 10) | ((c+10) << 5) | (d+10);
}

constexpr int MAX_HASH = hashKey(9, 9, 9, 9) + 1;
array<int, MAX_HASH> arr;
bitset<MAX_HASH> b;

vector<vector<int>> seq;
vector<vector<int>> diff;

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    int a;
    while(cin >> a) {
        vector<int> d(SECRETS), s(SECRETS + 1);
        s[0] = a;
        for(int i=0; i<SECRETS; ++i) {
            s[i+1] = op(s[i]);
            d[i] = (s[i+1]%10) - (s[i]%10);
        }

        seq.push_back(s);
        diff.push_back(d);
    }


    for(int i=0; i<seq.size(); ++i) {
        b.reset();
        for(int j=4; j<=SECRETS; ++j) {
            int k = hashKey(diff[i][j-4], diff[i][j-3], diff[i][j-2], diff[i][j-1] );
            if(!b[k]) {
                b[k] = true;
                arr[k] += seq[i][j] % 10;
            }
        }
    }

    int ans = 0;
    for(int i=0; i<MAX_HASH; ++i) {
        ans = max(ans, arr[i]);
    }
    cout << "Part 2 answer: "  << ans << endl;

    return 0;
}