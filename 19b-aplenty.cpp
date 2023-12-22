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
	struct Part {
		map<char, int> mp;
	};
	struct Range {
		map<char, int> lo, hi;
		ll content() {
			ll ret = 1;
			for (char c : {'x', 'm', 'a', 's'}) {
				ret *= hi[c] - lo[c] + 1;
			}
			return ret;
		}
		bool degen() {
			for (char c : {'x', 'm', 'a', 's'}) {
				if (lo[c] >= hi[c]) return 1;
			}
			return 0;
		}
	};
	struct Test {
		char c; char cmp; int val;
		bool operator()(Part p) {
			if (cmp == '!') return 1;
			if (cmp == '<') return p.mp[c] < val;
			if (cmp == '>') return p.mp[c] > val;
		}
	};
	struct Workflow {
		vector<pair<Test, string>> tests;
		string nxt(Part p) {
			debug(tests.size());
			for (auto [ok, to] : tests) {
				debug(ok(p));
				if (ok(p)) return to;
			}
			assert(0);
		}
	};
	auto split = [&](string s) -> vector<string> {
		vector<string> vec;
		string cur = "";
		for (char c : s) {
			if (c == '{' || c == '}' || c == ',') {
				if (cur != "") vec.push_back(cur), cur = "";
			}
			else cur.push_back(c);
		}
		if (cur != "") vec.push_back(cur);
		return vec;
	};

	map<string, Workflow> flows;

	bool workflows = 1;
	while (getline(cin, line)) {
		if (line.empty()) workflows = 0;
		else if (workflows) {
			auto tokens = split(line);
			string v = tokens[0];
			for (int i = 1; i < tokens.size(); ++i) {
				auto it = tokens[i].find(':');
				if (it == tokens[i].npos) {
					flows[v].tests.push_back({{'?', '!', 0}, tokens[i]});
					cout << v << " " << tokens[i] << '\n';
				}
				else {
					string to = tokens[i].substr(it+1);
					char c = tokens[i][0];
					char cmp = tokens[i][1];
					int val = stoi(tokens[i].substr(2, it-2));
					flows[v].tests.push_back({{c, cmp, val}, to});
					cout << v << " " << to << '\n';
				}
			}
		}
		else {
			map<string, vector<Range>> ranges;
			ranges["in"].push_back({
				{{'x', 1}, {'m', 1}, {'a', 1}, {'s', 1}},
				{{'x', 4000}, {'m', 4000}, {'a', 4000}, {'s', 4000}}
			});
			queue<string> q;
			map<string, int> deg;
			for (auto [v, wf] : flows) {
				for (auto [test, to] : wf.tests) {
					deg[to]++;
				}
			}
			q.push("in");
			while (!q.empty()) {
				auto v = q.front(); q.pop();
				for (Range r : ranges[v]) {
					debug(v, r.lo, r.hi);
					for (auto [test, to] : flows[v].tests) {
						Range cur = r;
						if (test.cmp == '<') {
							cur.hi[test.c] = min(test.val-1, cur.hi[test.c]);
							r.lo[test.c] = max(test.val, r.lo[test.c]);
						}
						if (test.cmp == '>') {
							cur.lo[test.c] = max(test.val+1, cur.lo[test.c]);
							r.hi[test.c] = min(test.val, r.hi[test.c]);
						}
						if (!cur.degen()) {
							ranges[to].push_back(cur);
						}
					}
				}
				for (auto [test, to] : flows[v].tests) {
					deg[to]--;
					if (deg[to] == 0) {
						q.push(to);
					}
				}
			}
			ll ans = 0;
			for (Range r : ranges["A"]) {
				ans += r.content();
				debug(r.lo, r.hi);
			}
			cout << ans << '\n';
			break;
		}
	}
}
