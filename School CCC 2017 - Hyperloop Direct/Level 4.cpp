#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
struct obstacle {
    int x1, x2, Y;
    double u1, u2;
};
 
int main() {
    int N;
    fin >> N;
    vector < obstacle > a(N);
    for(auto& x : a) {
        fin >> x.x1 >> x.x2 >> x.Y;
        x.u1 = atan2(x.Y, x.x1);
        x.u2 = atan2(x.Y, x.x2);
    }
    int T;
    fin >> T;
    while(T--) {
        int x, y;
        fin >> x >> y;
        double u = atan2(y, x);
        bool ok = true;
        for(auto x : a)
            if(!(u < min(x.u1, x.u2) || u > max(x.u1, x.u2) || (y < x.Y && x.Y > 0) || (y > x.Y && x.Y < 0)))
                ok = false;
        if(ok)
            fout << x << ' ' << y << ' ';
    }
}
 
