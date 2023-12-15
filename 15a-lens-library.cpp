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
		int cur = 0;
		for (char c : line) {
			if (c == ',') {
				ans += cur;
				cur = 0;
			}
			else {
				cur = (cur + c) * 17 % 256;
			}
		}
	}
	cout << ans << '\n';
}
