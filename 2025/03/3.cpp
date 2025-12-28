#include "../../AOC.h"

#define T 12


signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);

    string s;
    int ans = 0;
    while(getline(cin, s)) {
        int a[T], ai[T+1];
        int n = s.size();
        
        ai[0] = 0;
        for(int k=0; k<T; ++k)
            a[k] = -1;

        for(int k=0; k<T; ++k) {
            for(int i=ai[k]; i<(n-T+k+1); ++i) {
                if(s[i]-'0' > a[k]) {
                    a[k] = s[i]-'0';
                    ai[k+1] = i + 1;
                }
            }
        }

        for(int k=0; k<T; ++k) 
            ans += pow(10, T-k-1) * a[k];
    }

    cout << "Part 2 answer: " << ans << '\n';
    
    return 0;
}