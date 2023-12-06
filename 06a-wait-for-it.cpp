#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

vector<int> T = {48  ,   93   ,  84  ,   66};
vector<int> D = {261  , 1192 ,  1019  , 1063};

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	ll ans = 1;
	for (int i = 0; i < T.size(); ++i) {
		int cur = 0;
		for (int charge = 0; charge <= T[i] ; ++ charge) {
			int went = charge * (T[i] - charge);
			if (went > D[i]) cur++;
		}
		ans *= cur;
	}

	cout << ans << '\n';
}
