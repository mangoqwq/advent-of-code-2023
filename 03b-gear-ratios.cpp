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
	int N, M; N = g.size(), M = g[0].size();

	vector<vector<int>> marked(N, vector<int>(M));
	auto mark = [&](int x, int y) {
		if (g[x][y] == '.') return 1;
		vector<int> v;
		for (int i = y; i >= 0; --i) {
			if (!isdigit(g[x][i])) break;
			if (marked[x][i]) return 1;
			marked[x][i] = 1;
			v.push_back(g[x][i] - '0');
		}
		reverse(v.begin(), v.end());
		for (int i = y+1; i < M; ++i) {
			if (!isdigit(g[x][i])) break;
			if (marked[x][i]) return 1;
			marked[x][i] = 1;
			v.push_back(g[x][i] - '0');
		}
		if (v.empty()) return 1;
		int ret = 0;
		for (int x : v) ret = ret * 10 + x;
		return ret;
	};
	auto in = [&](int x, int y) {
		return x >= 0 && y >= 0 && x < N && y < M;
	};
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (g[i][j] != '*') continue;
			int cur = 1;
			int cnt = 0;
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					int nx = i + dx, ny = j + dy;
					if (!in(nx, ny)) continue;
					int ret = mark(nx, ny);
					if (ret != 1) cnt++;
					cur *= ret;
				}
			}
			if (cnt == 2) ans += cur;
		}
	}
	cout << ans << '\n';
}
