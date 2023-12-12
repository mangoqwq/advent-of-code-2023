#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	vector<string> g;
	while (getline(cin, line)) {
		g.push_back(line);
	}
	vector<int> cnt_row(g.size());
	vector<int> cnt_col(g[0].size());
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[0].size(); ++j) {
			cnt_row[i] += g[i][j] == '#';
			cnt_col[j] += g[i][j] == '#';
		}
	}

	const int E = 1000000;
	using pii = pair<int, int>;
	vector<pii> spots;
	int x = 0, y = 0;
	for (int i = 0; i < g.size(); ++i) {
		x = 0;
		for (int j = 0; j < g[0].size(); ++j) {
			if (g[i][j] == '#') spots.push_back({x,y});
			if (cnt_col[j] == 0) x += E;
			else x++;
		}
		if (cnt_row[i] == 0) y += E;
		else y++;
	}
	int ans = 0;
	for (auto [x, y] : spots) {
		for (auto [xp, yp] : spots) {
			ans += abs(xp - x) + abs(yp - y);
		}
	}
	cout << ans/2 << '\n';
}
