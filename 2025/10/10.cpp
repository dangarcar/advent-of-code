#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Test {
    vector<vector<int>> moves;
    vector<int> reqs;

    vector<vector<double>> extended;
};  

constexpr double EPS = 1e-5;

vector<vector<double>> A;
int n, m;

void print(int well) {
    for(int i=0; i<A.size(); ++i) {
        int color = 39;
        if(i < well) color = 32;
        if(i == well) color = 34;

        for(auto n: A[i]) {
            cout << format("\033[{}m{:+02.2f} ", color, n);
        }
        cout << '\n';
    }
    cout << endl;
}

bool isZero(double d) {
    return -EPS < d && d < EPS;
}


int sub(int i, vector<int>& sol, const int top) {
    if(i < 0) {
        auto a = 0;
        for(auto e: sol)
            a += e;        

        bool local=false;
        for(auto r: A) {
            double a = 0;
            for(int j=0; j<A[0].size()-1; ++j)
                a += r[j] * sol[j];

            if(abs(a - r.back()) > EPS)
                local = true;
        }

        if(local) 
            return 1e9;

        return a;
    }

    int jc = -1, lib = 0;
    for(int j=0; j<sol.size(); ++j) {
        if(isZero(A[i][j])) 
            continue;

        if(sol[j] == -1) {
            jc = j;
            lib++;
        }
    }

    int ans = 1e9;
    if(lib == 0) {
        ans = min(ans, sub(i-1, sol, top));
    } else if(lib == 1) {
        double a = 0;
        for(int j=0; j<sol.size(); ++j) {
            if(j != jc && !isZero(A[i][j])) {
                assert(sol[j] != -1);
                a += sol[j] * A[i][j];
            }
        } 

        auto b = (A[i][sol.size()] - a) / A[i][jc];
        bool integer = abs(b - (int)b) < EPS || abs(b - (int)b) > 1-EPS;
        if(integer && b > -EPS) {
            sol[jc] = round(b);

            ans = min(ans, sub(i-1, sol, top));

            sol[jc] = -1;
        }
    } else if(lib > 1) {
        for(int a=0; a<=top; ++a) {
            sol[jc] = a;

            ans = min(ans, sub(i, sol, top));

            sol[jc] = -1;
        }
    } else {
        cout << "AAAA\n";
    }

    return ans;
}



int solve(const Test& t) {
    A = t.extended;
    
    n = A.size(), m = A[0].size();
    for(int k=0; k<n; ++k) {
        sort(A.begin()+k, A.end(), [k](auto& a, auto& b) { return abs(a[k]) > abs(b[k]); });
    
        for(int i=k+1; i<n; ++i) {
            if(A[i][k] == 0) continue;

            auto c = A[i][k] / A[k][k];
            for(int j=k; j<m; ++j)
                A[i][j] -= c*A[k][j];
        }
    }
    
    //print(-1);

    vector<int> sol(t.moves.size(), -1);
    int ans = sub(n-1, sol, *max_element(t.reqs.begin(), t.reqs.end()));

    return ans;
}

signed main() {
    auto t = chrono::system_clock::now();

    string buf;    
    vector<Test> tests;
    while(getline(cin, buf)) {
        istringstream iss(buf);
        string s;
        iss >> s;
        Test t;

        while(iss >> s, s[0] != '{'){
            vector<int> v;
            for(int i=1; i<s.size(); i+=2)
                v.push_back(s[i] - '0');
            t.moves.push_back(v);
        }

        iss = istringstream(string(s.begin()+1, s.end()-1));
        char ch;
        int a;
        while(iss >> a) {
            t.reqs.push_back(a);
            iss >> ch;
        }


        t.extended.assign(t.reqs.size(), vector<double>(t.moves.size()+1, 0));
        for(int j=0; j<t.moves.size(); ++j) {
            for(auto i: t.moves[j])
                t.extended[i][j] = 1;
        }

        for(int i=0; i<t.reqs.size(); ++i) {
            t.extended[i].back() = t.reqs[i];
        }


        tests.push_back(t);
    }

    int ans = 0;
    for(int i=0; i<tests.size(); ++i) {
        int a = solve(tests[i]);

        if(a == 1e9 || a < 0) {
            cout << (i+1) << endl;
        }
        ans += a;
    }

    cout << "Part 2 answer: " << ans << '\n';
    cout << chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - t) << '\n'; 

    return 0;
}