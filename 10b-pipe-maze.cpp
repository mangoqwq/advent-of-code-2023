#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

using pii = pair<int, int>;
map<char, vector<pii>> mp = {
	{'|', {{-1, 0}, {1, 0}}},
	{'-', {{0, -1}, {0, 1}}},
	{'L', {{-1, 0}, {0, 1}}},
	{'J', {{-1, 0}, {0, -1}}},
	{'7', {{1, 0}, {0, -1}}},
	{'F', {{1, 0}, {0, 1}}},
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	vector<string> g;
	while (getline(cin, line)) {
		g.push_back(line);
	}
	int N = g.size();
	int M = g[0].size();
	int sx, sy; cin >> sx >> sy;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (g[i][j] == 'S') {
				sx = i, sy = j;
				g[i][j] = 'J'; // change as needed
				// g[i][j] = 'F'; // change as needed
				// g[i][j] = '7';
			}
		}
	}

	vector<vector<int>> marked(N, vector<int>(M, 0));
	int x = sx, y = sy, len = 0;
	pii from = {0, 0};
	do {
		marked[x][y] = 1;
		vector<pii> cand;
		for (auto [dx, dy] : mp[g[x][y]]) {
			cand.push_back({x + dx, y + dy});
		}
		for (auto [nx, ny] : cand) {
			if (pii{nx, ny} == from) continue;
			from = {x, y};
			tie(x, y) = tie(nx, ny);
			len++;
			break;
		}
	} while (!(x == sx && y == sy));

	vector<vector<int>> inside(N, vector<int>(M, 0));
	cout << "A" << '\n';
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (marked[i][j]) continue;
			int up = 0, down = 0, crosses = 0;
			for (int k = j-1; k >= 0; --k) {
				if (!marked[i][k]) continue;
				if (g[i][k] == 'L' || g[i][k] == 'J') up ^= 1;
				if (g[i][k] == 'F' || g[i][k] == '7') down ^= 1;
				if (g[i][k] == '|') up = down = 1;
				if (up && down)	{
					crosses++;
					up = down = 0;
				}
			}
			inside[i][j] = crosses;
			ans += crosses % 2;
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (marked[i][j]) cout << '.';
			else cout << inside[i][j];
		}
		cout << '\n';
	}

	cout << ans << '\n';
}
