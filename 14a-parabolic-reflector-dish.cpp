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
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (g[i][j] == 'O') {
				for (int k = i-1; k >= 0; --k) {
					if (g[k][j] == '.') {
						g[k+1][j] = '.';
						g[k][j] = 'O';
					}
					else break;
				}
			}
		}
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
