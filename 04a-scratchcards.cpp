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
		string a, b; iss >> a >> b;
		string s;
		set<int> seen;
		int num = 0;
		bool mine = 0;
		while (iss >> s) {
			if (s == "|") {
				mine = 1;
			}
			else {
				int x = stoi(s);
				if (mine) {
					num += seen.count(x);
				}
				else seen.insert(x);
			}
		}
		if (num) ans += (1 << (num-1));
	}
	cout << ans << '\n';

}
