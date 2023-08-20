#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
int32_t main() {
    int N, itr;
    cin >> N >> itr;
    int ans = 3 * N, nr = 3;
    for(int i = 1; i <= itr; ++i) {
        N /= 3;
        ans += nr * N;
        nr *= 4;
    }
    cout << ans;
}
 
