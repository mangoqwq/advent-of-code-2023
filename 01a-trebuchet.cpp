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
		vector<int> v;
		for (char c : line) {
			if (isdigit(c)) v.push_back(c - '0');
		}
		ans += (v.front())*10 + (v.back());
	}
	cout << ans << '\n';
}
