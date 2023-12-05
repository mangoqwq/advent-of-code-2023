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
	struct Interval { int l, r; };
	vector<Interval> loc;
	{
		getline(cin, line);
		istringstream iss(line);
		string tmp; iss >> tmp;
		int l, r;
		while (iss >> l >> r) {
			loc.push_back({l, r});
		}
	}
	vector<Interval> nxt;
	while (getline(cin, line)) {
		istringstream iss(line);
		if (line == "") {
			for (auto x : loc) {
				nxt.push_back(x);
			}
			loc = nxt;
			nxt.clear();
		}
		else if (!isdigit(line[0])) {
			continue;
		}
		else {
			int a, b, length;
			iss >> b >> a >> length;
			vector<Interval> again;
			auto process = [&](int l, int r, bool in) {
				if (in) {
					int diff = l - a;
					nxt.push_back({b + diff, r-l});
				}
				else again.push_back({l, r-l});
			};
			for (auto &[l, _] : loc) {
				int r = l + _;
				if (r <= a) process(l, r, 0);
				else if (l >= a+length) process(l, r, 0);
				else if (l >= a && r <= a+length) process(l, r, 1);
				else if (l >= a) process(l, a+length, 1), process(a+length, r, 0);
				else if (r <= a+length) process(l, a, 0), process(a, r, 1);
				else process(l, a, 0), process(a, a+length, 1), process(a+length, r, 0);
			}
			loc = again;
		}
	}
	ll ans = 1e18;
	for (auto [l, len] : loc) ans = min(ans, l);
	cout << ans << '\n';
}
