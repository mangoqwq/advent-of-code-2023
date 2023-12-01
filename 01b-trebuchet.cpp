#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

map<string, int> mp = {
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9},
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	int ans = 0;
	while (getline(cin, line)) {
		vector<int> v;
		for (int i = 0; i < line.size(); ++i) {
			if (isdigit(line[i])) v.push_back(line[i] - '0');
			for (int l = 3; l <= 5; ++l) {
				string s = line.substr(i, l);
				if (mp.count(s)) v.push_back(mp[s]);
			}
		}
		ans += (v.front())*10 + (v.back());
	}
	cout << ans << '\n';
}
