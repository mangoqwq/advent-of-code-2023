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

		// begin
		map<string, int> cnts;
		bool ok = 1;
		while (iss >> cnt >> c) {
			bool score = 0;
			if (c.back() == ',' || c.back() == ';') c.pop_back();
			if (c.back() != ',') score = 1;
			cnts[c] += cnt;
			if (score) {
				if (cnts["red"] <= 12 && cnts["green"] <= 13 && cnts["blue"] <= 14) ok &= 1;
				else ok = 0;
				cnts.clear();
			}
		}
		if (ok) ans += id;
	}
	cout << ans << '\n';
}
