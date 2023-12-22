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
	int ans = 0;
	while (getline(cin, line)) {
		if (line.empty()) workflows = 0;
		else if (workflows) {
			auto tokens = split(line);
			string v = tokens[0];
			for (int i = 1; i < tokens.size(); ++i) {
				auto it = tokens[i].find(':');
				if (it == tokens[i].npos) {
					flows[v].tests.push_back({{'?', '!', 0}, tokens[i]});
				}
				else {
					string to = tokens[i].substr(it+1);
					char c = tokens[i][0];
					char cmp = tokens[i][1];
					int val = stoi(tokens[i].substr(2, it-2));
					debug(c, cmp, val);
					flows[v].tests.push_back({{c, cmp, val}, to});
				}
			}
		}
		else {
			debug(flows["in"].nxt(Part{}));
			auto tokens = split(line);
			Part p;
			for (int i = 0; i < tokens.size(); ++i) {
				char c = tokens[i][0];
				int val = stoi(tokens[i].substr(2));
				p.mp[c] = val;
			}
			string state = "in";
			while (state != "R" && state != "A") {
				debug(state);
				state = flows[state].nxt(p);
			}
			int cur = 0;
			if (state == "A") {
				for (auto [_, val] : p.mp) {
					cur += val;
				}
			}
			ans += cur;
		}
	}
	cout << ans << '\n';
}
