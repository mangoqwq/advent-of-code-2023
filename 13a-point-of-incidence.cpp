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
		if (line == "") {
			int N = g.size();
			int M = g[0].size();
			for (int c = 1; c < M; ++c) {
				int bad = 0;
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < c; ++j) {
						int rj = c + (c-j) - 1;
						if (rj < M) bad += g[i][j] != g[i][rj];
					}
				}
				if (bad == 0) ans += c;
			}
			for (int r = 1; r < N; ++r) {
				int bad = 0;
				for (int i = 0; i < r; ++i) {
					for (int j = 0; j < M; ++j) {
						int ri = r + (r-i) - 1;
						if (ri < N) bad += g[i][j] != g[ri][j];
					}
				}
				if (bad == 0) ans += r * 100;
			}
			g.clear();
		}
		else g.push_back(line);
	}
	cout << ans << '\n';
}
