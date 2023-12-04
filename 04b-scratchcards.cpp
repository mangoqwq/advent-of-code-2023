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
	int id = 0;
	vector<ll> cnt(500, 1);
	while (getline(cin, line)) {
		id++;
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
		if (num) {
			for (int i = id + 1; i <= id + num; ++i) {
				cnt[i] += cnt[id];
			}
		}
	}
	ll ans = accumulate(cnt.begin()+1, cnt.begin()+id+1, 0LL);
	cout << ans << '\n';

}
