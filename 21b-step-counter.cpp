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
	int sx, sy, blank = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (g[i][j] == 'S') sx = i, sy = j;
			if (g[i][j] != '#') blank++;
		}
	}

	using pii = pair<int, int>;
	auto bfs = [&](int stx, int sty) -> vector<vector<int>> {
		vector<vector<int>> dist(N, vector<int>(M, 1e9));
		dist[stx][sty] = 0;
		queue<pii> q;
		q.push({stx, sty});
		while (!q.empty()) {
			auto [x, y] = q.front(); q.pop();
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
		return dist;
	};

	const int S = 26501365;

	auto calc = [&](int stx, int sty, int steps, int match = 0) -> int {
		auto dist = bfs(stx, sty);
		int ans = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (dist[i][j] <= steps && (S - dist[i][j]) % 2 == match) {
					ans++;
				}
			}
		}
		return ans;
	};

	debug(blank, calc(0,0,S) + calc(0,0,S,1));

	ll ans = calc(sx, sy, S);
	ll offset = 20*(N+M);
	auto go = [&](int init, int step, int cx, int cy, bool diag) {
		debug(init, step);
		ll left = S - init;
		left -= offset;
		ll big = left / step;
		left %= step;
		left += offset;
		if (diag) {
			if (big % 2 == 1) {
				big--;
				left += step;
			}
			ll num = big * (big + 1) / 2;
			ll tot_even = (num - (big/2)) / 2;
			ll tot_odd = tot_even + (big/2);
			ans += tot_even * calc(cx, cy, S, 0);
			ans += tot_odd * calc(cx, cy, S, 1);
		}
		else {
			if (big % 2 == 1) {
				big--;
				left += step;
			}
			ans += (big / 2) * calc(cx, cy, S, 0);
			ans += (big / 2) * calc(cx, cy, S, 1);
		}
		while (left >= 0) {
			big++;
			if (diag) {
				if (big % 2 == 1) ans += calc(cx, cy, left, 0) * big;
				if (big % 2 == 0) ans += calc(cx, cy, left, 1) * big;
			}
			else {
				if (big % 2 == 1) ans += calc(cx, cy, left, 0);
				if (big % 2 == 0) ans += calc(cx, cy, left, 1);
			}
			left -= step;
		}
		debug(big);
	};
	go(sx+1, N, N-1, sy, 0); // ^
	go(N-sx, N, 0, sy, 0); // v
	go(sy+1, M, sx, 0, 0); // <
	go(M-sy, M, sx, M-1, 0); // >
	go((sx+1) + (sy+1), N, N-1, M-1, 1); // <^
	go((sx+1) + (M-sy), N, N-1, 0, 1); // ^>
	go((N-sx) + (sy+1), N, 0, M-1, 1); // <v
	go((N-sx) + (M-sy), N, 0, 0, 1); // v>
	cout << ans << '\n';
}
