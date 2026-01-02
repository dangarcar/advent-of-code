#include <bits/stdc++.h>
using namespace std;
#define int long long


class AoCTimer {
public:
    __attribute__((no_profile_instrument_function, cold, noinline))
    AoCTimer(signed argc, char* argv[]) {
#ifdef OUT_FILE
        assert(argc == 2);
        this->name = argv[1];
        buf = cout.rdbuf(oss.rdbuf());
#endif

        start = chrono::system_clock::now();
    }
    

    __attribute__((no_profile_instrument_function, cold, noinline))
    ~AoCTimer() {
        auto end = chrono::system_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();

#ifdef OUT_FILE
        cout.rdbuf(buf);
        string s = oss.str();
        replace(s.begin(), s.end(), '\n', '\t');

        auto file = fopen(this->name, "a");
        fprintf(file, "%02d;%d;%ld;%s\n", DAY, YEAR, time, s.c_str());
        fclose(file);

#else
        cout << time << "us" << endl;
#endif
    }


private:
    chrono::system_clock::time_point start;

#ifdef OUT_FILE
    const char* name;
    ostringstream oss;
    streambuf* buf;
#endif

};
