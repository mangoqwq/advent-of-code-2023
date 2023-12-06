#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

vector<ll> T = {48938466};
vector<ll> D = {261119210191063};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	ll ans = 1;
	for (ll i = 0; i < T.size(); ++i) {
		ll cur = 0;
		for (ll charge = 0; charge <= T[i] ; ++charge) {
			ll went = charge * (T[i] - charge);
			if (went > D[i]) cur++;
		}
		ans *= cur;
	}

	cout << ans << '\n';
}
