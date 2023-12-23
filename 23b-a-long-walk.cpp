#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	vector<string> g;
	while (getline(cin, line)) {
		g.push_back(line);
	}
	int N = g.size();
	int M = g[0].size();
	using pii = pair<int, int>;
	set<pii> cand;
	for (int x = 0; x < N; ++x) {
		for (int y = 0; y < M; ++y) {
			if (g[x][y] == '#') continue;
			int sig = 0;
			for (int dir = 0; dir < 4; ++dir) {
				int nx = x + dx[dir], ny = y + dy[dir];
				if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
				if (g[nx][ny] == '#') continue;
				sig++;
			}	
			if (x == 0 && y == 1) sig = 3;
			if (x == N-1 && y == M-2) sig = 3;
			if (sig >= 3) {
				cand.insert({x, y});
			}
		}
	}
	struct Edge { int x, y; int d; };
	vector<vector<vector<Edge>>> adj(N, vector<vector<Edge>>(M));
	auto dfs = [&](auto self, int x, int y, int px, int py, int sx, int sy, int d) -> void {
		if (cand.count({x, y}) && tie(x, y) != tie(sx, sy)) {
			debug(sx, sy, x, y);
			adj[sx][sy].push_back({x, y, d});
			return;
		}
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
			if (g[nx][ny] == '#') continue;
			if (tie(nx, ny) == tie(px, py)) continue;
			self(self, nx, ny, x, y, sx, sy, d + 1);
		}
	};
	for (auto [x, y] : cand) {
		dfs(dfs, x, y, x, y, x, y, 0);
	}
	debug(cand);

	vector<vector<int>> vis(N, vector<int>(M, 0));
	int ans = 0, cur = 0;
	auto longest = [&](auto self, int x, int y) -> void {
		debug(x, y);
		if (x == N-1 && y == M-2) {
			ans = max(ans, cur);
			return;
		}
		vis[x][y] = 1;
		for (auto [nx, ny, d] : adj[x][y]) {
			if (vis[nx][ny]) continue;
			cur += d;
			self(self, nx, ny);
			cur -= d;
		}
		vis[x][y] = 0;
	};
	longest(longest, 0, 1);
	cout << ans << '\n';
}
