#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    int ans = 0;    
    while(cin) {
        int a, b;
        char c;
        cin >> a >> c >> b >> c;

        for(int e=a; e<=b; ++e) {
            string s = to_string(e);
            int sz = s.size();

            bool valid = false;
            for(int m=1; m<sz; ++m) {
                if(sz % m != 0) continue;

                bool eq = true;
                for(int k=1; k<sz/m; ++k)
                    for(int i=0; i<m; ++i)
                        if(s[i] != s[k*m + i])
                            eq = false;

                if(eq) {
                    valid = true;
                    break;
                } 
            }

            if(valid)
                ans += e;
        }

    }

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}