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
		for (int i = y; i >= 0; --i) {
			if (!isdigit(g[x][i])) break;
			marked[x][i] = 1;
		}
		for (int i = y; i < M; ++i) {
			if (!isdigit(g[x][i])) break;
			marked[x][i] = 1;
		}
	};
	auto in = [&](int x, int y) {
		return x >= 0 && y >= 0 && x < N && y < M;
	};
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (isdigit(g[i][j]) || g[i][j] == '.') continue;
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					int nx = i + dx, ny = j + dy;
					if (!in(nx, ny)) continue;
					mark(nx, ny);
				}
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		int cur = 0;
		for (int j = 0; j < M; ++j) {
			if (isdigit(g[i][j]) && marked[i][j]) cur = 10 * cur + g[i][j] - '0';
			if (!marked[i][j] || !isdigit(g[i][j])) {
				ans += cur;
				cur = 0;
			}
		}
		ans += cur;
	}
	cout << ans << '\n';
}
