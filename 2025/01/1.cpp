#include <bits/stdc++.h>
using namespace std;

//TODO: im very ashamed of this shit

int main() {
    int dial = 50, ans = 0;
    char c;
    while(cin >> c) {
        int inc; cin >> inc;
        cin.ignore();
        int s;
        if(c == 'L')
            s = -1;
        else
            s = 1;

        while(inc > 0) {
            dial += s;
            inc--;

            if(dial == 100)
                dial = 0;
            if(dial < 0)
                dial = 100 + dial;

            if(dial == 0) ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}