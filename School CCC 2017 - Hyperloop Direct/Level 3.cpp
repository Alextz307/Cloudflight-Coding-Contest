#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int main() {
    int x1, x2, Y;
    fin >> x1 >> x2 >> Y;
    double u1 = atan2(Y, x1), u2 = atan2(Y, x2);
    int T;
    fin >> T;
    while(T--) {
        int x, y;
        fin >> x >> y;
        double u = atan2(y, x);
        if(u < min(u1, u2) || u > max(u1, u2) || (y < Y && Y > 0) || (y > Y && Y < 0))
            fout << x << ' ' << y << ' ';
    }
}
 
