#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	ll ans = 0;
	while (getline(cin, line)) {
		istringstream iss(line);
		string s; iss >> s;
		vector<int> grp;
		int x; 
		while (iss >> x) {
			grp.push_back(x);
			char c;
			iss >> c;
		}
		int N = s.size();
		int M = grp.size();
		for (int it = 0; it < 4; ++it) {
			for (int i = 0; i < M; ++i) {
				grp.push_back(grp[i]);
			}
			s += "?" + s.substr(0, N);
		}
		s += '.';
		N = s.size();
		M = grp.size();

		vector<vector<ll>> dp(N+1, vector<ll>(M+1, 0));
		dp[0][0] = 1;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (grp[j] + i + 1 > N) continue;
				bool ok = s[grp[j] + i] != '#';
				for (int k = 0; k < grp[j]; ++k) {
					ok &= s[k + i] != '.';
				}
				if (ok) dp[i+grp[j]+1][j+1] += dp[i][j];
			}
			if (s[i] != '#') {
				for (int j = 0; j <= M; ++j) {
					dp[i+1][j] += dp[i][j];
				}
			}
		}
		ans += dp[N][M];
	}
	cout << ans << '\n';
}
