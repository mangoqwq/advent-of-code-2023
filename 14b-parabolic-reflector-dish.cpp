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
	auto rot = [&](int dx, int dy) {
		for (int i = (dx == 1 ? N-1 : 0); (dx == 1 ? (i >= 0) : (i < N)); i += (dx == 1 ? -1 : 1)) {
			for (int j = (dy == 1 ? M-1 : 0); (dy == 1 ? (j >= 0) : (j < N)); j += (dy == 1 ? -1 : 1)) {
				if (g[i][j] == 'O') {
					int x = i, y = j;
					while (true) {
						int nx = x + dx, ny = y + dy;
						if (!(nx >= 0 && nx < N && ny >= 0 && ny < M)) break;
						if (g[nx][ny] == '.') {
							g[x][y] = '.';
							g[nx][ny] = 'O';
						}
						else break;
						tie(x,y) = tie(nx,ny);
					}
				}
			}
		}
	};
	map<vector<string>, int> seen;
	vector<string> lst;
	int left = 1000000000;
	int it = 0;
	while (left) {
		rot(-1, 0);
		rot(0, -1);
		rot(1, 0);
		rot(0, 1);
		it++;
		left--;
		if (seen.count(g)) {
			int skip = it - seen[g];
			left %= skip;
		}
		seen[g] = it;
	}
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (g[i][j] == 'O') {
				ans += N - i;
			}
		}
	}
	cout << ans << '\n';
}
