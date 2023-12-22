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
	struct Block {
		int x1, y1, z1, x2, y2, z2;
	};
	struct Coord {
		int x, y, z; 
		bool operator<(const Coord &o) const {
			return tie(x,y,z) < tie(o.x, o.y, o.z);
		}
	};
	map<Coord, int> owner;
	vector<Block> blocks = {{0, 0, 0, 1000, 1000, 0}};
	int id = 0;
	while (getline(cin, line)) {
		istringstream iss(line);
		char _;
		int x1, y1, z1, x2, y2, z2;
		iss >> x1 >> _ >> y1 >> _ >> z1;
		iss >> _;
		iss >> x2 >> _ >> y2 >> _ >> z2;
		blocks.push_back({x1, y1, z1, x2, y2, z2});
		++id;
		for (int x = x1; x <= x2; ++x) {
			for (int y = y1; y <= y2; ++y) {
				for (int z = z1; z <= z2; ++z) {
					owner[{x,y,z}] = id;
				}
			}
		}
	}
	int N = blocks.size();
	struct Edge { int to, dist; };
	vector<vector<Edge>> adj(N);
	for (int i = 1; i < N; ++i) {
		auto [x1, y1, z1, x2, y2, z2] = blocks[i];
		for (int x = x1; x <= x2; ++x) {
			for (int y = y1; y <= y2; ++y) {
				int zb = min(z1, z2);
				for (int z = zb-1; z > 0; --z) {
					if (owner.count({x,y,z})) {
						debug(owner[{x,y,z}], i, zb - z + 1);
						adj[owner[{x,y,z}]].push_back({i, zb - z - 1});
						break;
					}
				}
			}
			adj[0].push_back({i, min(z1, z2)});
		}
	}

	auto dijkstra = [&](int ban) -> vector<int> {
		vector<int> dist(N, 1e9);
		dist[0] = 0;
		struct Item {
			int v, d;
			bool operator<(const Item &other) const {
				return d > other.d;
			}
		};
		priority_queue<Item> pq;
		pq.push({0, 0});
		while (!pq.empty()) {
			auto [v, d] = pq.top(); pq.pop();
			if (d != dist[v]) continue;
			for (auto [to, add] : adj[v]) {
				if (to == ban) continue;
				if (d + add < dist[to]) {
					dist[to] = d + add;
					pq.push({to, dist[to]});
				}
			}
		}
		return dist;
	};
	int ans = 0;
	auto base = dijkstra(-1);
	debug(base);
	for (int i = 1; i < N; ++i) {
		auto cur = dijkstra(i);
		cur[i] = base[i];
		ans += (cur == base);
	}
	cout << ans << '\n';
}
