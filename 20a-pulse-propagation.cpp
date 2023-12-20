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
	map<string, char> typ;
	map<string, vector<string>> adj;
	map<string, map<string, int>> conj;
	map<string, int> on;
	while (getline(cin, line)) {
		istringstream iss(line);
		string v; iss >> v;
		debug(v);
		if (v != "broadcaster") {
			char c = v.front();
			v = v.substr(1);
			typ[v] = c;
		}
		string arrow; iss >> arrow;
		string to;
		while (iss >> to) {
			if (to.back() == ',') to.pop_back();
			adj[v].push_back(to);
			conj[to][v] = 0;
			on[to] = 0;
		}
		on[v] = 0;
	}
	for (auto [v, to] : adj) {
		debug(v, to);
	}
	ll lo = 0, hi = 0;
	auto run = [&]() -> void {
		struct Event { string s; int pulse; };
		queue<Event> q;
		q.push({"broadcaster", 0});
		lo++;
		while (!q.empty()) {
			auto [s, pulse] = q.front(); q.pop();
			// if (pulse == 0) lo++;
			// else hi++;
			debug(s, pulse);
			for (auto to : adj[s]) {
				if (typ[to] == '%') {
					if (pulse == 0) {
						on[to] ^= 1;
						q.push({to, on[to]});
						lo++;
					}
					else hi++;
				}
				else if (typ[to] == '&') {
					conj[to][s] = pulse;
					if (pulse == 0) lo++;
					else hi++;
					bool all_high = [&]() -> bool {
						for (auto [from, val] : conj[to]) {
							if (!val) return 0;
						}
						return 1;
					}();
					if (all_high) {
						q.push({to, 0});
					}
					else q.push({to, 1});
				}
				else {
					if (pulse == 0) lo++;
					else hi++;
				}
			}
			debug(lo, hi);
		}
	};
	for (int i = 0; i < 1000; ++i) {
		run();
	}
	// run();
	cout << lo*hi << '\n';
}
