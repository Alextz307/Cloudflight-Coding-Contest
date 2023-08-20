#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int main() {
    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;
    double u1 = atan2(y1, x1), u2 = atan2(y2, x2);
    int T;
    fin >> T;
    while(T--) {
        int x, y;
        fin >> x >> y;
        double u = atan2(y, x);
        if(u < min(u1, u2) || u > max(u1, u2))
            fout << x << ' ' << y << ' ';
    }
}
 
