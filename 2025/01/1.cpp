#include "../../AOC.h"


signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);

    int dial = 50, ans = 0;
    char c;
    while(cin >> c) {
        int inc; cin >> inc;
        cin.ignore();

        int mod = inc % 100;
        ans += abs(inc / 100);
        
        bool zero = dial == 0;
        if(c == 'L') {
            dial -= mod;
            if(dial <= 0) 
                ans += !zero;
        } else {
            dial += mod;
            if(dial >= 100) 
                ans++;
        }
            
        dial = (dial + 100) % 100;            
    }

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}