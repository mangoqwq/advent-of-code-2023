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
	int ans = 0;
	vector<string> g;
	while (getline(cin, line)) {
		istringstream iss(line);
		g.push_back(line);
	}
	int N = g.size();
	int M = g[0].size();
	vector<vector<int>> energy(N, vector<int>(M));
	auto in = [&](int x, int y) -> bool {
		return x >= 0 && y >= 0 && x < N && y < M;
	};

	struct Beam {
		int x, y; int dx, dy;
		bool operator<(const Beam &o) const {
			return tie(x,y,dx,dy) < tie(o.x,o.y,o.dx,o.dy);
		}
	};
	
	vector<Beam> active;
	active.push_back({0,-1,0,1});
	set<Beam> vis;
	while (!active.empty()) {
		auto [x, y, dx, dy] = active.back(); active.pop_back();
		if (vis.count(Beam{x,y,dx,dy})) continue;
		vis.insert(Beam{x,y,dx,dy});
		if (in(x, y)) energy[x][y] = 1;

		int nx = x + dx, ny = y + dy;
		if (!in(nx, ny)) continue;
		if (dx == 0 && dy == -1) { // <
			if (g[nx][ny] == '|') {
				active.push_back({nx,ny,1,0});
				active.push_back({nx,ny,-1,0});
			}
			else if (g[nx][ny] == '/') active.push_back({nx,ny,1,0});
			else if (g[nx][ny] == '\\') active.push_back({nx,ny,-1,0});
			else active.push_back({nx,ny,dx,dy});
		}
		else if (dx == 0 && dy == 1) { // >
			if (g[nx][ny] == '|') {
				active.push_back({nx,ny,1,0});
				active.push_back({nx,ny,-1,0});
			}
			else if (g[nx][ny] == '/') active.push_back({nx,ny,-1,0});
			else if (g[nx][ny] == '\\') active.push_back({nx,ny,1,0});
			else active.push_back({nx,ny,dx,dy});
		}
		else if (dx == 1 && dy == 0) { // v
			if (g[nx][ny] == '-') {
				active.push_back({nx,ny,0,-1});
				active.push_back({nx,ny,0,1});
			}
			else if (g[nx][ny] == '/') active.push_back({nx,ny,0,-1});
			else if (g[nx][ny] == '\\') active.push_back({nx,ny,0,1});
			else active.push_back({nx,ny,dx,dy});
		}
		else { // ^
			if (g[nx][ny] == '-') {
				active.push_back({nx,ny,0,-1});
				active.push_back({nx,ny,0,1});
			}
			else if (g[nx][ny] == '/') active.push_back({nx,ny,0,1});
			else if (g[nx][ny] == '\\') active.push_back({nx,ny,0,-1});
			else active.push_back({nx,ny,dx,dy});
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			ans += energy[i][j];
		}
	}
	cout << ans << '\n';
}
