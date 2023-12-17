#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

int dxs[] = {-1, 0, 1, 0};
int dys[] = {0, 1, 0, -1};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	vector<string> g;
	while (getline(cin, line)) {
		istringstream iss(line);
		g.push_back(line);
	}
	int N = g.size();
	int M = g[0].size();
	struct State {
		int x, y, dx, dy, dist, run;
		bool operator<(const State &other) const {
			return tie(dist, x, y, dx, dy, dist, run) >
						 tie(other.dist, other.x, other.y, other.dx, other.dy, other.dist, other.run);
		}
	};
	struct State2 {
		int x, y, dx, dy, run;
		bool operator<(const State2 &other) const {
			return tie(x, y, dx, dy, run) >
						 tie(other.x, other.y, other.dx, other.dy, other.run);
		}
	};
	map<State2, int> best;
	priority_queue<State> pq;
	pq.push({0, 0, -100, -100, 0, 0});
	best[{0, 0, -100, -100, 0}] = 0;
	int ans = 1e9;
	while (!pq.empty()) {
		auto [x, y, ldx, ldy, dist, run] = pq.top(); pq.pop();
		int curdist = best[State2{x,y,ldx,ldy,run}];
		if (curdist != dist) continue;
		debug(x, y, curdist, run);
		if (x == N-1 && y == M-1) {
			ans = min(ans, curdist);
			break;
		}
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dxs[dir], ny = y + dys[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			bool same = 0;
			if (dxs[dir] == ldx && dys[dir] == ldy) same = 1;
			int nrun = (same ? run + 1 : 1);
			if (!same && ldx == -dxs[dir] && ldy == -dys[dir] && ldx != -100) continue;
			if (nrun >= 4) continue;
			int ndist = curdist + g[nx][ny] - '0';
			State nxt = {nx, ny, dxs[dir], dys[dir], ndist, nrun};
			State2 nxt2 = {nx, ny, dxs[dir], dys[dir], nrun};
			if (!best.count(nxt2) || best[nxt2] > ndist) {
				best[nxt2] = ndist;
				pq.push(nxt);
			}
		}
	}
	cout << ans << '\n';
}
