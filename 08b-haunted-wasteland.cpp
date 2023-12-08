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
	string dir;
	{
		getline(cin, dir);
	}
	int M = dir.size();
	debug(M);
	getline(cin, line);

	map<string, pair<string, string>> adj;
	while (getline(cin, line)) {
		istringstream iss(line);
		string rt, eq, ch1, ch2;
		iss >> rt >> eq >> ch1 >> ch2;
		ch1 = ch1.substr(1, 3);
		ch2 = ch2.substr(0, 3);
		adj[rt] = {ch1, ch2};
	}

	struct Pattern {
		int len, period;
		set<int> times;
	};
	auto solve = [&](string v) -> Pattern {
		map<pair<string, int>, int> vis;
		vis[{v,0}] = 0;
		int cnt = 0, period = -1;
		set<int> times;
		while (true) {
			char c = dir[cnt % M];
			if (c == 'L') v = adj[v].first;
			else v = adj[v].second;
			cnt++;
			if (v.back() == 'Z') times.insert(cnt);
			pair<string, int> key = {v, cnt%M};
			if (vis.count(key)) {
				period = cnt - vis[key];
				return {cnt, period, times};
			}
			vis[key] = cnt;
		}
	};
	vector<string> rts;
	for (auto [s, _] : adj) {
		if (s.back() == 'A') rts.push_back(s);
	}
	vector<Pattern> patterns;
	map<ll, int> cnts;
	ll ans = 1;
	for (auto v : rts) {
		auto [len, period, times] = solve(v);
		debug(len, period, times);
		patterns.push_back({len, period, times});

		int x = *times.begin();
		ans = lcm(ans, x);
	}
	cout << ans << '\n';
}
