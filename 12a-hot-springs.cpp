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
		string s; iss >> s;
		vector<int> grp;
		int x; 
		while (iss >> x) {
			grp.push_back(x);
			char c;
			iss >> c;
		}

		int N = s.size();
		int cur = 0;
		for (int msk = 0; msk < (1 << N); ++msk) {
			bool ok = [&]() -> bool {
				for (int j = 0; j < N; ++j) {
					if ((1 & (msk >> j)) == 0 && s[j] == '#') return 0;
					if ((1 & (msk >> j)) == 1 && s[j] == '.') return 0;
				}
				return 1;
			}();
			if (!ok) continue;
			vector<int> cgrp;
			int group = 0;
			for (int j = 0; j < N; ++j) {
				int b = (1 & (msk >> j));
				if (b) group++;
				else {
					if (group) cgrp.push_back(group);
					group = 0;
				}
			}
			if (group) cgrp.push_back(group);
			if (cgrp == grp) cur++;
		}
		debug("done");
		ans += cur;
	}
	cout << ans << '\n';
}
