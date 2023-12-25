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
	map<string, vector<string>> sadj;
	while (getline(cin, line)) {
		istringstream iss(line);
		string v; iss >> v;
		v.pop_back();
		string to;
		while (iss >> to) {
			sadj[v].push_back(to);
			sadj[to].push_back(v);
		}
	}
	map<string, int> id;
	int N = 0;
	for (auto [s, to] : sadj) {
		id[s] = N++;
	}
	vector<vector<int>> adj(N);
	vector<pair<int, int>> edges;
	for (auto [s, tos] : sadj) {
		for (auto to : tos) {
			adj[id[s]].push_back(id[to]);
			if (id[s] < id[to]) {
				edges.push_back(pair<int, int>{id[s], id[to]});
			}
		}
	}

	using pii = pair<int, int>;
	auto eq = [&](pii a, pii b) {
		return (a.first == b.first && a.second == b.second) || (a.first == b.second && a.second == b.first);
	};
	auto test = [&](pii ban1, pii ban2) -> ll {
		vector<pii> bridge;
		vector<int> vis(N);
		vector<int> tin(N), low(N), sz(N);
		int T = 0;
		auto dfs = [&](auto self, int v, int p) -> void {
			vis[v] = 1;
			tin[v] = low[v] = T++;
			sz[v] = 1;
			for (int to : adj[v]) {
				if (to == p) continue;
				if (eq({v, to}, ban1) || eq({v, to}, ban2)) continue;
				if (vis[to]) {
					low[v] = min(low[v], tin[to]);
				}
				else {
					self(self, to, v);
					sz[v] += sz[to];
					low[v] = min(low[v], low[to]);
					if (low[to] > tin[v]) {
						bridge.push_back({v, to});
					}
				}
			}
		};
		dfs(dfs, 0, 0);

		if (bridge.empty()) return -1;
		ll smz = min(sz[bridge[0].first], sz[bridge[0].second]);
		debug(smz, N - smz);
		return smz * (N - smz);
	};

	for (int i = 0; i < edges.size(); ++i) {
		debug(edges[i]);
		for (int j = i+1; j < edges.size(); ++j) {
			auto res = test(edges[i], edges[j]);
			if (res != -1) {
				cout << res << '\n';
			}
		}
	}
}
