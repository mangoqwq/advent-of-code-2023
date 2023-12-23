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
	int N = g.size(), M = g[0].size();
	int sx, sy;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (g[i][j] == 'S') sx = i, sy = j;
		}
	}

	using pii = pair<int, int>;
	vector<vector<int>> dist(N, vector<int>(M, 1e9));
	dist[sx][sy] = 0;
	queue<pii> q;
	q.push({sx, sy});
	while (!q.empty()) {
		auto [x, y] = q.front(); q.pop();
		debug(x, y);
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
			if (g[nx][ny] == '#') continue;
			if (dist[x][y] + 1 < dist[nx][ny]) {
				dist[nx][ny] = dist[x][y] + 1;
				q.push({nx, ny});
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (dist[i][j] <= 64 && (64 - dist[i][j]) % 2 == 0) {
				ans++;
			}
		}
	}
	cout << ans << '\n';
}
