#include <bits/stdc++.h>
using namespace std;
#define int long long


class AoCTimer {
public:
    AoCTimer() {
#ifdef OUT_FILE
        file = fopen(OUT_FILE, "a");
#endif

        start = chrono::system_clock::now();
    }
    

    ~AoCTimer() {
        end = chrono::system_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();

#ifdef OUT_FILE
        fprintf(file, "%02d %d %ld\n", DAY, YEAR, time);
        fclose(file);
#else
        cout << time << "us" << endl;
#endif
    }


private:
    chrono::system_clock::time_point start, end;

#ifdef OUT_FILE
    FILE* file;
#endif

};
