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
	vector<int> loc;
	{
		getline(cin, line);
		istringstream iss(line);
		string tmp; iss >> tmp;
		int x;
		while (iss >> x) loc.push_back(x);
	}
	vector<int> nxt;
	while (getline(cin, line)) {
		istringstream iss(line);
		if (line == "") {
			for (int x : loc) {
				if (x >= 0) nxt.push_back(x);
			}
			loc = nxt;
			nxt.clear();
		}
		else if (!isdigit(line[0])) {
			continue;
		}
		else {
			int a, b, l;
			iss >> b >> a >> l;
			for (int &x : loc) {
				if (x < 0) continue;
				if (x >= a && x < a + l) {
					int diff = x - a;
					nxt.push_back(b + diff);
					x = -x;
				}
			}
		}
	}
	int ans = *min_element(loc.begin(), loc.end());
	cout << ans << '\n';
}
