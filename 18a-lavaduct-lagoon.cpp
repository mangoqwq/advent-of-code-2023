#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

map<char, pair<int, int>> mp = {
	{'R', {1, 0}},
	{'L', {-1, 0}},
	{'U', {0, 1}},
	{'D', {0, -1}}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	ll sx = 0, sy = 0;
	vector<pair<ll, ll>> pts;
	vector<char> dirs;
	pts.push_back({sx, sy});
	while (getline(cin, line)) {
		istringstream iss(line);
		char c; iss >> c;
		ll dist; iss >> dist;
		sx += mp[c].first * dist;
		sy += mp[c].second * dist;
		dirs.push_back(c);
		pts.push_back({sx, sy});
	}
	debug(sx, sy);
	ll ans = 0;
	debug(pts);
	int outside = 1; // lol guess if it's 1 or -1
	for (int i = 1; i < pts.size(); ++i) {
		if (dirs[i-1] == 'R' && dirs[i] == 'U') pts[i].first++, pts[i].second--;
		if (dirs[i-1] == 'D' && dirs[i] == 'L') pts[i].first++, pts[i].second--;
		if (dirs[i-1] == 'R' && dirs[i] == 'D') pts[i].first++;
		if (dirs[i-1] == 'U' && dirs[i] == 'L') pts[i].first++;
		if (dirs[i-1] == 'L' && dirs[i] == 'U') pts[i].second--;
		if (dirs[i-1] == 'D' && dirs[i] == 'R') pts[i].second--;
		if (i >= 2 && dirs[i] == dirs[i-2]) {
			outside = -outside;
		}
		if (outside == 1) {
			if (dirs[i-1] == 'R' && dirs[i] == 'U') pts[i].first -= outside, pts[i].second += outside;
			if (dirs[i-1] == 'D' && dirs[i] == 'L') pts[i].first -= outside, pts[i].second += outside;
			if (dirs[i-1] == 'R' && dirs[i] == 'D') pts[i].first -= outside, pts[i].second -= outside;
			if (dirs[i-1] == 'U' && dirs[i] == 'L') pts[i].first -= outside, pts[i].second -= outside;
			if (dirs[i-1] == 'U' && dirs[i] == 'R') pts[i].first += outside, pts[i].second -= outside;
			if (dirs[i-1] == 'L' && dirs[i] == 'D') pts[i].first += outside, pts[i].second -= outside;
			if (dirs[i-1] == 'D' && dirs[i] == 'R') pts[i].first += outside, pts[i].second += outside;
			if (dirs[i-1] == 'L' && dirs[i] == 'U') pts[i].first += outside, pts[i].second += outside;
		}
		ans += pts[i].first * pts[i-1].second - pts[i].second * pts[i-1].first;
	}
	debug(pts);
	cout << abs(ans)/2 << '\n';
}
