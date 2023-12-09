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

	ll ans = 0;
	while (getline(cin, line)) {
		istringstream iss(line);
		vector<ll> vec;
		ll x;
		while (iss >> x) {
			vec.push_back(x);
		}
		auto predict = [&](auto self, vector<ll> v) -> ll {
			set<ll> s;
			for (ll x : v) s.insert(x);
			if (s.size() == 1) return v[0];

			vector<ll> diff;
			for (int i = 1; i < v.size(); ++i) {
				diff.push_back(v[i] - v[i-1]);
			}
			ll add = self(self, diff);
			return v.back() + add;
		};
		ans += predict(predict, vec);
	}
	cout << ans << '\n';
}
