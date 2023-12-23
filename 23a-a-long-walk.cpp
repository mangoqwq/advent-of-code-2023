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
	int sx = 0, sy = 1;
	int N = g.size();
	int M = g[0].size();
	// vector<vector<int>> vis(N, vector<int>(M, 0));
	int ans = 0, cur = 0;
	auto dfs = [&](auto self, int x, int y, int px, int py) -> void {
		debug(x, y);
		ans = max(ans, cur);
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
			if (g[nx][ny] == '#') continue;
			if (g[x][y] == '^' && dir != 0) continue;
			if (g[x][y] == '>' && dir != 1) continue;
			if (g[x][y] == 'v' && dir != 2) continue;
			if (g[x][y] == '<' && dir != 3) continue;
			if (tie(nx, ny) == tie(px, py)) continue;
			cur++;
			self(self, nx, ny, x, y);
			cur--;
		}
	};
	dfs(dfs, sx, sy, 0, 0);
	cout << ans << '\n';
}
