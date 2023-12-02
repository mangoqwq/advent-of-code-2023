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
	int ans = 0;
	while (getline(cin, line)) {
		istringstream iss(line);
		string c; int id, cnt;
		iss >> c >> id;
		iss >> c;

		map<string, int> cnts;
		map<string, int> mx;
		while (iss >> cnt >> c) {
			bool score = 0;
			if (c.back() != ',') score = 1;
			if (c.back() == ',' || c.back() == ';') c.pop_back();
			cnts[c] += cnt;
			if (score) {
				mx["red"] = max(mx["red"], cnts["red"]);
				mx["green"] = max(mx["green"], cnts["green"]);
				mx["blue"] = max(mx["blue"], cnts["blue"]);
				cnts.clear();
			}
		}
		ans += mx["red"] * mx["blue"] * mx["green"];
	}
	cout << ans << '\n';
}
